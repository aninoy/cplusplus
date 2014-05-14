#include<process.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
struct process
{
 int arrv,burst,pri,pid,wait,flag,start;
}p[100];
int flag=0,nop=-1,del=-1,order[100],o=0;
void insert(process x)
{
 int l;
 if(del==-1)
 {
  p[++del]=x;
  nop++;
 }
 else
 {
  if(flag==1)
   l=del;
  else
   l=del-1;
  for(int i=nop;i>l;i--)
  {
   if(p[i].pri>x.pri)
	p[i+1]=p[i];
   else
	break;
  }
  p[i+1]=x;
  nop++;
 }
}
void main()
{
 clrscr();order[0]=-1;
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
   cout<<"Priority: ";
   cin>>x.pri;
   cout<<"Process ID Number: ";
   cin>>x.pid;
   x.flag=0;
   insert(x);
   for(int j=0;j<=nop;j++)
	 cout<<p[j].pri<<"\t";
  }
  else
  {
   flag=1;
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
   {
	del++;
	flag=0;
   }
  }
  cout<<"\nDo you have anymore processes? 1/0: ";
  cin>>choice;
 }
 clrscr(); int sumw=0,sumtat=0;
 cout<<"Orer of execution of processes:-\n";
 for(int j=0;j<o;j++)
  cout<<order[j]<<"\t";
 cout<<"\n";
 for(int i=0;i<=nop;i++)
 {
  cout<<"Process ID: "<<p[i].pid<<"\n";
  cout<<"Arrival Time: "<<p[i].arrv<<"\n";
  //cout<<"Burst Time: "<<p[i].burst<<"\n";
  cout<<"Priority: "<<p[i].pri<<"\n";
  cout<<"Wait Time: "<<p[i].wait<<"\n";
  cout<<"Turn Around Time: "<<p[i].wait+p[i].burst<<"\n";
  sumw+=p[i].wait;
  sumtat+=p[i].wait+p[i].burst;
 }
 cout<<"Average Wait Time: "<<sumw/(nop+1)<<"\n";
 cout<<"Average Turn Around Time: "<<sumtat/(nop+1);//<<"\n";
 getch();
}