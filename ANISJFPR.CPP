#include<process.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
struct process
{
 int arrv,burst,comp,rem,pid,wait,tat,flag,start;
}p[100];
int nop=-1,del=-1,order[100],o=0;
void insert(process x)
{
 if(del==-1)
 {
  p[++del]=x;
  nop++;
 }
 else
 {
  for(int i=nop;i>=del;i--)
  {
   if(p[i].rem>x.rem)
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
 clrscr();order[o]=-1;
 int choice,t=0,done;
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
   x.rem=x.burst;
   cout<<"Process ID Number: ";
   cin>>x.pid;
   x.flag=0;
   insert(x);
   for(int j=0;j<=nop;j++)
	 cout<<p[j].rem<<"\t";
  }
  else
  {
   if(p[del].flag==0)
   {
	p[del].start=t;
	cout<<"Start Time = "<<p[del].start<<"\n";
	//p[del].wait=p[del].start-p[del].arrv;
	p[del].flag=1;
   }
   if(order[o-1]!=p[del].pid)
	order[o++]=p[del].pid;
   t++;
   cout<<"\nTime = \t\t"<<t<<"\n";
   cout<<"Process currently executing: "<<p[del].pid<<"\n";
   //done=t-p[del].start;
   //rem=p[del].burst-done;
   p[del].rem--;
   cout<<"Time remaining for its completion: "<<p[del].rem<<"\n";
   if(p[del].rem==0)
   {
	p[del].comp=t;
	cout<<"Completion Time = "<<p[del].comp<<"\n";
	p[del].tat=p[del].comp-p[del].arrv;
	p[del].wait=p[del].tat-p[del].burst;
	del++;
   }
  }
  cout<<"\nDo you have anymore processes? 1/0: ";
  cin>>choice;
 }
 clrscr(); float sumw=0,sumtat=0;
 cout<<"Order of execution of processes:-\n";
 for(int j=0;j<o;j++)
  cout<<order[j]<<"\t";
 cout<<"\n";
 for(int i=0;i<=nop;i++)
 {
  cout<<"Process ID: "<<p[i].pid<<"\n";
  cout<<"Arrival Time: "<<p[i].arrv<<"\n";
  cout<<"Burst Time: "<<p[i].burst<<"\n";
  cout<<"Wait Time: "<<p[i].wait<<"\n";
  cout<<"Turn Around Time: "<<p[i].tat<<"\n\n";
  sumw+=p[i].wait;
  sumtat+=p[i].tat;
 }
 cout<<"Average Wait Time: "<<sumw/(nop+1)<<"\n";
 cout<<"Average Turn Around Time: "<<sumtat/(nop+1)<<"\n";
 getch();
}
