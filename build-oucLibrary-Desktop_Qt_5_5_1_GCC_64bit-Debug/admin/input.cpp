#include <bits/stdc++.h>
using namespace std;
int main()
{
	fstream file;
	file.open("./admin.dat", ios::out);
	if(file.is_open())
		cout<<"open success!"<<endl;
	int currId=1;
	file.write((char *)(&currId),sizeof(int));
	int colnum=3;
	file.write((char *)(&colnum),sizeof(int));
	int col[4]={(colnum+3)*sizeof(int),(colnum+4)*sizeof(int),(colnum+4)*sizeof(int)+20,(colnum+4)*sizeof(int)+40};
	for(int i=0;i<=colnum;i++)
		file.write((char *)(&col[i]),sizeof(int));
	return 0;
}
