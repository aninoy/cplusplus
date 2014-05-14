#include<process.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
struct process
{
 int arrv,burst,pid,wait,flag,start;
}p[100];
int nop=-1,del=-1,order[100],o=0;
void insert(process x)
{
 p[++nop]=x;
 if(del==-1)
  del++;
}
void main()
{
 clrscr();order[o]=-1;
 int choice,t=0,rem,done;
 process x;
 cout<<"Do you have any processes? 1/0: ";
 cin>>choice;
 if(choice==0)
  exit(0);
 while((choice==1 || choice==0)&& del<=nop)
 {
  if(choice==1)
  {
   cout<<"Arrival Time: "<<t<<"\n";
   x.arrv=t;
   cout<<"Burst Time: ";
   cin>>x.burst;
   cout<<"Process ID Number: ";
   cin>>x.pid;
   x.flag=0;
   insert(x);
   for(int j=0;j<=nop;j++)
	cout<<p[j].pid<<"\t";

  }
  else
  {
   if(p[del].flag==0)
   {
    p[del].start=t;
    p[del].wait=p[del].start-p[del].arrv;
    p[del].flag=1;
   }
   if(order[o-1]!=p[del].pid)
	order[o++]=p[del].pid;
   t++;
   cout<<"\nTime = \t\t"<<t<<"\n";
   cout<<"Process currently executing: "<<p[del].pid<<"\n";
   done=t-p[del].start;
   rem=p[del].burst-done;
   cout<<"Time remaining for its completion: "<<rem<<"\n";
   if(rem==0)
	del++;
  }
  cout<<"\nDo you have anymore processes? 1/0: ";
  cin>>choice;
 }
 clrscr(); int sumw=0,sumtat=0;
 cout<<"Order of execution of processes:-\n";
 for(int i=0;i<o;i++)
  cout<<order[i]<<"\t";
 cout<<"\n";
 for(i=0;i<=nop;i++)
 {
  cout<<"Process ID: "<<p[i].pid<<"\n";
  cout<<"Arrival Time: "<<p[i].arrv<<"\n";
  cout<<"Wait Time: "<<p[i].wait<<"\n";
  cout<<"Turn Around Time: "<<p[i].wait+p[i].burst<<"\n\n";
  sumw+=p[i].wait;
  sumtat+=p[i].wait+p[i].burst;
 }
 cout<<"Average Wait Time: "<<sumw/(nop+1)<<"\n";
 cout<<"Average Turn Around Time: "<<sumtat/(nop+1)<<"\n";
 getch();
}