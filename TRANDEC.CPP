#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<process.h>
#include<string.h>
void main()
{
	char str[100],key[6],dyc[6][20];
	int len=strlen(str),part=len/6;
	cout<<"enter key:";
	gets(key);
	cout<<"enter string:";
	gets(str);
	for(int i=0,q=0;i<6;i++)
	{
		for(int j=0;j<part;j++)
			dyc[i][j]=str[q++];
		dyc[i][j]='\0';
	}
	q=0;
	for(int j=0;j<part;j++)
		for(i=0;i<6;i++)
		{
			int x=key[i]-'0'-1;
			str[q++]=dyc[x][j];
		}
	cout<<str;
	getch();
}