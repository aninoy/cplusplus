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
enum tokentype{ MAIN=10,INT,CHAR,IF,ELSE,WHILE,FOR,leftparen=20,rightparen,leftbrace,rightbrace,leftsq,rightsq,comma,semicolon,assign,equal,notequal,lesseq,greeq,less,gre,plus,minus,mul,divide,percent,not,IDEN=50,NUM=51,eof=90,UNK=100};
struct token
{
 char name[30];
 tokentype t;
 int lineno;
};
struct sym
{
 char name[30];
 char type[10];
};
token ost[]={   {"main",MAIN},
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
token T[100];
sym S[100];
int z=0;
int check(char n[10])
{
 for(int i=0;i<z;i++)
  if(!strcmp(n,S[i].name))
   return 1;
 return 0;
}
char datatype[10]="undefined";
int nt=0;
char miss[20];
int stmtflag[100],no=-1;

int program();
int declarations();
int statlist();
int dtype();
int idlist();
int stmt();
int assstat();
int decstat();
int loopstat();
int term();
int expn();
int simexpn();
int factor();
int seprime();
int eprime();
int tprime();
int relop();
int addop();
int mulop();

int tprime()
{
 if(mulop())
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
 else
  return 1;
}
int seprime()
{
 if(addop())
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
 else
  return 1;
}
int eprime()
{
 if(relop())
 {
  if(simexpn())
   return 1;
  else
   return 0;
 }
 else
  return 1;
}
int mulop()
{
 if(T[nt].t==37 || T[nt].t==38 || T[nt].t==39)
 {
  nt++;
  return 1;
 }
 strcpy(miss,"mathematical operator");
 return 0;
}
int addop()
{
 if(T[nt].t==35 || T[nt].t==36)
 {
  nt++;
  return 1;
 }
 strcpy(miss,"mathematical operator");
 return 0;
}
int relop()
{
 switch(T[nt].t)
 {
  case 29:
  case 30:
  case 31:
  case 32:
  case 33:
  case 34:nt++;
		  return 1;
  default: strcpy(miss,"relational operator");
		   return 0;
 }
}
int term()
{
 if(factor())
 {
  if(tprime())
   return 1;
 }
 return 0;
}
int factor()
{
 if(T[nt].t==50 || T[nt].t==51)
 {
  nt++;
  return 1;
 }
 else
 {
  strcpy(miss,"identifier or number");
  return 0;
 }
}

int simexpn()
{
 if(term())
 {
  if(seprime())
   return 1;
 }
 return 0;
}
int expn()
{
 if(simexpn())
 {
  if(eprime())
   return 1;
 }
 return 0;
}
int loopstat()
{
 if(T[nt++].t==15)
 {
  stmtflag[no]=1;
  if(T[nt++].t==20)
  {
   if(expn())
   {
	if(T[nt++].t==21)
	{
	 if(stmt())
	  return 1;
	 else
	  return 0;
	}
	else
	{
	 strcpy(miss,")");
	 return 0;
	}
   }
   else
	return 0;
  }
  else
  {
   strcpy(miss,"(");
   return 0;
  }
 }
 else
 {
  nt--;
  if(T[nt++].t==16)
  {
   stmtflag[no]=1;
   if(T[nt++].t==20)
   {
	if(assstat())
	{
	 if(T[nt++].t==27)
	 {
	  if(expn())
	  {
	   if(T[nt++].t==27)
	   {
		if(assstat())
		{
		 if(T[nt++].t==21)
		 {
		  if(stmt())
		   return 1;
		 }
		 else
		 {
		  strcpy(miss,")");
		  return 0;
		 }
		}
	   }
	   else
	   {
		if(stmtflag[no]==0)
		 strcpy(miss,";");
		return 0;
	   }
	  }
	 }
	 strcpy(miss,";");
	 return 0;
	}
   }
   else
   {
	if(stmtflag[no]==1)
	 strcpy(miss,"(");
	return 0;
   }
  }
  else
  {
   nt--;
   return 0;
  }
 }
}
int dprime()
{
 if(T[nt++].t==14)
 {
  if(stmt())
   return 1;
  else
   return 0;
 }
 else
 {
  nt--;
  return 1;
 }
}
int assstat()
{
 if(T[nt++].t==50)
 {
  stmtflag[no]=1;
  if(T[nt++].t==28)
  {
   if(expn())
	return 1;
   else
	return 0;
  }
  else
  {
   strcpy(miss,"=");
   return 0;
  }
 }
 else
 {
  nt--;
  return 0;
 }
}

int stmt()
{
 stmtflag[++no]=0;
 if(assstat() || decstat() || loopstat())
 {
  no--;
  return 1;
 }
 else
  return 0;
}

int decstat()
{
 if(T[nt++].t==13)
 {
  stmtflag[no]=1;
  if(T[nt++].t==20)
  {
   if(expn())
   {
	if(T[nt++].t==21)
	{
	 if(stmt())
	 {
	  if(dprime())
	   return 1;
	  else
	   return 0;
	 }
	 else
	  return 0;
	}
	else
	{
	 strcpy(miss,")");
	 return 0;
	}
   }
   else
	return 0;
  }
  else
  {
   strcpy(miss,"(");
   return 0;
  }
 }
 else
 {
  nt--;
  return 0;
 }
}
int idlist()
{
 if(T[nt++].t==50)
 {
  if(T[nt++].t==26)
  {
   if(idlist())
	return 1;
   else
   return 0;
  }
  else
  {
   nt--;
   return 1;
  }
 }
 else
 {
  strcpy(miss,"identifier");
  return 0;
 }
}
int dtype()
{
 if(T[nt].t==11 || T[nt].t==12)
 {
  nt++;
  return 1;
 }
 else
 {
  strcpy(miss,"datatype");
  return 0;
 }
}
int statlist()
{
 if(stmt())
 {
  if(T[nt++].t==27)
  {
   if(statlist())
	return 1;
   else
	return 0;
  }
  else
  {
   strcpy(miss,";");
   return 0;
  }
 }
 else
 {
  if(stmtflag[no]==0)
   return 1;
  else
   return 0;
 }
}
int declarations()
{
 if(dtype())
 {
  if(idlist())
  {
   if(T[nt++].t==27)
   {
	if(declarations())
	 return 1;
	else
	 return 0;
   }
   else
   {
	strcpy(miss,";");
	return 0;
   }
  }
  else
   return 0;
 }
 else
  return 1;
}
int program()
{
 if(T[nt++].t==10)
 {
  if(T[nt++].t==20)
  {
   if(T[nt++].t==21)
   {
	if(T[nt++].t==22)
	{
	 if(declarations())
	 {
	  if(statlist())
	  {
	   if(T[nt++].t==23)
		return 1;
	   else
	   {
		strcpy(miss,"}");
		return 0;
	   }
	  }
	  else
	   return 0;
	 }
	 else
	  return 0;
	}
	else
	{
	 strcpy(miss,"{");
	 return 0;
	}
   }
   else
   {
	strcpy(miss,")");
	return 0;
   }
  }
  else
  {
   strcpy(miss,"(");
   return 0;
  }
 }
 else
 {
  strcpy(miss,"main");
  return 0;
 }
}
void main()
{

 //// LEXICAL ANALYZER
 int x=0,i=0,flag=1,flag1=0,symflag=0,symflag2=0,line=1;
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
  fd.get(ch);
  while(ch==' ')
   fd.get(ch);
  while(!fd.eof())
  {
   switch(ch)
   {
	case ' ': if(flag==-1)
		  {
		   T[x].lineno=line;
		   T[x++].name[i++]='\0';
		   flag=1;
		  }
		  i=0;
		  fd.get(ch);
		  while(ch==' ')
		   fd.get(ch);
		  break;
	case '\n': if(flag==-1)
		   {
			T[x].lineno=line;
			T[x++].name[i++]='\0';
			flag=1;
		   }
		   fd.get(ch);
		   while(ch==' ')
			fd.get(ch);
		   i=0;
		   line++;
		   break;
	case '\t': if(flag==-1)
		   {
			T[x].lineno=line;
			T[x++].name[i]='\0';
			flag=1;
		   }
		   fd.get(ch);
		   while(ch==' ')
			fd.get(ch);
		   i=0;
		   break;
	case '\0': if(flag==-1)
		   {
			T[x].lineno=line;
			T[x++].name[i]='\0';
			flag=1;
		   }
		   fd.get(ch);
		   while(ch==' ')
			fd.get(ch);
		   i=0;
		   break;
	default: symflag=0;
		 symflag2=0;
		 if(flag==-1)
		 {
		  for(int j=7;j<28;j++)
		  {
		   if(ost[j].name[0]==ch)
		   {
			for(int p=7;p<28;p++)
			{
			 if(T[x].name[i-1]==ost[p].name[0])
			 {
			  symflag2=1;
			  if(p>=15 && p<=18)
			  {
			   if(j==15)
			   {
			T[x].name[i++]=ch;
			T[x].lineno=line;
			T[x++].name[i]='\0';
			i=0;flag=1;
			   }
			   else
			   {
			T[x].name[i]='\0';
			T[x++].lineno=line;
			i=0;flag=-1;
			T[x].name[i++]=ch;
			   }
			  }
			  else
			  {
			   T[x].lineno=line;
			   T[x++].name[i]='\0';i=0;flag=-1;
			   T[x].name[i++]=ch;
			  }
			  break;
			 }
			}
			if(symflag2==0)
			{
			 T[x].name[i]='\0';
			 T[x++].lineno=line;
			 i=0;flag=-1;
			 T[x].name[i++]=ch;
			}
			symflag=1;
			break;
		   }
		  }
		  if(symflag==0)
		  {
		   symflag2=0;
		   for(int p=7;p<28;p++)
		   {
			if(ost[p].name[0]==T[x].name[i-1])
			{
			 T[x].name[i]='\0';
			 T[x++].lineno=line;
			 i=0;flag=-1;
			 T[x].name[i++]=ch;
			 symflag2=1;
			}
		   }
		   if(symflag2==0)
		   {
			flag=-1;
			T[x].name[i++]=ch;
		   }
		  }
		 }
		 else
		 {
		  flag=-1;
		  T[x].name[i++]=ch;
		 }
		 fd.get(ch);
   }
  }
  T[x].lineno=line;
 }
 int l=-1;
 for(i=0;i<=x;i++)
 {
  int flag=0;
  for(int j=0;j<28;j++)
  {
   if(!strcmpi(T[i].name,ost[j].name))
   {
	flag=1;
	T[i].t=ost[j].t;
	break;
   }
  }
  if(j==1 || j==2)
  {
   l=T[i].lineno;
   strcpy(datatype,T[i].name);
  }
  if(flag==0)
  {
   if(isdigit(T[i].name[0]))
   {
	flag1=0;
	for(int j=1;j<strlen(T[i].name);j++)
	{
	 if(!isdigit(T[i].name[j]))
	 {
	  flag1=-1;
	  break;
	 }
	}
	if(flag1==0)
	 T[i].t=NUM;
	else
	 T[i].t=UNK;
   }
   else
   {
	if(isalpha(T[i].name[0]))
	{
	 flag1=0;
	 for(int j=1;j<strlen(T[i].name);j++)
	 {
	  if(!isalpha(T[i].name[j]) && !isdigit(T[i].name[j]) && T[i].name[j]!='_')
	  {
	   flag1=-1;
	   break;
	  }
	 }
	 if(flag1==0)
	 {
	  T[i].t=IDEN;
	  if(!check(T[i].name))
	  {
	   strcpy(S[z].name,T[i].name);
	   if(l==T[i].lineno)
	strcpy(S[z++].type,datatype);
	   else
	strcpy(S[z++].type,"undefined");
	  }
	 }
	 else
	  T[i].t=UNK;
	}
	else
	 T[i].t=UNK;
   }
  }
 }
 for(i=1;i<=line;i++)
 {
  cout<<"Line No. "<<i<<":-\n\n";
  cout<<"\nToken Name\tToken Value\tLine No.\n";
  for(int j=0;j<=x;j++)
  {
   if(i==T[j].lineno)
   cout<<T[j].name<<"\t\t"<<T[j].t<<"\t\t"<<T[j].lineno<<"\n";
  }
  cout<<"\nPress Any Key To Continue...";
  getch();
  clrscr();
 }
 cout<<"Symbol Table :-\n\n";
 for(i=0;i<z;i++)
  cout<<S[i].name<<"\t"<<S[i].type<<"\n";
 getch();

 //// PARSER
 clrscr();
 cout<<"......:::::ERRORS:::::.......\n\n";
 if(program())
  cout<<"No Errors";
 else
  cout<<"Error in Line No. "<<T[nt-2].lineno<<"==> "<<miss<<" expected.\n";
 getch();
}