#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<process.h>
#include<stdio.h>
void main()
{
 clrscr();
 FILE *f,*g;
 int i=0,k;
 char c;
 f=fopen("d:\Reem.txt","w+");
 if(f==NULL)
 {
  cout<<"Can't open file!";
  getch();
  exit(0);
 }
 else
  cout<<"File opened!"<<"\n";
 while(i<5)
 {
  c=char(i);
  c=putc(c,f);
  if(k==EOF)
  {
   cout<<"Error in writing";
   getch();
   exit(0);
  }
  i++;
 }
 cout<<"File Written!"<<"\n";
 g=fopen("d:\Reem.txt","r");
 if(g==NULL)
 {
  cout<<"Can't open file!";
  getch();
  exit(0);
 }
 cout<<"File Opened!"<<"\n";
 i=0;
 while(i<5)
 {
  c=getc(g);
  if(c==EOF)
  {
   cout<<"Error in reading";
   getch();
   exit(0);
  }
  cout<<c<<"\n";
  i++;
 }
 cout<<"File Read!"<<"\n";
 k=fclose(f);
 k=fclose(g);
 cout<<"File Closed!"<<"\n";
 getch();
}
