#include "widget.h"
#include "dbdemo.h"

#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QAction>
#include <QHeaderView>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent), choose(new QComboBox(this)), context(new QLineEdit(this)), start(new QPushButton(this)),
    log(new QPushButton(this)), showName(new QPushButton(this)),
    lot(new QPushButton(this)), logins(new Login()), showResults{(new TableWidget(this)),
    new TableWidget(),new TableWidget()}, userWidget(new QTabWidget(this)),
    rootWidget(new QTabWidget(this)), checkbox(new QCheckBox("根据当前结果查询", this)),
    resetButton(new QPushButton("重置搜索结果", this)),
    addCurrBook(new QPushButton("添加选中书", this)), addNewBook(new QPushButton("添加新书", this)),
    delBook(new QPushButton("删除书", this)), retBook(new QPushButton("还书", this)),
    losBook(new QPushButton("书丢失", this)), addPerson(new QPushButton("添加用户", this)),
    delPerson(new QPushButton("删除用户", this)), lendBook(new QPushButton("借书", this)),
    changeBook(new QPushButton("修改图书", this)), lendAgain(new QPushButton("续借", this))
{
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
    DbDemoFileOperate * cache2 = new DbDemoFileOperate((char *)"./books/books.dat");
    for(int i=1; i<=cache->GetCount(); i++)
    {
        cache->Getbynum(i);
        Bookcopy * copy = new Bookcopy(cache->Gettmp_sto());
        if(!cache2->Getbyid(copy->Getbookid()))
        {
            cache->Deletbyid(copy->GetId());
            i--;
        }
    }
    qDebug() << cache->GetCount();
    delete cache;
    delete cache2;
    setMaximumSize(800, 500);
    setMinimumSize(800, 500);
    createDialog();

    resetButton->setGeometry(680, 200, 80, 30);
    addCurrBook->setGeometry(680, 250, 80, 30);
    addCurrBook->hide();
    addNewBook->setGeometry(680, 300, 80, 30);
    addNewBook->hide();
    delBook->setGeometry(680, 350, 80, 30);
    delBook->hide();
    retBook->setGeometry(680, 250, 80, 30);
    retBook->hide();
    losBook->setGeometry(680, 300, 80, 30);
    losBook->hide();
    addPerson->setGeometry(680, 250, 80, 30);
    addPerson->hide();
    delPerson->setGeometry(680, 300, 80, 30);
    delPerson->hide();
    lendBook->setGeometry(680, 450, 80, 30);
    lendBook->hide();
    changeBook->setGeometry(680, 400, 80, 30);
    changeBook->hide();
    lendAgain->setGeometry(680, 250, 80, 30);
    lendAgain->hide();

    id = Empty;
    ope_aim = Book;
    memset(oks, true, sizeof(oks));

    choose->setGeometry(60, 120, 100, 30);

    context->setGeometry(200, 120, 300, 30);

    start->setGeometry(520, 120, 100, 30);
    start->setText("查询");
    connect(start, SIGNAL(clicked(bool)), this, SLOT(query()));

    createShowResult();

    log->setGeometry(710, 20, 40, 30);
    log->setText("登录");
    connect(log, SIGNAL(clicked(bool)), logins, SLOT(show()));

    showName->setGeometry(660, 20, 40, 30);
    showName->hide();

    lot->setGeometry(710, 20, 40, 30);
    lot->setText("注销");
    lot->hide();

    checkbox->setGeometry(400, 470, 200, 30);

    connect(logins, SIGNAL(login_success(QString,QString,int,Identify)), this, SLOT(login_success(QString,QString,int,Identify)));
    connect(lot, SIGNAL(clicked(bool)), this, SLOT(logout()));
    connect(userWidget,SIGNAL(currentChanged(int)),this,SLOT(chooseChange(int)));
    connect(rootWidget,SIGNAL(currentChanged(int)),this,SLOT(chooseChange(int)));
    connect(resetButton,SIGNAL(clicked(bool)),this,SLOT(initResult()));
    connect(retBook,SIGNAL(clicked(bool)),this,SLOT(returnBook()));
    connect(addPerson,SIGNAL(clicked(bool)),addUser,SLOT(exec()));
    connect(addUser,SIGNAL(submit(QList<QString>)),this,SLOT(addUsers(QList<QString>)));
    connect(delPerson,SIGNAL(clicked(bool)),this,SLOT(deleteUser()));
    connect(changeBook,SIGNAL(clicked(bool)),this,SLOT(changeBooks()));
    connect(lendBook,SIGNAL(clicked(bool)),this,SLOT(addBorrow()));
    connect(addCurrBook,SIGNAL(clicked(bool)),currBook,SLOT(exec()));
    connect(currBook,SIGNAL(submit(QList<QString>)),this,SLOT(addCurrBooks(QList<QString>)));
    connect(addNewBook,SIGNAL(clicked(bool)),newBook,SLOT(exec()));
    connect(newBook,SIGNAL(submit(QList<QString>)),this,SLOT(addNewBooks(QList<QString>)));
    connect(delBook,SIGNAL(clicked(bool)),this,SLOT(delBooks()));
    connect(lendAgain,SIGNAL(clicked(bool)),this,SLOT(lendAgain2()));
    initResult(0);
    chooseChange();
}

