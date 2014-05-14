#include<dos.h>
#include<iostream.h>
#include<graphics.h>
#include<conio.h>
void liner(int x1,int y1,int x2,int y2)
{
 int x=x1,y=y1;float x3=x1,x4=x2,m;
 if(x3==x4)
 {
  if(y2> y1)
   m=2;
  else
   m=-2;
 }
 else
  m=(y2-y1)/(x4-x3);
 if(m>=0)
 {
  if(m<1)
  {
   float dy=y2-y1,dx=x2-x1,de=2*dy,dne=2*(dy-dx),p=2*dy-dx;
   putpixel(x,y,15);
   while(x<x2)
   {
    if(p>0)
    {
     p+=dne;y++;x++;
    }
    else
    {
     if(p<=0)
     {
      p+=de;
      x++;
     }
    }
    putpixel(x,y,15);
   }
  }
  if(m>=1)
  {
   float dy=y2-y1,dx=x2-x1;
   float dn=-2*dx,dne=2*(dy-dx),p=dy-2*dx;
   putpixel(x,y,10);
   while(y<y2)
   {
    if(p>=0)
    {
     p+=dn;y++;
    }
    else
    {
     if(p<0)
     {
      p+=dne;
      x++;y++;
     }
    }
    putpixel(x,y,10);
   }
  }
 }
 if(m<0)
 {
  if(m>-1)
  {
   float dy=y1-y2,dx=x2-x1;
   float de=2*dy,dse=2*(dy-dx),p=2*dy-dx;
   putpixel(x,y,1);
   while(x<x2)
   {
    if(p>=0)
    {
     p+=dse;y--;x++;
    }
    else
    {
     if(p<0)
     {
      p+=de;
      x++;
     }
    }
    putpixel(x,y,1);
   }
  }
  if(m<=-1)
  {
   float dy=y1-y2,dx=x2-x1;
   float ds=-2*dx,dse=2*(dy-dx),p=dy-2*dx;
   putpixel(x,y,14);
   while(y2<y)
   {
    if(p>0)
    {
     p+=ds;y--;
    }
    else
    {
     if(p<=0)
     {
      p+=dse;
      x++;y--;
     }
    }
    putpixel(x,y,14);
   }
  }
 }
}
void main()
{
 int gm,gd=DETECT;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 int midx=getmaxx()/2;int midy=getmaxy()/2;
 int i=-100,flag=0;
 while(1)
 {
  cleardevice();
  liner(midx,0,midx,midy*2);
  liner(0,midy,midx*2,midy);
  liner(midx,midy-100+i,midx+100+i,midy);
  liner(midx-100-i,midy,midx,midy+100-i);
  liner(midx-100-i,midy,midx,midy-100+i);
  liner(midx,midy+100-i,midx+100+i,midy);
  if(i==100)
   flag=1;
  if(i==-100)
   flag=0;
  if(flag==0)
   i++;
  else
   i--;
  delay(5);
 }
 //getch();
}