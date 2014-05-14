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
 int flag;
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
int z=0,found=-1,misc=0;
int check(char n[10])
{
 for(int i=0;i<z;i++)
  if(!strcmp(n,S[i].name))
  {
   found=i;
   return 1;
  }
 return 0;
}
ofstream fs;
char typecode[2],idcode[10],factcode[10],fstopnd[10];
char datatype[10]="undefined";
int nt=0;
void convert()
{
 int len=strlen(T[nt].name);
 int num=0;
 char n[10];
 for(int i=len-1,j=0;i>=0;i--,j++)
  num+=(T[nt].name[i]-'0')*pow(10,j);
 n[0]='H';i=1;
 while(num!=0)
 {
  if(num%16<10)
   n[i++]=num%16+'0';
  else
  {
   switch(num%16)
   {
	case 10: n[i++]='A';break;
	case 11: n[i++]='B';break;
	case 12: n[i++]='C';break;
	case 13: n[i++]='D';break;
	case 14: n[i++]='E';break;
	case 15: n[i++]='F';break;
   }
  }
  num/=16;
 }
 n[i]='\0';
 for(i=strlen(n)-1,j=0;i>=0;i--,j++)
  factcode[j]=n[i];
}

char miss[20],stack[10][10];
int stmtflag[100],no=-1,tos=0,opflag=-1;

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
   if(T[nt-2].t==37)
   {
	fs<<" MOV BX, ";
	fs<<stack[tos--];
	fs<<"\n MOV AX, ";
	fs<<stack[tos--];
	fs<<"\n MUL BX\n MOV temp, AX\n";
	strcpy(stack[++tos],"temp");
   }
   else if(T[nt-2].t==38)
   {
	fs<<" MOV BX, ";
	fs<<stack[tos--];
	fs<<"\n MOV AX, ";
	fs<<stack[tos--];
	fs<<"\n DIV BX\n";
	fs<<" MOV temp, AL\n";
	strcpy(stack[++tos],"temp");
   }
   else if(T[nt-2].t==39)
   {
	fs<<" MOV BX, ";
	fs<<stack[tos--];
	fs<<"\n MOV AX, ";
	fs<<stack[tos--];
	fs<<"\n DIV BX\n";
	fs<<" MOV temp, AH\n";
	strcpy(stack[++tos],"temp");
   }
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
  opflag=T[nt-1].t;
  if(term())
  {
   if(opflag==35)
   {
	fs<<" MOV BX, ";
	fs<<stack[tos--];
	fs<<"\n MOV AX, ";
	fs<<stack[tos--];
	fs<<"\n ADD AX, BX\n MOV temp, AX\n";
	strcpy(stack[++tos],"temp");
   }
   else if(opflag==36)
   {
	fs<<" MOV BX, ";
	fs<<stack[tos--];
	fs<<"\n MOV AX, ";
	fs<<stack[tos--];
	fs<<"\n SUB AX, BX\n MOV temp, AX\n";
	strcpy(stack[++tos],"temp");
   }
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
  if(T[nt].t==50)
  {
   strcpy(stack[++tos],T[nt].name);
   if(check(T[nt].name))
   {
	if(strcmp(S[found].type,"undefined")==0)
	{
	 cout<<"'"<<T[nt].name<<"' is an undefined identifier in line no. "<<T[nt].lineno<<".\n";
	 misc=1;
	}
   }
  }
  else
  {
   convert();
   strcpy(stack[++tos],factcode);
  }
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
 stmtflag[++no]=0;
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
	 {
	  no--;
	  if(no!=-1)
	   stmtflag[no]=1;
	  return 1;
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
  nt--;stmtflag[no]=0;
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
		  {
		   no--;
		   return 1;
		  }
		 }
		 else
		 {
		  strcpy(miss,")");
		  return 0;
		 }
		}
		if(stmtflag[no]==-1)
		 return 0;
	   }
	   else
	   {
		if(stmtflag[no]==1)
		 strcpy(miss,";");
		return 0;
	   }
	  }
	 }
	 else
	 {
	  if(stmtflag[no]==1)
	   strcpy(miss,";");
	  return 0;
	 }
	}
	else
	 return 0;
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
   nt--;no--;
   return 0;
  }
 }
 return -1;
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
 stmtflag[++no]=0;
 if(T[nt++].t==50)
 {
  strcpy(idcode,T[nt-1].name);
  if(check(T[nt-1].name))
  {
   if(strcmp(S[found].type,"undefined")==0)
   {
	cout<<"'"<<T[nt-1].name<<"' is an undefined identifier in line no. "<<T[nt-1].lineno<<".\n";
	misc=1;
   }
  }
  stmtflag[no]=1;
  if(T[nt++].t==28)
  {
   if(expn())
   {
	fs<<" MOV AX, ";
	fs<<stack[tos--];
	fs<<"\n MOV ";
	fs<<idcode;
	fs<<", AX\n";
	no--;
	if(no!=-1)
	 stmtflag[no]=1;
	return 1;
   }
   else
	return 0;
  }
  else
  {
   stmtflag[no]=-1;
   strcpy(miss,"=");
   return 0;
  }
 }
 else
 {
  nt--;
  no--;
  return 0;
 }
}

int stmt()
{
 if(assstat() || decstat() || loopstat())
  return 1;
 else
  return 0;
}

int decstat()
{
 stmtflag[++no]=0;
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
	  {
	   no--;
	   return 1;
	  }
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
  nt--;no--;
  return 0;
 }
}
int idlist()
{
 if(T[nt++].t==50)
 {
  if(check(T[nt-1].name))
  {
   if(S[found].flag==0)
   {
	fs<<" ";
	fs<<T[nt-1].name;
	fs<<"  ";
	fs<<typecode;
	fs<<" ?\n";
	S[found].flag=1;
   }
   else
   {
	misc=1;
	cout<<"'"<<T[nt-1].name<<"' is multiply defined in line no. "<<T[nt-1].lineno<<".\n";
   }
  }
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
   if(T[nt++].t==24)
   {
	if(T[nt++].t==51)
	{
	 if(T[nt++].t==25)
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
	  strcpy(miss,"]");
	  return 0;
	 }
	}
	else
	{
	 strcpy(miss,"array range");
	 return 0;
	}
   }
   else
   {
	nt--;
	return 1;
   }
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
  if(T[nt].t==11) strcpy(typecode,"dw");
  else strcpy(typecode,"db");
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
  if(stmtflag[no]==0 || no==-1)
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
	  fs<<" temp dw ?\ndata ends\ncode segment\n";
	  fs<<" assume cs: code\n start:\n MOV AX, data\n MOV DS, AX\n";
	  if(statlist())
	  {
	   if(T[nt++].t==23)
	   {
		fs<<" MOV AH, 4CH\n int 21H\ncode ends\nend start";
		return 1;
	   }
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
 fs.open("noycode.txt",ios::out);
 fs<<"data segment\n";
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
	   S[z].flag=0;
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
 fd.close();
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
  clrscr();
 }
 cout<<"Symbol Table :-\n\n";
 for(i=0;i<z;i++)
  cout<<S[i].name<<"\t"<<S[i].type<<"\t\t"<<S[i].flag<<"\n";
 getch();

 //// PARSER
 clrscr();
 cout<<"......:::::ERRORS:::::.......\n\n";
 if(program())
 {
  if(misc==0)
   cout<<"No Errors. Program is syntactically correct.";
 }
 else
  cout<<"Error in Line No. "<<T[nt-2].lineno<<"==> "<<miss<<" expected.\n";
 getch();
 fs.close();
 cout<<"\nWritten in file!";
 getch();
}