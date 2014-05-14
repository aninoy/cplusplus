#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<ctype.h>
#include<fstream.h>
#include<stdio.h>

struct  symbol_table
{
  char name[20];
  char defined;
  unsigned int value;
  char error;
}ST[100];
int k;
int countline=0;
char temp[10],temp1[10];

int LC1=0;

typedef struct pst
{
 char opcode[5];
 unsigned int code;
 int no_of_opnds;
} table_pst;

table_pst PST[]={
		  {"MOV",010000,2},
		  {"CLR",005000,1},
		  {"ADD",060000,2},
		  {"SUB",005000,2},
		  {"INC",005200,1},
		  {"INCB",105200,1},
		  {"MOVB",110000,2},
		  {"CLRB",105000,1}
		};

typedef struct pot
{
 char pseudo[6];
}table_pot;

table_pot POT[]={
		  {"WORD"},{"BYTE"},
		  {"BLKW"},{"BLKB"}
		};

typedef struct registers
{
   char r[4];
}regi;
regi REG[]={
		 {"R0"},{"R1"},{"R2"},{"R3"},
		 {"R4"},{"R5"},{"R6"},{"R7"}
	   };


typedef enum{Identifier=1,Opcode,Leftparn,Rightparn,Number,Sign,Colon,Hash,
		 Equal,Register,Comma,Semicolon,Period,Nextline,Pseudo,Unidentified}tokentype;

struct token
{
	char name[10];
	tokentype t;
}tok[100];
int count=0;
int flag=0,j=0,fl=0;
int convert(char n[])
{
	int i=0;
	int num=0;
	while(n[i]!='\0')
	{
		num=num*10;
		num+=n[i]-'0';
		i++;
	}
	return num;
}


void scanner()
{
	char filename[20],ch;
	ifstream fd;
	clrscr();
	cout<<"\nEnter a filename: ";
	gets(filename);
	fd.open(filename,ios::nocreate);
	if(!fd)
	{
		cout<<"\nFile not found";
		getch();
		exit(0);
	}
	while(!fd.eof())
	{
		int i=0;
		fd.get(ch);
		while(ch!=' '&&!fd.eof()&&ch!='\n')
		{
			switch(ch)
			{
				  case ':':	strcpy(tok[count].name,":");
							tok[count].t=Colon;
							break;
				  case '+': strcpy(tok[count].name,"+");
							tok[count].t=Sign;
							break;
				  case '-': strcpy(tok[count].name,"-");
							tok[count].t=Sign;
							break;
				  case '/': strcpy(tok[count].name,"/");
							tok[count].t=Sign;
							break;
				  case '*': strcpy(tok[count].name,"*");
							tok[count].t=Sign;
							break;
				  case '(': strcpy(tok[count].name,"(");
							tok[count].t=Leftparn;
							break;
				  case ')': strcpy(tok[count].name,")");
							tok[count].t=Rightparn;
							break;
				  case ';': strcpy(tok[count].name,";");
							tok[count].t=Semicolon;
							break;
				  case '#': strcpy(tok[count].name,"#");
							tok[count].t=Hash;
							break;
				  case ',': strcpy(tok[count].name,",");
							tok[count].t=Comma;
							break;
				  case '=': strcpy(tok[count].name,",");
							tok[count].t=Equal;
							break;
				  case '.': strcpy(tok[count].name,".");
							tok[count].t=Period;
							break;
/*				  case '\n':strcpy(tok[count].name,"next");
							tok[count].t=Nextline;
							countline++;
							break;*/
				  default:  if(isdigit(ch))
							{
							   while(isdigit(ch))
							   {
									tok[count].name[i++]=ch;
									fd.get(ch);
							   }
							   tok[count].name[i]='\0';
							   tok[count].t=Number;
							   fl=1;
							}
							else if(isalpha(ch))
							{
							   while(isalpha(ch)||isdigit(ch))
							   {
									tok[count].name[i++]=ch;
									fd.get(ch);
							   }
							   tok[count].name[i]='\0';
							   strupr(tok[count].name);
							   while(j<8)
							   {
								   if(strcmp(tok[count].name,PST[j].opcode)==0)
								   {
									   tok[count].t=Opcode;
									   flag=1;
								   }
								   j++;
							   }
							   j=0;
							   while(j<6)
							   {
								   if(strcmp(tok[count].name,POT[j].pseudo)==0)
								   {
									   tok[count].t=Pseudo;
									   flag=1;
								   }
							   j++;
							   }
							   j=0;
							   while(j<8)
							   {
								   if(strcmp(tok[count].name,REG[j].r)==0)
								   {
									   tok[count].t=Register;
									   flag=1;
								   }
								   j++;
							   }
							   if(flag==0)
							   tok[count].t=Identifier;
							   fl=1;
							}//if
							else
								 tok[count].t=Unidentified;
			 }
			if(fl==0)
				fd.get(ch);
			count++;
			fl=0;
			flag=0;
			i=0;j=0;
		}
//		tok[count].name[i]='\0';
 //		cout<<tok[count].name<<endl;
//		count++;
	}
	for(int k=0;k<count;k++)
		cout<<tok[k].name<<"\t"<<tok[k].t<<"\n";
	getch();
}

