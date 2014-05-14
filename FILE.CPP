#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
void main()
{
clrscr();
int i;
ofstream out("chars", ios::out || ios::binary);
if(!out)
cout<<" cannot open the file..."<<"\n";
for( i=0;i<256;i++)
out<<char(i);
out.close();
ifstream in("chars", ios::in);
char ch;
while(in)
{
in.get(ch);
cout<<ch;
}
in.close();
getch();
}