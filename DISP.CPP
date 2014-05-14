#include<iostream.h>
#include<conio.h>
#include<dos.h>

void output(int x)
{
	int i;
	for(i=0;i<50;i++)
		outportb(0x3bc,x);
}
void main()
{
	clrscr();
	int i,x,z;
	int a[65]={0,4,2,6,1,5,3,7,32,36,34,38,33,37,35,39,
			   16,20,18,22,17,21,19,23,48,52,50,54,49,53,51,55,
			   8,12,10,14,9,13,11,15,40,44,42,46,41,45,43,47,
			   24,28,26,30,25,29,27,31,56,60,58,62,57,61,59,63};
	z=100;
	while(1)
	{
		for(i=0;i<z*8;i++)
		{
		for(x=27;x<=36;x++)
		{
			if(x%8<=4 && x%8>=3)
				output(a[x]);
			else
				continue;
		}
		}
		for(i=0;i<z*2;i++)
		{
		for(x=18;x<=45;x++)
		{
			if(x%8<=5 && x%8>=2)
				output(a[x]);
			else
				continue;
		}
		}
		for(i=0;i<z;i++)
		{
		for(x=9;x<=54;x++)
		{
			if(x%8<=6 && x%8>=1)
				output(a[x]);
			else
				continue;
		}
		}
		for(i=0;i<z/2;i++)
		{
		for(x=0;x<=63;x++)
		{
			if(x%8<=7 && x%8>=0)
				output(a[x]);
			else
				continue;
		}
		}
		//delay(z);
	}
	getch();
}