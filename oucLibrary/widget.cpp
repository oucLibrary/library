#include "widget.h"

#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QAction>
#include <QHeaderView>

Widget::Widget(QWidget *parent) :
    QWidget(parent), choose(new QComboBox(this)), context(new QLineEdit(this)), start(new QPushButton(this)),
    log(new QPushButton(this)), showName(new QPushButton(this)),
    lot(new QPushButton(this)), logins(new Login()), showBookResult(new QTableWidget(this)),
    userWidget(new QTabWidget(this)), rootWidget(new QTabWidget(this))
{
    setMaximumSize(700,500);
    setMinimumSize(700,500);

    id = Empty;

    choose->setGeometry(60, 120, 100, 30);
    choose->addItem("全部");
    choose->addItem("作者");
    choose->addItem("书籍");
    choose->addItem("分类");

    context->setGeometry(200, 120, 300, 30);

    start->setGeometry(520, 120, 100, 30);
    start->setText("查询");
    connect(start, SIGNAL(clicked(bool)), this, SLOT(query()));

    createShowBook();
    createUserWidget();
    createRootWidget();

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

void Widget::createShowBook()
{
    showBookResult->setGeometry(60, 170, 580, 300);
    showBookResult->setColumnCount(5);
    for(int i=0; i<4; i++)
        showBookResult->setColumnWidth(i, 120);
    QStringList header;
    header << "书名" << "作者" << "出版年份" << "出版社" << "可借阅数量" ;
    showBookResult->setHorizontalHeaderLabels(header);
    showBookResult->horizontalHeader()->setStretchLastSection(true);
    showBookResult->hide();
}

void Widget::createUserWidget()
{
    userWidget->setGeometry(60, 170, 580, 300);
    userWidget->hide();
}

void Widget::createRootWidget()
{
    rootWidget->setGeometry(60, 170, 580, 300);
    rootWidget->hide();
}

void Widget::query()
{
    if(id == Empty)
        showBookResult->show();
}

void Widget::login_success(QString username, QString password, Identify id)
{
    this->username = username;
    this->password = password;
    this->id = id;
    log->hide();
    showName->setText(username);
    showName->show();
    lot->show();
}

void Widget::logout()
{
    showName->hide();
    lot->hide();
    log->show();
    id = Empty;
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
