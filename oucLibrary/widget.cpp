#include "widget.h"
#include "dbdemo.h"

#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QAction>
#include <QHeaderView>

Widget::Widget(QWidget *parent) :
    QWidget(parent), choose(new QComboBox(this)), context(new QLineEdit(this)), start(new QPushButton(this)),
    log(new QPushButton(this)), showName(new QPushButton(this)),
    lot(new QPushButton(this)), logins(new Login()), showResults{(new TableWidget(this)),
    new TableWidget(),new TableWidget()},
    userWidget(new QTabWidget(this)), rootWidget(new QTabWidget(this))
{
    setMaximumSize(700,500);
    setMinimumSize(700,500);

    id = Empty;
    ope_aim = Book;

    choose->setGeometry(60, 120, 100, 30);

    context->setGeometry(200, 120, 300, 30);

    start->setGeometry(520, 120, 100, 30);
    start->setText("查询");
    connect(start, SIGNAL(clicked(bool)), this, SLOT(query()));

    createShowResult();

    log->setGeometry(630, 20, 40, 30);
    log->setText("登录");
    connect(log, SIGNAL(clicked(bool)), logins, SLOT(show()));

    showName->setGeometry(580, 20, 40, 30);
    showName->hide();

    lot->setGeometry(630, 20, 40, 30);
    lot->setText("注销");
    lot->hide();

    connect(logins, SIGNAL(login_success(QString,QString,Identify)), this, SLOT(login_success(QString,QString,Identify)));
    connect(lot, SIGNAL(clicked(bool)), this, SLOT(logout()));
    connect(userWidget,SIGNAL(currentChanged(int)),this,SLOT(chooseChange(int)));
    connect(rootWidget,SIGNAL(currentChanged(int)),this,SLOT(chooseChange(int)));
    chooseChange();
    initResult(0);
}

void Widget::createShowResult()
{
    showResults[0]->setGeometry(60, 170, 580, 300);
    showResults[0]->table->setColumnCount(6);
    for(int i=0; i<5; i++)
        showResults[0]->table->setColumnWidth(i, 90);
    QStringList header;
    header << "书名" << "ISBN号" << "作者" << "出版年份" << "出版社" << "当前状态" ;
    showResults[0]->table->setHorizontalHeaderLabels(header);
    showResults[0]->table->horizontalHeader()->setStretchLastSection(true);

    showResults[1]->setGeometry(60, 170, 580, 300);
    showResults[1]->table->setColumnCount(5);
    showResults[1]->table->setRowCount(20);
    for(int i=0; i<4; i++)
        showResults[1]->table->setColumnWidth(i, 100);
    header.clear();
    header << "姓名" << "借书名" << "ISBN号" << "借书日期" << "到期时间";
    showResults[1]->table->setHorizontalHeaderLabels(header);
    showResults[1]->table->horizontalHeader()->setStretchLastSection(true);

    showResults[2]->setGeometry(60, 170, 580, 300);
    showResults[2]->table->setColumnCount(5);
    showResults[2]->table->setRowCount(20);
    for(int i=0; i<4; i++)
        showResults[2]->table->setColumnWidth(i, 100);
    header.clear();
    header << "学号" << "姓名" << "性别" << "年龄" << "电话";
    showResults[2]->table->setHorizontalHeaderLabels(header);
    showResults[2]->table->horizontalHeader()->setStretchLastSection(true);
}

void Widget::createUserWidget()
{
    userWidget->setGeometry(60, 170, 580, 300);
    userWidget->addTab(showResults[0], QIcon(), "图书查询");
    userWidget->addTab(showResults[1], QIcon(), "借阅记录");
    userWidget->show();
}

void Widget::createRootWidget()
{
    rootWidget->setGeometry(60, 170, 580, 300);
    rootWidget->addTab(showResults[0], QIcon(), "图书查询");
    rootWidget->addTab(showResults[1], QIcon(), "借阅记录");
    rootWidget->addTab(showResults[2],QIcon(), "用户管理");
    rootWidget->show();
}