void Widget::createDialog()
{
    int inputNum = 8;
    vector<string> shows;
    shows.push_back("学号");
    shows.push_back("密码");
    shows.push_back("姓名");
    shows.push_back("性别");
    shows.push_back("邮箱");
    shows.push_back("电话");
    shows.push_back("年龄");
    shows.push_back("生日");
    addUser = new Dialog(inputNum,shows);
    shows.clear();
    inputNum = 1;
    shows.push_back("数目");
    currBook = new Dialog(inputNum,shows);
    inputNum = 5;
    shows.clear();
    shows.push_back("书名");
    shows.push_back("数量");
    shows.push_back("作者");
    shows.push_back("出版社");
    shows.push_back("isbn号");
    newBook = new Dialog(inputNum,shows);
}

void Widget::createShowResult()
{
    showResults[0]->setGeometry(60, 170, 580, 300);
    showResults[0]->table->setColumnCount(5);
    for(int i=0; i<5; i++)
        showResults[0]->table->setColumnWidth(i, 100);
    QStringList header;
    header << "书名" << "ISBN号" << "作者" << "出版社" << "当前状态" ;
    showResults[0]->table->setHorizontalHeaderLabels(header);
    showResults[0]->table->horizontalHeader()->setStretchLastSection(true);

    showResults[1]->setGeometry(60, 170, 580, 300);
    showResults[1]->table->setColumnCount(6);
    showResults[1]->table->setRowCount(20);
    for(int i=0; i<5; i++)
        showResults[1]->table->setColumnWidth(i, 90);
    header.clear();
    header << "姓名" << "学号" << "借书名" << "ISBN号" << "借书日期" << "到期时间";
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

    for(int i=0; i<3; i++)
    {
        showResults[i]->table->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
        showResults[i]->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        showResults[i]->table->verticalHeader()->setHidden(true);
    }
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
    if(index == -1)
        index = ope_aim;
    oks[index] = true;
    if(index == 0)
        file[index] = new DbDemoFileOperate((char *)"./books/books.dat");
    else if(index == 1)
        file[index] = new DbDemoFileOperate((char *)"./borrows/borrows.dat");
    else
        file[index] = new DbDemoFileOperate((char *)"./persons/persons.dat");
    if(index == 1 && id == User)
    {
        if(oks[index])
        {
            file[index]->Query((char *)(&num),2,(char *)"./borrows/1.dat");
            delete file[index];
            file[index] = new DbDemoFileOperate((char *)"./borrows/1.dat");
        }
        else
        {
            file[index]->Query((char *)(&num),2,(char *)"./borrows/2.dat");
            delete file[index];
            file[index] = new DbDemoFileOperate((char *)"./borrows/2.dat");
        }
        oks[index] = !oks[index];
    }
    showResult();
    connect(showResults[index]->page,SIGNAL(currentPageChanged(int)),this,SLOT(showResult(int)));
}

