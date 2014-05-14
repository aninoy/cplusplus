#include<iostream.h>
#include<dos.h>
#include<conio.h>
#include<math.h>
#include<process.h>
#include<graphics.h>
int gd=DETECT,gm;

float in[4][5]={{100,100,100,100,50},{50,100,100,50,50},{100,100,50,50,50},{1,1,1,1,1}};
//{{100,50,100,1},{100,100,100,1},{100,100,50,1},{100,50,50,1},{50,50,50,1}};
//float rot[4][4]={{1/1.414,0,1/1.414,0},{0,1,0,0},{-1/1.414,0,1/1.414,0},{0,0,0,1}};
float rot[4][4]={{cos(0.01),0,sin(0.01),0},{0,1,0,0},{-sin(0.01),0,cos(0.01),0},{0,0,0,1}};
//float rot[4][4]={{cos(,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
float trn[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
float nin[2][5];
float a[4][5];
float midx,midy;

void draw()
{
cleardevice();
setcolor(RED);
for(int i=0;i<5;i++)
{
nin[0][i]=in[0][i]+midx-in[2][i]*sin(float(45.0*3.14/180.0))/tan(float(63.4*3.14/180.0));
nin[1][i]=0-in[1][i]+midy+in[2][i]*cos(float(45.0*3.14/180.0))/tan(float(63.4*3.14/180.0));
}
for(int j=0;j<3;j++)
{
line(nin[0][j],nin[1][j],nin[0][j+1],nin[1][j+1]);
line(nin[0][j],nin[1][j],nin[0][4],nin[1][4]);
}
line(nin[0][3],nin[1][3],nin[0][0],nin[1][0]);
line(nin[0][3],nin[1][3],nin[0][4],nin[1][4]);
}


void mul(float s[4][4])
{
float ans;
//cout<<"so";
for(int r=0;r<4;r++)
{
for(int c=0;c<5;c++)
{
ans=0;
for(int rc=0;rc<4;rc++)
{
ans+=s[r][rc]*in[rc][c];
}
a[r][c]=ans;
}
}
//cout<<"out";
}
void reas()
{
for(int r=0;r<4;r++)
{
for(int c=0;c<5;c++)
{
in[r][c]=a[r][c];
a[r][c]=0;
}}}
void rot1();
void trans()
{
float tx,ty,tz;

tx=-in[0][4];
ty=-in[1][4];
tz=-in[2][4];
trn[0][3]=tx;
trn[1][3]=ty;
trn[2][3]=tz;
mul(trn);
//cout<<"ya";
reas();
//draw();
//cout<<"ma";
//getch();
rot1();
//draw();
tx=-tx;//in[0][4];
ty=-ty;//in[1][4];
tz=-tz;//in[2][4];
trn[0][3]=tx;
trn[1][3]=ty;
trn[2][3]=tz;
mul(trn);
reas();
draw();
delay(10);
}


void rot1()
{
mul(rot);
reas();
}

void main()
{
clrscr();
initgraph(&gd,&gm,"d:\\tc\\bgi");
midx=getmaxx()/2;
midy=getmaxy()/2;
draw();
//getch();
trans();
setcolor(RED);
while(!kbhit())
trans();
exit(0);

//draw();
getch();
}
