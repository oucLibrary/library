
#ifndef _DB_DEMO_H_
#define _DB_DEMO_H_

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
    char a[50];
    //class Time;
public:
    DbDemo();
    DbDemo(int ,string);
    int GetId();
    void SetId(int);
    string GetA();
    void SetA(string);
};

class DbDemoFileOperate{
public:
    DbDemoOperate(string fileName);
    DbDemoOperate();
    FileWrite();
    QueryById(int);
    QueryByA(string);
private:
    File *filetp;
};

#endif //_DB_DEMO_H_
