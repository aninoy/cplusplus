#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>

int j,a;
class string
{
char st[100];
public:
string()
{
strcpy(st," ");
}
void get()
{
cout<<" enter the string.."<<"\n";
gets(st);
}
char* gstr()
{
return(st);
}
void put()
{
puts(st);
}


void sort(char s[][20]);
};
void string::sort(char s[][20])
{
char temp[20];
for(int k=0;k<5;k++)
{
for(j=0;j<5-k-1;j++)
{
a=strcmp(s[j],s[j+1]);
if(a>0)
{
strcpy(temp,s[j]);
strcpy(s[j],s[j+1]);
strcpy(s[j+1],temp);
}
}
}
for(j=0;j<5;j++)
puts(s[j]);

}

 void main()
 {
 clrscr();
string str[5];
 string temp;
 char st[5][20];
 cout<<" enter the strings..."<<"\n";
 for(int i=0;i<5;i++)
 {
 str[i].get();
}
 cout<<" printing the original list of strings.."<<"\n";
 for(i=0;i<5;i++)
 {
str[i].put();
 }
 for(i=0;i<5;i++)
 {
 strcpy(st[i],str[i].gstr());
 }
 for(i=0;i<5;i++)
 {
 cout<<"\n"<<st[i];
 }
 temp.sort(st);

 getch();
 }