void Widget::query()
{
    if(!checkbox->checkState())
    {
        oks[ope_aim] = true;
        delete file[ope_aim];
        if(ope_aim == Book)
        {
            file[ope_aim] = new DbDemoFileOperate((char *)"./books/books.dat");
        }
        else if(ope_aim == Borrow)
            file[ope_aim] = new DbDemoFileOperate((char *)"./borrows/borrows.dat");
        else
            file[ope_aim] = new DbDemoFileOperate((char *)"./persons/persons.dat");
    }
    char aim[50];
    string author = context->text().toStdString();
    for(int i=0; i<50; i++)
    {
        if(i < (int)author.length())
            aim[i] = author[i];
        else aim[i] = '\0';
    }
    if(ope_aim == Book)
    {
        if(choose->currentIndex() == 0 || choose->currentIndex() == 1)
        {
            int queryline;
            if(choose->currentIndex() == 0)
                queryline = 5;
            else queryline = 2;
            if(oks[ope_aim])
            {
                file[ope_aim]->Query(aim, queryline, (char *)"./books/1.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./books/1.dat");
            }
            else
            {
                file[ope_aim]->Query(aim, queryline, (char *)"./books/2.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./books/2.dat");
            }
            oks[ope_aim] = !oks[ope_aim];
        }
        else if(choose->currentIndex() == 2)
        {
            DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./bookkinds/bookkinds.dat");
            cache->Query(aim,2,(char *)"./bookkinds/1.dat");
            delete cache;
            cache = new DbDemoFileOperate((char *)"./bookkinds/1.dat");
            if(cache->GetCount() == 0)
            {
                QMessageBox::warning(this,(char *)"查找分类错误","没有该分类");
                return;
            }
            delete cache;
            if(!Getmulti(new DbDemoFileOperate((char *)"./bookkinds/1.dat"),1,new DbDemoFileOperate((char *)"./classification/classification.dat"),3,(char *)"./classification/1.dat"))
            {
                QMessageBox::warning(this,"查找分类失败","该分类没有书");
                return;
            }
            if(oks[ope_aim])
            {
                Getmulti(new DbDemoFileOperate((char *)"./classification/1.dat"),2,file[ope_aim],1,(char *)"./books/1.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./books/1.dat");
            }
            else
            {
                Getmulti(new DbDemoFileOperate((char *)"./classification/1.dat"),2,file[ope_aim],1,(char *)"./books/2.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./books/2.dat");
            }
            oks[ope_aim] = !oks[ope_aim];
        }
    }
    else if(ope_aim == Borrow)
    {
        if(id == User)
            return;
        if(choose->currentIndex() == 0)
        {
            DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./persons/persons.dat");
            if(oks[Person])
            {
                cache->Query(aim,4,(char *)"./persons/1.dat");
                delete cache;
                cache = new DbDemoFileOperate((char *)"./persons/1.dat");
            }
            else
            {
                cache->Query(aim,4,(char *)"./persons/2.dat");
                delete cache;
                cache = new DbDemoFileOperate((char *)"./persons/2.dat");
            }
            if(cache->GetCount() == 0)
            {
                QMessageBox::warning(this,"查找借阅人错误","没有该用户");
                delete cache;
                return;
            }
            if(oks[ope_aim])
            {
                Getmulti(cache,1,file[ope_aim],2,(char *)"./borrows/1.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./borrows/1.dat");
            }
            else
            {
                Getmulti(cache,1,file[ope_aim],2,(char *)"./borrows/2.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./borrows/2.dat");
            }
            delete cache;
            oks[ope_aim] = !oks[ope_aim];
        }
        else if(choose->currentIndex() == 1)
        {
            DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./books/books.dat");
            if(oks[Book])
            {
                cache->Query(aim,2,(char *)"./books/1.dat");
                delete cache;
                cache = new DbDemoFileOperate((char *)"./books/1.dat");
            }
            else
            {
                cache->Query(aim,2,(char *)"./books/2.dat");
                delete cache;
                cache = new DbDemoFileOperate((char *)"./books/2.dat");
            }
            if(cache->GetCount() == 0)
            {
                QMessageBox::warning(this,"查找书名错误","没有该书");
                delete cache;
                return;
            }
            if(!Getmulti(cache,1,new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat"),2,(char *)"./bookcopy/1.dat"))
            {
                QMessageBox::warning(this,"查找书名错误","该图书库存为空,请尽快删除该书名记录");
                delete cache;
                return;
            }
            delete cache;
            cache = new DbDemoFileOperate((char *)"./bookcopy/1.dat");
            if(oks[ope_aim])
            {
                Getmulti(cache,1,file[ope_aim],3,(char *)"./borrows/1.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./borrows/1.dat");
            }
            else
            {
                Getmulti(cache,1,file[ope_aim],3,(char *)"./borrows/2.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./borrows/2.dat");
            }
            delete cache;
            oks[ope_aim] = !oks[ope_aim];
        }
        else if(choose->currentIndex() == 2)
        {
            DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./persons/persons.dat");
            if(oks[Person])
            {
                cache->Query(aim,2,(char *)"./persons/1.dat");
                delete cache;
                cache = new DbDemoFileOperate((char *)"./persons/1.dat");
            }
            else
            {
                cache->Query(aim,2,(char *)"./persons/2.dat");
                delete cache;
                cache = new DbDemoFileOperate((char *)"./persons/2.dat");
            }
            if(cache->GetCount() == 0)
            {
                QMessageBox::warning(this,"查找借阅人错误","没有该用户");
                delete cache;
                return;
            }
            if(oks[ope_aim])
            {
                Getmulti(cache,1,file[ope_aim],2,(char *)"./borrows/1.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./borrows/1.dat");
            }
            else
            {
                Getmulti(cache,1,file[ope_aim],2,(char *)"./borrows/2.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./borrows/2.dat");
            }
            delete cache;
            oks[ope_aim] = !oks[ope_aim];
        }
    }
    else if(ope_aim == Person)
    {
        if(choose->currentIndex() == 0 || choose->currentIndex() == 1)
        {
            int queryline;
            if(choose->currentIndex() == 0)
                queryline = 4;
            else queryline = 2;
            if(oks[ope_aim])
            {
                file[ope_aim]->Query(aim, queryline, (char *)"./persons/1.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./persons/1.dat");
            }
            else
            {
                file[ope_aim]->Query(aim, queryline, (char *)"./persons/2.dat");
                delete file[ope_aim];
                file[ope_aim] = new DbDemoFileOperate((char *)"./persons/2.dat");
            }
            oks[ope_aim] = !oks[ope_aim];
        }
    }
    showResult();
}

void Widget::login_success(QString username, QString password, int num, Identify id)
{
    this->username = username;
    this->password = password;
    this->num = num;
    this->id = id;
    initResult(1);
    log->hide();
    showName->setText(username);
    showName->show();
    if(id == User)
    {
        createUserWidget();
        changeInfor = new test(this->num);
        connect(showName,SIGNAL(clicked(bool)),changeInfor,SLOT(exec()));
    }
    else
    {
        showResults[Book]->table->setEditTriggers(QAbstractItemView::DoubleClicked);
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
    lendBook->hide();
    if(id == User)
    {
        userWidget->removeTab(1);
        userWidget->removeTab(0);
        userWidget->hide();
        lendAgain->hide();
    }
    else if(id == Root)
    {
        showResults[Book]->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        rootWidget->removeTab(2);
        rootWidget->removeTab(1);
        rootWidget->removeTab(0);
        rootWidget->hide();
        addCurrBook->hide();
        addNewBook->hide();
        delBook->hide();
        retBook->hide();
        losBook->hide();
        delPerson->hide();
        addPerson->hide();
        changeBook->hide();
    }
    showResults[0]->setParent(this);
    showResults[0]->setGeometry(60, 170, 580, 300);
    showResults[0]->show();
    id = Empty;
    chooseChange();
}

void Widget::showResult(int page)
{
    Ope_aim index = ope_aim;
    showResults[index]->page->setMaxPage(file[index]->GetCount()/20+(file[index]->GetCount()%20!=0));
    showResults[index]->page->setCurrentPage(page);
    show_id[index].clear();
    showResults[index]->table->setRowCount(0);
    for(int i=0;i<min(20, file[index]->GetCount()-20*(page-1));i++)
    {
        showResults[index]->table->setRowCount(i+1);
        if(index == 0)
        {
            Books * book = new Books(file[index]->PrintFile(i+1+20*(page-1),1));
            show_id[index].push_back(book->GetId());
            showResults[index]->table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(book->Getname())));
            showResults[index]->table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(book->Getisbn())));
            showResults[index]->table->setItem(i,2,new QTableWidgetItem(QString::fromStdString(book->Getauthor())));
            showResults[index]->table->setItem(i,3,new QTableWidgetItem(QString::fromStdString(book->Getpress())));
            showResults[index]->table->setItem(i,4,new QTableWidgetItem(QString("%1/%2").arg(book->Getleft()).arg(book->Getamount())));
        }
        else if(index == 1)
        {
            Borrows * borrow = new Borrows(file[index]->PrintFile(i+1+20*(page-1),1));
            show_id[index].push_back(borrow->GetId());
            showResults[index]->table->setItem(i,4,new QTableWidgetItem(borrow->GetfirstTime().toString("yyyy-MM-dd")));
            if(!borrow->GetifReturn())
                showResults[index]->table->setItem(i,5,new QTableWidgetItem(borrow->GetlastTime().toString("yyyy-MM-dd")));
            else
                showResults[index]->table->setItem(i,5,new QTableWidgetItem(borrow->GetlastTime().toString("yyyy-MM-dd")+QString("(已归还)")));
            DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
            if(!cache->Getbyid(borrow->GetbookId()))
            {
                delete cache;
                QMessageBox * mess = new QMessageBox();
                mess->setText("数据出错");
                mess->exec();
                exit(0);
            }
            Bookcopy * bookcopy = new Bookcopy(cache->Gettmp_sto());
            delete cache;
            cache = new DbDemoFileOperate((char *)"./books/books.dat");
            if(!cache->Getbyid(bookcopy->Getbookid()))
            {
                delete cache;
                QMessageBox * mess = new QMessageBox();
                mess->setText("数据出错");
                mess->exec();
                exit(0);
            }
            Books * book = new Books(cache->Gettmp_sto());
            showResults[index]->table->setItem(i,2,new QTableWidgetItem(QString::fromStdString(book->Getname())));
            showResults[index]->table->setItem(i,3,new QTableWidgetItem(QString::fromStdString(book->Getisbn())));
            delete cache;
            cache = new DbDemoFileOperate((char *)"./persons/persons.dat");
            if(!cache->Getbyid(borrow->GetstudentId()))
            {
                delete cache;
                QMessageBox * mess = new QMessageBox();
                mess->setText("数据出错");
                mess->exec();
                exit(0);
            }
            delete cache;
            Persons * person = new Persons(cache->Gettmp_sto());
            showResults[index]->table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(person->Getname())));
            showResults[index]->table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(person->Getaccount())));
        }
        else if(index == 2)
        {
            Persons * person = new Persons(file[index]->PrintFile(i+1+20*(page-1),1));
            show_id[index].push_back(person->GetId());
            showResults[index]->table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(person->Getaccount())));
            showResults[index]->table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(person->Getname())));
            if(person->Getsex() == 1)
                showResults[index]->table->setItem(i,2,new QTableWidgetItem(QString("男")));
            else showResults[index]->table->setItem(i,2,new QTableWidgetItem(QString("女")));
            showResults[index]->table->setItem(i,3,new QTableWidgetItem(QString::number(person->Getage())));
            showResults[index]->table->setItem(i,4,new QTableWidgetItem(QString::fromStdString(person->Getphone())));
        }
    }
}

