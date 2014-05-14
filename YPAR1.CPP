#include<iostream.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<io.h>
int val,flags=0;
struct symboltable
{
 char name[100];
 int value;
}symtab[100];
int line=1;
struct identifier
{
 char name[100];
 char type[20];
 int value;
 int f;
}id[20],in[20],ch[20];
int j=0;
int j1=0,j2=0,j3=0;
enum{rbopen=20,rbclose,cbopen,cbclose,sqbopen,sqbclose,comma,colon,equal,ne=30,lt=33,gt,plus,minus,multiply,divide,mod,number=51,unknown=100};

struct keyword
{
 char name[10];
 int value;
}kw[]={{"main",10},{"int",11},{"char",12},{"if",13},{"else",14},{"while",15},{"for",16}};
char token[20];
char token1[20];
char *p;

void eatwhitespaces()
{
 while(*p == ' '||*p == '\t'||*p=='\n')
 {
  if(*p=='\n')
  {
   ++line;
   strcpy(token1,"undefined");
  }
  p++;
 }
}
char *pos;
int scanner()
{
 strcpy(token1,"undefined");
 eatwhitespaces();
 char *pe;
 //    p=token;
 //    pos=token;
 switch(*p)
 {
	case '(':p++;
			 strcpy(token,"(");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=rbopen;
			 j++;
			 return rbopen;
	case ')':p++;
			 strcpy(token,")");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=rbclose;
			 j++;
			 return rbclose;
	case '{':p++;
			 strcpy(token,"{");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=cbopen;
			 j++;
			 return cbopen;
	case '}':p++;
			 strcpy(token,"}");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=cbclose;
			 j++;
			 return cbclose;
	case '[':p++;
			 strcpy(token,"[");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=sqbopen;
			 j++;
			 return sqbopen;
	case ']':p++;
			 strcpy(token,"]");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=sqbclose;
			 j++;
			 return sqbclose;
	case ',':p++;
			 strcpy(token,",");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=comma;
			 j++;
			 return comma;
	case ';':p++;
			 strcpy(token,";");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=colon;
			 j++;
			 return colon;
	case '=':p++;
			 strcpy(token,"=");
			 if(*p=='=')
			 {
			  strcat(token,"=");
			  strcpy(symtab[j].name,token);
			  symtab[j].value=29;
			  j++;
			  p++;
			 }
			 else
			 {
			  strcpy(symtab[j].name,token);
			  symtab[j].value=equal;
			  j++;
			 }
			 return equal;
	case '<':p++;
			 strcpy(token,"<");
			 if(*p=='=')
			 {
			  strcat(token,"=");
			  strcpy(symtab[j].name,token);
			  symtab[j].value=31;
			  j++;
			  p++;
			 }
			 else
			 {
			  strcpy(symtab[j].name,token);
			  symtab[j].value=lt;
			  j++;
			 }
			 return lt;
	case '>':p++;
			 strcpy(token,">");
			 if(*p=='=')
			 {
			  strcat(token,"=");
			  strcpy(symtab[j].name,token);
			  symtab[j].value=32;
			  j++;
			  p++;
			 }
			 else
			 {
			  strcpy(symtab[j].name,token);
			  symtab[j].value=gt;
			  j++;
			 }
			 return gt;
	case '!':p++;
			 strcpy(token,"!");
			 if(*p=='=')
			 {
			  strcat(token,"=");
			  strcpy(symtab[j].name,token);
			  symtab[j].value=30;
			  j++;
			  p++;
			 }
			 return ne;
	case '+':p++;
			 strcpy(token,"+");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=plus;
			 j++;
			 return plus;
	case '-':p++;
			 strcpy(token,"-");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=minus;
			 j++;
			 return minus;
	case '*':p++;
			 strcpy(token,"*");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=multiply;
			 j++;
			 return multiply;
	case '/':p++;
			 strcpy(token,"/");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=divide;
			 j++;
			 return divide;
	case '%':p++;
			 strcpy(token,"%");
			 strcpy(symtab[j].name,token);
			 symtab[j].value=mod;
			 j++;
			 return mod;
	default:int flag=0;
			int flag1=0;
			pos = token;
			if(isdigit(*p))
			{
			 while(isdigit(*p))
			 {
			  *pos = *p;
			  pos++;
			  p++;
			 }
			 *pos = '\0';
			 //    cout<<token<<"Number\n";
			 return number;
			}
			else if(isalpha(*p))
			{
			 while(isalnum(*p)||*p == '_'|| *p=='@'||*p=='#'||*p=='~'||*p=='?'||*p=='$'||*p=='%'||*p=='^')
			 {
			  if(*p=='@'||*p=='#'||*p=='~'||*p=='?'||*p=='$'||*p=='%'||*p=='^')
			  {
			   flag1=3;
			  }
			  *pos = *p;
			  pos++;
			  p++;
			 }
			 *pos = '\0';
			 for(int i = 0; i <= 6; i++)
			 {
			  if(strcmp(token, kw[i].name)==0)
			  {
			   val=kw[i].value;
			   strcpy(symtab[j].name,token);
			   if(strcmp(token,"int")==0||strcmp(token,"char")==0)
				strcpy(token1,token);
			   symtab[j].value=val;
			   j++;
			   flag=1;
			   return val;
			  }
			 }
			 if(flag==0)
			 {
			  strcpy(symtab[j].name,token);
			  symtab[j].value=100;
			  j++;
			  if(strcmp(token1,"int")==0)
			  {
			   if(flag1==0)
			   {
				int fl=0;
				for(int s3=0;s3<j3;s3++)
				{
				 if(strcmp(token,in[s3].name)==0)
				 {
				  fl=1;
				  break;
				 }
				}
				  if(fl==0)
				  {
				strcpy(in[j3].name,token);
				strcpy(in[j3].type,token1);
				in[j3].value=100;
				in[j3].f=0;
				j3++;
				break;
			   }
			   }
			   else
			   {
				strcpy(id[j1].name,token);
				strcpy(id[j1].type,"undefined");
				id[j1].value=100;
				j1++;
				break;
			   }
			  }
			  else if(strcmp(token1,"char")==0)
			  {
			   if(flag1==0)
			   {             int fl1=0;

				for(int s4=0;s4<j2;s4++)
					{
					if(strcmp(token,ch[s4].name)==0)
					{
					fl1=1;
					break;
					}
					}
					if(fl1==0)
					{
				strcpy(ch[j2].name,token);
				strcpy(ch[j2].type,token1);
				ch[j2].value=100;
				ch[j2].f=0;
				j2++;
				break;
				}
			   }
			   else
			   {
				strcpy(id[j1].name,token);
				strcpy(id[j1].type,"undefined");
				id[j1].value=100;
				j1++;
				break;
			   }
			  }
			  else
			  {
			   strcpy(id[j1].name,token);
			   strcpy(id[j1].type,"undefined");
			   id[j1].value=100;
			   j1++;
			   break;
			  }
			 }
			}
			else
			{
			 token[0]=*p++;
			 token[1]='\0';
			 strcpy(symtab[j].name,token);
			 symtab[j].value=100;
			 j++;
			}
 }
 return 1;
}

