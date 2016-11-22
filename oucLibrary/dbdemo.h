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

#endif // DBDEMO_H
