#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<ctype.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>

int keywords=10,symbols=20,id=50,num=51,eof=90,unknown=100;

char key[7][6]={"main","int","char","if","else","while","for"};
char symb[20][3]={"(",")","{","}","[","]",",",";","=","==","!=","<=",">=","<",">","+","-","*","/","%"};

struct token{
char type[15];
char name[10];
int t;
int line;
}tok[100];
int tcount=0;
int count=0;
int linenum=1;
token ids[50];
int itop=-1;
int otop=-1;
token ops[50];


char filename[20];
char ofname[20];
ifstream fd;

int ispace(char ch)
{
	if(ch==' '||ch=='\n'||ch=='\t'||fd.eof())
		return 1;
	else
		return 0;
}


int issymbol(char c)
{
	char d;
	char e[3];
	int flag=0;
	for(int i=0;i<20;i++)
	{
		if(c==symb[i][0])
			return 20+i;
	}
	if(flag==0)
		if(ispace(c))
			return 1;
	return 0;
}


void scanner()
{
	int flag=0,fl=0,j=0;
	char ch;
	clrscr();
	cout<<"\nEnter a filename: ";
	gets(filename);
	fd.open(filename,ios::nocreate);
	cout<<"===============SCANNER OUTPUT==============="<<endl;
	if(!fd)
	{
		cout<<"\nFile not found";
		getch();
		exit(0);
	}
	while(!fd.eof())
	{
		int i=0;
		if(ch=='\n')
			linenum++;
		fd.get(ch);
		while(ch!=' '&&!fd.eof()&&ch!='\t'&&ch!='\n')
		{
			switch(ch)
			{
				  default:	if(isdigit(ch))
							{
								int dflag=0;
								while(isalnum(ch)||(!issymbol(ch)))
								{
									if(!isdigit(ch))
									{
									if(isalpha(ch)||(!issymbol(ch)))
										{
											dflag=1;
										}
									}
									tok[count].name[i++]=ch;
									fd.get(ch);
								}
							tok[count].name[i]='\0';
							if(dflag==0)
							{
								tok[count].t=51;
								strcpy(tok[count].type,"number");
							}
							else
							{
								tok[count].t=100;
								strcpy(tok[count].type,"unknown");
							}
							fl=1;
						}
						else if(isalpha(ch))
						{
						   int iflag=0;
						   while(isalnum(ch)||(!issymbol(ch)))
						   {
							if(!isalnum(ch))
							{
								if((issymbol(ch))==0)
								{
									iflag=1;
								}
							}
							tok[count].name[i++]=ch;
							fd.get(ch);
						   }
						   tok[count].name[i]='\0';
						   if(iflag==0)
						   {
							while(j<7)
							{
								if(strcmp(tok[count].name,key[j])==0)
								{
								   tok[count].t=keywords+j;
								   strcpy(tok[count].type,"keyword");
								   flag=1;
								}
								j++;
							}
							j=0;
							if(flag==0)
							{
								tok[count].t=id;
								strcpy(tok[count].type,"identifier");
							}
						  //	fl=1;
						   }//if
						   else
						   {
								tok[count].t=unknown;
								strcpy(tok[count].type,"unknown");
						   }
						   fl=1;
						}
						else if(issymbol(ch))
						{
							if(ispace(ch)==0)
							{
							int val=issymbol(ch);
							switch(ch)
							{
								case '=':	tok[count].name[0]=ch;
											fd.get(ch);
											if(ch=='=')
											{
												tok[count].name[1]=ch;
												tok[count].name[2]='\0';
												tok[count].t=29;
												strcpy(tok[count].type,"symbol");
											}
											else
											{
												tok[count].name[1]='\0';
												tok[count].t=28;
												strcpy(tok[count].type,"symbol");
												fl=1;
											}
											break;
								case '!':               char temp[20];
											tok[count].name[0]=ch;
											fd.get(ch);
											if(ch=='=')
											{
												tok[count].name[1]=ch;
												tok[count].name[2]='\0';
												tok[count].t=30;
												strcpy(tok[count].type,"symbol");
											}
											else
											{
												int as=0;
												temp[as++]='!';
												while(!ispace(ch)&&!issymbol(ch))
												{
													temp[as++]=ch;
													fd.get(ch);
												}
											temp[as]='\0';
												if(strcmp(tok[count-1].type,"symbol")==0)
												{
													strcpy(tok[count].name,temp);
													tok[count].t=unknown;
													strcpy(tok[count].type,"unknwon");
												}
												else
												{
													strcat(tok[count-1].name,temp);
													strcpy(tok[count-1].type,"unknown");
													tok[count-1].t=100;
													count--;
												}
												fl=1;
											}
											break;
								case '<':	tok[count].name[0]=ch;
											fd.get(ch);
											if(ch=='=')
											{
												tok[count].name[1]=ch;
												tok[count].name[2]='\0';
												tok[count].t=31;
												strcpy(tok[count].type,"symbol");
											}
											else
											{
												tok[count].name[1]='\0';
												tok[count].t=33;
												strcpy(tok[count].type,"symbol");
												fl=1;
											}
											break;
								case '>':	tok[count].name[0]=ch;
											fd.get(ch);
											if(ch=='=')
											{
												tok[count].name[1]=ch;
												tok[count].name[2]='\0';
												tok[count].t=32;
												strcpy(tok[count].type,"symbol");
											}
											else
											{
												tok[count].name[1]='\0';
												tok[count].t=34;
												strcpy(tok[count].type,"symbol");
												fl=1;
											}
											break;
								default:    tok[count].name[0]=ch;
											tok[count].name[1]='\0';
											tok[count].t=val;
											strcpy(tok[count].type,"symbol");

							}
							}
						}
						else
						{
							while(!ispace(ch)&&!issymbol(ch))
							{
								tok[count].name[i++]=ch;
								fd.get(ch);
							}
							tok[count].t=unknown;
							strcpy(tok[count].type,"unknwon");
							fl=1;
						}
			 }
			 if(fl==0)
			 fd.get(ch);
			 tok[count].line=linenum;
			 count++;
			fl=0;
			flag=0;
			i=0;j=0;
		}
	}
	cout<<count;
	for(int k=0;k<count;k++)
	{
		cout<<tok[k].name<<"\t"<<tok[k].t<<"\t"<<tok[k].line<<"\t"<<k<<"\n\n";
//		getch();
	}
	getch();
}


