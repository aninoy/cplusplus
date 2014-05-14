#include<iostream.h>
#include<conio.h>
int a[100],n1,sum;
int f(int n,int i,int s,int b[])
{
 int flag=0;
 for(int j=0;j<n1;j++)
 {
  if(b[j]!=0) flag=1;
 }
 if(flag==0 && n!=0 && i>=n1) return -1;
 else
 {
  int flag1=-1;
  for(int j=0;j<n1;j++)
  {
   if(b[j]!=-1) flag1=1;
  }
  if(flag1!=-1 && n==0)
  {
   sum=s;
   return 1;
  }
  else if(flag!=0 && n!=0 && i>=n1) return 0;
  else
  {
   if(i==0)
   {
	s=0;
	for(int k=0;k<n1;k++)
	 b[k]=-1;
   }
   for(j=n/a[i];j>=0;)
   {
	b[i]=j;
	switch(f(n-j*a[i],i+1,s+j,b))
	{
	 case 1: return 1;
	 case -1: return -1;
	 case 0: j--;//return 0;
	}
   }
   return 0;
  }
 }
}
void main()
{
 clrscr();
 int num,x=-1,i=-1,b[10];
 cout<<"Enter the sum and coins: ";
 cin>>num;
 while(x!=0)
 {
  cin>>x;
  a[++i]=x;
 }
 n1=i;
 for(int j=0;j<n1;j++)
  b[j]=-1;
 for(i=0;i<n1-1;i++)
 {
  for(j=0;j<=n1-i-1;j++)
  {
   if(a[j]<a[j+1])
   {
	int t=a[j];
	a[j]=a[j+1];
	a[j+1]=t;
   }
  }
 }
 sum=-1;
 int res=f(num,0,0,b);
 if(res==-1)
  cout<<"-1";
 else
  cout<<"Min num: "<<sum;
 getch();
}