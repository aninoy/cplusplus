#include<ctype.h>
#include<stdlib.h>
#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
enum tokentype{IDENTIFIER=1,OPCODE,NUMBER,SIGN,COLON,COMMA,SEMICOLON,HASH,LEFTPAREN,RIGHTPAREN,LITERAL,ATSIGN,EQUAL,PERIOD,REGISTER,UNDEFINED,PSEUDO};
struct token
{
 char name[5];
 char opcode[10];
 int optype;
 tokentype t;
 long int opc;
 int lc;
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
			 {"#","0",0,HASH}
			};
token T[100];
int x=-1;
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
  while(!fd.eof())
  {
   //fd.get(ch);
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
			  //else
			  // x++;
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  //T[x].t=COLON;
			  strcpy(T[x++].name,":");
			  i=0;
			  flag=1;
			  //fd.get(ch);
			  //while(ch==' ')
			   //fd.get(ch);
			  break;
	case '#': if(flag==-1)
			  {
			   T[x++].name[i++]='\0';
			   flag=1;
			  }
			  i=0;
			  strcpy(T[x++].name,"#");

			  //T[x++].t=;
			  fd.get(ch);
			  while(ch==' ')
			   fd.get(ch);
			  break;
	case ',': if(flag==-1)
			  {
			   T[x++].name[i]='\0';
			   flag=1;
			  }
			  i=0;
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
	default: flag=-1;
			 T[x].name[i++]=ch;
			 fd.get(ch);
   }

   /*while(ch!=' ' && ch!=':' && ch!=',' && ch!='\0' && ch!='\n' && !fd.eof())
   {
	T[x].name[i++]=ch;
	fd.get(ch);
   }
   T[x].name[i]='\0';  */
  }
 }
 for(int i=0;i<=x;i++)
 {
  int flag=0;
  for(int j=0;j<28;j++)
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
}
