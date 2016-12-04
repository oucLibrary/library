#include <bits/stdc++.h>
using namespace std;
int main()
{
	fstream file;
	file.open("./admin.dat", ios::out);
	if(file.is_open())
		cout<<"open success!"<<endl;
	int currId=0;
	file.write((char *)(&currId),sizeof(int));
	int colnum=4;
	file.write((char *)(&colnum),sizeof(int));
	int col[5]={(colnum+3)*sizeof(int),(colnum+4)*sizeof(int),(colnum+4)*sizeof(int)+50,(colnum+4)*sizeof(int)+70,(colnum+4)*sizeof(int)+90};
	for(int i=0;i<=colnum;i++)
		file.write((char *)(&col[i]),sizeof(int));
	return 0;
}
