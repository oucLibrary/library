#ifndef DBDEMO_H
#define DBDEMO_H

#include <bits/stdc++.h>
#include <QDate>
using namespace std;

class DbDemo{
protected:
    int id;
public:
    DbDemo();  //构造函数
    DbDemo(int tmp);
    DbDemo(char *tmp); //从文件操作类的缓存直接读取的构造函数
    int GetId();   //获取id
    void SetId(int);  //设置id
};

class DbDemoFileOperate{//column and raw are all started from 0
public:
    DbDemoFileOperate();  //无特定意义
    DbDemoFileOperate(char *fileName); //实例化一类，打开一个文件名为fileName 的文件
    void FileWrite(DbDemo *demo, int pos = -1,bool ok=false);    //文件写入 moren no cache file and after the file
    void Query(char *aim,int column,bool ok);  //通过id查询,bool变量表示是否二次搜索,从第一列开始
    char* PrintFile (int pageNum, int printNum);//显示数据 bool表示是否是缓存文件中的,int表示取出的条数
    int GetPageCount(int printNum);//输出页码总数，int变量为每页显示的数据条数,bool代表操作是否为缓存文件；
    int GetCount();//输出数据总条数，bool表示操作是否为缓存文件；
    void Order(int column); //对缓存文件排序，若无缓存文件则复制原文件作为缓存文件；
    bool Getbyid(int tid);  //按照id查询，如果能查找到返回true，否则返回false。如果查找不到，tmp_sto为NULL，否则查找结果存储在tmp_sto。
private:
    fstream file;
    char *tmp_sto;          //存储按照id查询结果的一条记录的缓存
    char * aim;
    int currId;             //当前id
    int colnum;             //列数
    int count;              //记录条数
    vector<int>col;         //每一列的起始位置
};

class Books:public DbDemo{
private:
    Books(char *tmp);
    Books(int tid,QString tbookName,int tamount,int tleft, QString tauthor,QString tpress,QString tisbn);
    char name[50];
    int amount;
    int left;//还有多少本可借阅
    char author[20];
    char press[20];
    char isbn[20];
public:
    int Getamount();
    void Setamount(int tmp);
    int Getleft();
    void Setleft(int tleft);
    char *Getauthor();
    void Setname(QString tmp);
    char *Getname();
    void Setauthor(QString tmp);
    char *Getpress();
    void Setpress(QString tmp);
    char *Getisbn();
    void Setisbn(QString tmp);
};

class Bookcopy:public DbDemo{
public:
    Bookcopy(){}
    Bookcopy(int tid,int tbookid,int tlend);
    Bookcopy(char *tmp);
    void Setbookid(int tmp);
    void Setlend(int tmp);
    int Getbookid();
    int Getlend();
private:
    int bookid;
    int lend;
};

class BookKinds:public DbDemo{
public:
    BookKinds(char *tmp);
    BookKinds(int tid,QString tkindName);
    void SetkindName(QString tmp);
    char *GetkindName();
private:
    char kindName[50];
};

class Classification:public DbDemo{
private:
    Classification(int tid,int tbookid,int tkindid);
    Classification(char *tmp);
    int bookid;
    int kindid;
public:
    int Getbookid();
    void Setbookid(int tmp);
    int Getkindid();
    void Setkindid(int tmp);
};

class Persons:public DbDemo{
private:
    char account[20];
    char password[20];
    char name[20];
    int sex;
    char email[50];
    char phone[15];//
    int age;
    QDate birth;
public:
    void Setname(QString tmp);
    char *Getname();
    Persons(char *tmp);
    Persons(int tid,QString taccount,QString tpassword,QString tname,int tsex,QString temail,QString tphone,int tage,QDate birth);
    char *Getaccount();
    void Setaccount(QString tmp);
    char *Getpassword();
    void Setpassword(QString tmp);
    int Getsex();
    void Setsex(int tmp);
    char *Getemail();
    void Setemail(QString tmp);
    char *Getphone();
    void Setphone(QString tmp);
    int Getage();
    void Setage(int tmp);
    QDate Getbirth();
    void Setbirth(QDate tmp);
};

class Borrows:public DbDemo{
private:
    int studentId;
    int bookId;
    QDate firstTime;
    int ifLend;
    QDate lastTime;
    int ifReturn;
public:
    Borrows(char *);
    Borrows(int tid,int tstudentId,int tbookId,QDate tfirstTime,int tifLend,QDate lastTime,int tifReturn);
    int GetstudentId();
    void SetstudentId(int tmp);
    int GetbookId();
    void SetbookId(int tmp);
    QDate GetfirstTime();
    void SetfirstTime(QDate tmp);
    int GetifLend();
    void SetifLend(int tmp);
    QDate GetlastTime();
    void SetlastTime(QDate tmp);
    int GetifReturn();
    void SetifReturn(int tmp);
};

class Admins:public DbDemo{
private:
    char account[20];
    char password[20];
public:
    Admins(int tid, QString taccount,QString tpassword);
    Admins(char *tmp);
    char *Getaccount();
    void Setaccount(QString tmp);
    char *Getpassword();
    void Setpassword(QString tmp);
};

#endif // DBDEMO_H