void Widget::chooseChange(int index)
{
    choose->clear();
    if(index == 0)
    {
        if(id == Root)
        {
            addCurrBook->show();
            addNewBook->show();
            changeBook->show();
            lendBook->show();
            delBook->show();
            retBook->hide();
            losBook->hide();
            delPerson->hide();
            addPerson->hide();
        }
        else if(id == User)
        {
            lendAgain->hide();
            lendBook->show();
        }
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
            addCurrBook->hide();
            addNewBook->hide();
            lendBook->hide();
            delBook->hide();
            retBook->show();
            losBook->show();
            delPerson->hide();
            changeBook->hide();
            addPerson->hide();
        }
        else if(id == User)
        {
            lendAgain->show();
            lendBook->hide();
        }
    }
    else if(index == 2)
    {
        if(id == Root)
        {
            addCurrBook->hide();
            addNewBook->hide();
            changeBook->hide();
            lendBook->hide();
            delBook->hide();
            retBook->hide();
            losBook->hide();
            delPerson->show();
            addPerson->show();
        }
        else if(id == User)
        {
            lendAgain->hide();
            lendBook->hide();
        }
        ope_aim = Person;
        choose->addItem("姓名");
        choose->addItem("帐号");
    }
    showResult();
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

void Widget::returnBook()
{
    int ans = showResults[ope_aim]->table->currentRow();
    if(ans == -1)
    {
        QMessageBox::warning(this,"还书失败","请先选中借阅记录");
        return;
    }
    if(!file[ope_aim]->Getbyid(show_id[ope_aim][ans]))
    {
        QMessageBox::warning(this,"还书失败","未搜索到该借阅记录,请检查数据库");
        return;
    }
    Borrows * borrow = new Borrows(file[ope_aim]->Gettmp_sto());
    if(borrow->GetifReturn())
    {
        QMessageBox::warning(this,"还书失败","该图书已归还");
        return;
    }
    int bookcopyid = borrow->GetbookId();
    DbDemoFileOperate * cache =new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
    if(!cache->Getbyid(bookcopyid))
    {
        delete cache;
        QMessageBox::warning(this,"还书失败","未搜索到该书,请检查数据库");
        return;
    }
    Bookcopy * bookcopy = new Bookcopy(cache->Gettmp_sto());
    bookcopy->Setlend(0);
    int bookid = bookcopy->Getbookid();
    DbDemoFileOperate * cache2 =new DbDemoFileOperate((char *)"./books/books.dat");
    if(!cache2->Getbyid(bookid))
    {
        delete cache2;
        QMessageBox::warning(this,"还书失败","未搜索到该书信息,请检查数据库");
        return;
    }
    Books * book = new Books(cache2->Gettmp_sto());
    book->Setleft(book->Getleft()+1);
    cache->Changebyid(bookcopyid,bookcopy->Getmy_cache());
    cache2->Changebyid(bookid,book->Getmy_cache());
    cache2->Getbyid(bookid);
    delete cache;
    delete cache2;
    cache = new DbDemoFileOperate((char *)"./borrows/borrows.dat");
    borrow->SetifReturn(1);
    borrow->SetifLend(0);
    borrow->SetlastTime(QDate::currentDate());
    cache->Changebyid(borrow->GetId(),borrow->Getmy_cache());
    delete cache;
    initResult(Borrow);
    initResult(Book);
    int day = max((int)borrow->GetlastTime().daysTo(QDate::currentDate()), 0);
    QMessageBox::warning(this,"还书成功",QString("还书成功,预留定金200元,应返还定金%1元").arg(200-min(200,day)));
}

