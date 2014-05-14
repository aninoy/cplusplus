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
enum tokentype{IDENTIFIER=1,OPCODE,NUMBER,PLUS,MINUS,COLON,COMMA,SEMICOLON,HASH,LEFTPAREN,RIGHTPAREN,LITERAL,ATSIGN,EQUAL,PERIOD,REGISTER,UNDEFINED,PSEUDO};
long int reg[8]={20,56,26,1000,432,234,467,894};
int N=0,C=0,Z=0,V=0;
int nol;
struct list
{
 long int lcint;
 char lcval[7],mccode[7];
}L[20];
struct token
{
 char name[5];
 char opcode[10];
 int optype;
 tokentype t;
 long int opc;
};

struct opcode
{
 struct token T[10];
 char name[20];
 int loc;
 int notk;
 int now;
 int optype;
 int opc[4];
}O[100];
struct sym
{
 char name[30];
 int value;
 char def,err;
};
token ost[]={{"mov","010000",02,OPCODE},
			 {"clr","005000",01,OPCODE},
			 {"add","060000",02,OPCODE},
			 {"sub","160000",02,OPCODE},
			 {"com","005100",01,OPCODE} ,
			 {"inc","005200",01,OPCODE},
			 {"dec","005300",01,OPCODE},
			 {"neg","005400",01,OPCODE},
			 {"movb","110000",02,OPCODE},
			 {"clrb","105000",01,OPCODE},
			 {"comb","105100",01,OPCODE},
			 {"negb","105400",01,OPCODE},
			 {"WORD","0",02,PSEUDO},
			 {"BYTE","0",01,PSEUDO},
			 {"BLKW","0",02,PSEUDO},
			 {"BLKB","0",01,PSEUDO},
			 {"TITLE","0",01,PSEUDO},
			 {"END","0",01,PSEUDO},
			 {"R0","0",0,REGISTER},
			 {"R1","1",0,REGISTER},
			 {"R2","2",0,REGISTER},
			 {"R3","3",0,REGISTER},
			 {"R4","4",0,REGISTER},
			 {"R5","5",0,REGISTER},
			 {"R6","6",0,REGISTER},
			 {"R7","7",0,REGISTER},
			 {":","0",0,COLON},
			 {"#","0",1,HASH},
			 {"(","0",1,LEFTPAREN},
			 {")","0",1,RIGHTPAREN},
			 {",","0",1,COMMA},
			 {"+","0",1,PLUS},
			 {"-","0",1,MINUS}
			};
token T[100];
sym S[100];
char globuf[7];
int x=-1,g=0;
int findloc(int loc)
{
 for(int i=0;i<nol;i++)
 {
  if(L[i].lcint==loc)
   return i;
 }
 return -1;
}
void tictoc()
{
 int i=0;
 while(i<5)
 {
  gotoxy(40,19);
  cout<<"Please Wait";
  gotoxy(40,20);
  switch(i)
  {
   case 4:
   case 0: cout<<"| ";
		   break;
   case 1: cout<<"/ ";
		   break;
   case 2: cout<<"--";
		   break;
   case 3: cout<<"\\ ";
		   break;
  }
  i++;
  delay(300);
  gotoxy(40,19);
  cout<<"           ";
  gotoxy(40,20);
  cout<<"  ";
 }
}
void display()
{
 clrscr();
 cout<<"Registers:-\n\n";
 for(int i=0;i<8;i++)
  cout<<"R"<<i<<": "<<reg[i]<<"\n";
 gotoxy(1,15);
 cout<<"Condition Codes:-\n\n";
 cout<<"C: "<<C<<"\n"<<"Z: "<<Z<<"\n"<<"N: "<<N<<"\n"<<"V: "<<V<<"\n";
 gotoxy(30,1);
 cout<<"Memory:-";
 for(i=0;i<20;i++)
 {
  gotoxy(30,i+3);
  cout<<L[i].lcval<<"\t\t"<<L[i].mccode<<"\n";
 }
}
void tostring(int b)
{
 char buffer2[7];
 itoa(b,buffer2,10);
 strcpy(globuf,"000000");
 int i=0,j=5;
 while(buffer2[i]!='\0')i++;
 while(i!=0)
 {
  globuf[j]=buffer2[i-1];
  i--;
  j--;
 }
}
int octtodec(int k)
{
 int sum=0,b=0,a;
 while(k!=0)
 {
  a=k%10;
  sum=sum+a*pow(8,b);
  b++;
  k/=10;
 }
 return sum;
}
int dectooct(int k)
{
 int a,b=0,sum=0;
 while(k!=0)
 {
  a=k%8;
  sum=sum+a*pow(10,b);
  b++;
  k/=8;
 }
 return sum;
}
int search(char n[])
{
 int t=-1;
 for(int i=0;i<g;i++)
 {
  if(strcmp(S[i].name,n)==0)
   t=i;
 }
 return t;
}

