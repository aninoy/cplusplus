#include<dos.h>
#include<iostream.h>
#include<conio.h>
void main()
{
 clrscr();
 int i=0;
 while(i<5)
 {
  gotoxy(10,10);
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
  delay(1000);
 }
 getch();
}
