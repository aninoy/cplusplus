#include<dos.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
int posn[5][5];
void display()
{
 for(int i=0;i<5;i++)
 {
  gotoxy(posn[i][0],posn[i][1]);
  cout<<"*";
 }
}
void main()
{
 clrscr();
 int i;
 posn[0][0]=10;
 posn[1][0]=9;
 posn[2][0]=8;
 posn[3][0]=7;
 posn[4][0]=6;
 posn[0][1]=10;
 posn[1][1]=10;
 posn[2][1]=10;
 posn[3][1]=10;
 posn[4][1]=10;
 for(i=0;i<10000;i++)
 {
  for(int j=0;j<5;j++)
  {
   posn[j][0]=posn[j][0]+1;
   if(posn[j][0]>79)
	posn[j][0]=0;
  }
  display();
  delay(50);
  clrscr();
 }
 getch();
}