void main()
{
 int flag=-1;
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
  x=0;int i=0;
  fd.get(ch);
  while(ch==' ')
   fd.get(ch);
  while(!fd.eof())
  {
   switch(ch)
   {
	case ' ': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  fd.get(ch);
			  while(ch==' ')
			  fd.get(ch);
			  break;
	case ':': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  T[x].t=COLON;
			  strcpy(T[x].name,":");
			  i=0;
			  flag=1;x++;
			  break;
	case '(': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  T[x].t=LEFTPAREN;
			  strcpy(T[x++].name,"(");
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  break;
	case ')': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  T[x].t=RIGHTPAREN;
			  strcpy(T[x++].name,")");
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  break;
	case '+': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  T[x].t=PLUS;
			  strcpy(T[x++].name,"+");
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  break;
	case '-': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  T[x].t=MINUS;
			  strcpy(T[x++].name,"-");
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  break;
	case '#': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  T[x].t=HASH;
			  strcpy(T[x++].name,"#");
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  break;
	case ',': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  T[x].t=COMMA;
			  strcpy(T[x++].name,",");
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  break;
	case '\n': if(flag==-1)
			   {
				T[x++].name[i++]='\0';
				flag=1;
			   }
			   fd.get(ch);
			   while(ch==' ')
				fd.get(ch);
			   i=0;
			   break;
	case '\0': if(flag==-1)
			   {
				T[x++].name[i]='\0';
				flag=1;
			   }
			   fd.get(ch);
			   while(ch==' ')
				fd.get(ch);
			   i=0;
			   break;
	default:  flag=-1;
			  T[x].name[i++]=ch;
			  fd.get(ch);
   }
  }
 }
 for(int i=0;i<=x;i++)
 {
  int flag=0;
  for(int j=0;j<33;j++)
  {
   if(!strcmpi(T[i].name,ost[j].name))
   {
	flag=1;
	T[i].t=ost[j].t;
	T[i].optype=ost[j].optype;
	strcpy(T[i].opcode,ost[j].opcode);
	T[i].opc=atoi(T[i].opcode);
   }
  }
  if(flag==0)
  {
   if(isdigit(T[i].name[0]))
   {
	T[i].t=NUMBER;
	if(T[i-1].t!=HASH)
		T[i].optype=1;
	else
		T[i].optype=0;
	strcpy(T[i].opcode,"0\0");
   }
   else
   {
	T[i].t=IDENTIFIER;
	T[i].optype=0;
	strcpy(T[i].opcode,"0\0");
   }
  }
 }
 for(i=0;i<=x;i++)
 {
  cout<<T[i].name<<"\t";
  cout<<T[i].t<<"\t";
  cout<<T[i].optype<<"\t";
  cout<<T[i].opcode<<"\t";
  cout<<T[i].opc<<"\n";
 }
 getch();

 //PASS ONE
 int lc=16,l=0,k=0;
 for(i=0;i<=x;i++)
 {
  switch(T[i].t)
  {
   case IDENTIFIER: int p=search(T[i].name);
			if(p==-1)
			{
			 strcpy(S[g].name,T[i].name);
			 if(T[i+1].t==COLON)
			 {
			  S[g].def='Y';
			  S[g].value=dectooct(lc);
			  S[g++].err='N';
			 }
			 else
			 {
			  S[g].value=-1;
			  S[g].def='N';
			  S[g++].err='Y';
			 }
			}
			else
			{
			 if(T[i+1].t==COLON)
			 {
			  if(S[p].def=='Y')
			  {
			   S[p].err='Y';
			   S[p].def='D';
			  }
			  else
			  {
			   S[p].value=dectooct(lc);
			   S[p].err='N';
			   S[p].def='Y';
			  }
			 }
			}
			break;
   case OPCODE: strcpy(O[k].name,T[i].name);
		O[k].loc=lc;
		O[k].opc[0]=T[i].opc;
		O[k].optype=T[i].optype;
		lc+=2;
		l=0;
		O[k].now=1;
		int f=T[i].optype;
		int y;
		if(f==1)
		 y=1;
		else
		 y=0;
		for(int j=0;j<f;j++)
		{
		 strcpy(O[k].T[l].name,T[++i].name);
		 O[k].T[l++].t=T[i].t;
		 f+=T[i].optype;
		 switch(T[i].t)
		 {
		  case HASH: lc+=2;
				 O[k].now++;
				 break;
		  case IDENTIFIER: int p=search(T[i].name);
						   if(p==-1)
						   {
							strcpy(S[g].name,T[i].name);
							if(T[i+1].t==5)
							{
							 S[g].def='Y';
							 S[g].value=dectooct(lc);
							 S[g++].err='N';
							}
							else
							{
							 S[g].value=-1;
							 S[g].def='N';
							 S[g++].err='Y';
							}
						   }
						   lc+=2;
						   O[k].now++;
						   break;
		  case NUMBER: if(O[k].T[l-2].t!=HASH)
					   {
						lc+=2;
						O[k].now++;
					   }
					   break;
		  //case MINUS:
		  case PLUS: f--;
					 break;
		  case RIGHTPAREN: f-=y;
						   break;
		 }
		}
		O[k].notk=l;
		k++;
		break;

  }
 }
 cout<<"\nSymbol Table:- \n";
 cout<<"Name\tValue\tDefined\tError\n";
 for(int x1=0;x1<g;x1++)
 {
  cout<<S[x1].name<<"\t"<<S[x1].value<<"\t"<<S[x1].def<<"\t"<<S[x1].err<<"\n";
 }
 getch();
 cout<<"List of Opcodes\n";
 for(x1=0;x1<k;x1++)
 {
  cout<<O[x1].name<<"\t"<<O[x1].now<<"\n";
  for(int x2=0;x2<O[x1].notk;x2++)
   cout<<O[x1].T[x2].name<<"\t";
  cout<<"\n";
 }
 getch();


 //PASS TWO
 for(x1=0;x1<k;x1++)
 {
  l=0;int flag=0;
  for(int x2=0;x2<O[x1].notk;x2++)
  {
   if(O[x1].optype==1)
	flag=1;
   while(strcmp(O[x1].T[x2].name,",")!=0 && flag==0)
   {
	switch(O[x1].T[x2].t)
	{
	 case HASH: O[x1].opc[0]+=2700;
		O[x1].opc[++l]=atoi(O[x1].T[x2+1].name);
		break;
	 case IDENTIFIER: O[x1].opc[0]+=6700;
					  int p=search(O[x1].T[x2].name);
					  int ival=octtodec(S[p].value);
					  int cur=octtodec(O[x1].loc)+2*O[x1].now;
					  O[x1].opc[++l]=dectooct(fabs(ival-cur));
					  break;
	 case REGISTER: O[x1].opc[0]+=(O[x1].T[x2].name[1]-48)*100;
					break;
	 case LEFTPAREN: O[x1].opc[0]+=(O[x1].T[++x2].name[1]-48)*100;
					 O[x1].opc[0]+=1000;
					 break;
	 case NUMBER: if(O[x1].T[x2-1].t!=HASH)
				  {
				   O[x1].opc[0]+=6000;
				   int save=x2;
				   x2+=2;
				   O[x1].opc[0]+=(O[x1].T[x2].name[1]-48)*100;
				   O[x1].opc[++l]=atoi(O[x1].T[save].name);
				  }
				  break;
	 case PLUS: O[x1].opc[0]+=1000;
				break;
	 case MINUS: O[x1].opc[0]+=3000;
				 break;
	}
	x2++;
   }
   flag=1;
   switch(O[x1].T[x2].t)
   {
	case HASH: O[x1].opc[0]+=27;
			   break;
	case IDENTIFIER: O[x1].opc[0]+=67;
					 int p=search(O[x1].T[x2].name);
					 int ival=octtodec(S[p].value);
					 int cur=O[x1].loc+2*O[x1].now;
					 char buf[20];
					 itoa(fabs(ival-cur),buf,10);
					 O[x1].opc[++l]=atoi(buf);
					 break;
	case REGISTER: O[x1].opc[0]+=O[x1].T[x2].name[1]-48;
				   break;
	case LEFTPAREN: O[x1].opc[0]+=O[x1].T[++x2].name[1]-48+10;
					break;
	case PLUS: O[x1].opc[0]+=10;
			   break;
	case MINUS: O[x1].opc[0]+=30;
				break;
   }
  }
 }
 for(i=0;i<20;i++)
 {
  strcpy(L[i].lcval,"");
  strcpy(L[i].mccode,"");
 }
 cout<<"\n\nProgram Listing :- \n";
 cout<<"LC Value\tMachine Code\n";
 nol=0;
 for(x1=0;x1<k;x1++)
 {
  for(int x2=0;x2<O[x1].now;x2++)
  {
   int v=dectooct(O[x1].loc+2*x2);
   L[nol].lcint=v;
   tostring(v);
   strcpy(L[nol].lcval,globuf);
   strcat(L[nol].lcval,"\0");
   tostring(O[x1].opc[x2]);
   strcpy(L[nol].mccode,globuf);
   strcat(L[nol].mccode,"\0");
   cout<<L[nol].lcval<<"\t\t"<<L[nol].mccode<<"\n";
   nol++;
  }
 }
 getch();

 //SIMULATOR
 char buffer1[6],buffer2[6];
 display();
 gotoxy(1,24);
 cout<<"Press any key to start execution...";
 getch();
 int j,addr;
 for(i=0;i<k;i++)
 {
  j=0;
  tostring(O[i].opc[j]);
  gotoxy(1,24);
  cout<<globuf;
  getch();
  switch(globuf[1])
  {
   case '0': if(globuf[2]=='5')
			 {
			  switch(globuf[4])
			  {
			   case '0': reg[globuf[5]-48]=0;
						 break;
			   case '1': addr=reg[globuf[5]-48];
						 int pos=findloc(addr);
						 strcpy(L[pos].mccode,"000000");

						 break;
			   case '2': addr=reg[globuf[5]-48];
						 pos=findloc(addr);
						 strcpy(L[pos].mccode,"000000");
						 reg[globuf[5]-48]=dectooct(octtodec(addr)+2);
						 break;
			   case '4': addr=reg[globuf[5]-48];
						 pos=findloc(addr);
						 strcpy(L[pos].mccode,"000000");
						 reg[globuf[5]-48]=dectooct(octtodec(addr)-2);
						 break;
			   case '6': addr=O[i+1].loc;
						 gotoxy(1,24);
						 cout<<addr;
						 addr=addr+octtodec(O[i].opc[++j]);
						 pos=findloc(dectooct(addr));
						 strcpy(L[pos].mccode,"000000");
						 break;
			  }
			  Z=1;
			 }
			 else
			 {
			  gotoxy(1,24);
			  cout<<"Not a machine instruction.";
			 }
			 break;
   case '1': int src;
			 switch(globuf[2])
			 {
			  case '0': src=reg[globuf[3]-48];
						break;
			  case '1': addr=reg[globuf[3]-48];
						int pos=findloc(addr);
						src=atoi(L[pos].mccode);
						break;
			  case '2': if(globuf[3]=='7')
						 src=O[i].opc[++j];
						else
						{
						 addr=reg[globuf[3]-48];
						 int pos=findloc(addr);
						 src=atoi(L[pos].mccode);
						 reg[globuf[3]-48]+=2;
						}
						break;
			  case '4': reg[globuf[3]-48]=dectooct(octtodec(reg[globuf[3]-48])-2);
						addr=reg[globuf[3]-48];
						pos=findloc(addr);
						src=atoi(L[pos].mccode);
						break;
			  case '6': if(globuf[3]=='7')
						{
						 int p=search(O[i].T[0].name);
						 pos=findloc(S[p].value);
						 src=atoi(L[pos].mccode);
						}
						else
						{
						 int p=O[i].opc[++j];
						 addr=dectooct(octtodec(p)+octtodec(reg[globuf[3]-48]));
						 pos=findloc(addr);
						 src=atoi(L[pos].mccode);
						}
						break;
			 }
			 switch(globuf[4])
			 {
			  case '0': reg[globuf[5]-48]=src;
						break;
			  case '1': addr=reg[globuf[5]-48];
						int pos=findloc(addr);
						tostring(src);
						strcpy(L[pos].mccode,globuf);
						break;
			  case '2': addr=reg[globuf[3]-48];
						pos=findloc(addr);
						src=atoi(L[pos].mccode);
						break;
			 }
			 break;

  }
  tictoc();
  display();
  getch();
 }
 gotoxy(1,24);
 cout<<"Execution Over.Press any key to exit...";
 getch();
}
