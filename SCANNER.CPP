#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
enum tokentype{IDENTIFIER=1,OPCODE,NUMBER,SIGN,COLON,COMMA,SEMICOLON,LEFTPAREN,RIGHTPAREN,LITERAL,ATSIGN,EQUAL,PERIOD,REGISTER,UNDEFINED,PSEUDOOPCODE};
struct token
{
 char name[10];
 tokentype t;
}T[100];
int x=-1;
void main()
{
 char file[20],ch;
 ifstream fd;
 clrscr();
 cout<<"Enter a file name: ";
 gets(file);
 fd.open(file,ios::nocreate);
 if(!fd)
 {
  cout<<"This file doesnt exist!\n";
  getch();
  exit(0);
 }
 else
 {
  while(!fd.eof())
  {
   int i=0;
   x++;
   fd.get(ch);
   while(ch!=' ' && ch!=',' && ch!='\0' && ch!='\n' && !fd.eof())
   {
	T[x].name[i++]=ch;
	fd.get(ch);
   }
   T[x].name[i]='\0';
   cout<<T[x].name<<"\n";
  }
 }
 getch();
}
