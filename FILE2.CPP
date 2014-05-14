#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
class sid
{
int goal,win;
public:
sid()
{
goal=0;
win=0;
}
void get()
{
cout<<" enter the no. of goals and wins.."<<"\n";
cin>>goal>>win;
}
void put()
{
cout<<goal<<"\t"<<win<<"\n";
}
int isequal(int g)
{
if(goal==g)
return 1;
else
return 0;
}
};
void main()
{
clrscr();
sid s;
ofstream out("temp.txt");
for(int i=0;i<3;i++)
{
s.get();
out.write((char*) &s, sizeof(sid));
}
out.close();
cout<<"printing contents of the file.."<<"\n";
ifstream in("temp.txt");
in.read((char*) &s, sizeof(sid));
while(in)
{
s.put();
in.read((char*) &s, sizeof(sid));
}
in.close();
cout<<" showing u a record of ur choice..."<<"\n";
int ch;
cin>>ch;
ifstream in1("temp.txt");
in1.seekg(sizeof(sid)*(ch-1));
in1.read((char*) &s, sizeof(sid));
s.put();

getch();
}
