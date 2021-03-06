#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<dos.h>
ifstream fd;
int tnp=0,line=1;
enum tokentype{ MAIN=10,INT,CHAR,IF,ELSE,WHILE,FOR,SWITCH,CASE,leftparen=20,rightparen,leftbrace,rightbrace,leftsq,rightsq,comma,colon,semicolon,assign,equal,notequal,lesseq,greeq,less,gre,plus,minus,mul,divide,percent,not,IDEN=50,NUM=51,eof=90,UNK=100};
struct token
{
 char name[30];
 tokentype t;
 int lineno;
}T;
struct sym
{
 char name[30];
 char type[10];
 int flag;
};
token ost[]={   {"main",MAIN},
				{"int",INT},
				{"char",CHAR},
				{"for",FOR},
				{"while",WHILE},
				{"if",IF},
				{"else",ELSE},
				{"switch",SWITCH},
				{"case",CASE},
				{"(",leftparen},
				{")",rightparen},
				{"{",leftbrace},
				{"}",rightbrace},
				{"[",leftsq},
				{"]",rightsq},
				{",",comma},
				{":",colon},
				{";",semicolon},
				{"=",assign},
				{"!",not},
				{"<",less},
				{">",gre},
				{"==",equal},
				{"!=",notequal},
				{"<=",lesseq},
				{">=",greeq},
				{"+",plus},
				{"-",minus},
				{"/",divide},
				{"%",percent},
				{"*",mul}
			};
char ch;
int scanner(void)
{
 int symflag=0,flag=0,tover=0;
 fd.get(ch);
 if(fd.eof())
 {
  //cout<<"Reached the end of file\n";
  T.t=100;
  return -1;
 }
 while(ch==' '|| ch=='\n'|| ch=='\0' || ch=='\t'|| fd.eof())
 {
  if(ch=='\n')line++;
  if(fd.eof())return -1;
  fd.get(ch);
 }
 while(1)
 {
  switch(ch)
  {
   case ' ': if(flag==1)
			 {
			  T.name[tnp]='\0';
			  T.lineno=line;
			  tnp=0;tover=1;
			 }
			 break;
   case '\n': if(flag==1)
			  {
			   T.name[tnp]='\0';
			   T.lineno=line;
			   line++;
			   tnp=0;tover=1;
			  }
			  break;
   case '\t': if(flag==1)
			  {
			   T.name[tnp]='\0';
			   T.lineno=line;
			   tnp=0;tover=1;
			  }
			  break;
   default:  for(int i=9;i<31;i++)
			 {
			  if(ost[i].name[0]==ch)
			  {
			   //T.t=ost[i].t;
			   symflag=1;
			   break;
			  }
			 }
			 if(symflag==1)
			 {
			  if(i>=17 && i<=20)
			  {
			   if(flag==0)
			   {
				T.name[tnp++]=ch;
				fd.get(ch);
				if(ch=='=')
				{
				 T.name[tnp++]=ch;
				 T.name[tnp]='\0';
				 T.lineno=line;
				 tnp=0;tover=1;
				}
				else
				{
				 T.name[tnp]='\0';
				 tnp=0;tover=1;
				 T.lineno=line;
				 int x=fd.tellg();
				 fd.seekg(x-1);
				}
			   }
			   else
			   {
				T.name[tnp]='\0';
				tnp=0;tover=1;
				T.lineno=line;
				int x=fd.tellg();
				 fd.seekg(x-1);
			   }
			  }
			  else
			  {
			   if(flag==0)
			   {
				T.name[tnp++]=ch;
				T.name[tnp]='\0';
				tnp=0;tover=1;
				T.lineno=line;
			   }
			   else
			   {
				T.name[tnp]='\0';
				tnp=0;
				tover=1;
				T.lineno=line;
				int x=fd.tellg();
				fd.seekg(x-1);
			   }
			  }
			 }
			 else
			 {
			  flag=1;
			  T.name[tnp++]=ch;
			 }


  }
  if(tover==1)
   break;
  fd.get(ch);
 }
 int flag2=0,flag1=-1;
 for(int j=0;j<31;j++)
 {
  if(!strcmpi(T.name,ost[j].name))
  {
   flag2=1;
   T.t=ost[j].t;
   break;
  }
 }
 if(flag2==0)
 {
  if(isdigit(T.name[0]))
  {
   flag1=0;
   for(int j=1;j<strlen(T.name);j++)
   {
	if(!isdigit(T.name[j]))
	{
	 flag1=-1;
	 break;
	}
   }
   if(flag1==0)
	T.t=NUM;
   else
	T.t=UNK;
  }
  else
  {
   if(isalpha(T.name[0]))
   {
	flag1=0;
	for(int j=1;j<strlen(T.name);j++)
	{
	 if(!isalpha(T.name[j]) && !isdigit(T.name[j]) && T.name[j]!='_')
	 {
	  flag1=-1;
	  break;
	 }
	}
	if(flag1==0)
	 T.t=IDEN;
	else
	 T.t=UNK;
   }
   else
	 T.t=UNK;
  }
 }
 return 1;
}

int exp();
int list();
int ret=0;

void main()
{
 char file[20],ch;
 clrscr();
 cout<<"Enter the file name: ";
 gets(file);
 fd.open(file,ios::nocreate);
 if(!fd)
 {
  cout<<"This file doesn't exist!\n";
  getch();
  exit(0);
 }
 if(exp())
 {
  ret=0;
  ret=scanner();
  if(ret==-1)
  {
   cout<<"Syntactically Correct Code\n";
   fd.get(ch);
   //cout<<"eof: "<<ch;
  }
  else
   cout<<"Error: extra symbols";
  getch();
  fd.close();
 }
}

int exp()
{
 scanner();
 if(T.t==20)
 {
  if(list())
  {
   ret=0;
   ret=scanner();
   if(ret!=-1)
   {
	if(T.t==21)
	 return 1;
	else
	{
	 cout<<") missing";
	 getch();
	 exit(0);
	}
   }
   else
   {
	cout<<") missing";
	getch();
	exit(0);
   }
  }
 }
 else
 {
  if(T.t==50)
   return 1;
  else
  {
   cout<<"( or identifier missing";
   getch();
   exit(0);
  }
 }
}

int list()
{
 if(exp())
 {
  scanner();
  if(T.t==comma)
  {
   if(list())
	return 1;
  }
  else
  {
   int x=fd.tellg();
   fd.seekg(x-1);
   return 1;
  }
 }
 else
  return 0;
}
