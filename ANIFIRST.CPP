#include<iostream.h>
#include<conio.h>
#include<process.h>
struct mem
{
 int stadd,hole,flag;
}m[50];
int proc[15],n=-1;
void insert(mem x)
{
 m[++n]=x;
}
int first(int s)
{
 int flag=0,j=0;
 for(int i=0;i<=n;i++)
 {
  if(m[i].hole>=s)
  {
   flag=1;
   j=i;
   break;
  }
 }
 if(flag==1)
 {
  m[j].hole-=s;
  m[j].stadd+=s;
 }
 return flag;
}
void main()
{
 clrscr();
 int choice1=-1,choice2=-1,size,y;
 mem x;
 cout<<"Do you have any free space? 1/0: ";
 cin>>choice1;
 if(choice1==0)
 {
  cout<<"Do you have any processes? 1/0: ";
  cin>>choice2;
  if(choice2==0)
   exit(0);
 }
 while(choice1!=0 || choice2!=0)
 {
  if(choice1==1)
  {
   cout<<"Enter the Starting Address: ";
   cin>>x.stadd;
   cout<<"Enter the Hole Size: ";
   cin>>x.hole;
   x.flag=0;
   insert(x);
   //cout<<"\n";
   //for(int k=0;k<=n;k++)
   // cout<<m[k].stadd<<"\t";
   cout<<"\n";
   cout<<"Do you have anymore free space? 1/0: ";
   cin>>choice1;
  }
  else
  {
   if(choice2==-1)
   {
	cout<<"Do you have any processes? 1/0: ";
	cin>>choice2;
	choice1=0;
   }
  }
  if(choice2==1)
  {
   cout<<"Enter Process Size: ";
   cin>>size;
   y=first(size);
   if(y==0)
    cout<<"This process can't be allocated memory!\n";
   else
   {
    cout<<"New ASL :-\n";
    for(int i=0;i<=n;i++)
     cout<<m[i].stadd<<"\t"<<m[i].hole<<"\n";
   }
   cout<<"\nDo you have anymore processes? 1/0: ";
   cin>>choice2;
  }
 }
 getch();
}