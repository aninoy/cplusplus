#include<iostream.h>
#include<conio.h>
#include<process.h>

int save=-1,point=-1,nof=-1,len,ref[100],frame[10],time[10],full=-1;
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
 if(point==-1)
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
 for(i=0,t=0;i<len;i++,t++)
 {
  flag=-1;
  if(full==nof-1)
  {
   if(!search(ref[i]))
   {
	flag=0;fault++;
	frame[point]=ref[i];
	time[point]=t;
   }
   else
   {
	flag=1;
	hit++;
	time[save]=t;
   }
  }
  else
  {
   frame[++full]=ref[i];
   time[full]=t;
  }
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