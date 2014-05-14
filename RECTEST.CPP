#include<iostream.h>
#include<conio.h>
void test(int i)
{
 int flag=0;
 switch(i)
 {
  case 1: flag=1;
		  break;
  case 2: flag=5;
		  break;
  case 3: flag=10;
		  break;
  case 4: flag=15;
		  break;
  //case 5: flag=20;
 }
 if(i>5)
  return;
 test(i+1);
 cout<<"i: "<<i<<"\tflag: "<<flag<<"\n";
}
void main()
{
 clrscr();
 test(0);
 getch();
}