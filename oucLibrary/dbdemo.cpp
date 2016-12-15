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
    this->fileName = new char[strlen(fileName)];
    for(int i=0; i<strlen(fileName); i++)
        this->fileName[i] = fileName[i];
    file.open(fileName, ios::ate|ios::in|ios::out);
    if(!file.is_open())
    {
        QMessageBox * messagebox = new QMessageBox();
        messagebox->setText("打开文件失败");
        messagebox->exec();
        exit(0);
    }
    file.seekg(0, ios::beg);
    file.read((char*)(&file_num),sizeof(int));
    file.read((char *)(&currId), sizeof(int));
    file.read((char *)(&colnum), sizeof(int));
    for(int i=0; i<=colnum; i++)
    {
        int pos;
        file.read((char *)(&pos), sizeof(int));
        col.push_back(pos);
    }
    aim = new char[col[colnum]*100];
    tmp_sto=NULL;
}
void DbDemoFileOperate::SetcurrId(int tid){
    currId=tid;
    file.seekp(sizeof(int),ios::beg);
    file.write((char*)(&tid),sizeof(int));
    reOpen();
}
void DbDemoFileOperate::Setfile_num(int tnum){
    file_num=tnum;
    file.seekp(0,ios::beg);
    file.write((char*)(&tnum),sizeof(int));
    reOpen();
}
int DbDemoFileOperate::Getfile_num(){
    return file_num;
}

void DbDemoFileOperate::FileWrite(char *demo,int pos,bool ok)      //写入第pos条文件,默认写入文件末尾
{
    char *aim=(char *)demo;
    if(pos==-1){
        file.seekp(sizeof(int)*(colnum+4)+file_num*col[colnum],ios::beg);
        file.write(aim,col[colnum]);
        file.seekp(-col[colnum],ios::cur);
        if(!ok){
            file.write((char *)(&currId),sizeof(int));
            SetcurrId(currId+1);
        }
        Setfile_num(file_num+1);
    }
    else{
        file.seekp(sizeof(int)*(colnum+4)+pos*col[colnum],ios::beg);
        file.write(aim,col[colnum]);
    }
    reOpen();
}
void DbDemoFileOperate::Query(char *aim, int column, char *road)
{
    fstream cache;
    int nnum=0;
    cache.open(road,ios::out|ios::binary);
    cache.write((char*)(&nnum),sizeof(int));
    cache.write((char *)(&currId), sizeof(int));
    cache.write((char *)(&colnum), sizeof(int));
    for(int i=0; i<=colnum; i++)
    {
        int pos = col[i];
        cache.write((char *)(&pos), sizeof(int));
    }

    file.seekg(col[column-1]+sizeof(int)*(colnum+4), ios::beg);
    char infor[col[colnum]];
    int i=0;
    while(i<file_num&&file.read(infor, col[column]-col[column-1]))
    {
        i++;
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
                nnum++;
            }
        }
    }
    cache.seekp(0,ios::beg);
    cache.write((char*)(&nnum),sizeof(int));
    cache.close();
    reOpen();
}
char* DbDemoFileOperate::PrintFile(int pageNum, int printNum)
{
    file.seekg(sizeof(int)*(colnum+4)+col[colnum]*printNum*(pageNum-1),ios::beg);
    file.read(aim,col[colnum]*printNum);
    return aim;
}
int DbDemoFileOperate::GetCount()
{
    return Getfile_num();
}

int DbDemoFileOperate::GetPageCount(int per_page_num)
{
    return GetCount()/per_page_num+(GetCount()%per_page_num!=0);
}

char *DbDemoFileOperate::Gettmp_sto(){
    return tmp_sto;
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
            file.seekg((siz+4)*sizeof(int)+col[siz]*sta,ios::beg);
            file.read(cache1,col[siz]);
            file.seekg((siz+4)*sizeof(int)+col[siz]*stb,ios::beg);
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
            file.seekg((siz+4)*sizeof(int)+col[siz]*sta,ios::beg);
            file.read(cache1,col[siz]);
            order_tmp.write(cache1,col[siz]);
            sta++;
        }
        while(stb<=edb){
            file.seekg((siz+4)*sizeof(int)+col[siz]*stb,ios::beg);
            file.read(cache2,col[siz]);
            order_tmp.write(cache2,col[siz]);
            stb++;
        }
        file.seekp((siz+4)*sizeof(int)+col[siz]*st,ios::beg);
        order_tmp.seekg(0,ios::beg);
        for(int i=st;i<=ed;i++){
            order_tmp.read(cache1,col[siz]);
            file.write(cache1,col[siz]);
        }
    }
}

