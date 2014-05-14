#include<stdio.h>
#include<iostream.h>
#include<conio.h>
void main()
{
 clrscr();
 int i,j,k,l;
 char a[100];
 cout<<"Enter a 4 letter string: ";
 gets(a);
 cout<<"All permutations  are:- \n";
 for( i=0;i<4;i++)
 {
  for(j=0;j<4;j++)
  {
   if(a[j]==a[i])
	continue;
   for(k=0;k<4;k++)
   {
	if(a[i]==a[k] || a[j]==a[k])
	 continue;
	for(l=0;l<4;l++)
	{
	 if(a[i]==a[l] || a[j]==a[l] || a[k]==a[l])
	  continue;
	 cout<<a[i]<<a[j]<<a[k]<<a[l]<<"\n";
	}
   }
  }
 }
 getch();
}