int exun()
{
 int fl=0;
 int t1;
 for(int s3=0;s3<j3;s3++)
 {
  if(strcmp(token,in[s3].name)==0)
  {
   t1=in[s3].f;
   if(in[s3].f==0)
	in[s3].f=1;
   fl=1;
   break;
  }
 }
 if(fl==0)
  for(int s5=0;s5<j2;s5++)
  {
   if(strcmp(token,ch[s5].name)==0)
   {
	t1=ch[s5].f;
	if(ch[s5].f==0)
	 ch[s5].f=1;
	fl=1;
	break;
   }
  }
 if(fl==1)
  return t1;
 else
  return 0;
}
int exun1()
{
 int fl=0;
 int t1;
 for(int s3=0;s3<j3;s3++)
 {
  if(strcmp(token,in[s3].name)==0)
  {
   t1=in[s3].f;
   if(in[s3].f==0)
	in[s3].f=1;
   fl=1;
   break;
  }
 }
 if(fl==0)
  for(int s5=0;s5<j2;s5++)
  {
   if(strcmp(token,ch[s5].name)==0)
   {
	t1=ch[s5].f;
	if(ch[s5].f==0)
	 ch[s5].f=1;
	fl=1;
	break;
   }
  }
 return fl;
}


char err[100];
int relop()
{
 if(strcmp(token,"==")==0 ||strcmp(token,"!=")==0 ||strcmp(token,"<=")==0 || strcmp(token,">=")==0 || strcmp(token,">")==0 || strcmp(token,"<")==0)
  return 1;
 else
  return 0;
}
int id1();
int factor()
{
 if(scanner()==number)
 {
  return 1;
 }
 else
 {
  if(id1())
   {
	if(exun1()==0)
	{
	 cout<<"line "<<line<<"\t";
	 cout<<"undefined variable\n";
	}
	return 1;
   }
  else
   return 0;
 }
}

