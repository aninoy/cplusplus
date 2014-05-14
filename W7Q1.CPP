#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<process.h>
int xmax=0,ymax=0,xmin=0,ymin=0;
int code(int x,int y)
{
 int c=0;
 if(x<xmin)c=1;
 if(x>xmax)c=2;
 if(y<ymin)c=4;
 if(y>ymax)c=8;
 return c;
}
void main()
{
 int gm,gd=DETECT,x1,y1,x2,y2;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 cout<<"Enter the bottom left coordinates of clip rectangle: -\n";
 cin>>xmin>>ymin;
 cout<<"Enter the top right coordinates of clip rectangle: -\n";
 cin>>xmax>>ymax;
 cout<<"Enter the coordinates of the end points of the line to be clipped:-\n";
 cin>>x1>>y1>>x2>>y2;
 int c1=code(x1,y1);
 int c2=code(x2,y2);
 cout<<"codes: "<<c1<<"\t"<<c2<<"\n";
 int cod=c1,x,y;
 float m=(y2-y1)/float(x2-x1);
 clrscr();
 rectangle(xmin,ymin,xmax,ymax);
 line(x1,y1,x2,y2);
 getch();
 while(c1 | c2>0)
 {
  if(c1==c2)
  {
   cout<<"Line Rejected!";
   getch();
   exit(0);
  }
  cod=c1;
  if(cod==0)
   cod=c2;
  if(cod==8)
  {
   y=ymax;
   x=x1+(ymax-y1)/m;
  }
  if(cod==4)
  {
   y=ymin;
   x=x1+(ymin-y1)/m;
  }
  if(cod==2)
  {
   x=xmax;
   y=y1+(xmax-x1)*m;
  }
  if(cod==1)
  {
   x=xmin;
   y=y1+(xmin-x1)*m;
  }
  if(cod==c1)
  {
   x1=x;y1=y;
   c1=code(x1,y1);
  }
  else if(cod==c2)
  {
   x2=x;y2=y;
   c2=code(x2,y2);
  }
 }
 clrscr();
 rectangle(xmin,ymin,xmax,ymax);
 line(x1,y1,x2,y2);
 getch();
}

