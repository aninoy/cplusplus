#include<iostream.h>
#include<conio.h>
#include<ctype.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<fstream.h>
#include<stdlib.h>
enum tokentype{ MAIN=10,INT,CHAR,IF,ELSE,WHILE,FOR,leftparen=20,rightparen,leftbrace,rightbrace,leftsq,rightsq,comma,semicolon,assign,equal,notequal,lesseq,greeq,less,gre,plus,minus,mul,divide,percent,not,IDEN=50,NUM=51,eof=90,UNK=100};
struct token
{
 char name[10];
 tokentype t;
 int lineno;
}T;
token ost[]={
				{"main",MAIN},
				{"int",INT},
				{"char",CHAR},
				{"for",FOR},
				{"while",WHILE},
				{"if",IF},
				{"else",ELSE},
				{"(",leftparen},
				{")",rightparen},
				{"{",leftbrace},
				{"}",rightbrace},
				{"[",leftsq},
				{"]",rightsq},
				{",",comma},
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
void scanner();
int program();
int assstat();
int expn();
int simexpn();
int eprime();
int seprime();
int tprime();
int mulop();
int addop();
int relop();
int factor();
int term();
ofstream fs;
ifstream fd;
int line=1,tos=0;
char idcode[5],stack[10][10];
tokentype opcode,rel;
int mulop()
{
 scanner();
 if(T.t==mul || T.t==divide || T.t==percent)
 {
  opcode=T.t;
  return 1;
 }
 else
  return 0;
}
int addop()
{
 scanner();
 if(T.t==plus || T.t==minus)
 {
  opcode=T.t;
  return 1;
 }
 else
  return 0;
}
int relop()
{
 scanner();
 switch(T.t)
 {
  case less:
  case gre:
  case greeq:
  case lesseq:
  case equal:
  case notequal:rel=T.t;
				return 1;
  default: return 0;
 }
}
int factor()
{
 scanner();
 if(T.t==NUM || T.t==IDEN)
 {
  char val[10];
  strcpy(stack[++tos],T.name);
  return 1;
 }
 else
  return 0;
}
int tprime()
{
 if(mulop())
 {
  if(factor())
  {
   fs<<" MOV BX, "<<stack[tos--]<<"\n";
   fs<<" MOV AX, "<<stack[tos--]<<"\n";
   switch(opcode)
   {
	case mul: fs<<" MUL BX\n";
			  fs<<" MOV temp, AX\n";
			  break;
	case divide: fs<<" DIV BX\n";
				 fs<<" MOV temp, AL\n";
				 break;
	case percent: fs<<" DIV BX\n";
				  fs<<" MOV temp, AH\n";
				  break;
   }
   strcpy(stack[++tos],"temp");
   if(tprime())
	return 1;
   else
	return 0;
  }
  else
   return 0;
 }
 else
 {
  int x=strlen(T.name);
  fd.seekg(-x,ios::cur);
  return 1;
 }
}
int term()
{
 if(factor())
 {
  if(tprime())
   return 1;
  else
   return 0;
 }
 else
  return 0;
}
int seprime()
{
 if(addop())
 {
  if(term())
  {
   fs<<" MOV BX, "<<stack[tos--]<<"\n";
   fs<<" MOV AX, "<<stack[tos--]<<"\n";
   switch(opcode)
   {
	case plus: fs<<" ADD AX, BX\n";
			   fs<<" MOV temp, AX\n";
			   break;
	case minus: fs<<" SUB AX, BX\n";
				fs<<" MOV temp, AL\n";
				break;
   }
   strcpy(stack[++tos],"temp");
   if(seprime())
	return 1;
   else
	return 0;
  }
  else
   return 0;
 }
 else
 {
  int x=strlen(T.name);
  fd.seekg(-x,ios::cur);
  return 1;
 }
}
int eprime()
{
 if(relop())
 {
  if(simexpn())
  {
   fs<<" MOV BX, "<<stack[tos--]<<"\n";
   fs<<" MOV AX, "<<stack[tos--]<<"\n";
   fs<<" CMP AX, BX\n";
   switch(rel)
   {
	case less: fs<<" JL fstat\n fupd: ";break;
	case gre: fs<<" JG fstat\n fupd: ";break;
	case lesseq: fs<<" JLE fstat\n fupd: ";break;
	case greeq: fs<<" JGE fstat\n fupd: ";break;
	case equal: fs<<" JE fstat\n fupd: ";break;
	case notequal: fs<<" JNE fstat\n fupd: ";break;
   }
   return 1;
  }
  else
   return 0;
 }
 else
 {
  int x=strlen(T.name);
  fd.seekg(-x,ios::cur);
  return 1;
 }
}
int simexpn()
{
 if(term())
 {
  if(seprime())
   return 1;
  else
   return 0;
 }
 else
  return 0;
}
int expn()
{
 if(simexpn())
 {
  if(eprime())
   return 1;
  else
   return 0;
 }
 else
  return 0;
}
int assstat()
{
 scanner();
 if(T.t==IDEN)
 {
  strcpy(idcode,T.name);
  scanner();
  if(T.t==assign)
  {
   if(expn())
   {
	fs<<" MOV AX, "<<stack[tos--]<<"\n";
	fs<<" MOV "<<idcode<<", AX\n";
	return 1;
   }
   else
	return 0;
  }
  else
   return 0;
 }
 else
  return 0;
}
int program()
{
 scanner();
 if(T.t==FOR)
 {
  scanner();
  if(T.t==leftparen)
  {
   if(assstat())
   {
	scanner();
	if(T.t==semicolon)
	{
	 if(expn())
	 {
	  scanner();
	  if(T.t==semicolon)
	  {
	   if(assstat())
	   {
		scanner();
		if(T.t==rightparen)
		{
		 if(assstat())
		 {
		  scanner();
		  if(T.t==semicolon)
		   return 1;
		  else
		   return 0;
		 }
		 else
		  return 0;
		}
		else
		 return 0;
	   }
	   else
		return 0;
	  }
	  else
	   return 0;
	 }
	 else
	  return 0;
	}
	else
	 return 0;
   }
   else
	return 0;
  }
  else
   return 0;
 }
 else
  return 0;
}

void scanner()
{
 char ch;
 int flag=0,i=0,symflag=0,read=-1;
 while(!fd.eof())
 {
  fd.get(ch);
  switch(ch)
  {
   case '\0':
   case '\t':
   case ' ': if(flag==1)
			 {
			  T.name[i]='\0';
			  T.lineno=line;
			  i=0;flag=0;read=1;
			 }
			 //fd.get(ch);
			 break;
   case '\n':if(flag==1)
			 {
			  T.name[i]='\0';
			  T.lineno=line;
			  i=0;flag=0;read=1;
			 }
			 line++;
			 //fd.get(ch);
			 break;
   default:  for(int j=7;j<28;j++)
			 {
			  if(ost[j].name[0]==ch)
			  {
			   symflag=1;
			   break;
			  }
			 }
			 if(symflag==1)
			 {
			  if(flag==1)
			  {
			   flag=0;
			   T.name[i]='\0';
			   T.lineno=line;
			   read=1;
			   i=0;
			   fd.seekg(-1,ios::cur);
			  }
			  else
			  {
			   T.name[i++]=ch;
			   if(j>=15 && j<=18)
			   {
				symflag=0;
				fd.get(ch);
				for(j=7;j<28;j++)
				{
				 if(ost[j].name[0]==ch)
				 {
				  symflag=1;
				  break;
				 }
				}
				if(symflag==1 && j==15)
				 T.name[i++]=ch;
				else
				 fd.seekg(-1,ios::cur);
			   }
			   T.name[i]='\0';
			   T.lineno=line;
			   i=0;
			   flag=0;
			   read=1;
			  }
			 }
			 else
			 {
			  flag=1;read=0;
			  T.name[i++]=ch;
			  //fd.get(ch);
			 }
  }
  if(read==1)
   break;
 }
 if(flag==1)
 {
  T.lineno=line;
  T.name[i]='\0';
 }
 flag=0;
 for(i=0;i<28;i++)
 {
  if(strcmp(ost[i].name,T.name)==0)
  {
   T.t=ost[i].t;
   flag=1;
   break;
  }
 }
 if(flag==0)
 {
  if(isalpha(T.name[0]))
  {
   for(int j=1;j<strlen(T.name);j++)
   {
	if(!(isalpha(T.name[j]) || isdigit(T.name[j]) || T.name[j]=='_'))
	{
	 flag=1;
	 break;
	}
   }
   if(flag==1)
	T.t=UNK;
   else
	T.t=IDEN;
  }
  else if(isdigit(T.name[0]))
  {
   flag=0;
   for(int j=1;j<strlen(T.name);j++)
   {
	if(!isdigit(T.name[j]))
	{
	 flag=1;
	 break;
	}
   }
   if(flag==1)
	T.t=UNK;
   else
	T.t=NUM;
  }
  else
   T.t=UNK;
 }
}
void main()
{
 char file[20];
 fs.open("trycode.txt",ios::out);
 fs<<"code segment\n";
 clrscr();
 cout<<"Enter the file name: ";
 gets(file);
 fd.open(file,ios::in);
 if(!fd)
 {
  cout<<"This file doesn't exist!";
  getch();
  exit(0);
 }
 line=1;
 /*cout<<"....:::SCANNER OUTPUT:::....\n";
 cout<<"Name\t\tType\t\tLine No.\n\n";
 while(!fd.eof())
 {
  scanner();
  cout<<T.name<<"\t\t"<<T.t<<"\t\t"<<T.lineno<<"\n";
  getch();
 }*/
 if(program())
  cout<<"Program is syntactically correct.";
 else
  cout<<"Error in program at "<<T.lineno<<" with token "<<T.name;
 fs<<" MOV AH, 4CH\n INT 21H\ncode ends\n";
 fs.close();
 fd.close();
 getch();
}