int scount=0;
struct ST{
char name[20];
char type[20];
}st[100];

/*void genst()
{
	int i=0,j=0,flag=0;
	while(i<count)
	{
		flag=0;
		while(tok[i].t!=11&&tok[i].t!=12&&tok[i].t!=50)
		{
			i++;
		}
		j=i;
		switch(tok[i].t)
		{
			case 11:                j++;
						while(((strcmp(tok[j].type,"keyword")!=0)&&tok[j].t!=27)&&j<count)
						{
							if(tok[j].t==50)
							{
								for(int k=0;k<scount;k++)
								{
									if(strcmp(tok[j].name,st[k].name)==0)
									{
										flag=1;
										break;
									}
								}
								if(flag==0)
								{
									strcpy(st[scount].type,"int");
									strcpy(st[scount].name,tok[j].name);
									scount++;
								}
							}
							j++;
						}
						break;

			case 12:    		j++;
						while(((strcmp(tok[j].type,"keyword")!=0)&&tok[j].t!=27)&&j<count)
						{
							if(tok[j].t==50)
							{
								for(int k=0;k<scount;k++)
								{
									if(strcmp(tok[j].name,st[k].name)==0)
									{
										flag=1;
										break;
									}
								}
								if(flag==0)
								{
									strcpy(st[scount].type,"char");
									strcpy(st[scount].name,tok[j].name);
									scount++;
								}
							}
							j++;
						}
						break;
			case 50:	for(int k=0;k<scount;k++)
					{
						if(strcmp(tok[j].name,st[k].name)==0)
						{
							flag=1;
							break;
						}
					}
					if(flag==0)
					{
						strcpy(st[scount].type,"undefined");
						strcpy(st[scount].name,tok[j].name);
						scount++;
					}
					j++;

		}
		i=j;
	}
	for(i=0;i<scount;i++)
		cout<<st[i].name<<"\t"<<st[i].type<<"\n";
} */
char nu[2]={' ','\0'};
ofstream ofd;
char dtype[6];
int dt;
int pcount=0;
char msg[50];

void write(char a[])
{
	for(int i=0;a[i]!='\n';i++);
	i++;
	ofd.write(a,i);
}

void pushi(token a)
{
	ids[++itop]=a;
}

token popi()
{
	return ids[itop--];
}


