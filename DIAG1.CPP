#include<iostream.h>
#include<conio.h>
#include<dos.h>

void main()
{
	clrscr();
	int i,a;
	//a=inportb(0x3bc);
	//cout<<"Value = "<<a<<endl;
	for(i=0;i<50;i++)
		outportb(0x3bc,0);
	cout<<"Value = "<<int(inportb(0x3bc));
	getch();
}