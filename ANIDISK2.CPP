#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<process.h>
int movement=0,old=-1,dir=-1,max=-1,nor=-1,head=-1,num=-1,flag=0,init=-1,flag1=-1;
struct req
{
 int cyl,flag;
}R[100];
void menu()
{
 cout<<"\n1.FCFS\n2.SSTF\n3.SCAN\n4.LOOK\n5.CSCAN\n6.CLOOK\n7.EXIT\n";
}
int search(int j)
{
 int pos=-1;
 for(int i=0;i<=nor;i++)
 {
  if(R[i].flag==0 && R[i].cyl==j)
  {
   pos=i;
   break;
  }
 }
 return pos;
}
void fcfs()
{
 head=R[num].cyl;
 if(num==nor)
 {
  flag=0;
  num=-1;
 }
}
void sstf()
{
 int small=999,pos=-1;
 for(int i=0;i<=nor;i++)
 {
  if(fabs(R[i].cyl-head)<small && R[i].flag==0)
  {
   small=fabs(R[i].cyl-head);
   pos=i;
  }
 }
 head=R[pos].cyl;
 R[pos].flag=1;
 if(num==nor)
 {
  flag=0;
  num=-1;
 }
}
void scan()
{
 int pos;
 if(init==head)
 {
  if(dir==0)
   flag1=0;
  else
   flag1=1;
 }
 if(flag1==0)
 {
  for(int j=head-1;j>=0;j--)
  {
   pos=search(j);
   if((pos==-1 && j== 0) || pos!=-1)
	break;
  }
  if(pos!=-1)
  {
   head=R[pos].cyl;
   R[pos].flag=1;
  }
  else
  {
   head=dir;
   num--;
  }
  if(head==0)
   flag1=1;
 }
 else
 {
  for(int j=head+1;j<max;j++)
  {
   pos=search(j);
   if((pos==-1 && j==max-1)|| pos!=-1)
	break;
  }
  if(pos!=-1)
  {
   head=R[pos].cyl;
   R[pos].flag=1;
  }
  else
  {
   head=max-1;
   num--;
  }
  if(head==max-1)
   flag1=0;
 }
 if(num==nor)
 {
  flag=0;
  num=-1;
 }
}
void look()
{
 int pos;
 if(init==head)
 {
  if(dir==0)
   flag1=0;
  else
   flag1=1;
 }
 back:
 if(flag1==0)
 {
  for(int j=head-1;j>=0;j--)
  {
   pos=search(j);
   if((pos==-1 && j== 0) || pos!=-1)
	break;
  }
  if(pos!=-1)
  {
   head=R[pos].cyl;
   R[pos].flag=1;
  }
  else
   flag1=1;
 }
 if(flag1==1)
 {
  for(int j=head+1;j<max;j++)
  {
   pos=search(j);
   if((pos==-1 && j==max-1)|| pos!=-1)
	break;
  }
  if(pos!=-1)
  {
   head=R[pos].cyl;
   R[pos].flag=1;
  }
  else
  {
   flag1=0;
   goto back;
  }
 }
 if(num==nor)
 {
  flag=0;
  num=-1;
 }
}
void cscan()
{
 int pos;
 if(dir==0)
 {
  if(head<=init && head!=0)
  {
   for(int j=head-1;j>=0;j--)
   {
	pos=search(j);
	if((pos==-1 && j== 0) || pos!=-1)
	 break;
   }
   if(pos!=-1)
   {
	head=R[pos].cyl;
	R[pos].flag=1;
   }
   else
   {
	head=dir;
	num--;
   }
  }
  else
  {
   if(head==0)
   {
	head=max-1;
	num--;
   }
   else
   {
	if(head>init)
	{
	 for(int j=head-1;j>init;j--)
	 {
	  pos=search(j);
	  if((pos==-1 && j==max-1) || pos!=-1)
	   break;
	 }
	 if(pos!=-1)
	 {
	  head=R[pos].cyl;
	  R[pos].flag=1;
	 }
	}
   }
  }
 }
 else
 {
  if(head>=init && head!=max-1)
  {
   for(int j=head+1;j<max;j++)
   {
	pos=search(j);
	if((pos==-1 && j==max-1)|| pos!=-1)
	 break;
   }
   if(pos!=-1)
   {
	head=R[pos].cyl;
	R[pos].flag=1;
   }
   else
   {
	head=dir;
	num--;
   }
  }
  else
  {
   if(head==max-1)
   {
	head=0;
	num--;
   }
   else
   {
	if(head<init)
	{
	 for(int j=head+1;j<max;j++)
	 {
	  pos=search(j);
	  if((pos==-1 && j==max-1)|| pos!=-1)
	   break;
	 }
	 if(pos!=-1)
	 {
	  head=R[pos].cyl;
	  R[pos].flag=1;
	 }
	}
   }
  }
 }
 if(num==nor)
 {
  flag=0;
  num=-1;
 }
}
void clook()
{
 int pos;
 if(dir==0)
 {
  if(head<=init && head!=0)
  {
   for(int j=head-1;j>=0;j--)
   {
	pos=search(j);
	if((pos==-1 && j== 0) || pos!=-1)
	 break;
   }
   if(pos!=-1)
   {
	head=R[pos].cyl;
	R[pos].flag=1;
   }
   else
	head=max-1;
  }
  if(head>init)
  {
   for(int j=head-1;j>=0;j--)
   {
	pos=search(j);
	if((pos==-1 && j==max-1) || pos!=-1)
	 break;
   }
   if(pos!=-1)
   {
	head=R[pos].cyl;
	R[pos].flag=1;
   }
  }
 }
 else
 {
  if(head>=init && head!=max-1)
  {
   for(int j=head+1;j<max;j++)
   {
	pos=search(j);
	if((pos==-1 && j==max-1)|| pos!=-1)
	 break;
   }
   if(pos!=-1)
   {
	head=R[pos].cyl;
	R[pos].flag=1;
   }
   else
	head=-1;
  }
  if(head<init)
  {
   for(int j=head+1;j<max;j++)
   {
	pos=search(j);
	if((pos==-1 && j==max-1)|| pos!=-1)
	 break;
   }
   if(pos!=-1)
   {
	head=R[pos].cyl;
	R[pos].flag=1;
   }
  }
 }
 if(num==nor)
 {
  flag=0;
  num=-1;
 }
}

