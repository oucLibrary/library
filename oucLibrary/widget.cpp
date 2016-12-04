#include "widget.h"

#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QAction>
#include <QHeaderView>

Widget::Widget(QWidget *parent) :
    QWidget(parent), choose(new QComboBox(this)), context(new QLineEdit(this)), start(new QPushButton(this)),
    log(new QPushButton(this)), showName(new QPushButton(this)),
    lot(new QPushButton(this)), logins(new Login()), showBookResult(new TableWidget(this)),
    showBorrowResult(new TableWidget()), showUserResult(new TableWidget()),
    userWidget(new QTabWidget(this)), rootWidget(new QTabWidget(this))
{
    setMaximumSize(700,500);
    setMinimumSize(700,500);

    id = Empty;
    ope_aim = Book;

    choose->setGeometry(60, 120, 100, 30);
    choose->addItem("全部");
    choose->addItem("作者");
    choose->addItem("书籍");
    choose->addItem("分类");

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
}

void Widget::createShowResult()
{
    showBookResult->setGeometry(60, 170, 580, 300);
    showBookResult->table->setColumnCount(5);
    for(int i=0; i<4; i++)
        showBookResult->table->setColumnWidth(i, 120);
    QStringList header;
    header << "书名" << "作者" << "出版年份" << "出版社" << "可借阅数量" ;
    showBookResult->table->setHorizontalHeaderLabels(header);
    showBookResult->table->horizontalHeader()->setStretchLastSection(true);

    showBorrowResult->setGeometry(60, 170, 580, 300);
    showBorrowResult->table->setColumnCount(5);
    for(int i=0; i<4; i++)
        showBorrowResult->table->setColumnWidth(i, 120);
    header.clear();
    header << "姓名" << "借书名" << "借书日期" << "到期时间" << "还书时间";
    showBorrowResult->table->setHorizontalHeaderLabels(header);
    showBorrowResult->table->horizontalHeader()->setStretchLastSection(true);

    showUserResult->setGeometry(60, 170, 580, 300);
    showUserResult->table->setColumnCount(4);
    for(int i=0; i<3; i++)
        showUserResult->table->setColumnWidth(i, 150);
    header.clear();
    header << "姓名" << "帐号" << "密码" << "电话";
    showUserResult->table->setHorizontalHeaderLabels(header);
    showUserResult->table->horizontalHeader()->setStretchLastSection(true);
}

void Widget::createUserWidget()
{
    userWidget->setGeometry(60, 170, 580, 300);
    userWidget->addTab(showBookResult, QIcon(), "图书查询");
    userWidget->addTab(showBorrowResult, QIcon(), "借阅记录");
    userWidget->show();
}

void Widget::createRootWidget()
{
    rootWidget->setGeometry(60, 170, 580, 300);
    rootWidget->addTab(showBookResult, QIcon(), "图书查询");
    rootWidget->addTab(showBorrowResult, QIcon(), "借阅记录");
    rootWidget->addTab(showUserResult,QIcon(), "用户管理");
    rootWidget->show();
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
        showBookResult->show();
        showBookResult->page->setMaxPage(result[ope_aim]->GetPageCount(15));
        connect(showBookResult->page, SIGNAL(currentPageChanged(int)), this, SLOT(showResult(int)));
    }
}

void Widget::login_success(QString username, QString password, Identify id)
{
    this->username = username;
    this->password = password;
    this->id = id;
    log->hide();
    showName->setText(username);
    showName->show();
    if(id == User)
        createUserWidget();
    else
        createRootWidget();
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
    showBookResult->setParent(this);
    showBookResult->setGeometry(60, 170, 580, 300);
    showBookResult->show();
    id = Empty;
}

void Widget::showResult(int page)
{
    char * aim = result[ope_aim]->PrintFile(page, 15);
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
