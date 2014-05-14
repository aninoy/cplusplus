#include<conio.h>
#include<iostream.h>
#include<stdlib.h>
void main()
{
 clrscr();
 int a;
 cout<<"Enter : ";
 cin>>a;
 char m[3];
 itoa(a,m,8);
 cout<<"Neg: "<<m;
 char x='7'-'0';
 cout<<"x: "<<x;
 getch();
}