void genst()
{
	int flag=0;
	for(int k=0;k<scount;k++)
	{
		if(strcmp(tok[pcount].name,st[k].name)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		strcpy(st[scount].type,dtype);
		strcpy(st[scount].name,tok[pcount].name);
		scount++;
	}
	else
	{
		strcpy(msg," multiple declaration for ");
		strcat(msg,tok[pcount].name);
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	}
}

void equal()
{
token id1=popi();
token id2=popi();
strcpy(msg,"MOV AX,");
strcat(msg,id1.name);
strcat(msg,"\n");
write(msg);
strcpy(msg,"MOV ");
strcat(msg,id2.name);
strcat(msg,",AX\n");
write(msg);
}

void mul(int op)
{
token id2=popi();
token id1=popi();
strcpy(msg,"MOV AX,");
strcat(msg,id1.name);
strcat(msg,"\n");
write(msg);
strcpy(msg,"MOV BX,");
strcat(msg,id2.name);
strcat(msg,"\n");
write(msg);
switch(op)
{
	case 37:strcpy(msg,"MUL BX\n");
		break;
	case 38:
	case 39:strcpy(msg,"DIV BX\n");
}
write(msg);
tcount++;
char tempno[10];
itoa(tcount,tempno,10);
token temp;
temp.t=50;
strcpy(temp.name,"temp");
strcat(temp.name,tempno);
pushi(temp);
strcpy(msg,"MOV temp");
strcat(msg,tempno);
switch(op)
{
case 37:strcat(msg,",AX\n");
	break;
case 38:strcat(msg,",AL\n");
	break;
case 39:strcat(msg,",AH\n");
	break;
}

write(msg);
}


void add(int op)
{
token id2=popi();
token id1=popi();
strcpy(msg,"MOV AX,");
strcat(msg,id1.name);
strcat(msg,"\n");
write(msg);
switch(op)
{
	case 35:strcpy(msg,"ADD AX,");
		break;
	case 36:strcpy(msg,"SUB AX,");
		break;
}
strcat(msg,id2.name);
strcat(msg,"\n");
write(msg);
tcount++;
char tempno[10];
itoa(tcount,tempno,10);
token temp;
temp.t=50;
strcpy(temp.name,"temp");
strcat(temp.name,tempno);
pushi(temp);
strcpy(msg,"MOV temp");
strcat(msg,tempno);
strcat(msg,",AX\n");
write(msg);
}


void idlist()
{
	char msg[50];
	if(tok[pcount].t==50)
	{
		genst();
		strcpy(msg,tok[pcount].name);
		pcount++;
		if(dt==1)
			strcat(msg," dw ");
		else
		strcat(msg," db ");
		if(tok[pcount].t==24)
		{
			strcat(msg,tok[pcount+1].name);
			strcat(msg," dup(?)\n");
		}
		else
		strcat(msg,"?\n");
		write(msg);
	}
	else
	{

		strcpy(msg," Identifier expected");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	}
	if(tok[pcount].t==26)
	{
		pcount++;
		idlist();
	}
	else if(tok[pcount].t==24)
	{
		pcount++;
		if(tok[pcount].t==51)
		{
			pcount++;
			if(tok[pcount].t==25)
			{
				pcount++;
				if(tok[pcount].t==26)
				{
					pcount++;
					idlist();
				}
				else if(tok[pcount].t==27)
				{
					pcount++;
					return;
				}
				else
				{
					strcpy(msg," Declaration missing ;");
					cout<<"error at line"<<tok[pcount].line;
					puts(msg);
					strcpy(msg," declaration syntax error");
					cout<<"error at line"<<tok[pcount].line;
					puts(msg);
					getch();
					exit(0);
				}
			}
			else
			{
				strcpy(msg," ] expected");
				cout<<"error at line"<<tok[pcount].line;
				puts(msg);
				getch();
				exit(0);
			}
		}
		else
		{
			strcpy(msg," array size unknown");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
	}
	else if(tok[pcount].t==27)
	{
		pcount++;
		return;
	}
	else
	{
		strcpy(msg," Declaration missing ;");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		strcpy(msg," declaration syntax error");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	}
}

void dec()
{
	while(pcount<count-1)
	{
		if(tok[pcount].t==11)
		{
			   pcount++;
			   strcpy(dtype,"int");
			   dt=1;
			   idlist();
		}
		else if(tok[pcount].t==12)
		{
			pcount++;
			strcpy(dtype,"char");
			dt=2;
			idlist();
		}
		else
			return;
	}
}

void genst1()
{
	int flag=0;
	for(int k=0;k<scount;k++)
	{
		if(strcmp(tok[pcount].name,st[k].name)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		strcpy(msg," undeclared variable ");
		strcat(msg,tok[pcount].name);
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	}
}

void factor()
{
	if(tok[pcount].t==50)
	{
		genst1();
		pushi(tok[pcount]);
		pcount++;
	}
	else if(tok[pcount].t==51)
	{
		pushi(tok[pcount]);
		pcount++;
	}
	else
	{
			strcpy(msg," identifier or number expected");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
	}
}

void tprime()
{
	if(tok[pcount].t>=37&&tok[pcount].t<=39)
	{
		int op=tok[pcount].t;
		pcount++;
		factor();
		mul(op);
		tprime();
	}
	else
		return;
}

void term()
{
	factor();
	tprime();
}

void seprime()
{
	if(tok[pcount].t==35||tok[pcount].t==36)
	{
		int op=tok[pcount].t;
		pcount++;
		term();
		add(op);
		seprime();
	}
	else
		return;
}
void sim_exp()
{
	term();
	seprime();
}
void eprime()
{
	if(tok[pcount].t>=29&&tok[pcount].t<=34)
	{
		pcount++;
		sim_exp();
	}
	else
		return;
}
void exp()
{
	sim_exp();
	eprime();
}

int ass_stat()
{
	if(tok[pcount].t==50)
	{
		genst1();
		pushi(tok[pcount]);
		pcount++;
	}
	else
	{
		return 0;
	}
	if(tok[pcount].t==28)
	{
		pcount++;
	}
	else
	{
			strcpy(msg," equal to operator missing");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
	}
	exp();
	equal();
	return 1;
}

void stat();

void dprime()
{
	if(tok[pcount].t==14)
	{
		pcount++;
		stat();
	}
	else
		return;
}

int dec_stat()
{
	if(tok[pcount].t==13)
	{
		pcount++;
	}
	else
		return 0;
	if(tok[pcount].t==20)
	{
		pcount++;
	}
	else
	{
		strcpy(msg," ( missing");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	}
	exp();
	if(tok[pcount].t==21)
	{
		pcount++;
	}
	else
	{
		strcpy(msg," ) missing");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	}
	stat();
	dprime();
	return 1;
}

int loop_stat()
{
	if(tok[pcount].t==15)
	{
		pcount++;
		if(tok[pcount].t==20)
		{
			pcount++;
		}
		else
		{
			strcpy(msg," ( missing");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		exp();
		if(tok[pcount].t==21)
		{
			pcount++;
		}
		else
		{
			strcpy(msg," ) missing");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		stat();
	}
	else if(tok[pcount].t==16)
	{
		pcount++;
		if(tok[pcount].t==20)
		{
			pcount++;
		}
		else
		{
			strcpy(msg," ( missing");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		if(!ass_stat())
		{
			strcpy(msg," assignment statement missing");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		if(tok[pcount].t==27)
		{
			pcount++;
		}
		else
		{
			strcpy(msg," statement missing ;");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		exp();
		if(tok[pcount].t==27)
		{
			pcount++;
		}
		else
		{
			strcpy(msg," statement missing ;");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		if(!ass_stat())
		{
			strcpy(msg," assignment statement missing");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		if(tok[pcount].t==21)
		{
			pcount++;
		}
		else
		{
			strcpy(msg," ) missing");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
		stat();
	}
	else
		return 0;
	return 1;
}

void stat()
{
		if(ass_stat())
		{
			if(tok[pcount].t==27)
			{
				pcount++;
			}
			else
			{
				strcpy(msg," statement missing ;");
				cout<<"error at line"<<tok[pcount].line;
				puts(msg);
				getch();
				exit(0);
			}
		}
		else if(dec_stat())
		{}
		else if(loop_stat())
		{}
		else
		{
			strcpy(msg," expression syntax");
			cout<<"error at line"<<tok[pcount].line;
			puts(msg);
			getch();
			exit(0);
		}
}
void stat_list()
{
	while(pcount<count-1)
	{
		stat();
		stat_list();
	}
}

void parser()
{
	if(tok[0].t!=10)
	{
		strcpy(msg," main is missing");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	}
	if(tok[1].t!=20)
	{
		strcpy(msg," declaration syntax error");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	 }
	 if(tok[2].t!=21)
	 {
		strcpy(msg," ) expected");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	 }
	 if(tok[3].t!=22)
	 {
		strcpy(msg," declaration syntax error");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	 }
	 if(tok[count-1].t!=23)
	 {
		strcpy(msg," } expected");
		cout<<"error at line"<<tok[pcount].line;
		puts(msg);
		getch();
		exit(0);
	 }
	 pcount=4;
	 strcpy(msg,"data segment\n");
	 write(msg);
	 dec();
	 strcpy(msg,"data ends\n");
	 write(msg);
	 strcpy(msg,"code segment\n");
	 write(msg);
	 stat_list();
	 strcpy(msg,"code ends\n");
	 write(msg);
	 for(int i=0;i<scount;i++)
		cout<<st[i].name<<"\t"<<st[i].type<<"\n";

}


void main()
{
clrscr();
scanner();
clrscr();
for(int i=0;filename[i]!='.';i++)
	ofname[i]=filename[i];
strcat(ofname,".txt");
ofd.open(ofname,ios::trunc);
puts(filename);
puts(ofname);
//genst();
//clrscr();
parser();
cout<<"parsing successful";
getch();
}


