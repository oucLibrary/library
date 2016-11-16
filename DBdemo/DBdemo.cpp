#include<iostream>
#include<bits/stdc++.h>
#include "DBdemo.h"


//DbDemo方法
DbDemo::DbDemo(){};
DbDemo::DbDemo(int id1,string a1){
    id=id1;
    for(int i=0;i<a1.length();i++){
        a[i]=a1[i];
    }
    a[a1.length()]=0;
}

int DbDemo::GetId(){
    return id;
}

void DbDemo::SetId(int id1){
    id=id1;
}
string DbDemo::GetA(){
    string str=a;
    return str;
}
void DbDemo::SetA(string a1){
    for(int i=0;i<a1.length();i++){
        a[i]=a1[i];
    }
    a[a1.length()]=0;
}
//DbDemoFileOperate方法
DbDemoFileOperate::DbDemoFileOperate(){
}
DbDemoFileOperate::DbDemoOperate(string fileName){

}