void label()
{
	 int flag=0;
	 for(int i=0;i<j;i++)
	 {
	   if(strcmp(temp,ST[i].name)==0)
	   {
	flag=1;
	break;
	   }
	   else
	 flag=0;
	 }
	 if(flag==0)//label not listed in ST
	 {
	  strcpy(ST[j].name,temp);
	  ST[j].defined='Y';
	  ST[j].value=LC1;
	  ST[j].error='N';
	  j++;
	 }
	 else
	  if(ST[i].defined=='N')
	  {
	 ST[i].defined='Y';
	 ST[i].value=LC1;
	  }
	  else if(ST[i].defined=='Y')
	ST[i].error='Y';
}

void label1()
{
	 int flag=0;
	 for(int i=0;i<j;i++)
	 {
	   if(strcmp(temp,ST[i].name)==0)
	   {
	flag=1;
	break;
	   }
	   else
	 flag=0;
	 }
	 if(flag==0)//label not listed in ST
	 {
	  strcpy(ST[j].name,temp);
	  ST[j].defined='N';
	  ST[j].value=-1;
	  ST[j].error='N';
	  j++;
}
}
void pseudo()
{
	if(strcmp(tok[k].name,"WORD")==0)
	{
		k++;
		LC1=LC1+2;
		k++;
	}
	else if( strcmp(tok[k].name,"BYTE")==0)
	{
	   k++;
	   LC1=LC1+1;
	   k++;
	}
	else if( strcmp(tok[k].name,"BLKW")==0)
	{
		k++;
		int no=convert(tok[k].name);
		LC1=LC1+2*no;
		k++;
	}
	else if( strcmp(tok[k].name,"BLKB")==0)
	{
		k++;
		int no=convert(tok[k].name);
		LC1=LC1+no;
		k++;
	}
}

