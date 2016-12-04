#include "dbdemo.h"

#include <QMessageBox>


//DbDemo方法
DbDemo::DbDemo(){}
DbDemo::DbDemo(char *tmp){
    id=*((int*)tmp);
}
DbDemo::DbDemo(int tmp){
    id=tmp;
}

int DbDemo::GetId(){
    return id;
}

void DbDemo::SetId(int id1){
    id=id1;
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
    aim = new char[col[colnum]*100];
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
char* DbDemoFileOperate::PrintFile(int pageNum, int printNum)
{
    file.seekp(sizeof(int)*(colnum+3)+col[colnum]*printNum*(pageNum-1),ios::beg);
    file.read(aim,col[colnum]*printNum);
    return aim;
}
int DbDemoFileOperate::GetCount()
{
    file.seekp(0,ios::end);
    int num=file.tellp();
    return (num-(sizeof(int))*(colnum+3))/col[colnum];
}

int DbDemoFileOperate::GetPageCount(int per_page_num)
{
    return GetCount()/per_page_num+(GetCount()%per_page_num!=0);
}

void make_order(int st,int ed,fstream &file,int column,vector<int>&col){
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
            file.read(cache1,col[siz]);
            file.seekg((siz+3)*sizeof(int)+col[siz]*stb,ios::beg);
            file.read(cache2,col[siz]);
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
            file.read(cache1,col[siz]);
            order_tmp.write(cache1,col[siz]);
            sta++;
        }
        while(stb<=edb){
            file.seekg((siz+3)*sizeof(int)+col[siz]*stb,ios::beg);
            file.read(cache2,col[siz]);
            order_tmp.write(cache2,col[siz]);
            stb++;
        }
        file.seekp((siz+3)*sizeof(int)+col[siz]*st,ios::beg);
        order_tmp.seekg(0,ios::beg);
        for(int i=st;i<=ed;i++){
            order_tmp.read(cache1,col[siz]);
            file.write(cache1,col[siz]);
        }
    }
}

void DbDemoFileOperate::Order(int column)
{
    int len=GetCount();
    make_order(0,len-1,file,column,col);
}
Books::Books(int tid,QString tname,int tamount,QString tauthor,QString tpress,QString tisbn):DbDemo(tid){
    Setname(tname);
    Setamount(tamount);
    Setauthor(tauthor);
    Setpress(tpress);
    Setisbn(tisbn);
}
Books::Books(char *tmp):DbDemo(tmp){
    tmp+=sizeof(int);
    amount=*((int *)tmp);
    tmp+=sizeof(int);
    for(int i=0;i<20;i++){
        author[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<20;i++){
        press[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<20;i++){
        isbn[i]=*tmp;
        tmp++;
    }
}

char *Books::Getname(){
    return name;
}
void Books::Setname(QString tmp){
    memset(name,0,sizeof(name));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<49;i++){
        name[i]=tmp.toStdString()[i];
    }
}

int Books::Getamount(){
    return amount;
}

void Books::Setamount(int tmp){
    amount=tmp;
}

char *Books::Getisbn(){
    return isbn;
}

void Books::Setisbn(QString tmp){
    memset(isbn,0,sizeof(isbn));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        isbn[i]=tmp.toStdString()[i];
    }
}

char *Books::Getauthor(){
    return author;
}

void Books::Setauthor(QString tmp){
    memset(author,0,sizeof(author));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        author[i]=tmp.toStdString()[i];
    }
}

char *Books::Getpress(){
    return press;
}

void Books::Setpress(QString tmp){
    memset(press,0,sizeof(press));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        press[i]=tmp.toStdString()[i];
    }
}

Bookcopy::Bookcopy(int tid,int tbookid,int tlend):DbDemo(tid){
    bookid=tbookid;
    lend=tlend;
}

Bookcopy::Bookcopy(char *tmp):DbDemo(tmp){
    tmp+=sizeof(int);
    bookid=*((int *)tmp);
    tmp+=sizeof(int);
    lend=*((int *)tmp);
}

void Bookcopy::Setbookid(int tmp){
    bookid=tmp;
}

void Bookcopy::Setlend(int tmp){
    lend=tmp;
}

int Bookcopy::Getbookid(){
    return bookid;
}

int Bookcopy::Getlend(){
    return lend;
}


BookKinds::BookKinds(char *tmp):DbDemo(tmp){
    tmp+=sizeof(int);
    for(int i=0;i<50;i++){
        kindName[i]=*tmp;
        tmp++;
    }
}

BookKinds::BookKinds(int tid,QString tkindName):DbDemo(tid){
    SetkindName(tkindName);
}

void BookKinds::SetkindName(QString tmp){
    memset(kindName,0,sizeof(kindName));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<49;i++){
        kindName[i]=tmp.toStdString()[i];
    }
}

char *BookKinds::GetkindName(){
    return kindName;
}
Classification::Classification(int tid,int tbookid,int tkindid):DbDemo(tid){
    bookid=tbookid;
    kindid=tkindid;
}

Classification::Classification(char *tmp):DbDemo(tmp){
    tmp+=sizeof(int);
    bookid=*((int *)tmp);
    tmp+=sizeof(int);
    kindid=*((int *)tmp);
}

int Classification::Getbookid(){
    return bookid;
}

