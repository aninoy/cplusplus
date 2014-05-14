#include<iostream.h>
#include<conio.h>
#include<dos.h>

void main()
{
	clrscr();
	int i,x;
	/*int a[65]={0,1,2,3,4,5,6,7,
			   8,9,10,11,12,13,14,15,
			   16,17,18,19,20,21,22,23,
	*/
	while(1)
	{
		for(x=0;x<=65;x++)
		{

			for(i=0;i<50;i++)
				outportb(0x3bc,x)
		}
	}
	getch();
}