int id1()
{
 int f2=0;
 for(int i=0;i<j3;i++)
 {
  if(strcmp(token,in[i].name)==0)
  {
   /*if(in[i].f==0)
   {
	in[i].f=1;
   }
   else
   {
	cout<<"line "<<line<<"\t";
	cout<<"doubly defined variable\n";
   } */
   f2=1;
   break;
  }
 }
 if(f2==0)
 {
  for(int i=0;i<j2;i++)
  {
   if(strcmp(token,ch[i].name)==0)
   {
	/*if(ch[i].f==0)
   {
   ch[i].f=1;
   }
   else
   {
	cout<<"line "<<line<<"\t";
	cout<<"doubly defined variable\n";
   }  */
	f2=1;
	break;
   }
  }
  if(f2==0)
  {
   for(int i=0;i<j1;i++)
   {
	if(strcmp(token,id[i].name)==0)
	{
	 f2=1;
	 break;
	}
   }
  }
 }

 /*else return 0;
 if(f2==0)
  return 0;
 /*if(exun())
 {
  cout<<"line "<<line<<"\t"<<"doubly defined variable\n";
  return 1;
 }
 else
 {
  if(f2==-1)
  {
   cout<<"line "<<line<<"\t"<<"undefined variable\n";
   return 1;
  }
  else return 1;
 }         */
 return f2;
}

int idlist()
{
 //int f3=0;
 if(id1()==1)
 {
  if(exun()==1)
  {
  cout<<"line "<<line<<"\t";
  cout<<"doubly defined variable\n";
  }
  //f3=1;
  scanner();
  if(strcmp(token,",")==0)
  {
   scanner();
   if(idlist()==1)
	return 1;
   else
	return 0;
  }
  else if(strcmp(token,"[")==0)
  {
   if(scanner()==number)
   {
	scanner();
	if(strcmp(token,"]")==0)
	{
	 scanner();
	 if(strcmp(token,",")==0)
	 {
	  scanner();
	  if(idlist())
	   return 1;
	  else
	   return 0;
	 }
	 else
	 {
	  int l=strlen(token);
	  for(int a1=0;a1<l;a1++)
	   p--;
	  return 1;
	 }
	}
	else

	{cout<<"line "<<line<<"\n";
	cout<<"] missing";
	getch();
	exit(0);
	}
   }
   else
	{
	cout<<"line "<<line<<"\n";
	cout<<"array range missing";
       getch();
       exit(0);
       }//	strcat(err,line));
  }
  else
  {
   int l=strlen(token);
   for(int a1=0;a1<l;a1++)
	p--;
   return 1;
  }
 }
 else
  return 0;
 return -1;
}

int tprime()
{
 if(strcmp(token,"*")==0 || strcmp(token,"/")==0)
 {
  if(factor()==1)
  {
   scanner();
   if(tprime()==1)
	return 1;
   else
	return 0;
  }
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"factor missing");
   return 0;
  }
 }
 else
 {
  for(int i=0;i<strlen(token);i++)
   p--;
  return 1;
 }
}


int term()
{
 if(factor()==1)
 {
  scanner();
  if(tprime()==1)
  {
   return 1;
  }
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"tprime missing");
   return 0;
  }
 }
 else
  return 0;
}


int seprime()
{
 if(strcmp(token,"+")==0 || strcmp(token,"-")==0)
 {
  if(term()==1)
  {
   scanner();
   if(seprime()==1)
   {
	return 1;
   }
   else
	return 1;
  }
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"term missing");
   return 0;
  }
 }
 else
 {
  for(int i=0;i<strlen(token);i++)
   p--;
  return 1;
 }
}


int simpleexpn()
{
 if(term()==1)
 {
  scanner();
  if(seprime()==1)
  {
   return 1;
  }
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"seprime missing");
   return 0;
  }
 }
 else
  return 0;
}


int eprime()
{
 if(relop()==1)
 {
  if(simpleexpn()==1)
  {
   return 1;
  }
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"simple expn missing");
   return 0;
  }
 }
 else
 {
  int l=strlen(token);
  for(int a3=0;a3<l;a3++)
   p--;
  return 1;
 }
}