void Classification::Setbookid(int tmp){
    bookid=tmp;
}

int Classification::Getkindid(){
    return kindid;
}

void Classification::Setkindid(int tmp){
    kindid=tmp;
}

Persons::Persons(int tid,QString taccount,QString tpassword,QString tname,int tsex,QString temail,QString tphone,int tage,QDate tbirth):DbDemo(tid){
    Setaccount(taccount);
    Setpassword(tpassword);
    Setname(tname);
    Setsex(tsex);
    Setemail(temail);
    Setphone(tphone);
    Setage(tage);
    Setbirth(tbirth);
}
Persons::Persons(char *tmp):DbDemo(tmp){
    tmp+=sizeof(int);
    for(int i=0;i<20;i++){
        account[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<20;i++){
        password[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<20;i++){
        name[i]=*tmp;
        tmp++;
    }
    sex=*((int *)tmp);
    tmp+=sizeof(int);
    for(int i=0;i<50;i++){
        email[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<15;i++){
        phone[i]=*tmp;
        tmp++;
    }
    age=*((int *)tmp);
    tmp+=sizeof(int);
    birth=*((QDate*)tmp);
}

char *Persons::Getaccount(){
    return account;
}

void Persons::Setaccount(QString tmp){
    memset(account,0,sizeof(account));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        account[i]=tmp.toStdString()[i];
    }
}
char *Persons::Getpassword(){
    return password;
}
void Persons::Setpassword(QString tmp){
    memset(password,0,sizeof(password));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        password[i]=tmp.toStdString()[i];
    }
}
int Persons::Getsex(){
    return sex;
}

void Persons::Setsex(int tmp){
    sex=tmp;
}
char *Persons::Getemail(){
    return email;
}

void Persons::Setemail(QString tmp){
    memset(email,0,sizeof(email));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<49;i++){
        email[i]=tmp.toStdString()[i];
    }
}

char *Persons::Getphone(){
    return phone;
}

void Persons::Setphone(QString tmp){
    memset(phone,0,sizeof(phone));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<14;i++){
        phone[i]=tmp.toStdString()[i];
    }
}

int Persons::Getage(){
    return age;
}

void Persons::Setage(int tmp){
    age=tmp;
}

QDate Persons::Getbirth(){
    return birth;
}

void Persons::Setbirth(QDate tmp){
    birth=tmp;
}

char *Persons::Getname(){
    return name;
}

void Persons::Setname(QString tmp){
    memset(name,0,sizeof(name));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        name[i]=tmp.toStdString()[i];
    }
}

Borrows::Borrows(char *tmp):DbDemo(tmp){
    tmp+=sizeof(int);
    studentId=*((int *)tmp);
    tmp+=sizeof(int);
    bookId=*((int *)tmp);
    tmp+=sizeof(int);
    firstTime=*((QDate *)tmp);
    tmp+=sizeof(QDate);
    ifLend=*((int *)tmp);
    tmp+=sizeof(int);
    lastTime=*((QDate *)tmp);
    tmp+=sizeof(QDate);
    ifReturn=*((int *)tmp);
    tmp+=sizeof(int);
}

Borrows::Borrows(int tid,int tstudentId,int tbookId,QDate tfirstTime,int tifLend,QDate tlastTime,int tifReturn):DbDemo(tid){
    SetstudentId(tstudentId);
    SetbookId(tbookId);
    SetfirstTime(tfirstTime);
    SetifLend(tifLend);
    SetlastTime(tlastTime);
    SetifReturn(tifReturn);
}

int Borrows::GetstudentId(){
    return studentId;
}

void Borrows::SetstudentId(int tmp){
    studentId=tmp;
}

int Borrows::GetbookId(){
    return bookId;
}

void Borrows::SetbookId(int tmp){
    bookId=tmp;
}

QDate Borrows::GetfirstTime(){
    return firstTime;
}

void Borrows::SetfirstTime(QDate tmp){
    firstTime=tmp;
}

int Borrows::GetifLend(){
    return ifLend;
}

void Borrows::SetifLend(int tmp){
    ifLend=tmp;
}

QDate Borrows::GetlastTime(){
    return lastTime;
}

void Borrows::SetlastTime(QDate tmp){
    lastTime=tmp;
}

int Borrows::GetifReturn(){
    return ifReturn;
}

void Borrows::SetifReturn(int tmp){
    ifReturn=tmp;
}

Admins::Admins(int tid, QString taccount,QString tpassword):DbDemo(tid){
    Setaccount(taccount);
    Setpassword(tpassword);
}

Admins::Admins(char *tmp):DbDemo(tmp){
    tmp+=sizeof(int);
    for(int i=0;i<20;i++){
        account[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<20;i++){
        password[i]=*tmp;
        tmp++;
    }
}

char *Admins::Getaccount(){
    return account;
}

void Admins::Setaccount(QString tmp){
    memset(account,0,sizeof(account));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        account[i]=tmp.toStdString()[i];
    }
}

char *Admins::Getpassword(){
    return password;
}

void Admins::Setpassword(QString tmp){
    memset(password,0,sizeof(password));
    for(int i=0;i<(int)tmp.toStdString().length()&&i<19;i++){
        password[i]=tmp.toStdString()[i];
    }
}
