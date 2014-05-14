                                                                     
                                                                     
                                                                     
                                             
#include<graphics.h>
#include<dos.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

float midx,midy;
struct p1
{
float x,y,z;
}pt[5]={{0,0,0},{-50,-50,0},{-50,-100,0},{50,-100,0},{50,-50,0}};

struct p2
{
float x,y;
}pt1[5];

void project()
{
float xv=cos((45*3.14)/180)/tan((63.4*3.14)/180);
float yv=sin((45*3.14)/180)/tan((63.4*3.14)/180);

for(int i=0;i<5;i++)
{
pt1[i].x=pt[i].x-pt[i].z*xv;
pt1[i].y=pt[i].y+pt[i].z*yv;
}

}

float m1[4][5]={{0,-50,-50,50,50},{0,-50,-100,-100,-50},{0,0,0,0,0},{1,1,1,1,1}};

void draw()
{
project();
line(midx+pt1[0].x,midy-pt1[0].y,midx+pt1[1].x,midy-pt1[1].y);
line(midx+pt1[0].x,midy-pt1[0].y,midx+pt1[2].x,midy-pt1[2].y);
line(midx+pt1[0].x,midy-pt1[0].y,midx+pt1[3].x,midy-pt1[3].y);
line(midx+pt1[0].x,midy-pt1[0].y,midx+pt1[4].x,midy-pt1[4].y);

line(midx+pt1[1].x,midy-pt1[1].y,midx+pt1[2].x,midy-pt1[2].y);
line(midx+pt1[2].x,midy-pt1[2].y,midx+pt1[3].x,midy-pt1[3].y);
line(midx+pt1[3].x,midy-pt1[3].y,midx+pt1[4].x,midy-pt1[4].y);
line(midx+pt1[4].x,midy-pt1[4].y,midx+pt1[1].x,midy-pt1[1].y);

}

void matmul(float ma[4][4],float mb[4][5],float mc[4][5])
{

	int r,c;
	for(r=0;r<4;r++)
	{
		for(c=0;c<5;c++)
		{
		mc[r][c]=ma[r][0]*mb[0][c]+ma[r][1]*mb[1][c]+ma[r][2]*mb[2][c]+ma[r][3]*mb[3][c];
		}
	}

}

float ml[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
float mf[4][5];
void reassign(float a[4][4])
{
for(int i=0;i<4;i++)
{
for(int j=0;j<4;j++)
{
if(i==j)
a[i][j]=1;
else
a[i][j]=0;
}
}
}

void rotatez()
{
for(int i=0;i<360;i++)
{
reassign(ml);
float ang=(45*3.14)/180;

ml[0][0]=cos(ang);
ml[0][1]=-1*sin(ang);
ml[1][0]=(sin(ang));
ml[1][1]=cos(ang);

matmul(ml,m1,mf);

reassign(ml);
for(int j=0;j<5;j++)
{
pt[j].x=mf[0][j];
pt[j].y=mf[1][j];
pt[j].z=mf[2][j];
}
cleardevice();

//sleep(1);
draw();
delay(50);
//getch();
for(int i=0;i<4;i++)
{
for(int j=0;j<5;j++)
{
m1[i][j]=mf[i][j];
}
}
}
}

void translate();
void translate1();


void rotatex()
{
for(int i=0;i<360;i++)
{
float ang=(10*3.14)/180;
reassign(ml);
ml[1][1]=cos(ang);
ml[1][2]=-1*sin(ang);
ml[2][1]=(sin(ang));
ml[2][2]=cos(ang);

matmul(ml,m1,mf);

reassign(ml);
for(int j=0;j<5;j++)
{
pt[j].x=mf[0][j];
pt[j].y=mf[1][j];
pt[j].z=mf[2][j];
}
//cleardevice();
reassign(ml);

//sleep(1);

//getch();
for(int i=0;i<4;i++)
{
for(int j=0;j<5;j++)
{
m1[i][j]=mf[i][j];
}
}


cleardevice();
draw();
delay(50);
}
}


void rotatey()
{
float mid=midy;

for(int mm=midy;mm>0;mm--)
{
midy=midy-1;
//for(int i=0;i<360;i++)
//{
float ang=(45*3.14)/180;

ml[0][0]=cos(ang);
ml[0][2]=sin(ang);
ml[2][0]=-1*(sin(ang));
ml[2][2]=cos(ang);

matmul(ml,m1,mf);

reassign(ml);
for(int j=0;j<5;j++)
{
pt[j].x=mf[0][j];
pt[j].y=mf[1][j];
pt[j].z=mf[2][j];
}
cleardevice();

//sleep(1);
draw();
delay(50);
//getch();
for(int i=0;i<4;i++)
{
for(int j=0;j<5;j++)
{
m1[i][j]=mf[i][j];
}
}
//
}


midy=0;
for(int mm2=0;mm2<2*(mid)-100;mm2++)
{
midy=midy+1;
float ang=(45*3.14)/180;

ml[0][0]=cos(ang);
ml[0][2]=sin(ang);
ml[2][0]=-1*(sin(ang));
ml[2][2]=cos(ang);

matmul(ml,m1,mf);

reassign(ml);
for(int j=0;j<5;j++)
{
pt[j].x=mf[0][j];
pt[j].y=mf[1][j];
pt[j].z=mf[2][j];
}
cleardevice();
draw();
delay(50);
//getch();
for(int i=0;i<4;i++)
{
for(int j=0;j<5;j++)
{
m1[i][j]=mf[i][j];
}
}
//
}

}

void translate()
{
reassign(ml);
ml[0][3]=-60;
ml[1][3]=-70;
ml[2][3]=-75;

matmul(ml,m1,mf);

reassign(ml);
for(int j=0;j<5;j++)
{
pt[j].x=mf[0][j];
pt[j].y=mf[1][j];
pt[j].z=mf[2][j];
}
//cleardevice();
//getch();
//sleep(1);
//draw();
for(int i=0;i<4;i++)
{
for(int j=0;j<5;j++)
{
m1[i][j]=mf[i][j];
}
}
}


void translate1()
{

ml[0][3]=60;
ml[1][3]=70;
ml[2][3]=75;

matmul(ml,m1,mf);

reassign(ml);
for(int j=0;j<5;j++)
{
pt[j].x=mf[0][j];
pt[j].y=mf[1][j];
pt[j].z=mf[2][j];
}
cleardevice();

//sleep(1);
//draw();
//delay(100);
//getch();
for(int i=0;i<4;i++)
{
for(int j=0;j<5;j++)
{
m1[i][j]=mf[i][j];
}
}
}




void main()
{
clrscr();

int gd=DETECT,gm;
initgraph(&gd,&gm,"d:\\tc\\bgi");
midx=getmaxx()/2;
midy=getmaxy()/2;

draw();
rotatex();
getch();
}