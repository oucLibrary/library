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

bool Books::Getlend(){
    return lend;
}

void Books::Setlend(bool tmp){
    lend=tmp;
}

char *Books::Getauthor(){
    return author;
}

void Books::Setauthor(char *tmp){
    strcpy(author,tmp);
}

char *Books::Getpress(){
    return press;
}

void Books::Setpress(char *tmp){
    strcpy(press,tmp);
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

Persons::Persons(int id, string name, char account[], char password[], char sex,
    char email[], char phone[], int age, QDate birth): DbDemo(id, name), sex(sex),age(age),birth(birth)
{
    for(int i=0;i<20;i++)
    {
        this->account[i] = account[i];
        this->password[i] = password[i];
    }
    for(int i=0;i<50;i++)
        this->email[i] = email[i];
    for(int i=0;i<15;i++)
        this->phone[i] = phone[i];
}

char *Persons::Getaccount(){
    return account;
}

void Persons::Setaccount(char *tmp){
    strcpy(account,tmp);
}
char *Persons::Getpassword(){
    return password;
}
void Persons::Setpassword(char *tmp){
    strcpy(password,tmp);
}
bool Persons::Getsex(){
    return sex;
}

void Persons::Setsex(bool tmp){
    sex=tmp;
}
char *Persons::Getemail(){
    return email;
}

void Persons::Setemail(char *tmp){
    strcpy(email,tmp);
}

char *Persons::Getphone(){
    return phone;
}

void Persons::Setphone(char *tmp){
    strcpy(phone,tmp);
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

bool Borrows::GetifLend(){
    return ifLend;
}

void Borrows::SetifLend(bool tmp){
    ifLend=tmp;
}

QDate Borrows::GetlastTime(){
    return lastTime;
}

void Borrows::SetlastTime(QDate tmp){
    lastTime=tmp;
}

bool Borrows::GetifReturn(){
    return ifReturn;
}

void Borrows::SetifReturn(bool tmp){
    ifReturn=tmp;
}

Admins::Admins(int id, string name, char account[20], char password[20]): DbDemo(id, name)
{
    for(int i=0; i<20; i++)
    {
        this->account[i] = account[i];
        this->password[i] = password[i];
    }
}

char *Admins::Getaccount(){
    return account;
}

void Admins::Setaccount(char *tmp){
    strcpy(account,tmp);
}

char *Admins::Getpassword(){
    return password;
}

void Admins::Setpassword(char *tmp){
    strcpy(password,tmp);
}