void Widget::deleteUser()
{
    int ans = showResults[ope_aim]->table->currentRow();
    if(ans == -1)
    {
        QMessageBox::warning(this,"删除用户失败","请先选中要删除的用户");
        return;
    }
    int studentId = show_id[ope_aim][ans];
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./borrows/borrows.dat");
    cache->Query((char *)(&studentId),2,(char *)"./borrows/3.dat");
    delete cache;
    cache = new DbDemoFileOperate((char *)"./borrows/3.dat");
    for(int i=1; i<=cache->GetCount(); i++)
    {
        cache->Getbynum(i);
        Borrows * borrows = new Borrows(cache->Gettmp_sto());
        if(!borrows->GetifReturn())
        {
            delete borrows;
            delete cache;
            QMessageBox::warning(this,"删除用户失败","该用户还有图书未归还,请先清空该用户的借阅记录");
            return;
        }
        delete borrows;
    }
    DbDemoFileOperate * cache2 = new DbDemoFileOperate((char *)"./borrows/borrows.dat");
    for(int i=1; i<=cache->GetCount(); i++)
    {
        cache->Getbynum(i);
        Borrows * borrows = new Borrows(cache->Gettmp_sto());
        cache2->Deletbyid(borrows->GetId());
        delete borrows;
    }
    delete cache2;
    delete cache;
    cache = new DbDemoFileOperate((char *)"./persons/persons.dat");
    cache->Deletbyid(studentId);
    delete cache;
    initResult(Borrow);
    initResult();
    QMessageBox::warning(this,"删除成功","成功删除该用户");
}