int expn()
{
 if(simpleexpn()==1)
 {
  scanner();
  if(eprime()==1)
   return 1;
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"eprime missing");
   return 0;
  }
 }
 else
  return 0;
}


int assignstat()
{
 scanner();
 if(id1()==1)
 {
  if(exun1()==0)
  {
   cout<<"line "<<line<<"\t";
   cout<<"undefined variable\n";
  }
  scanner();
  if(strcmp(token,"=")==0)
  {
   if(expn()==1)
   {
	return 1;
   }
   else
   {
	cout<<"line "<<line<<"\n";
	cout<<"expn missing";
	getch();
	exit(0);
   }
  }
  else
  {
  cout<<"line "<<line<<"\n";
   cout<<"= missing";
   getch();
   exit(0);
  }
 }
 else
 {
  for(int a2=0;a2<strlen(token);a2++)p--;
  return 0;
 }
}




int decisionstat();
int loopingstat();

int stat()
{
 if(assignstat()==1 || decisionstat()==1 || loopingstat()==1)
 {
  return 1;
 }
 else
  return 0;
}

int statlist()
{
 if(stat()==1)
 {
  scanner();
  if(strcmp(token,";")==0)
  {
   if(statlist()==1)
   {
	return 1;
   }
   else
   {
	//strcpy(err,"statlist missing");
	return 0;
   }
  }
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"; missing");
   return 0;
  }
 }
 else
 {
  int l=strlen(token);
  for(int a5=0;a5<l;a5++)
   p--;
  return 1;
 }
}


int dprime()
{
 scanner();
 if(strcmp(token,"else")==0)
 {
  if(stat()==1)
  {
   return 1;
  }
  else
   return 0;
 }
 else
 {
  int l=strlen(token);
  for(int a4=0;a4<l;a4++)
   p--;
  return 1;
 }
}


int decisionstat()
{
 scanner();
 if(strcmp(token,"if")==0)
 {
  scanner();
  if(strcmp(token,"(")==0)
  {
   if(expn()==1)
   {
	scanner();
	if(strcmp(token,")")==0)
	{
	 if(stat()==1)
	 {
	  if(dprime()==1)
	  {
	   //cout<<"valid decision statement";
	   return 1;
	  }
	  else
	  {
	   cout<<"line "<<line<<"\n";
	   cout<<"dprime missing";
	   getch();
	   exit(0);
	  }
	 }
	 else
	 {
	  cout<<"line "<<line<<"\n";
	  cout<<"stat missing";
	  getch();
	  exit(0);
	 }
	}
	else
	{
	 cout<<"line "<<line<<"\n";
	 cout<<") missing";
	 getch();
	 exit(0);
	}
   }
   else
   {
	cout<<"line "<<line<<"\n";
	cout<<"expn missing";
	getch();
	exit(0);
   }
  }
  else
  {
  cout<<"line "<<line<<"\n";
   cout<<"( missing";
   getch();
   exit(0);
  }
 }
 else
 {
  for(int i=0;i<strlen(token);i++)
   p--;
  return 0;
 }
}


