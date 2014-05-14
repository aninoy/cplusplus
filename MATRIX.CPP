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
		cprintf(" ");
		delay(1);
		gotoxy(rand()%80+1,rand()%60+1);
		c=rand()%2;
		cout<<c;
		k=rand()%15;
		for(j=0;j<k;j++)
			cout<<" ";
		textcolor(LIGHTGREEN);
		cprintf(" ");
		delay(1);
		gotoxy(rand()%80+1,rand()%60+1);
		c=rand()%2;
		cout<<c;

	}
	getch();
}