void Widget::addUsers(QList<QString> list)
{
    Persons * person = new Persons(1, list.at(0), list.at(1), list.at(2), list.at(3)==QString("男"),
        list.at(4), list.at(5), list.at(6).toInt(), QDate::fromString(list.at(7)));
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./persons/persons.dat");
    cache->Query(person->Getaccount(),2,(char *)"./persons/3.dat");
    delete cache;
    cache = new DbDemoFileOperate((char *)"./persons/3.dat");
    if(cache->GetCount())
    {
        delete cache;
        QMessageBox::warning(this,"添加用户失败","该帐号已存在!");
        return;
    }
    delete cache;
    cache = new DbDemoFileOperate((char *)"./admins/admins.dat");
    cache->Query(person->Getaccount(),2,(char *)"./admins/3.dat");
    delete cache;
    cache = new DbDemoFileOperate((char *)"./admins/3.dat");
    if(cache->GetCount())
    {
        delete cache;
        QMessageBox::warning(this,"添加用户失败","该账户已存在!");
        return;
    }
    delete cache;
    cache = new DbDemoFileOperate((char *)"./persons/persons.dat");
    cache->FileWrite(person->Getmy_cache());
    delete cache;
    initResult();
    QMessageBox::warning(this,"添加用户成功","已成功添加该用户");
}

void Widget::addBorrow()
{
    int ans = showResults[ope_aim]->table->currentRow();
    if(ans == -1)
    {
        QMessageBox::warning(this,"借阅失败","请先选中要借阅的书");
        return;
    }
    int bookid = show_id[ope_aim][ans];
    vector<string>list;
    if(id == Root)
        list.push_back("用户帐号");
    list.push_back("图书id");
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
    cache->Query((char *)(&bookid),2,(char *)"./bookcopy/3.dat");
    delete cache;
    cache = new DbDemoFileOperate((char *)"./bookcopy/3.dat");
    int inputNum=cache->GetCount();
    for(int i=1; i<=cache->GetCount(); i++)
    {
        cache->Getbynum(i);
        Bookcopy * bookcopy = new Bookcopy(cache->Gettmp_sto());
        list.push_back(QString::number(bookcopy->GetId()).toStdString());
    }
    delete cache;
    borrowBook = new Dialog(inputNum,list);
    connect(borrowBook,SIGNAL(submit(QList<QString>)),this,SLOT(addBorrows(QList<QString>)));
    borrowBook->exec();
    delete borrowBook;
}

