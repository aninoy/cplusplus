#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
void main()
{
	int c,k,i,j;
	randomize();
	clrscr();

	while(1)
	{
		textcolor(GREEN);
		cprintf("32  ");
		delay(0.9);
		c=rand()%100;
		cout<<c;
		k=rand()%8;
		for(j=0;j<k;j++)
			cout<<" ";
		k=rand()%5;
		if(k==1)
		{
			textcolor(WHITE);
			cprintf("0");
		}
	}
	getch();
}