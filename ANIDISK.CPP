#include<math.h>
#include<process.h>
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
int req[1000],copy[1000],pre=-1,ptr=0,ptr1=0,max,num1=0,num=0,cur;
void menu()
{
 cout<<"1.FCFS\n2.SSTF\n3.SCAN\n4.C-SCAN\n5.LOOK\n6.C-LOOK\n7.EXIT";
}
void fcfs()
{
 cur=copy[ptr++];
}
void sstf()
{
 int small=999,pos=-1;
 for(int j=ptr;j<num;j++)
 {
  if(fabs(copy[j]-cur)<small)
  {
   small=fabs(copy[j]-cur);
   pos=j;
  }
 }
 cur=copy[pos];
 for(j=pos+1;j<num;j++)
  req[j-1]=copy[j];
 num--;
}
void scan()
{
 cur=save;
 int pos,j,small=999;
 back:
  for(j=ptr;j<num;j++)
  {
   if(copy[j]>pre && req[j]<small)
   {
    small=copy[j];
    pos=j;
   }
  }
  if(small==999 && pre!=max-1)
  {
   pre=0;
   goto back;
  }
 pre=cur;
 cur=copy[pos];
 for(j=pos+1;j<num;j++)
  req[j-1]=copy[j];
 num--;
}
void main()
{
 clrscr();
 int save,flag=0,max,choice2,choice;
 cout<<"Enter the maximum no. of disks: ";
 cin>>max;
 cout<<"Enter the cylinder in which current request is being serviced: ";
 cin>>cur;
 save=cur;
 cout<<"Do you have any cylinders with pending requests? 1/0: ";
 cin>>choice;
 while(1)
 {
  if(choice==1)
  {
   cout<<"Cylinder no.: ";
   cin>>req[num];
   copy[num]=req[num++];
   num1++;
  }
  else
  {
   //choice=0;
   cout<<"Current Head Location: "<<cur<<"\n";
   menu();
   cout<<"\nEnter your choice: ";
   cin>>choice2;
   for(int k=0;k<num1;k++)
    copy[k]=req[k];
   cur=save;
   num=num1;
   while(1)
   {
    if(choice==0)
    {
     switch(choice2)
     {
      case 1: fcfs();
			  break;
	  case 2: sstf();
			  break;
	  case 3: if(pre==-1)
			  {
			   cout<<"Enter previously serviced request: \n";
			   cin>>pre;
			  }
			  scan();
			  break;
	  case 4: //cscan();
			  break;
	  case 5: //look();
			  break;
	  case 6: //clook();
			  break;
	  case 7: exit(0);
	 }
	 cout<<"Current Head Location: "<<cur<<"\n";
    }
    else
    {
     cout<<"Cylinder number: ";
     cin>>req[num];
     copy[num]=req[num++];
     num1++;
    }
    cout<<"Do you have anymore cylinders? 1/0: ";
    cin>>choice;
    if(ptr==num)
    {
     flag=1;
     break;
    }
   }
  }
  if(!flag)
  {
   cout<<"Do you have anymore cylinders? 1/0: ";
   cin>>choice;
  }
 }
 getch();
}