bool DbDemoFileOperate::Getbyid(int tid){
    if(tmp_sto!=NULL){
        delete tmp_sto;
        tmp_sto=NULL;
    }
    file.seekg(sizeof(int)*(colnum+4),ios::beg);
    char tmp[col[colnum]+10];
    int i=0;
    while(i<file_num&&file.read(tmp,col[colnum])){
        i++;
        int cur_id=*((int *)tmp);
        if(cur_id==tid){
            tmp_sto=new char[col[colnum]+10];
            for(int i=0;i<col[colnum];i++){
                tmp_sto[i]=tmp[i];
            }
            return true;
        }
    }
    return false;
}

void DbDemoFileOperate::Order(int column)
{
    int len=GetCount();
    make_order(0,len-1,file,column,col);
}

bool DbDemoFileOperate::Changebyid(int tid,char *tmp){
    file.seekg(sizeof(int)*(colnum+4),ios::beg);
    char *buff=new char[col[colnum]+10];
    int i=0;
    while(i<file_num&&file.read(buff,col[colnum])){
        i++;
        if(*((int*)buff)==tid){
            file.seekp(sizeof(int)*(colnum+4)+(i-1)*col[colnum],ios::beg);
            file.write(tmp,col[colnum]);
            reOpen();
            return true;
        }
    }
    return false;
}

bool DbDemoFileOperate::Deletbyid(int tid){
    char *buff=new char[col[colnum]+10];
    int i=0;
    char *tar=new char[col[colnum]+10];
    file.seekg(sizeof(int)*(colnum+4)+(file_num-1)*col[colnum],ios::beg);
    file.read(tar,col[colnum]);
    file.seekg(sizeof(int)*(colnum+4),ios::beg);
    while(i<file_num&&file.read(buff,col[colnum])){
        i++;
        if((*(int*)buff)==tid){
            file.seekp(((int)file.tellg())-col[colnum],ios::beg);
            file.write(tar,col[colnum]);
            Setfile_num(file_num-1);
            reOpen();
            return true;
        }
    }
    return false;
}

bool DbDemoFileOperate::Getbynum(int tnum){
    if(tnum>file_num)return false;
    tnum--;
    file.seekg(sizeof(int)*(4+colnum)+tnum*col[colnum],ios::beg);
    if(tmp_sto != NULL)
    {
        delete tmp_sto;
        tmp_sto = NULL;
    }
    tmp_sto=new char[col[colnum]+10];
    file.read(tmp_sto,col[colnum]);
    return true;
}

int DbDemoFileOperate::Getsiz(int col_num){
    if(col_num>colnum||col_num<=0)return 0;
    return col[col_num]-col[col_num-1];
}
int DbDemoFileOperate::Getst(int col_num){
    if(col_num>colnum||col_num<=0)return 0;
    return col[col_num-1];
}

int DbDemoFileOperate::GetcurrId()
{
    return currId;
}

void DbDemoFileOperate::reOpen()
{
    file.close();
    file.open(fileName, ios::ate|ios::in|ios::out);
    file.close();
    file.open(fileName, ios::ate|ios::in|ios::out);
}

DbDemoFileOperate::~DbDemoFileOperate()
{
    file.close();
}

bool Getmulti(DbDemoFileOperate *f1, int from, DbDemoFileOperate *f2, int tar, char *file3){
    bool find_rel=0;
    if(f1->Getsiz(from)!=f2->Getsiz(tar))return find_rel;
    for(int i=1;i<=f1->Getfile_num();i++){
        f1->Getbynum(i);
        for(int j=1;j<=f2->Getfile_num();j++){
            int ll=f1->Getsiz(from);
            f2->Getbynum(j);
            bool ook=1;
            for(int k=0;k<ll;k++){
                if(*(f1->Gettmp_sto()+f1->Getst(from)+k)!=*(f2->Gettmp_sto()+f2->Getst(tar)+k)){
                    ook=0;
                    break;
                }
            }
            if(ook){
                if(!find_rel){
                    find_rel=1;
                    f2->Query(f2->Gettmp_sto(),1,file3);
                }
                else{
                    DbDemoFileOperate f3(file3);
                    f3.FileWrite(f2->Gettmp_sto(),-1,1);
                    f3.~DbDemoFileOperate();
                }
            }
        }
    }
    return find_rel;
}

