#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
void main()
{
	clrscr();
	int r,c,i,j,a;
	char x;
	randomize();
	while(1)
	{
	r=14;
	c=41;
	a=0;
	while(r>=2)
	{
		for(i=r-1;i<r+a;i++)
		{
			for(j=c-1;j<c+a;j++)
			{
				gotoxy(j,i);
				x=rand()*100+32;
				cout<<x;
			}
		}
		delay(50);
		r--;
		c--;
		a+=2;
	}
	while(c>=2)
	{
		for(i=c-1;i<c+a;i++)
		{
			for(j=1;j<=25;j++)
			{
				gotoxy(i,j);
				x=rand()*100+32;
				cout<<x;
			}
		}
		c--;
		a+=2;
		delay(10);
	}
	delay(500);
	while(c<=28)
	{
		for(i=1;i<=25;i++)
		{
			gotoxy(c,i);
			cout<<" ";
			gotoxy(80-c,i);
			cout<<" ";
		}
		delay(50);
		c++;
	}
	a=22;
	while(r<=14)
	{
		for(i=1;i<=25;i++)
		{
			gotoxy(c,i);
			cout<<" ";
			gotoxy(80-c,i);
			cout<<" ";
		}
		for(i=c;i<=c+a;i++)
		{
			gotoxy(i,r);
			cout<<" ";
			gotoxy(i,26-r);
			cout<<" ";
		}
		a-=2;
		c++;
		r++;
		delay(50);
	}
	}
	getch();
}