void Widget::addNewBooks(QList<QString> list)
{
    Books new_book(0,list.at(0),list.at(1).toInt(),list.at(1).toInt(),list.at(2),list.at(3),list.at(4));
    if(new_book.Getamount()<=0 || new_book.Getamount()>50)
    {
        QMessageBox::warning(this,"添加失败","图书数目必须为正整数且不能超过50");
        return;
    }
    DbDemoFileOperate *addbookfile;
    addbookfile=new DbDemoFileOperate((char *)"./books/books.dat");
    addbookfile->Query(new_book.Getisbn(),7,(char *)"./books/3.dat");
    delete addbookfile;
    addbookfile = new DbDemoFileOperate((char *)"./books/3.dat");
    if(addbookfile->GetCount())
    {
        delete addbookfile;
        QMessageBox::warning(this,"添加失败","该isbn号已经有对应的书了!");
        return;
    }
    delete addbookfile;
    addbookfile = new DbDemoFileOperate((char *)"./books/books.dat");
    addbookfile->FileWrite(new_book.Getmy_cache(),-1,false);
    int c_id=addbookfile->GetcurrId()-1;
    delete addbookfile;
    addbookfile=new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
    Bookcopy new_bookcopy(0,c_id,0);
    for(int i=0;i<new_book.Getamount();i++){
        addbookfile->FileWrite(new_bookcopy.Getmy_cache(),-1,false);
    }
    delete addbookfile;
    initResult();
    QMessageBox::warning(this,"添加成功","成功添加新书");
}

void Widget::addCurrBooks(QList<QString> list)
{
    int num = list.at(0).toInt();
    int ans = showResults[ope_aim]->table->currentRow();
    if(ans == -1)
    {
        QMessageBox::warning(this,"添加失败","请先选中书籍");
        return;
    }
    int id=show_id[ope_aim][ans];
    DbDemoFileOperate *newbookfile;
    newbookfile=new DbDemoFileOperate((char *)"./books/books.dat");
    newbookfile->Getbyid(id);
    Books newbook(newbookfile->Gettmp_sto());
    newbook.Setamount(newbook.Getamount()+num);
    newbook.Setleft(newbook.Getleft()+num);
    if(newbook.Getamount()<=0 || newbook.Getamount()>50 || num<=0)
    {
        QMessageBox::warning(this,"添加图书失败","添加图书数目必须大于0且图书总数不能超过50");
        return;
    }
    newbookfile->Changebyid(newbook.GetId(),newbook.Getmy_cache());
    delete newbookfile;
    newbookfile=new DbDemoFileOperate((char *)(char *)"./bookcopy/bookcopy.dat");
    Bookcopy newbookcopy(0,newbook.GetId(),0);
    for(int i=0;i<num;i++){
        newbookfile->FileWrite(newbookcopy.Getmy_cache(),-1,false);
    }
    delete newbookfile;
    initResult();
    QMessageBox::warning(this,"添加成功","成功添加该书");
}

void Widget::delBooks()
{
    int ans = showResults[ope_aim]->table->currentRow();
    if(ans == -1)
    {
        QMessageBox::warning(this,"删除失败","请先选中要删除的书");
        return;
    }
    int bookid = show_id[ope_aim][ans];
    vector<string>list;
    list.push_back("图书id");
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
    cache->Query((char *)(&bookid),2,(char *)"./bookcopy/3.dat");
    delete cache;
    cache = new DbDemoFileOperate((char *)"./bookcopy/3.dat");
    int inputNum=cache->GetCount();
    for(int i=1; i<=cache->GetCount(); i++)
    {
        cache->Getbynum(i);
        Bookcopy * bookcopy = new Bookcopy(cache->Gettmp_sto());
        list.push_back(QString::number(bookcopy->GetId()).toStdString());
    }
    delete cache;
    dBook = new Dialog(inputNum,list);
    connect(dBook,SIGNAL(submit(QList<QString>)),this,SLOT(deleteBook(QList<QString>)));
    dBook->exec();
    delete dBook;
}

void Widget::changeBooks()
{
    int ans = showResults[ope_aim]->table->currentRow();
    if(ans == -1)
    {
        QMessageBox::warning(this,"修改失败","请先选中书籍");
        return;
    }
    int id=show_id[ope_aim][ans];
    QList<QString>list;
    for(int i=0;i<4;i++)
        list << showResults[ope_aim]->table->item(ans,i)->text();
    file[ope_aim]->Getbyid(id);
    Books * book = new Books(file[ope_aim]->Gettmp_sto());
    book->Setname(list.at(0));
    book->Setisbn(list.at(1));
    book->Setauthor(list.at(2));
    book->Setpress(list.at(3));
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./books/books.dat");
    cache->Changebyid(id,book->Getmy_cache());
    delete cache;
    QMessageBox::warning(this,"修改成功","成功修改当前图书");
    initResult();
}