int loopingstat()
{
 scanner();
 if(strcmp(token,"while")==0)
 {
  scanner();
  if(strcmp(token,"(")==0)
  {
   if(expn()==1)
   {
	scanner();
	if(strcmp(token,")")==0)
	{
	 if(stat()==1)
	 {
	  //cout<<"valid while loop";
	  return 1;
	 }
	 else
	 {
	  cout<<"line "<<line<<"\n";
	  cout<<"missing stat";
	  getch();
	  exit(0);
	 }
	}
	else
	{
	 cout<<"line "<<line<<"\n";
	 cout<<") missing";
	 getch();
	 exit(0);
	}
   }
   else
   {
	cout<<"line "<<line<<"\n";
	cout<<"expn missing";
	getch();
	exit(0);
   }
  }
  else
  {
   cout<<"line "<<line<<"\n";
   cout<<"( missing";
   getch();
   exit(0);
  }
 }
 else if(strcmp(token,"for")==0)
 {
  scanner();
  if(strcmp(token,"(")==0)
  {
   if(assignstat()==1)
   {
	scanner();
	if(strcmp(token,";")==0)
	{
	 if(expn()==1)
	 {
	  scanner();
	  if(strcmp(token,";")==0)
	  {
	   if(assignstat()==1)
	   {
		scanner();
		if(strcmp(token,")")==0)
		{
		 if(stat()==1)
		 {
		  //cout<<"valid for stmt";
		  return 1;
		 }
		 else
		 {
		  cout<<"line "<<line<<"\n";
		  cout<<"stat in for missing";
		  getch();
		  exit(0);
		 }
		}
		else
		{
		 cout<<"line "<<line<<"\n";
		 cout<<") missing";
		 getch();
		 exit(0);
		}
	   }
	   else
	   {
		cout<<"line "<<line<<"\n";
		cout<<"2nd assignstmt in for loop missing";
		getch();
		exit(0);
	   }
	  }
	  else
	  {
	  cout<<"line "<<line<<"\n";
	  //cout<<"line "<<line<<"\n";
	   cout<<"2nd ; in for loop missing";
	   getch();
	   exit(0);
	  }
	 }
	 else
	 {
	  cout<<"line "<<line<<"\n";
	  cout<<"expn missing";
	  getch();
	  exit(0);
	 }
	}
	else
	{
	 cout<<"line "<<line<<"\n";
	 cout<<"first ; in for loop missing";
	 getch();
	 exit(0);
	}
   }
   else
   {     cout<<"line "<<line<<"\n";
	cout<<"1st assignstat in for loop missing";
	getch();
	exit(0);
   }
  }
  else
  {
   cout<<"line "<<line<<"\n";
   cout<<"( in for loop missing";
   getch();
   exit(0);
  }
 }
 else
 {
  for(int i=0;i<strlen(token);i++)
   p--;
  return 0;
 }
}


int datatype()
{
 if(strcmp(token,"int")==0 || strcmp(token,"char")==0)
  return 1;
 else
  return 0;
}


int declarations()
{
 if(datatype()==1)
 {
  scanner();
  if(idlist()==1)
  {
   scanner();
   if(strcmp(token,";")==0)
   {
	scanner();
	if(declarations())
	{
	 return 1;
	}
	else
	 return 0;
   }
   else
   {
	cout<<"line "<<line<<"\n";
	strcpy(err,"; missing");
	return 0;
   }
  }
  else
  {
   cout<<"line "<<line<<"\n";
   strcpy(err,"id missing");
   return 0;
  }
 }
 else
 {
  int l=strlen(token);
  for(int a2=0;a2<l;a2++)
   p--;
  return 1;
 }
}


int program()
{
 scanner();
 if(strcmp(token,"main")==0)
 {
  scanner();
  if(strcmp(token,"(")==0)
  {
   scanner();
   if(strcmp(token,")")==0)
   {
	scanner();
	if(strcmp(token,"{")==0)
	{
	 scanner();
	 if(declarations()==1)
	 {
	  //scanner();
	  if(statlist())
	  {
	   scanner();
	   if(strcmp(token,"}")==0)
	   {
		cout<<"valid prog";
		return 1;
	   }
	   else
	   {
		   //	cout<<"line "<<line<<"\n";
		strcpy(err,"} missing");
		return 0;
	   }
	  }
	  else
	  {
	   //strcpy(err,"invalid stmt");
	   return 0;
	  }
	 }
	 else
	  return 0;
	}
	else
	{
	 strcpy(err,"missing { after main");
	 return 0;
	}
   }
   else
   {
	strcpy(err,"missing ) after main");
	return 0;
   }
  }
  else
  {
   strcpy(err,"missing ( after main");
   return 0;
  }
 }
 else
 {
  strcpy(err,"missing main");
  return 0;
 }
}


void main()
{
 clrscr();
 char fname[15];
 cout<<"enter the file name";
 cin>>fname;
 FILE *f;
 char p1;
 f=fopen(fname,"rt");
 char line[80];
 char c1;
 int i=0;
 char ar[20000];
 c1=fgetc(f);
 //int f1=open("t.cpp",O_RDWR);
 while(!feof(f))
 {
  ar[i]=c1;
  cout<<ar[i];
  i++;
  c1=fgetc(f);
 }
 ar[i]='@';
 //int g=i;
 p=ar;
 //clrscr();
 cout<<"....:::: ERRORS ::::....\n\n";
 if(*p!='@')
 {
  program();
  cout<<err<<"\n";
 }
 /*getch();
 for(int i1=0;i1<j1;i1++)
 {
 cout<<id[i1].name<<" ";
 } */

 fclose(f);
 getch();
}