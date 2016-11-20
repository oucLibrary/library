#include "dbdemo.h"

#include <QMessageBox>


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
DbDemoFileOperate::DbDemoFileOperate(char *fileName)
{
    file.open(fileName, ios::app|ios::in|ios::out);
    if(!file.is_open())
    {
        QMessageBox * messagebox = new QMessageBox();
        messagebox->setText("打开文件失败");
        messagebox->exec();
    }
    file.seekg(0, ios::beg);
    file.read((char *)(&currId), sizeof(int));
    file.read((char *)(&colnum), sizeof(int));
    for(int i=0; i<=colnum; i++)
    {
        int pos;
        file.read((char *)(&pos), sizeof(int));
        col.push_back(pos);
    }
}
void DbDemoFileOperate::FileWrite(DbDemo *demo,int pos)      //写入第pos条文件,默认写入文件末尾
{
    //if(pos == -1)
      //  file.seekp(0, ios::end);
    //else
      //  file.seekp(pos*fileLen+2*sizeof(int), ios::beg);
    //file.write((char *)(demo),fileLen);
}
void DbDemoFileOperate::Query(char *aim, int column, bool ok)
{
    fstream cache;
    if(ok)
        cache.open("1.dat", ios::out|ios::binary);
    else cache.open("2.dat", ios::out|ios::binary);
    cache.write((char *)(&currId), sizeof(int));
    cache.write((char *)(&colnum), sizeof(int));
    for(int i=0; i<=colnum; i++)
    {
        int pos = col[i];
        cache.write((char *)(&pos), sizeof(int));
    }

    file.seekg(col[column-1]+sizeof(int)*(colnum+3), ios::beg);
    char infor[col[colnum]];
    while(file.read(infor, col[column]-col[column-1]))
    {
        for(int i=0; i<col[column]-col[column-1]; i++)
        {
            if(infor[i] != aim[i])
            {
                file.seekg(col[colnum]-col[column]+col[column-1], ios::cur);
                break;
            }
            else if(i == col[column]-col[column-1]-1)
            {
                file.seekg(-col[column], ios::cur);
                file.read(infor, col[colnum]);
                cache.write(infor, col[colnum]);
                file.seekg(col[column-1],ios::cur);
            }
        }
    }
}