void Widget::addBorrows(QList<QString> list)
{
    if(id == User)
        list.insert(0, username);
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./persons/persons.dat");
    char * aim = new char[50];
    for(int i=0; i<50; i++)
    {
        if(i <= list.at(0).length())
            aim[i] = list.at(0).toStdString()[i];
        else aim[i] = '\0';
    }
    cache->Query(aim,2,(char *)"./persons/3.dat");
    delete cache;
    cache = new DbDemoFileOperate((char *)"./persons/3.dat");
    if(!cache->GetCount())
    {
        delete cache;
        QMessageBox::warning(this,"借书失败","没有对应的用户");
        return;
    }
    Persons * persons = new Persons(cache->PrintFile(1,1));
    delete cache;
    cache = new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
    if(!cache->Getbyid(list.at(1).toInt()))
    {
        delete cache;
        QMessageBox::warning(this,"借书失败","没有对应的书");
        return;
    }
    Bookcopy * bookcopy = new Bookcopy(cache->Gettmp_sto());
    if(bookcopy->Getlend())
    {
        delete cache;
        QMessageBox::warning(this,"借书失败","该图书已借出");
        return;
    }
    bookcopy->Setlend(1);
    cache->Changebyid(list.at(1).toInt(),bookcopy->Getmy_cache());
    delete cache;
    cache = new DbDemoFileOperate((char *)"./books/books.dat");
    cache->Getbyid(bookcopy->Getbookid());
    Books * book = new Books(cache->Gettmp_sto());
    book->Setleft(book->Getleft()-1);
    cache->Changebyid(book->GetId(),book->Getmy_cache());
    delete cache;
    cache = new DbDemoFileOperate((char *)"./borrows/borrows.dat");
    Borrows * borrow = new Borrows(1, persons->GetId(), list.at(1).toInt(), QDate::currentDate(), 0, QDate::currentDate().addDays(30), 0);
    cache->FileWrite(borrow->Getmy_cache(),-1);
    delete cache;
    initResult(Book);
    initResult(Borrow);
    QMessageBox::warning(this,"借书成功",QString("用户%1成功借出图书%2").arg(persons->Getname()).arg(book->Getname()));
}

void Widget::deleteBook(QList<QString> list)
{
    int bookcopyid = list.at(0).toInt();
    DbDemoFileOperate *delfile;
    delfile=new DbDemoFileOperate((char *)"./bookcopy/bookcopy.dat");
    if(!delfile->Getbyid(bookcopyid)){
       delete delfile;
       QMessageBox::warning(this,"不存在这本书","请确认书籍id是否正确");
       return;
    }
    Bookcopy delbook(delfile->Gettmp_sto());
    if(delbook.Getlend()){
        delete delfile;
        QMessageBox::warning(this,"本书在借","请先将该书归还");
        return;
    }
    delfile->Deletbyid(delbook.GetId());
    delete delfile;
    delfile=new DbDemoFileOperate((char *)"./books/books.dat");
    delfile->Getbyid(delbook.Getbookid());
    Books delb(delfile->Gettmp_sto());
    delb.Setamount(delb.Getamount()-1);
    delb.Setleft(delb.Getleft()-1);
    if(delb.Getamount())
        delfile->Changebyid(delb.GetId(),delb.Getmy_cache());
    else
        delfile->Deletbyid(delb.GetId());
    delete delfile;
    initResult();
    QMessageBox::warning(this,"删除成功","成功删除该图书");
}

void Widget::lendAgain2()
{
    int ans = showResults[ope_aim]->table->currentRow();
    if(ans == -1)
    {
        QMessageBox::warning(this,"续借失败","请先选中借阅记录");
        return;
    }
    int id=show_id[ope_aim][ans];
    DbDemoFileOperate * cache = new DbDemoFileOperate((char *)"./borrows/borrows.dat");
    if(!cache->Getbyid(id))
    {
        QMessageBox::warning(this,"借阅失败","数据错误,请检查数据文件");
        exit(0);
    }
    Borrows * borrows = new Borrows(cache->Gettmp_sto());
    if(borrows->GetifLend())
    {
        delete cache;
        QMessageBox::warning(this,"续借失败","当前图书已经续借过了,无法继续续借");
        return;
    }
    borrows->SetifLend(1);
    borrows->SetlastTime(borrows->GetlastTime().addDays(30));
    cache->Changebyid(id,borrows->Getmy_cache());
    delete cache;
    initResult();
    QMessageBox::warning(this,"续借成功","当前图书已成功续借");
}

Widget::~Widget()
{
}
