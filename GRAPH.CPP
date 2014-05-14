#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
int midx,midy;
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
   if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
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
    if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
     putpixel(x,y,15);
   }
  }
  if(m>=1)
  {
   float dy=y2-y1,dx=x2-x1;
   float dn=-2*dx,dne=2*(dy-dx),p=dy-2*dx;
   if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
     putpixel(x,y,15);
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
    if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
     putpixel(x,y,15);
   }
  }
 }
 if(m<0)
 {
  if(m>-1)
  {
   float dy=y1-y2,dx=x2-x1;
   float de=2*dy,dse=2*(dy-dx),p=2*dy-dx;
   if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
     putpixel(x,y,15);
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
    if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
     putpixel(x,y,15);
   }
  }
  if(m<=-1)
  {
   float dy=y1-y2,dx=x2-x1;
   float ds=-2*dx,dse=2*(dy-dx),p=dy-2*dx;
   if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
     putpixel(x,y,15);
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
    if((x<midx-100 || x>midx+100) || (y<midy-100 || y>midy+100))
     putpixel(x,y,15);
   }
  }
 }
}
void circles(int r)
{
 int x=0,y=r;
 int d=1-r;
 while(y>=x)
 {
  if(d<0)
   d+=2*x+3;
  else
  {
   d+=2*x-2*y+5;
   y--;
  }
  x++;
  circle(midx,midy,200);
  rectangle(midx-100,midy-100,midx+100,midy+100);
  liner(midx-x,midy+y,midx+x,midy-y);
  cleardevice();
  delay(1);
 }
 d=float(x+0.5)*float(x+0.5)+float(y-1)*float(y-1)-r*r;
 while(y>=0)
 {
  if(d<0)
  {
   d+=2*x-2*y+5;
   x++;
  }
  else
   d+=3-2*y;
  y--;
  cleardevice();
  circle(midx,midy,200);
  rectangle(midx-100,midy-100,midx+100,midy+100);
  liner(midx-x,midy+y,midx+x,midy-y);
  delay(1);
 }
 d=float(x-0.5)*float(x-0.5)+float(y-1)*float(y-1)-r*r;
 while(abs(y)<=x)
 {
  if(d<0)
   d+=3-2*y;
  else
  {
   d+=5-2*x-2*y;
   x--;
  }
  y--;
  cleardevice();
  circle(midx,midy,200);
  rectangle(midx-100,midy-100,midx+100,midy+100);
  liner(midx-x,midy+y,midx+x,midy-y);
  delay(1);
 }
 d=float(x-1)*float(x-1)+float(y-0.5)*float(y-0.5)-r*r;
 while(x>=0)
 {
  if(d<0)
  {
   d+=5-2*x-2*y;
   y--;
  }
  else
   d+=3-2*x;
  x--;
  cleardevice();
  circle(midx,midy,200);
  rectangle(midx-100,midy-100,midx+100,midy+100);
  liner(midx-x,midy+y,midx+x,midy-y);
  delay(1);
 }
}

void  main()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 midx=getmaxx()/2;
 midy=getmaxy()/2;
 while(1)
 {
  circles(200);
 }
 //getch();
}



