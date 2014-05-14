#include<process.h>
#include<fstream.h>
#include<math.h>
#include<iostream.h>
#include<conio.h>
int min(int a,int b,int c)
{
 int x=a>b?b:a;
 if(c>x)
  return x;
 else
  return c;
}
int global(int ref[],int test[],int rlen,int tlen)
{
 int dtw[100][100];
 int i,j;
 for(i=0;i<tlen;i++)	//7nm
 {
  for(j=0;j<rlen;j++)
  {
   if(i>0 && j==0)	//2
	dtw[i][j]=999;
   else
	dtw[i][j]=fabs(ref[j]-test[i]);
   if(i==0 && j!=0)	//2
	dtw[i][j]+=dtw[i][j-1];
   if(i>0 && j>0)//2
	dtw[i][j]+=min(dtw[i-1][j-1],dtw[i-1][j],dtw[i][j-1]);	//1
  }
 }
 int small=dtw[0][rlen-1];
 for(i=1;i<tlen;i++)	//m-1
 {
  if(dtw[i][rlen-1]<small)
   small=dtw[i][rlen-1];
 }
 for(i=0;i<tlen;i++)
 {
  for(j=0;j<rlen;j++)
   cout<<dtw[i][j]<<"\t";
  cout<<"\n";
  getch();
 }
 cout<<"\n";
 return small;
}
void main()
{
 clrscr();
 char ch;
 int j,i=0,test[50];
 ifstream fd;
 fd.open("c:\\human.txt",ios::in);
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
 cout<<"The test file : \n";
 for(j=0;j<i;j++)
 {
  cout<<test[j]<<"\t";
 }
 getch();
 int testlen=i,ref[100];
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
 cout<<"\nThe ref file :\n";
 for(j=0;j<i;j++)
 {
  cout<<ref[j]<<"\t";
 }
 getch();
 cout<<"\n";
 int reflen=i;
 int a=global(ref,test,reflen,testlen);
 cout<<"Global Cost: "<<a<<"\n";
 getch();
}