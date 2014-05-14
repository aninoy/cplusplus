#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
void main()
{
	clrscr();
	char *inp,*key,*key1,*res;
	char A[26]="abcdefghijklmnopqrstuvwxyz",B[26];
	gets(inp);
	gets(key);
	int i=0,j,k=-1,flag,len;
	while(i<strlen(key))
	{
		j=0;flag=0;
		while(j<=k)
		{
			if(*(key+i)==*(key1+j))
				flag=1;
			j++;
		}
		if(flag!=1)
			*(key1+ ++k)=*(key+i);
		i++;
	}
	*(key1+ ++k)='\0';
	i=0;len=strlen(key1);
	while(i<len)
	{
		B[i]=*(key1+i);
		i++;
	}
	i=0;
	while(i<26)
		if(A[i++]==*(key1+len-1)) break;

	k=len-1;j=i+1;
	while(k<26)
	{
		flag=0;i=0;
		while(i<=k)
		{
			if(A[j]==B[i]) flag=1;
			i++;
		}
		if(flag!=1)
			B[++k]=A[j];
		j++;
		j%=26;
	}
	cout<<"B= "<<B;
	getch();
}