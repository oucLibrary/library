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
    file.open(fileName, ios::ate|ios::in|ios::out);
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
void DbDemoFileOperate::FileWrite(DbDemo *demo,int pos,bool ok)      //写入第pos条文件,默认写入文件末尾
{
    //if(pos == -1)
      //  file.seekp(0, ios::end);
    //else
      //  file.seekp(pos*fileLen+2*sizeof(int), ios::beg);
    //file.write((char *)(demo),fileLen);
    char *aim=(char *)demo;
    if(pos==-1){
        file.seekp(0,ios::end);
        file.write(aim,col[colnum]);
        file.seekp(-col[colnum],ios::end);
        if(!ok){
            file.write((char *)(&currId),sizeof(int));
            currId++;
            file.seekp(0,ios::beg);
            file.write((char *)(&currId),sizeof(int));
        }
    }
    else{
        file.seekp(sizeof(int)*(colnum+3)+pos*col[colnum],ios::beg);
        file.write(aim,col[colnum]);
    }
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
int GetCount(bool ok)
{
    file.seekp(0,ios::end);
    return (file.tellp()-(sizeof(int))*(colnum+3))/col[colnum];
}

int GetPageCount(int per_page_num,bool ok=0)
{
    return GetCount(ok)/per_page_num+(GetCount(ok)%per_page_num!=0);
}

void make_order(int st,int ed,fstream file,int column,vector<int>col){
    if(st!=ed){
        int siz=col.size();
        siz--;
        char cache1[col[siz]],cache2[col[siz]];
        int  mid=(st+ed)>>1;
        make_order(st,mid,file,column,col);
        make_order(mid+1,ed,file,column,col);
        int sta=st,eda=mid,stb=mid+1,edb=ed;
        fstream order_tmp("3.dat",ios::in|ios::out);
        while(sta!=eda&&stb!=edb){
            file.seekg((siz+3)*sizeof(int)+col[siz]*sta,ios::beg);
            file.read(cache1,col[colnum]);
            file.seekg((siz+3)*sizeof(int)+col[siz]*stb,ios::beg);
            file.read(cache2,col[colnum]);
            bool ok=1;
            for(int i=col[column];i<col[column+1];i++){
                if(cache1[i]!=cache2[i]){
                    if(cache1[i]>cache2[i]){
                        ok=0;
                        break;
                    }
                }
            }
            if(ok){
                order_tmp.write(cache1,col[siz]);
                sta++;
            }
            else{
                order_tmp.write(cache2,col[siz]);
                stb++;
            }
        }
        while(sta<=eda){
            file.seekg((siz+3)*sizeof(int)+col[siz]*sta,ios::beg);
            file.read(cache1,col[colnum]);
            order_tmp.write(cache1,col[siz]);
            sta++;
        }
        while(stb<=edb){
            file.seekg((siz+3)*sizeof(int)+col[siz]*stb,ios::beg);
            file.read(cache2,col[colnum]);
            order_tmp.write(cache2,col[siz]);
            stb++;
        }
        file.seekp((siz+3)*sizeof(int)+col[siz]*st,ios::beg);
        order_tmp.seekg(0,ios::beg);
        for(int i=st;i<=ed;i++){
            order_tmp.read(cache1,col[siz]);
            file.write(cache,col[siz]);
        }
    }
}

void Order(int column, bool ok=0)
{
    int len=GetCount();
    make_order(0,len-1,file,column,col);
}
