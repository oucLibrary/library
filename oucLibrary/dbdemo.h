#ifndef DBDEMO_H
#define DBDEMO_H

#include <bits/stdc++.h>
using namespace std;
/*
class Time{
private:
    int timestamp;
    int YY;
    int MM;
    int DD;
public:
    Time();
};*/

class DbDemo{
private:
    int id;
    char name[50];
    //class Time;
public:
    DbDemo();  //构造函数
    DbDemo(int ,string); //带参数的构造函数
    int GetId();   //获取id
    void SetId(int);  //设置id
    string GetName();  //获取a的值
    void SetName(string);  //设置a的值
};

class DbDemoFileOperate{
public:
    DbDemoFileOperate(char *fileName); //实例化一类，打开一个文件名为fileName 的文件
    DbDemoFileOperate();  //无特定意义
    void FileWrite(DbDemo);    //文件写入
    void QueryById(int,bool);  //通过id查询,bool变量表示是否二次搜索
    void QueryByA(string,bool); // 通过a查询,bool变量表示是否是二次搜索
    DbDemo* PrintFile(int,int,bool);//显示数据 bool表示是否是缓存文件中的,int表示取出的条数
    int GetPageCount(int,bool);//输出页码总数，int变量为每页显示的数据条数,bool代表操作是否为缓存文件；
    int GetCount(bool);//输出数据总条数，bool表示操作是否为缓存文件；
    void OrderById(bool); //对缓存文件排序，若无缓存文件则复制原文件作为缓存文件；
    void OrderByA(bool);//对缓存文件排序，若无缓存文件则复制原文件作为缓存文件；
private:
    FILE *filetp;
    string tempFileName;  //缓存文件的文件名
};

#endif // DBDEMO_H
