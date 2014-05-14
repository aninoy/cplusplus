#include<string.h>
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
int n;
char a[100];
void main()
{
 clrscr();
 int count[100],i=1;
 int perm(int[],int);
 cout<<"Enter a string: ";
 gets(a);
 n=strlen(a);
 cout<<n<<"\n";
 cout<<"All permutations  are:- \n";
 for(i=0;i<10;i++)
  count[i]=-1;
 i=1;
 int res=perm(count,i);
 cout<<"Done";
 getch();
}
int perm(int count[100],int i)
{
 int flag=0,flag1=0,flag2=0,k,l;
 for(k=0;k<i;k++)
 {
  if(count[k]>=n)
   flag=1;
 }
 if(flag!=1)
 {
  for(k=0;k<i;k++)
  {
   for(l=k+1;l<i;l++)
   {
	if(a[k]==a[l])
	{
	 flag1=1;
	 break;
	}
   }
  }
  if(i==1)
   flag1=0;
  if(flag1==0)
  {
   if(i==n)
   {
	for(k=0;k<i;k++)
	 cout<<a[count[k]];
	cout<<"\n";
   }
   else
   {
	i++;
	count[i]++;
   label:flag2=perm(count,i);
	if(flag2==-1)
	{
	 count[i]++;
	 goto label;
	}
   }
  }
  else
  {
   cout<<"Condition Wrong in level "<<i<<"\n";
   return -1;
  }
 }
 else
 {
  cout<<"Stopped";
  return 0;
 }
}