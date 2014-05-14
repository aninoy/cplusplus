#include<iostream.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
int val;
struct symboltable
{
char name[50];
int value;
}symtab[80];

struct identifier
{
char name[50];
char type[50];
int value;
}id[50];
int j=0;
int j1=0;
enum{rbopen=20,rbclose,cbopen,cbclose,sqbopen,sqbclose,comma,colon,equal,ne=30,lt=33,gt,plus,minus,multiply,divide,mod,number=51,unknown=100};

struct keyword
{
char name[50];
int value;
}kw[]={{"main",10},{"int",11},{"char",12},{"if",13},{"else",14},{"while",15},{"for",16}};
char token[50];
char token1[50];
char *p;

void eatwhitespaces() {
	while(*p == ' '||*p == '\t') {
		p++;
	}
}
char *pos;
int scanner() {
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

	case ')':
		 p++;
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
		  p++;}
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
		  p++;}
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
		  p++;}
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


		   default:
		   int flag=0;
		   int flag1=0;
		   pos = token;
		   if(isdigit(*p)) {
				while(isdigit(*p)) {
					*pos = *p;
					pos++;
					p++;
				}
				*pos = '\0';
				//cout<<token<<"Number\n";
				strcpy(symtab[j].name,token);
				symtab[j].value=number;
				j++;

				return number;
			}



		else if(isalpha(*p))
			 {
			  while(isalnum(*p)||*p == '_'|| *p=='@'||*p=='#'||*p=='~'||*p=='?'||*p=='$'||*p=='%'||*p=='^')
			  {
				if(*p=='@'||*p=='#'||*p=='~'||*p=='?'||*p=='$'||*p=='%'||*p=='^')
				{flag1=3;}

				*pos = *p;
				pos++;
				p++;
			  }


				*pos = '\0';

				for(int i = 0; i <= 6; i++)
				{

					if(strcmp(token, kw[i].name)==0)
					{

						val = kw[i].value;
						strcpy(symtab[j].name,token);
						if((strcmp(kw[i].name,"int")==0) || strcmp(kw[i].name,"char")==0)
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
					 symtab[j].value=50;
					 j++;

						  if(strcmp(token1,"int")==0||strcmp(token1,"char")==0)
						  {
						   if(flag1==0)
						   {
							strcpy(id[j1].name,token);
							strcpy(id[j1].type,token1);
							id[j1].value=50;
							j1++;
						   }
						   else if(flag1==3)
						   {
								strcpy(id[j1].name,token);
								strcpy(id[j1].type,"undefined");
								id[j1].value=50;
								j1++;
						   }
						  }
						  else
						  {
						   strcpy(id[j1].name,token);
						   strcpy(id[j1].type,"undefined");
						   id[j1].value=50;
						   j1++;
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
void main()
{
 clrscr();
 char fname[15];
 cout<<"enter the file name";
 cin>>fname;
 // int j=0;
 FILE *f;
 char p1;
 f=fopen(fname,"rt");
 char line[80];
 while(fgets(line,80,f)!=NULL)
 {
  p=line;
  getch();
  strcpy(token1,"undefined");
  while(*p!='\n'&& *p!='\0')
  {
   scanner();
  }
 }
 for(int i=0;i<j;i++)
 {
  cout<<symtab[i].name<<"  "<<symtab[i].value;
  cout<<"\n";
  getch();
 }
cout<<"\n\n";
 cout<<"======================IDENTIFIERS=================================";
 cout<<"\nUNDEFINED\n";
 for(int i1=0;i1<j1;i1++)
 {
  if(strcmp(id[i1].type,"undefined")==0)
  {
   cout<<id[i1].name<<"     "<<id[i1].value;
   cout<<"\n";
  }
 }
 cout<<"\nINT\n";
 for(int i31=0;i31<j1;i31++)
 {
  if(strcmp(id[i31].type,"int")==0)
  {
   cout<<id[i31].name<<"     "<<id[i31].value;
   cout<<"\n";
  }
 }
 cout<<"\nCHAR\n";
 for(int i21=0;i21<j1;i21++)
 {
  if(strcmp(id[i21].type,"char")==0)
  {
   cout<<id[i21].name<<"     "<<id[i21].value;
   cout<<"\n";
  }
 }
 fclose(f);
 getch();
}