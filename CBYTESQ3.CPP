#include<iostream.h>
#include<conio.h>
#include<dos.h>
void main()
{
 clrscr();
 int n,a[10],b[10],c[10],flag=0;
 cout<<"Enter : ";
 cin>>n;
 for(int i=0;i<n;i++)
  cin>>a[i]>>b[i]>>c[i];
 for(i=0;i<50;i++)
 {
  for(int j=0;j<50;j++)
  {
   for(int k=0;k<50;k++)
   {
	if(!(i==j==k==0))
	{
	 int s1=0,s2=0,s3=0;
	 for(int x=0;x<n;x++)
	 {
	  s1+=i*a[x];
	  s2+=j*b[x];
	  s3+=k*c[x];
	  if(s1==s2==s3)
	  {
	   flag=1;
	   break;
	  }
	 }
	}
   }
  }
 }
 if(flag==1)
  cout<<"Yes";
 else
  cout<<"No";
 getch();
}