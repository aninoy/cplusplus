#include<iostream.h>
#include<conio.h>
#include<process.h>
int cur=-1,save=-1,point=-1,nof=-1,len,ref[100],frame[10],time[10],full=-1;
int search(int x)
{
 for(int i=0;i<nof;i++)
 {
  if(frame[i]==x)
  {
   save=i;
   return 1;
  }
 }
 return 0;
}
void update()
{
 /*if(point==-1)
  point=0;
 else
 {
  int small=999;
  for(int i=0;i<nof;i++)
  {
   if(time[i]<small)
   {
	point=i;
	small=time[i];
   }
  }
 }*/
 for(int i=0;i<=full;i++)
 {
  int flag=-1;
  for(int j=cur+1;j<len;j++)
  {
   if(ref[j]==frame[i])
   {
	flag=1;
	time[i]=j;
	break;
   }
  }
  if(flag==-1)
   time[i]=99;
 }
 int small=-1;
 for(i=0;i<=full;i++)
 {
  if(time[i]>small)
  {
   point=i;
   small=time[i];
  }
 }
}
void main()
{
 clrscr();
 int flag=-1,fault=0,hit=0,t;
 cout<<"Enter the Number of Frames: ";
 cin>>nof;
 for(int i=0;i<nof;i++)
  frame[i]=-1;
 cout<<"Enter the length of reference string: ";
 cin>>len;
 cout<<"Enter the process numbers:-\n";
 for(i=0;i<len;i++)
  cin>>ref[i];
 for(i=0;i<len;i++)
 {
  cur=i;
  flag=-1;
  if(full==nof-1)
  {
   if(!search(ref[i]))
   {
	flag=0;fault++;
	frame[point]=ref[i];
   }
   else
   {
	flag=1;
	hit++;
   }
  }
  else
   frame[++full]=ref[i];
  update();
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