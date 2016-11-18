#include "dbdemo.h"


//DbDemo方法
DbDemo::DbDemo(){}
DbDemo::DbDemo(int id1,string a1){
    id=id1;
    for(int i=0; i<(int)a1.length(); i++){
        name[i]=a1[i];
    }
    name[a1.length()]=0;
}

int DbDemo::GetId(){
    return id;
}

void DbDemo::SetId(int id1){
    id=id1;
}
string DbDemo::GetName(){
    string str=name;
    return str;
}
void DbDemo::SetName(string a1){
    for(int i=0;i<(int)a1.length();i++){
        name[i]=a1[i];
    }
    name[a1.length()]=0;
}
//DbDemoFileOperate方法
DbDemoFileOperate::DbDemoFileOperate(){
}
DbDemoFileOperate::DbDemoFileOperate(char *fileName){
    file.open(fileName, ios::app|ios::in|ios::out);
}
void DbDemoFileOperate::FileWrite(DbDemo *demo,int pos)      //写入第pos条文件,默认写入文件末尾
{
    if(pos == -1)
        file.seekp(0, ios::end);
    else
        file.seekp(pos*fileLen+2*sizeof(int), ios::beg);
    file.write((char *)(demo),fileLen);
}
void DbDemoFileOperate::QueryById(int id,bool ok)           //ok=false往第一个缓存文件放,ok=true往第二个缓存文件放
{
    char buffer[fileLen];
    fstream cache;
    if(ok)
        cache.open("1.dat",ios::out);
    else cache.open("2.dat",ios::out);
    int cache_id=0;
    cache.write((char *)(&cache_id),sizeof(int));
    cache.write((char *)(&fileLen),sizeof(int));
    file.seekp(2*sizeof(int), ios::beg);
    int curr_id;
    int pos=2*sizeof(int);
    while(file.read((char*)(&curr_id),sizeof(int)))
    {
        if(curr_id == id)
        {
            file.read(buffer,fileLen-sizeof(int));
            cache.write((char *)(&cache_id),sizeof(int));
            cache_id++;
            cache.write(buffer,fileLen-sizeof(int));
        }
        else
            file.read((char*)(buffer),fileLen-sizeof(int));
        pos+=fileLen;
    }
    cache.seekp(0,ios::beg);
    cache.write((char *)(&cache_id),sizeof(int));
    cache.close();
}
void DbDemoFileOperate::QueryByName(char name[50], bool ok)
