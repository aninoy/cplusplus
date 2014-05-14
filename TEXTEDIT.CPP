#include<string.h>
#include<io.h>
#include<fstream.h>
#include <process.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <iomanip.h>
int lineno[25],lines;
char linebuf[25][80];
void setxy();
void cursor(int k)
{
 int x=wherex();int y=wherey();
 switch(k)
 {
  case 72: gotoxy(x-1,y-1);
		   break;
  case 75: gotoxy(x-2,y);
		   break;
  case 77: gotoxy(x,y);
		   break;
  case 80: gotoxy(x-1,y+1);
		   break;
 }
 setxy();
}
void setxy()
{
 int x=wherex();
 int y=wherey();
 gotoxy(7,24);
 cout<<y-2<<" i ";
 gotoxy(78,24);
 cout<<x-1<<"  ";
 gotoxy(x,y);
}
char textinput()
{
 char *fbuf;int xpos,ypos;
 textbackground(0);
 textcolor(15);
 char c,str[80];int i=0,j=0,x;
 gotoxy(2,3);
 while(1)
 {
  xpos=wherex();
  ypos=wherey();
  gettext(xpos,ypos,xpos,ypos,fbuf);
  c=getche();
  setxy();
  x=c;
  switch(x)
  {
   case 0: c=getch();
		   x=c;
		   puttext(xpos,ypos,xpos,ypos,fbuf);
		   switch(x)
		   {
			case 72:
			case 75:
			case 77:
			case 80: cursor(x);
			              break;
			default: return c;
		   }
		   break;
   case 13: str[j++]='\n';
			lineno[i]=j;
			strcpy(linebuf[i],str);
			i++;
			j=0;
			lines=i;
			gotoxy(2,3+i);
			setxy();
			break;
   case 8:  cout<<' ';
			setxy();
			cout<<char(8);
			j--;
			break;
   default: str[j++]=c;
			str[j]='\0';
			strcpy(linebuf[i],str);
			lines=i;
			break;
  }
 }
}

void menu(char);
void frame(void)
{
 clrscr();
 gotoxy(1,1);
 textattr(112);
 cprintf(" File         Edit                                                     Help     ");
 gotoxy(1,2);
 cout<<char(218);
 for(int i=0;i<78;i++)
  cout<<char(196);
 cout<<char(191);
 for(i=3;i<24;i++)
 {
  gotoxy(1,i);
  cout<<char(179);
  gotoxy(80,i);
  cout<<char(179);
 }
 gotoxy(1,23);
 cout<<char(192);
 for(i=2;i<80;i++)
 {
  gotoxy(i,23);
  cout<<char(196);
 }
 gotoxy(80,23);
 cout<<char(217);
 textattr(112);
 cprintf("Line:                                                                Column:   ");
}


