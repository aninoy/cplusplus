#include<process.h>
#include<fstream.h>
#include<math.h>
#include<iostream.h>
#include<conio.h>
int ref[500],test[500],tlen=0,rlen=0;
int min(int a,int b,int c)
{
 int x=a>b?b:a;
 if(c>x)
  return x;
 else
  return c;
}
int global()
{
 int mat[50][300];
 int i,j;
 for(i=0;i<tlen;i++)	//7nm
 {
  for(j=0;j<rlen;j++)
  {
   if(i>0 && j==0)		//2
	mat[i][j]=9999;
   else
	mat[i][j]=abs(ref[j]-test[i]);
  if(i>0 && j>0)	//2
   {
	int g=min(mat[i-1][j-1],mat[i-1][j],mat[i][j-1]);	//1
	mat[i][j]=mat[i][j]+g;
   }
  }
 }
 int small=mat[tlen-1][0];
 for(i=1;i<rlen;i++)	//m-1
 {
  if(mat[tlen-1][i]<small)
   small=mat[tlen-1][i];
 }
 for(i=0;i<tlen;i++)
 {
  for(j=0;j<rlen;j++)
   cout<<mat[i][j]<<"\t";
  cout<<"\n";
 }
 cout<<"\n";
 return small;
}
void main()
{
 clrscr();
 char ch;
 int j,i=0;
 ifstream fd;
 fd.open("c:\\chahes.txt",ios::in);
 if(!fd)
 {
  cout<<"Can't open file!";
  exit(1);
 }
 fd.get(ch);
 test[0]=0;
 while(!fd.eof())
 {
  if(ch!='\n')
   test[i]=test[i]*10+ch-'0';
  else
  {
   i++;
   test[i]=0;
  }
  fd.get(ch);
 }
 fd.close();
 int sum=0;
 cout<<"The test file : \n";
 for(j=0;j<i;j++)
 {
  cout<<test[j]<<"\t";
  sum+=test[j];
 }
 getch();
 tlen=i;
 int tavg=sum/tlen;
 cout<<"Len: "<<tlen<<"\tAvg: "<<tavg;
 ifstream f;
 f.open("c:\\tauba.txt",ios::in);
 f.get(ch);
 ref[0]=0;i=0;
 while(!f.eof())
 {
  if(ch!='\n')
   ref[i]=ref[i]*10+ch-'0';
  else
  {
   i++;
   ref[i]=0;
  }
  f.get(ch);
 }
 f.close();
 sum=0;
 cout<<"\nThe ref file :\n";
 for(j=0;j<i;j++)
 {
  cout<<ref[j]<<"\t";
  sum+=ref[j];
 }
 getch();
 cout<<"\n";
 rlen=i;
 int ravg=sum/rlen;
 cout<<"Len: "<<rlen<<"\tAvg: "<<ravg<<"\n";
 if(ravg>tavg)
 {
  for(i=0;i<tlen;i++)
  {
   test[i]+=(ravg-tavg);
  }
 }
 else if(ravg<=tavg)
 {
  for(i=0;i<rlen;i++)
  {
	ref[i]+=(tavg-ravg);
  }
 }
 cout<<"After shifting\n";
 for(j=0;j<tlen;j++)
 {
  cout<<test[j]<<"\t";
 }
 cout<<"\n";
 getch();
 for(j=0;j<rlen;j++)
 {
  cout<<ref[j]<<"\t";
 }
 cout<<"\nDTW\n";
 getch();
 int a=global();
 cout<<"Global Cost: "<<a<<"\n";
 getch();
}