#include <bits/stdc++.h>
using namespace std;
int main()
{
	fstream file;
	file.open("books.dat", ios::out);
	if(file.is_open())
		cout<<"open success!"<<endl;
	int currId=1;
	file.write((char *)(&currId),sizeof(int));
	int colnum=7;
	file.write((char *)(&colnum),sizeof(int));
	int col[8]={(colnum+3)*sizeof(int),(colnum+4)*sizeof(int),(colnum+4)*sizeof(int)+50,(colnum+5)*sizeof(int)+50,(colnum+6)*sizeof(int)+50,(colnum+6)*sizeof(int)+70,(colnum+6)*sizeof(int)+90,(colnum+6)*sizeof(int)+110};
	for(int i=0;i<=colnum;i++)
		file.write((char *)(&col[i]),sizeof(int));
	return 0;
}