void file(void)
{
 //textattr(07);
 char *framebuf;
 gotoxy(9,2);cout<<char(191);
 gotoxy(2,3);highvideo();cprintf("N");normvideo();cprintf("ew    ");
 gotoxy(9,3);cout<<char(179);
 gotoxy(2,4);highvideo();cprintf("O");normvideo();cprintf("pen  ");
 gotoxy(9,4);cout<<char(179);
 gotoxy(2,5);highvideo();cprintf("S");normvideo();cprintf("ave  ");
 gotoxy(9,5);cout<<char(179);
 gotoxy(2,6);highvideo();cprintf("C");normvideo();cprintf("lose ");
 gotoxy(9,6);cout<<char(179);
 gotoxy(2,7);cprintf("E");highvideo();cprintf("x");normvideo();cprintf("it  ");
 gotoxy(9,7);cout<<char(179);
 gotoxy(1,8);
 cout<<char(192);
 for(int i=0;i<7;i++)
  cout<<char(196);
 cout<<char(217);
 char option=getch();
 switch(option)
 {
  case 'x': exit(0);
			break;
  case 'n': frame();
			for(int i=0;i<25;i++)
			 linebuf[i][0]='\0';
			char m=textinput();
			menu(m);
			break;
  case 'o': char path1[100];int xpos1,ypos1;
			gettext(10,10,40,15,framebuf);
			gotoxy(10,10);cout<<char(218);
			for(i=1;i<30;i++)
			{
			 gotoxy(10+i,10);
			 cout<<char(196);
			}
			gotoxy(40,10);cout<<char(191);
			gotoxy(10,11);cout<<char(179);gotoxy(40,11);cout<<char(179);
			gotoxy(10,12);cout<<char(179);gotoxy(12,12);cprintf("  Enter a File path:\n");gotoxy(40,12);cout<<char(179);
			gotoxy(10,13);cout<<char(179);gotoxy(40,13);cout<<char(179);
			gotoxy(10,14);cout<<char(179);gotoxy(40,14);cout<<char(179);
			gotoxy(10,15);cout<<char(192);
			for(i=0;i<30;i++)
			 cout<<char(196);
			gotoxy(40,15);cout<<char(217);
			gotoxy(12,13);gets(path1);
			ifstream ifd;
			ifd.open(path1,ios::nocreate|ios::in|ios::app);
			if(ifd==NULL)
			{ gotoxy(12,12);cout<<"Didn't Open\n";}
			frame();
			puttext(10,10,40,15,framebuf);
			gotoxy(2,3);
			char z;int r=0,c=0;
			while(!ifd.eof())
			{
			 ifd.get(z);
			 cout<<z;
			 if(z=='\n')
			 {
			  r++;c=0;
			 }
			 else
			 {
			  linebuf[r][c]=z;
			  c++;
			 }
			}
			ifd.close();
			z=textinput();
			menu(z);
			break;
  case 's': char path[30];int xpos2,ypos2;
			ypos2=wherey();
			xpos2=wherex();
			gettext(1,1,80,25,framebuf);
			gotoxy(10,10);cout<<char(218);
			for(i=1;i<30;i++)
			cout<<char(196);
			cout<<char(191);
			gotoxy(10,11);cout<<char(179);gotoxy(40,11);cout<<char(179);
			gotoxy(10,12);cout<<char(179);cprintf("  Enter a File path:\n");gotoxy(40,12);cout<<char(179);
			gotoxy(10,13);cout<<char(179);gotoxy(40,13);cprintf("%c",char(179));
			gotoxy(10,14);cout<<char(179);gotoxy(40,14);cout<<char(179);
			gotoxy(10,15);cout<<char(192);
			for(i=0;i<30;i++)
			 cout<<char(196);
			gotoxy(40,15);cout<<char(217);
			gotoxy(12,13);gets(path);
			ofstream fd;
			fd.open(path,ios::trunc);
			for(int k=0;k<=lines;k++)
			{
			 fd.write(linebuf[k],lineno[k]);
			}
			fd.close();
			frame();
			puttext(1,1,80,25,framebuf);
			gotoxy(xpos2,ypos2);
			break;
  //case 'c':
  case 27: frame();
		   puttext(1,1,80,25,framebuf);
		   gotoxy(2,3);
		   break;
 }
}


void edit(void)
{
 textattr(07);
 gotoxy(14,2);cout<<char(218);gotoxy(23,2);cout<<char(191);
 gotoxy(14,3);cout<<char(179);highvideo();cprintf(" P");normvideo();cprintf("aste  ");cout<<char(179);
 gotoxy(14,4);cout<<char(179);highvideo();cprintf(" C");normvideo();cprintf("ut    ");cout<<char(179);
 gotoxy(14,5);cout<<char(179);cprintf(" C");highvideo();cprintf("o");normvideo();cprintf("py   ");cout<<char(179);
 gotoxy(14,6);cout<<char(179);highvideo();cprintf(" S");normvideo();cprintf("earch ");cout<<char(179);
 gotoxy(14,7);cout<<char(192);
 for(int i=0;i<8;i++)
  cout<<char(196);
 cout<<char(217);
}
void help(void)
{
 textattr(07);
 gotoxy(71,2);cout<<char(218);
 gotoxy(71,3);cout<<char(179);highvideo();cprintf("C");normvideo();cprintf("ontents");
 gotoxy(71,4);cout<<char(179);highvideo();cprintf("I");normvideo();cprintf("ndex");
 gotoxy(71,5);cout<<char(179);highvideo();cprintf("S");normvideo();cprintf("earch");
 gotoxy(71,6);cout<<char(192);
 for(int i=0;i<8;i++)
  cout<<char(196);
 cout<<char(217);
}
void menu(char x)
{
 int c2;
 c2=x;
 switch(c2)
 {
  case 33:file();
		  break;
  case 18:edit();
		  break;
  case 35:help();
		  break;
 }
}
void main()
{
 int c1;
 frame();
 c1=getch();
 while(c1==0)
 {
  c1=getch();
  menu(c1);
  c1=getch();
 }
 getch();
}
