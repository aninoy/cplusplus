#include<process.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
struct process
{
 int arrv,burst,comp,rem,pid,wait,tat,flag,start;
}p[100];
int nop=-1,del=-1,dele[100],k=0,order[100],o=0,time[100];
void insert(process x)
{
 p[++nop]=x;
}
int search(int x)
{
 for (int i=0;i<=k;i++)
 {
  if(dele[i]==x)
   return 1;
 }
 return 0;
}
void main()
{
 clrscr();   order[0]=-1;
 int send,choice,t=0,q,flag=0;
 process x;
 for(int j=0;j<100;j++)
  dele[j]=-1;
 cout<<"Enter the value of Q= ";
 cin>>q;
 cout<<"Do you have any processes? 1/0: ";
 cin>>choice;
 if(choice==0)
  exit(0);
 else
  nop=-2;
 while((choice==1 || choice==0)&& k!=nop+1)
 {
  flag=0;
  if(nop==-2)
   nop=-1;
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
	 cout<<p[j].pid<<"\t";
  }
  else
  {
   //cout<<"Nop = "<<nop+1<<"\n";
   del++;
   send=del%(nop+1);
   del=send;
   cout<<"Send = "<<send<<"\n";
   flag=search(send);
   cout<<"flag = "<<flag<<"\n";
   if(flag==0)
   {
	if(p[del].flag==0)
	{
	 p[del].start=t;
	 p[del].flag=1;
	}
	if(order[o-1]!=p[del].pid)
	{
	 order[o]=p[del].pid;
	 time[o++]=t;
	}
	if(p[del].rem>=q)
	 j=q;
	else
	 j=p[del].rem;
	t+=j;
	cout<<"\nTime = "<<t<<"\n";
	cout<<"Process currently executing: "<<p[del].pid<<"\n";
	p[del].rem-=j;
	cout<<"Time remaining for its completion: "<<p[del].rem<<"\n";
	if(p[del].rem==0)
	{
	 p[del].comp=t;
	 cout<<"Completion Time = "<<p[del].comp<<"\n";
	 p[del].tat=p[del].comp-p[del].arrv;
	 p[del].wait=p[del].tat-p[del].burst;
	 dele[k++]=del;
	}
   }
  }
  if(flag!=1)
  {
   cout<<"\nDo you have anymore processes? 1/0: ";
   cin>>choice;
  }
 }
 time[o]=t;
 int tot=t,dyn;
 dyn=80/tot-1;
 if( dyn==0)
  dyn++;
 clrscr(); float sumw=0,sumtat=0;
 gotoxy(2,5);
 //cout<<"Order of execution of processes:-\n";
 cout<<"Gantt Chart:- \n\n";
 int c,y,k=-1;
 gotoxy(2,9);
 for(j=0;j<o;j++)
 {
  c=wherex();
  y=wherey();
  gotoxy(c,y-2);
  cout<<char(218);
  gotoxy(c,y-1);
  cout<<char(179)<<" "<<order[j];
  gotoxy(c,y);
  cout<<char(192);
  //gotoxy(5+k+2,9);cout<<char(179);
  //gotoxy(5+k+2,10);cout<<char(179);
  //gotoxy(6+time[j]-time[j-1]+1,9);
  for(k=0;k<(time[j+1]-time[j])*dyn;k++)
  {
   gotoxy(c+k+1,y-2);
   cout<<char(196);
   gotoxy(c+k+1,y);
   cout<<char(196);
  }
 }
 c=wherex();
 y=wherey();
 gotoxy(c,y-2);
 cout<<char(191);
 gotoxy(c,y-1);
 cout<<char(179);
 gotoxy(c,y);
 cout<<char(217);
 cout<<"\n\n";
 for(int i=0;i<=nop;i++)
 {
  cout<<"Process ID: "<<p[i].pid<<"\n";
  cout<<"Arrival Time: "<<p[i].arrv<<"\n"		;
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
