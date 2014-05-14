
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
int old[10],req[10][10],finish[10],alloc[10][10],x=0,need[10][10],avail[10],max[10][10],nor,nop=0,seq[10];
int compare(int a[],int b[])
{
 int flag=1;
 for(int i=0;i<nor;i++)
 {
  if(a[i]>b[i])
   flag=0;
 }
 if(flag==0)
  return 0;
 else
  return 1;
}
void safety(void)
{
 int work[10],flag=0;
 for(int i=0;i<nor;i++)
  work[i]=avail[i];
 for(i=0;i<nop;i++)
  finish[i]=-1;
 int j=0;
 while(flag==0)
 {
  for(i=0;i<nop;i++)
   old[i]=finish[i];
  for(j=0;j<nop;j++)
  {
   if((finish[j]==-1) && (compare(req[j],work)))
   {
    finish[j]=1; flag=1;
    for(i=0;i<nor;i++)
    {
     work[i]=work[i]+alloc[j][i];

    }
   }
  }
  flag=1;
  for(i=0;i<nop;i++)
  {
   if(finish[i]!=old[i])
    flag=0;
  }
 }
 cout<<"The system is deadlocked for:- \n";
 flag=0;
 for(i=0;i<nop;i++)
 {
  if(finish[i]==-1)
  {
   flag=1;
   cout<<i<<"\t";
  }
 }
 if(flag==0)
  cout<<"None of the processes!\n";
 cout<<"\n";
}
void main()
{
 clrscr();
 cout<<"Enter the no. of resource types: ";
 cin>>nor;
 char ch;
 int id;
 cout<<"Enter available row\n";
 for(int i=0;i<nor;i++)
  cin>>avail[i];
 cout<<"Do you have any processes? y/n : ";
 cin>>ch;
 while(ch=='y')
 {
  cout<<"Enter the allocation row\n";
  for(int i=0;i<nor;i++)
   cin>>alloc[nop][i];
  cout<<"Enter the Request row\n";
  for(i=0;i<nor;i++)
  {
   cin>>req[nop][i];
   //need[nop][i]=max[nop][i]-alloc[nop][i];
  }
  nop++;
  cout<<"Do you have any processes? y/n: ";
  cin>>ch;
 }
 safety();
 // cout<<"System is in safe state!\n";
 /*/else
  //cout<<"System is not in safe state!\n";
 //cout<<"Is there any request? y/n: ";
 //cin>>ch;
 //while(ch=='y')
 //{
  cout<<"Enter the process no. that makes a request: ";
  cin>>id;
  cout<<"Enter its request: \n";
  for(i=0;i<nor;i++)
   cin>>req[i];
  if(!compare(req,need[id]))
   cout<<"Process can't request for more than its need!\n";
  else
  {
   if(!compare(req,avail))
    cout<<"Process must wait!\n";
   else
   {
    for(i=0;i<nor;i++)
    {
     avail[i]=avail[i]-req[i];
     alloc[id][i]+=req[i];
     need[id][i]=need[id][i]-req[i];
    }
    if(safety())
    {
     cout<<"Safe Sequence is :-\n";
     for(i=0;i<nop;i++)
      cout<<seq[i]<<"\t";
     cout<<"\nRequest is Granted\n";
    }
    else
    {
     cout<<"Request not Granted!\n";
     for(i=0;i<nor;i++)
     {
      avail[i]=avail[i]+req[i];
      alloc[id][i]=alloc[id][i]-req[i];
      need[id][i]=need[id][i]+req[i];
     }
    }
   }
  }
  cout<<"Is there any request? y/n: ";
  cin>>ch;
 } */
 getch();
}