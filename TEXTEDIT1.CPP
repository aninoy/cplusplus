#include<string.h>
#include<fcntl.h>
#include <process.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <iomanip.h>
char *textinput(char *buf[])
{
 
 char c,str[100];int i=0,x;
 gotoxy(2,2);
 while(1)
 {
  c=getche();
  x=c;
  switch(x)
  {
   case 0: break;               
   case 13: strcat(str,'\0');
	 buf[i]=str;
                 i++;
	 break;
   default: strcat(str,c);
  }
  if(x==0)
   break;
 }
 return buf;
}
void menu(void);
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
 cprintf(" Status:                                                      Line:   Column:   ");
}


void file(void)
{
 //textattr(07);
 char *framebuf;
 gettext(1,1,80,25,framebuf);
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
void menu(void)
{
 int c=getch();
 if(c==0)
 {
  c=getch();
  switch(c)
  {
   case 33:file();
                char option=getch();
  	switch(option)
  	{
  	 case 'x': exit(0);
                              break;
  
  	case 'N': frame();
                              char *buffer[80];
                              buffer=textinput(buffer);
                              char c=getch();
                              switch(c)
                              {
                               case 33: file();
                                             break;
 	               case 18: edit();
 	                             break;
	               case 35: help();
	                             break;
               	             }
                             break;
  
  	//case 'O':
  
  	case 'S':    char path[30];
		gotoxy(10,10);cout<<char(218);
		for(i=0;i<30;i++)
	 	cout<<char(196);
		cout<<char(191);
		gotoxy(10,11);cout<<char(179);gotoxy(30,11);cout<<char(179);
		gotoxy(10,12);cout<<char(179);cprintf("  Enter a File path:\n");gotoxy(30,11);cout<<char(179);
		gotoxy(10,13);cout<<char(179);gotoxy(30,11);cout<<char(179);
		gotoxy(10,14);cout<<char(179);gotoxy(30,11);cout<<char(179);
		gotoxy(10,15);cout<<char(192);
		for(i=0;i<20;i++)
		 cout<<char(196);
		gotoxy(20,11);cout<<char(217);
		gotoxy(12,13);gets(path);
		frame();
		puttext(1,1,80,25,framebuf);
		break;

  	//case 'C':

  	case 27: frame();
		puttext(1,1,80,25,framebuf);
                	break;
 	}
                break;

   case 18:edit();

   case 35:help();
  }
 }
}
void main()
{
 int c;
 frame();
 menu();
 getch();
}
