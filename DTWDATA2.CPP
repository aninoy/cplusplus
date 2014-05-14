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
 return small;
}
void main()
{
 clrscr();
 char ch;
 int j,i=0,temp[500];
 ifstream fd;
 fd.open("c:\\kajras.txt",ios::in);
 if(!fd)
 {
  cout<<"Can't open test file!";
  getch();
  exit(1);
 }
 fd.get(ch);
 test[0]=0;
 int nos=0;
 int a[100];
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
 for(j=0;j<i;j++)
 {
  temp[j]=test[j];
  sum+=test[j];
 }
 tlen=i;
 int tavg=sum/tlen;
 ifstream f;
 f.open("c:\\ref.txt",ios::in);
 if(!f)
 {
  cout<<"Can't Open reference file\n";
  getch();
  exit(1);
 }
 while(!f.eof())
 {
  f.get(ch);
  ref[0]=0;i=0;
  while(ch!='#' && !f.eof())
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
  if(ch=='#')
   f.get(ch);
  sum=0;
  for(j=0;j<i;j++)
  {
   sum+=ref[j];
  }
  rlen=i;
  int ravg=sum/rlen;
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
  a[nos]=global();
  nos++;
  for(j=0;j<tlen;j++)
   test[j]=temp[j];
 }
 clrscr();
 cout<<"Song No. \tMin Global Cost\n\n";
 for(j=0;j<nos;j++)
  cout<<j+1<<"\t\t"<<a[j]<<"\n";
 getch();
}