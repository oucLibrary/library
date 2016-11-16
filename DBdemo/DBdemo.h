
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
    DbDemoFileOperate(string fileName); //ʵ����һ�࣬��һ���ļ���ΪfileName ���ļ�
    DbDemoFileOperate();  //���ض�����
    void FileWrite(DbDemo);    //�ļ�д��
    void QueryById(int,bool);  //ͨ��id��ѯ,bool������ʾ�Ƿ��������
    void QueryByA(string,bool); // ͨ��a��ѯ,bool������ʾ�Ƿ��Ƕ�������
    DbDemo* PrintFile(int,int,bool);//��ʾ���� bool��ʾ�Ƿ��ǻ����ļ��е�,int��ʾȡ��������
    int GetPageCount(int,bool);//���ҳ��������int����Ϊÿҳ��ʾ����������,bool��������Ƿ�Ϊ�����ļ���
    int GetCount(bool);//���������������bool��ʾ�����Ƿ�Ϊ�����ļ���
    void OrderById(bool); //�Ի����ļ��������޻����ļ�����ԭ�ļ���Ϊ�����ļ���
    void OrderByA(bool);//�Ի����ļ��������޻����ļ�����ԭ�ļ���Ϊ�����ļ���
private:
    File *filetp;
    string tempFileName;  //�����ļ����ļ���
};

#endif //_DB_DEMO_H_