Books::Books(int tid, QString tname, int tamount, int tleft, QString tauthor, QString tpress, QString tisbn):DbDemo(tid){
    Setname(tname);
    Setamount(tamount);
    Setleft(tleft);
    Setauthor(tauthor);
    Setpress(tpress);
    Setisbn(tisbn);
    my_cache=new char[sizeof(id)+sizeof(name)+sizeof(amount)+sizeof(left)+sizeof(author)+sizeof(press)+sizeof(isbn)];
}
Books::Books(char *tmp){
    id=*((int*)tmp);
    tmp+=sizeof(int);
    for(int i=0;i<50;i++){
        name[i]=*tmp;
        tmp++;
    }
    amount=*((int *)tmp);
    tmp+=sizeof(int);
    left=*((int *)tmp);
    tmp+=sizeof(int);
    for(int i=0;i<20;i++){
        author[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<20;i++){
        press[i]=*tmp;my_cache=new char[sizeof(id)+sizeof(name)+sizeof(amount)+sizeof(left)+sizeof(author)+sizeof(press)+sizeof(isbn)];
        tmp++;
    }
    for(int i=0;i<20;i++){
        isbn[i]=*tmp;
        tmp++;
    }
    my_cache=new char[sizeof(id)+sizeof(name)+sizeof(amount)+sizeof(left)+sizeof(author)+sizeof(press)+sizeof(isbn)];
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

int Books::Getleft(){
    return left;
}

void Books::Setleft(int tleft){
    left=tleft;
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

char *Books::Getmy_cache(){
    char *cur_c=my_cache;
    char *tt=(char *)(&id);
    for(int i=0;i<(int)sizeof(id);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char *)(name);
    for(int i=0;i<(int)sizeof(name);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char *)(&amount);
    for(int i=0;i<(int)sizeof(amount);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char *)(&left);
    for(int i=0;i<(int)sizeof(amount);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(author);
    for(int i=0;i<(int)sizeof(author);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(press);
    for(int i=0;i<(int)sizeof(press);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(isbn);
    for(int i=0;i<(int)sizeof(isbn);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    return my_cache;
}

Bookcopy::Bookcopy(int tid,int tbookid,int tlend):DbDemo(tid){
    bookid=tbookid;
    lend=tlend;
    my_cache=new char[sizeof(int)*3];
}

Bookcopy::Bookcopy(char *tmp){
    id=*((int *)tmp);
    tmp+=sizeof(int);
    bookid=*((int *)tmp);
    tmp+=sizeof(int);
    lend=*((int *)tmp);
    my_cache=new char[sizeof(int)*3];
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

char *Bookcopy::Getmy_cache(){
    char *cur_c=my_cache;
    char *tt=(char*)(&id);
    for(int i=0;i<(int)sizeof(id);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char *)(&bookid);
    for(int i=0;i<(int)sizeof(bookid);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char *)(&lend);
    for(int i=0;i<(int)sizeof(lend);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    return my_cache;
}

BookKinds::BookKinds(char *tmp){
    id=*((int*)tmp);
    tmp+=sizeof(int);
    for(int i=0;i<20;i++){
        kindName[i]=*tmp;
        tmp++;
    }
    my_cache=new char[sizeof(id)+sizeof(kindName)];
}

BookKinds::BookKinds(int tid,QString tkindName):DbDemo(tid){
    SetkindName(tkindName);
    my_cache=new char[sizeof(id)+sizeof(kindName)];
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

char *BookKinds::Getmy_cache(){
    char *cur_c=my_cache;
    char *tt=(char*)(&id);
    for(int i=0;i<(int)sizeof(id);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=kindName;
    for(int i=0;i<(int)sizeof(kindName);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    return my_cache;
}

Classification::Classification(int tid,int tbookid,int tkindid):DbDemo(tid){
    bookid=tbookid;
    kindid=tkindid;
    my_cache=new char[sizeof(int)*3];
}

Classification::Classification(char *tmp){
    id=*((int*)tmp);
    tmp+=sizeof(int);
    bookid=*((int *)tmp);
    tmp+=sizeof(int);
    kindid=*((int *)tmp);
    my_cache=new char[sizeof(int)*3];
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

char *Classification::Getmy_cache(){
    char *cur_c=my_cache;
    char *tt=(char*)(&id);
    for(int i=0;i<(int)sizeof(id);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char *)(&bookid);
    for(int i=0;i<(int)sizeof(bookid);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char *)(&kindid);
    for(int i=0;i<(int)sizeof(kindid);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    return my_cache;
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
    my_cache=new char[sizeof(id)+sizeof(account)+sizeof(password)+sizeof(name)+sizeof(sex)+sizeof(email)+sizeof(phone)+sizeof(age)+sizeof(birth)];
}
Persons::Persons(char *tmp){
    id=*((int*)tmp);
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
    my_cache=new char[sizeof(id)+sizeof(account)+sizeof(password)+sizeof(name)+sizeof(sex)+sizeof(email)+sizeof(phone)+sizeof(age)+sizeof(birth)];
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

char *Persons::Getmy_cache(){
    char *cur_c=my_cache;
    char *tt=(char*)(&id);
    for(int i=0;i<(int)sizeof(id);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=account;
    for(int i=0;i<(int)sizeof(account);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=password;
    for(int i=0;i<(int)sizeof(password);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=name;
    for(int i=0;i<(int)sizeof(name);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&sex);
    for(int i=0;i<(int)sizeof(sex);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=email;
    for(int i=0;i<(int)sizeof(email);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=phone;
    for(int i=0;i<(int)sizeof(phone);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&age);
    for(int i=0;i<(int)sizeof(age);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&birth);
    for(int i=0;i<(int)sizeof(birth);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    return my_cache;
}

Borrows::Borrows(char *tmp){
    id=*((int*)tmp);
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
    my_cache=new char[sizeof(id)+sizeof(studentId)+sizeof(bookId)+sizeof(firstTime)+sizeof(ifLend)+sizeof(lastTime)+sizeof(lastTime)+sizeof(ifReturn)];
}

Borrows::Borrows(int tid,int tstudentId,int tbookId,QDate tfirstTime,int tifLend,QDate tlastTime,int tifReturn):DbDemo(tid){
    SetstudentId(tstudentId);
    SetbookId(tbookId);
    SetfirstTime(tfirstTime);
    SetifLend(tifLend);
    SetlastTime(tlastTime);
    SetifReturn(tifReturn);
    my_cache=new char[sizeof(id)+sizeof(studentId)+sizeof(bookId)+sizeof(firstTime)+sizeof(ifLend)+sizeof(lastTime)+sizeof(lastTime)+sizeof(ifReturn)];
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

char *Borrows::Getmy_cache(){
    char *cur_c=my_cache;
    char *tt=(char*)(&id);
    for(int i=0;i<(int)sizeof(id);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&studentId);
    for(int i=0;i<(int)sizeof(studentId);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&bookId);
    for(int i=0;i<(int)sizeof(bookId);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&firstTime);
    for(int i=0;i<(int)sizeof(firstTime);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&ifLend);
    for(int i=0;i<(int)sizeof(ifLend);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&lastTime);
    for(int i=0;i<(int)sizeof(lastTime);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=(char*)(&ifReturn);
    for(int i=0;i<(int)sizeof(ifReturn);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    return my_cache;
}

Admins::Admins(int tid, QString taccount,QString tpassword):DbDemo(tid){
    Setaccount(taccount);
    Setpassword(tpassword);
    my_cache=new char[sizeof(int)+sizeof(account)+sizeof(password)];
}

Admins::Admins(char *tmp){
    id=*((int*)tmp);
    tmp+=sizeof(int);
    for(int i=0;i<20;i++){
        account[i]=*tmp;
        tmp++;
    }
    for(int i=0;i<20;i++){
        password[i]=*tmp;
        tmp++;
    }
    my_cache=new char[sizeof(int)+sizeof(account)+sizeof(password)];
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

char *Admins::Getmy_cache(){
    char *cur_c=my_cache;
    char *tt=(char*)(&id);
    for(int i=0;i<(int)sizeof(id);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=account;
    for(int i=0;i<(int)sizeof(account);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    tt=password;
    for(int i=0;i<(int)sizeof(password);i++){
        *cur_c=*tt;
        cur_c++;
        tt++;
    }
    return my_cache;
}
