#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>
void main()
{
	clrscr();
	char str[6][35];
	char enc[6][35];
	char inp[210];
	int i=0,j,k=0;
	for(i=0;i<30;i++)
		for(j=0;j<6;j++)
			enc[i][j]=str[i][j]='\0';
	char key[6],sort[6];
	cout<<"Enter 6 digit numeric key : ";
	gets(key);
	puts(key);
	cout<<"Enter String to be encoded : ";
	gets(inp);
	puts(inp);
	int loc[6];
	int len=strlen(inp);
	i=0;
	while(k<len)
	{
	 for(j=0;j<6;j++)
	 {
		while(inp[k]==' ')
			k++;
		str[j][i]=inp[k++];
	 }
	 i++;
	}
	for(i=0;i<6;i++)
		puts(str[i]);
	getch();
	strcpy(sort,key);
	for(i=0;i<6;i++)
		loc[i]=0;
	for(i=0;i<6;i++,k++)
	{
		int small=sort[i],posn=i;
		for(j=i+1;j<6;j++)
		{
			if(small>sort[j])
			{
				small=sort[j];
				posn=j;
			}
		}
		int temp=sort[i];
		sort[i]=small;
		sort[posn]=temp;
	}
	for(i=0;i<6;i++)
		cout<<sort[i]<<"\n";
	getch();
	for(i=0;i<6;i++)
	{
		j=0;
		while(j<6)
		{
			if(sort[i]==key[j])
				loc[i]=j;
			j++;
		}
	}
	for(i=0;i<6;i++)
	 cout<<loc[i]<<"\n";
	for(i=0;i<6;i++)
	{
		int l=loc[i];
		strcpy(enc[i],str[l]);
	}
	cout<<"The Encrypted data is:-\n";
	for(i=0;i<6;i++)
		puts(enc[i]);
	getch();
}



