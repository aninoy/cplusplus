#include<iostream.h>
#include<math.h>
#include<dos.h>
#include<conio.h>
#include<graphics.h>
float ang=45.0*3.14/180.0;
float ang1=63.4*3.14/180.0;
float mat1[4][4],mat3[4][5];
float mat2[4][5]={{100,100,100,100,50},{50,100,100,50,50},{100,100,50,50,50},{1,1,1,1,1}};
int midx,midy,m=4,n=5,p=4,q=4;
void matmult()
{
 for(int i=0;i<p;i++)
 {
  for(int j=0;j<5;j++)
  {
   mat3[i][j]=0;
   for(int k=0;k<m;k++)
    mat3[i][j]+=mat1[i][k]*mat2[k][j];
  }
 }
 for(i=0;i<4;i++)
  for(int j=0;j<5;j++)
   mat2[i][j]=mat3[i][j];
}
void display()
{
 cleardevice();
 line(0,midy,midx*2,midy);
 line(midx,0,midx,midy*2);
 line(0,midx*tan(ang)+midy,midx*2,midy-midx*tan(ang));
 for(int i=0;i<3;i++)
  line(midx+mat3[0][i],midy-mat3[1][i],midx+mat3[0][i+1],midy-mat3[1][i+1]);
 line(midx+mat3[0][3],midy-mat3[1][3],midx+mat3[0][0],midy-mat3[1][0]);
 for(i=0;i<=3;i++)
  line(midx+mat3[0][i],midy-mat3[1][i],midx+mat3[0][4],midy-mat3[1][4]);
 delay(10);
}
void tran22d()
{
 for(int i=0;i<5;i++)
 {
  mat3[0][i]-=mat3[2][i]*cos(ang)/tan(ang1);
  mat3[1][i]-=mat3[2][i]*sin(ang)/tan(ang1);
 }
}
void rotation(char x)
{
 float a=mat2[0][4];
 float b=mat2[1][4];
 float c=mat2[2][4];
 float ang2=1.0*3.14/180.0;
 while(!kbhit())
 {
  for(int i=0;i<4;i++)
  {
   for(int j=0;j<4;j++)
   {
    if(i==j) mat1[i][j]=1;
    else mat1[i][j]=0;
   }
  }
  switch(x)
  {
   case 'x': mat1[1][3]=-b;mat1[2][3]=-c;break;
   case 'y': mat1[0][3]=-a;mat1[2][3]=-c;break;
   case 'z': mat1[0][3]=-a;mat1[1][3]=-b;break;
  }
  matmult();
  for(i=0;i<4;i++)
  {
   for(int j=0;j<4;j++)
   {
    if(i==j) mat1[i][j]=1;
    else mat1[i][j]=0;
   }
  }
  switch(x)
  {
   case 'x': mat1[1][1]=mat1[2][2]=cos(ang2);
	     mat1[1][2]=-sin(ang2);
	     mat1[2][1]=sin(ang2);
	     break;
   case 'y': mat1[2][2]=mat1[0][0]=cos(ang2);
	     mat1[0][2]=-sin(ang2);
	     mat1[2][0]=sin(ang2);
	     break;
   case 'z': mat1[0][0]=mat1[1][1]=cos(ang2);
	     mat1[0][1]=-sin(ang2);
	     mat1[1][0]=sin(ang2);
	     break;
  }
  matmult();
  for(i=0;i<4;i++)
  {
   for(int j=0;j<4;j++)
   {
    if(i==j) mat1[i][j]=1;
    else mat1[i][j]=0;
   }
  }
  switch(x)
  {
   case 'x': mat1[1][3]=b;mat1[2][3]=c;break;
   case 'y': mat1[0][3]=a;mat1[2][3]=c;break;
   case 'z': mat1[0][3]=a;mat1[1][3]=b;break;
  }
  matmult();
  tran22d();
  display();
 }
}
void main()
{
 clrscr();
 int gm,gd=DETECT;
 char axis;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 midx=getmaxx()/2;
 midy=getmaxy()/2;
 cout<<"Enter the axis (x/y/z): ";
 cin>>axis;
 for(int i=0;i<4;i++)
  for(int j=0;j<5;j++)
   mat3[i][j]=mat2[i][j];
 tran22d();
 display();
 getch();
 rotation(axis);
}