void main()
{
 clrscr();
 int i,algo=-1,choice=-1;
 cout<<"Enter the max no. of requests: ";
 cin>>max;
 cout<<"\nRequests should be of the form : 0........"<<max-1<<"\n";
 cout<<"Enter the current head position: ";
 cin>>init;
 cout<<"\nDo you have any requests pending? 1/0: ";
 cin>>choice;
 if(choice==0)
  exit(0);
 while(1)
 {
  if(choice==1)
  {
   cout<<"Cylinder No. : ";
   cin>>R[++nor].cyl;
   R[nor].flag=0;
  }
  else
  {
   while(1)
   {
	if(choice==0)
	{
	 num++;
	 if(flag==0)
	 {
	  if(movement!=0)
	   cout<<"Total Head Movement: "<<movement<<" tracks\n";
	  menu();
	  flag=1;
	  cout<<"Enter your choice: ";
	  cin>>algo;
	  if(algo!=1 && algo!=2 && algo!=7)
	  {
	   cout<<"The head is moving towards (0 / 199): ";
	   cin>>dir;
	  }
	  for(int i=0;i<=nor;i++)
	   R[i].flag=0;
	  head=init;
	  old=init;
	  movement=0;
	  cout<<"Initial Head Position: "<<head<<"\n";
	 }
	 switch(algo)
	 {
	  case 1: fcfs();
			  break;
	  case 2: sstf();
			  break;
	  case 3: scan();
			  break;
	  case 4: look();
			  break;
	  case 5: cscan();
			  break;
	  case 6: clook();
			  break;
	  case 7: exit(0);
	 }
	 cout<<"Current Head Position: "<<head<<"\n";
	 movement=movement+fabs(head-old);
	 old=head;
	}
	else
	{
	 cout<<"Cylinder No. : ";
	 cin>>R[++nor].cyl;
	 R[nor].flag=0;
	}
	cout<<"Do you have anymore pending requests? 1/0: ";
	cin>>choice;
   }
  }
  cout<<"Do you have anymore pending requests? 1/0: ";
  cin>>choice;
 }
}