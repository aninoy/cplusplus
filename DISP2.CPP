#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<process.h>


int a[8][8]={0,4,2,6,1,5,3,7,
			 32,36,34,38,33,37,35,39,
			 16,20,18,22,17,21,19,23,
			 48,52,50,54,49,53,51,55,
			 8,12,10,14,9,13,11,15,
			 40,44,42,46,41,45,43,47,
			 24,28,26,30,25,29,27,31,
			 56,60,58,62,57,61,59,63};
int b[8][8];
#define ABORT 0

int c_break(void)
{
   //ntf("Control-Break pressed.  Program aborting ...\n");
   return (ABORT);
}

void output(int x)
{
	int i;
	for(i=0;i<50;i++)
		outportb(0x3bc,x);
}

void disparray()
{
	int i,j,del;
	char c;
	cout<<"\nDelay = ";
	cin>>del;

	while(1)
	{

		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				if(b[i][j]==1)
					output(a[i][j]);
				delay(del);
			}
		}
	}
}
void inputarray()
{
	int i,j,r,c;
	r=c=1;
	for(i=0;i<8;i++)
	{
		c=1;
		for(j=0;j<8;j++)
		{
			gotoxy(c,r);
			b[i][j]=getch()-48;
			if(b[i][j]==1)
				cout<<"o";
			else
				cout<<".";
			c+=2;
		}
		r++;
	}
}
void dispmatrix()
{
	clrscr();
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
			cout<<"_ ";
		cout<<endl;
	}
}
void main()
{
	clrscr();
	int i,j,x,z;
	ctrlbrk(c_break);
	dispmatrix();
	inputarray();
	disparray();
	getch();
}