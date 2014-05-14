#include<iostream.h>
#include<conio.h>
int top=-1,stack[5];
void display(int n)
{
 if(n==1)
 {
  clrscr();
  cout<<"Previous Stack Condition\n\n";
  if(top==-1)
   cout<<"Stack Empty\nTop: Undefined";
  else
  {
   for(int i=top;i>=0;i--)
	cout<<stack[i]<<"\n";
   cout<<"Top: "<<stack[top];
  }
 }
 else
 {
  gotoxy(20,4);cout<<"--->";
  gotoxy(30,1);cout<<"Current Stack Condition";
  for(int i=top,j=0;i>=0;i--,j++)
  {
   gotoxy(30,3+j);cout<<stack[i];
  }
  gotoxy(30,3+j);
  if(top==-1)
   cout<<"Top: Undefined";
  else
   cout<<"Top: "<<stack[top];
 }
 gotoxy(2,24);cout<<"Press any key to continue...";
}
void main()
{
 clrscr();
 int choice;
 cout<<"1.Insert\n2.Delete\n3.Exit\nEnter your choice: ";
 cin>>choice;
 while(choice<3)
 {
  switch(choice)
  {
   case 1:cout<<"\n\nEnter the number to be inserted: ";
		  cin>>choice;
		  if(top<4)
		  {
		   display(1);
		   stack[++top]=choice;
		   display(2);
		  }
		  else
		   cout<<"\n\nStack Overflow Condition!";
		  getch();
		  break;
   case 2:if(top>=0)
		  {
		   display(1);
		   choice=stack[top--];
		   display(2);
		   cout<<"\n\nThe number deleted from Stack is: "<<choice;
		  }
		  else
		   cout<<"\n\nStack Underflow Condition!";
		  getch();
		  break;
  }
  clrscr();
  cout<<"1.Insert\n2.Delete\n3.Exit\nEnter your choice: ";
  cin>>choice;
 }
}