void opcode()    //pass1
{
int n=0;
for(int i=0;i<15; i++)
{
	if(strcmp(temp1,PST[i].opcode)==0)
	{
		n=PST[i].no_of_opnds;
		break;
	}
}
if(n==1)
{
	k++;
	if(tok[k].t==Identifier||tok[k].t==Hash||tok[k].t==Number)
	{
		LC1=LC1+4;
		strcpy(temp,tok[k].name);
		if(tok[k].t==Identifier)
		{
			k++;
			label1();
		}
		if(tok[k].t==Hash)
			k+=2;
		if(tok[k].t==Number)
			k+=4;
	}
	else if(tok[k].t==Register||tok[k].t==Leftparn||tok[k].t==Sign)
	{
		LC1=LC1+2;
		if(tok[k].t==Leftparn)
		{
			k+=2;
			if(tok[k].t==Sign)
				k++;
		}
		if(tok[k].t==Sign)
		{
			k+=3;
		}
		k++;
	}
}

if(n==2)
{
	k++;
	if(tok[k].t==Identifier||tok[k].t==Hash||tok[k].t==Number)
	{
		LC1=LC1+4;
		strcpy(temp,tok[k].name);
		if(tok[k].t==Identifier)
		{
			k++;
			label1();
		}
		if(tok[k].t==Hash)
			k+=2;
		if(tok[k].t==Number)
			k+=4;
	}
	else if(tok[k].t==Register||tok[k].t==Leftparn||tok[k].t==Sign)
	{
		LC1=LC1+2;
		if(tok[k].t==Leftparn)
		{
			k+=2;
			if(tok[k].t==Sign)
			k++;
		}
		if(tok[k].t==Sign)
		{
			k+=3;
		}
		k++;
	}
	k++;
	if(tok[k].t==Identifier||tok[k].t==Hash||tok[k].t==Number)
	{
		LC1=LC1+2;
		strcpy(temp,tok[k].name);
		if(tok[k].t==Identifier)
		{
			k++;
			label1();
		}
		if(tok[k].t==Hash)
			k+=2;
		if(tok[k].t==Number)
			k+=4;
	}
	else if(tok[k].t==Register||tok[k].t==Leftparn||tok[k].t==Sign)
	{
		if(tok[k].t==Leftparn)
		{
			k+=2;
			if(tok[k].t==Sign)
			k++;
		}
		if(tok[k].t==Sign)
		{
			k+=3;
		}
		k++;
	}
}
}

void equal()
{
   for(int i=0;i<j;i++)
   {
	 if(strcmp(temp,ST[i].name)==0)
	  {
	flag=1;
	break;
	  }
	 else
	flag=0;
	  }
	 if(flag==0)//label not listed in ST
	 {
	  strcpy(ST[j].name,temp);
	  ST[j].defined='Y';
	  ST[j].error='N';
	  if(tok[k].t==Period)
	  {
			ST[j].value=LC1;
			k++;
	  }
	  else
	  {
			ST[j].value=convert(tok[k].name);
			k++;
	  }
	j++;
	 }
	 else if(ST[i].defined=='N')
	  {
	 ST[i].defined='Y';
	  if(tok[k].t==Period)
	  {
			ST[i].value=LC1;
			k++;
	  }
	  else
	  {
			ST[j].value=convert(tok[k].name);
			k++;
	  }

	  }
	  else if(ST[i].defined=='Y')
	  {
	  ST[i].error='Y';
	  k++;
	 }

}



void pass1()
{
	j=0;
//	int i=0;
	k=0;
	while(k<count)
	{
			strcpy(temp,tok[k].name);
			if(tok[k].t==Identifier)
			{
				 k++;
				 if(tok[k].t==Colon)
				 {
					   k++;
					   label();
					   strcpy(temp1,tok[k].name);
					   if(tok[k].t==Opcode)
					   {
						   opcode();
					   }
					   else if(tok[k].t==Period)
					   {
						   k++;
						   pseudo();
					   }
					  /* else
					   {
						   printf("Unidentified");
					   }*/
				}
				else if(tok[k].t==Equal)
				{
					k++;
					equal();
				}
/*			else
			{
				printf("Unidentified");
			}
*/
	   }//if identifier
	   else if(tok[k].t==Opcode)
	   {
		   strcpy(temp1,tok[k].name);
//		   k++;
		   opcode();
	   }
/*	   else if(tok[k].t==Period)
	   {
			k++;
			if(tok[k].t==Equal)
			{
				k++;
				equateLC();
			}
*/
	 //  break;
	   }//while(ptr)
	}//while(fgets)
//pass1



void main()
{
scanner();
//getch();
clrscr();
pass1();
for(int i=0;i<j;i++)
{
	cout<<ST[i].name<<"\t"<<ST[i].value<<"\t"<<ST[i].defined<<ST[i].error;
	cout<<"\n";
}
getch();
}


