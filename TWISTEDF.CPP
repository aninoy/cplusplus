#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
void ellpts(int xc,int yc,int x,int y,int col)
{
 putpixel(xc+x,yc-y,col);
 putpixel(xc+x,yc+y,col);
 putpixel(xc-x,yc-y,col);
 putpixel(xc-x,yc+y,col);
}
void ell(int xc,int yc,int a,int b)
{
 int x=0,y=b;
 float d=pow(b,2)-pow(a,2)*b+pow(a,2)/4;
 ellpts(xc,yc,x,y,10);
 while((y*pow(a,2))>(x*pow(b,2)))
 {
  if(d<0)
   d+=(2*(float)x+1)*pow(b,2);
  else
  {
   d+=(2*(float)x+1)*pow(b,2)-(float)y*2*pow(a,2);
   y--;
  }
  x++;
  ellpts(xc,yc,x,y,10);
 }
 cout<<"x: "<<x<<" "<<y<<" ";
 getch();
 d=pow(b,2)*((float)x+0.5)*((float)x+0.5)+pow(a,2)*((float)y-1)*((float)y-1)-pow(a,2)*pow(b,2);
 while(y>0)
 {
  if(d>=0)
   d-=pow(a,2)*(2*(float)y-1);
  else
  {
   d+=2*pow(b,2)*((float)x+1)-pow(a,2)*(2*(float)y+1);
   x++;
  }
  y--;
  ellpts(xc,yc,x,y,10);
 }
}
void main()
{
 int gm,gd=DETECT;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 ell(200,200,200,100);
 getch();
}
