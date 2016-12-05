#include <bits/stdc++.h>
using namespace std;
int main()
{
	fstream file;
	file.open("user.dat", ios::out);
	if(file.is_open())
		cout<<"open success!"<<endl;
	int currId=1;
	file.write((char *)(&currId),sizeof(int));
	int colnum=9;
	file.write((char *)(&colnum),sizeof(int));
	int col[10]={(colnum+3)*sizeof(int),(colnum+4)*sizeof(int),(colnum+4)*sizeof(int)+50,(colnum+4)*sizeof(int)+70,(colnum+4)*sizeof(int)+90,(colnum+4)*sizeof(int)+91,(colnum+4)*sizeof(int)+141,(colnum+4)*sizeof(int)+156,(colnum+5)*sizeof(int)+156,(colnum+5)*sizeof(int)+164};
	for(int i=0;i<=colnum;i++)
		file.write((char *)(&col[i]),sizeof(int));
	return 0;
}
