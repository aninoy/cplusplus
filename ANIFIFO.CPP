#include<iostream.h>
#include<conio.h>
#include<process.h>

int point=-1,nof=-1,len,ref[100],frame[10],full=-1;
int search(int x)
{
 for(int i=0;i<=full;i++)
 {
  if(frame[i]==x)
   return 1;
 }
 return 0;
}

void main()
{
 clrscr();
 int flag=-1,fault=0,hit=0;
 cout<<"Enter the Number of Frames: ";
 cin>>nof;
 for(int i=0;i<nof;i++)
  frame[i]=0;
 cout<<"Enter the length of reference string: ";
 cin>>len;
 cout<<"Enter the process numbers:-\n";
 for(i=0;i<len;i++)
  cin>>ref[i];
 for(i=0;i<len;i++)
 {
  flag=-1;
  if(point==-1)
  {
   frame[++point]=ref[i];
   full++;
  }
  else
  {
   if(full==nof-1)
   {
	if(!search(ref[i]))
	{
	 flag=0;fault++;
	 frame[point]=ref[i];
	 point++;
	 point=point%nof;
	}
	else
	{
	 flag=1;
	 hit++;
	}
   }
   else
   {
	if(!search(ref[i]))
	 frame[++full]=ref[i];
	else
	{
	 flag=1;
	 hit++;
	}
   }
  }
  for(int j=0;j<nof;j++)
   cout<<frame[j]<<"\t";
  cout<<"Point: "<<point;
  if(flag==1)
   cout<<"\tHit";
  cout<<"\n";
  getch();
 }
 cout<<"Hit Ratio: "<<hit<<" / "<<len<<"\n";
 getch();
}