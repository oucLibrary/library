
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
    DbDemo();  //���캯��
    DbDemo(int ,string); //�������Ĺ��캯��
    int GetId();   //��ȡid
    void SetId(int);  //����id
    string GetA();  //��ȡa��ֵ
    void SetA(string);  //����a��ֵ
};

class DbDemoFileOperate{
public:
    DbDemoOperate(string fileName); //ʵ����һ�࣬��һ���ļ���ΪfileName ���ļ�
    DbDemoOperate();  //���ض�����
    void FileWrite(DbDemo);    //�ļ�д��
    void QueryById(int,bool);  //ͨ��id��ѯ,bool������ʾ�Ƿ��������
    void QueryByA(string,bool); // ͨ��a��ѯ,bool������ʾ�Ƿ��Ƕ�������
    DbDemo* PrintFile(int,bool);//��ʾ���� bool��ʾ�Ƿ��ǻ����ļ��е�,int��ʾȡ��������
    int PageCout(int);//���ҳ��������int����Ϊÿҳ��ʾ������������
    int TempPageCount(int);//��������ļ�ҳ��������int����Ϊÿҳչʾ������������
    void OrderById(bool); //�Ի����ļ��������޻����ļ�����ԭ�ļ���Ϊ�����ļ���
    void OrderByA(bool);//�Ի����ļ��������޻����ļ�����ԭ�ļ���Ϊ�����ļ���
private:
    File *filetp;
    string tempFileName;  //�����ļ����ļ���
};

#endif //_DB_DEMO_H_