void Widget::initResult(int index)
{
    if(index == 0)
        return;//file[index] = new DbDemoFileOperate("./book/book.dat");
    else if(index == 1)
        return;//file[index] = new DbDemoFileOperate("./borrow/borrow.dat");
    else
        file[index] = new DbDemoFileOperate("./person/person.dat");
    showResults[index]->page->setMaxPage(file[index]->GetCount()/20+(file[index]->GetCount()%20!=0));
    char * ans = new char[5000];
    //ans = file[index]->PrintFile(1, 20);
    show_id[index].clear();
    for(int i=0;i<20;i++)
    {
        qDebug() << i<< endl;
        if(index == 2)
        {
            Persons * person = (Persons*)file[index]->PrintFile(i+1,1);
            if(person->GetId() == 0)
                return;
            show_id[index].push_back(person->GetId());
            showResults[2]->table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(person->Getaccount())));
            showResults[2]->table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(person->Getname())));
            if(person->Getsex() == 1)
                showResults[2]->table->setItem(i,2,new QTableWidgetItem(QString("男")));
            else showResults[2]->table->setItem(i,2,new QTableWidgetItem(QString("女")));
            showResults[2]->table->setItem(i,3,new QTableWidgetItem(QString::number(person->Getage())));
            showResults[2]->table->setItem(i,4,new QTableWidgetItem(QString::fromStdString(person->Getphone())));
            showResults[2]->table->setRowCount(i+1);
            //ans += sizeof(int)*3+133;
            qDebug() << person->Getbirth().toString("yyyy-MM-dd");
        }
    }
}

void Widget::query()
{
    delete file[ope_aim];
    file[ope_aim] = new DbDemoFileOperate((char *)"book.dat");
    file[ope_aim]->Query((char *)"c++", 3, false);
    delete result[ope_aim];
    result[ope_aim] = new DbDemoFileOperate((char *)"1.dat");
    if(id == Empty)
    {
        showResults[0]->show();
        showResults[0]->page->setMaxPage(result[ope_aim]->GetPageCount(15));
        connect(showResults[0]->page, SIGNAL(currentPageChanged(int)), this, SLOT(showResult(int)));
    }
}

void Widget::login_success(QString username, QString password, Identify id)
{
    this->username = username;
    this->password = password;
    this->id = id;
    initResult(1);
    log->hide();
    showName->setText(username);
    showName->show();
    if(id == User)
        createUserWidget();
    else
    {
        createRootWidget();
        initResult(2);
    }
    lot->show();
}

void Widget::logout()
{
    showName->hide();
    lot->hide();
    log->show();
    if(id == User)
    {
        userWidget->removeTab(1);
        userWidget->removeTab(0);
        userWidget->hide();
    }
    if(id == Root)
    {
        rootWidget->removeTab(2);
        rootWidget->removeTab(1);
        rootWidget->removeTab(0);
        rootWidget->hide();
    }
    showResults[0]->setParent(this);
    showResults[0]->setGeometry(60, 170, 580, 300);
    showResults[0]->show();
    id = Empty;
    chooseChange();
}

void Widget::showResult(int page)
{
    char * aim = result[ope_aim]->PrintFile(page, 15);
}

void Widget::chooseChange(int index)
{
    choose->clear();
    if(index == 0)
    {
        ope_aim = Book;
        choose->addItem("作者");
        choose->addItem("书名");
        choose->addItem("分类");
    }
    else if(index == 1)
    {
        ope_aim = Borrow;
        if(id == Root)
        {
            choose->addItem("姓名");
            choose->addItem("书名");
            choose->addItem("帐号");
        }
    }
    else if(index == 2)
    {
        ope_aim = Person;
        choose->addItem("姓名");
        choose->addItem("帐号");
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont font;
    font.setCapitalization(QFont::SmallCaps);//设置大小写
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);//设置间距
    font.setPixelSize(30);
    painter.setFont(font);//添加字体
    painter.drawText(QRectF(150, 40, 400, 40), Qt::AlignCenter, QString("欢迎使用图书管理系统"));
    QWidget::paintEvent(event);
}

Widget::~Widget()
{
}
