#ifndef DBDEMO_H
#define DBDEMO_H

#include <bits/stdc++.h>
#include <QDate>
using namespace std;

class DbDemo{
protected:
    int id;
    char name[50];
    //class Time;
public:
    DbDemo();  //构造函数
    DbDemo(int ,string); //带参数的构造函数
    int GetId();   //获取id
    void SetId(int);  //设置id
    string GetName();  //获取name的值
    void SetName(string);  //设置name的值
};

class DbDemoFileOperate{//column and raw are all started from 0
public:
    DbDemoFileOperate();  //无特定意义
    DbDemoFileOperate(char *fileName); //实例化一类，打开一个文件名为fileName 的文件
    void FileWrite(DbDemo *demo, int pos = -1,bool ok=false);    //文件写入 moren no cache file and after the file
    void Query(char *aim,int column,bool ok);  //通过id查询,bool变量表示是否二次搜索
    char* PrintFile (int pageNum, int printNum);//显示数据 bool表示是否是缓存文件中的,int表示取出的条数
    int GetPageCount(int printNum);//输出页码总数，int变量为每页显示的数据条数,bool代表操作是否为缓存文件；
    int GetCount();//输出数据总条数，bool表示操作是否为缓存文件；
    void Order(int column); //对缓存文件排序，若无缓存文件则复制原文件作为缓存文件；
private:
    fstream file;

    char * aim;
    int currId;             //当前id
    int colnum;             //列数
    int count;              //记录条数
    vector<int>col;         //每一列的起始位置
};

class Books:public DbDemo{
private:
    bool lend;
    char author[20];
    char press[20];
public:
    bool Getlend();
    void Setlend(bool tmp);
    char *Getauthor();
    void Setauthor(char *tmp);
    char *Getpress();
    void Setpress(char *tmp);
};

class BookKinds:public DbDemo{

};

class Classification:public DbDemo{
private:
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
    bool sex;
    char email[50];
    char phone[15];//
    int age;
    QDate birth;
public:
    Persons(int id, string name, char account[20], char password[20], char sex, char email[50], char phone[15], int age, QDate birth);
    char *Getaccount();
    void Setaccount(char *tmp);
    char *Getpassword();
    void Setpassword(char *tmp);
    bool Getsex();
    void Setsex(bool tmp);
    char *Getemail();
    void Setemail(char *tmp);
    char *Getphone();
    void Setphone(char *tmp);
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
    bool ifLend;
    QDate lastTime;
    bool ifReturn;
public:
    int GetstudentId();
    void SetstudentId(int tmp);
    int GetbookId();
    void SetbookId(int tmp);
    QDate GetfirstTime();
    void SetfirstTime(QDate tmp);
    bool GetifLend();
    void SetifLend(bool tmp);
    QDate GetlastTime();
    void SetlastTime(QDate tmp);
    bool GetifReturn();
    void SetifReturn(bool tmp);
};

class Admins:public DbDemo{
private:
    char account[20];
    char password[20];
public:
    Admins(int id, string name, char account[20], char password[20]);
    char *Getaccount();
    void Setaccount(char *tmp);
    char *Getpassword();
    void Setpassword(char *tmp);
};

#endif // DBDEMO_H
