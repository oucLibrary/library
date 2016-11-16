#include "dbdemo.h"


//DbDemo方法
DbDemo::DbDemo(){}
DbDemo::DbDemo(int id1,string a1){
    id=id1;
    for(int i=0;i<a1.length();i++){
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
    if((filetp = fopen(fileName, "rw")) == NULL)
        exit(0);
}
