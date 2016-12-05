#include <bits/stdc++.h>
using namespace std;
int main()
{
	fstream file;
	file.open("person.dat", ios::out);
	if(file.is_open())
		cout<<"open success!"<<endl;
	int currId=1;
	file.write((char *)(&currId),sizeof(int));
	int colnum=9;
	file.write((char *)(&colnum),sizeof(int));
	int col[10]={(colnum+3)*sizeof(int),(colnum+4)*sizeof(int),(colnum+4)*sizeof(int)+20,(colnum+4)*sizeof(int)+40,(colnum+4)*sizeof(int)+60,(colnum+5)*sizeof(int)+60,(colnum+5)*sizeof(int)+110,(colnum+5)*sizeof(int)+125,(colnum+6)*sizeof(int)+125,(colnum+6)*sizeof(int)+133};
	for(int i=0;i<=colnum;i++)
		file.write((char *)(&col[i]),sizeof(int));
	return 0;
}
