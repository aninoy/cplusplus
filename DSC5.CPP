#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<math.h>
int nor=-1;
int proc[20];
int tot,curr,prev;
int movt=0;
int i=0;

void choice();
void result(int a[])
{
	cout<<"Sequence of execution is : -"<<endl;
	//cout<<curr<<"\t";
	for(int j=0;j<i;j++)
	{
		cout<<a[j]<<"\t";
	}
	cout<<endl<<"Total head movement = ";
	int x;
	for(j=0;j<i-1;j++)
	{
	  //if(a[j]>a[j+1])
	  //{
		x=fabs(a[j]-a[j+1]);
		movt+=x;
		//cout<<movt<<"\t";
	 // }
	  //else if(a[j+1]>a[j])
	  //{
	   //	int y=fabs(a[j+1]-a[j]);
	   //	movt+=y;
		//cout<<movt<<"\t";
	 // }
	}
	/*if(curr>a[0])
	{
		int z=curr-a[0];
		movt+=z;
	}
	else
	{
		int z=a[0]-curr;
		movt+=z;
	}                */
	//movt=movt-a[i-1];
	cout<<endl<<movt<<endl;
	getch();
	choice();
}

void fcfs()
{
	result(proc);
}

void sstf()
{
	int a[20];
	for(int j=0;j<=i;j++)
	{
		a[j]=proc[j];
	}
	for(j=0;j<i;j++)
	{
		for(int k=j+1;k<i;k++)
		{
			if(fabs(curr-a[j])>fabs(curr-a[k]))
			{
				int temp;
				temp=a[j];
				a[j]=a[k];
				a[k]=temp;
			}
		   }
	}
	result(a);
	choice();
}
void scan()
{
	int a[20];
	int b[20];
	for(int j=0;j<i;j++)
	{
		a[j]=proc[j];
	}
	cout<<"Enter previous track position : ";
	cin>>prev;
	for(j=0;j<i;j++)
	{
		for(int k=j+1;k<i;k++)
		{
			if(a[j]>a[k])
			{
				int temp;
				temp=a[j];
				a[j]=a[k];
				a[k]=temp;
			}
		}
	}
	j=0;
	while(a[j]<curr)
		j++;
	int count=j;
	if(prev<curr)
	{
		a[i++]=tot-1;
		//cout<<"AI"<<a[i];
		for(int k=0;k<j;k++)
		{
			b[k]=a[k];
		}
		for(k=0;k<j;k++)
		{
			for(int x=0;x<i;x++)
			{
				a[x]=a[x+1];
			}
		}
		for(int x=0;x<i;x++)
			cout<<a[x]<<"\t";
		for(k=j;k>0;k--)
		{
			//for(int x=i-j;x<=i;x++)
				cout<<a[i-k];
				a[i-k]=b[k-1];
				//cout<<"HI:  "<<a[i-k-1];

		}
		result(a);

	}
	if(prev>curr)
	{

		for(int q=0;q<i;q++)
			cout<<a[q]<<" ";

		cout<<i<<endl;
		for(q=i;q>0;q--)
		{
			//cout<<a[j]<<" ";
			a[q]=a[q-1];
			cout<<a[q]<<" ";
		}
		a[0]=0;
		i++;
		cout<<endl;
		for(q=0;q<i;q++)
			cout<<a[q]<<" ";
		//cout<<"AI"<<a[i];
		for(int k=0;k<=count;k++)
		{
			for(int w=k+1;w<=count+1;w++)
			{
				if(a[w]>a[k])
				{
					int temp=a[w];
					a[w]=a[k];
					a[k]=temp;
				}
			}//cout<<a[w]<<endl;
		}

				   /*	for(int k=0;k<=j;k++)
		{
			b[k]=a[k];
		}
		for(k=0;k<j;k++)
		{
			for(int x=0;x<=i;x++)
			{
				a[x]=a[x+1];
			}
		}
		for(int x=0;x<i;x++)

			cout<<a[x]<<"\t";
		for(k=j-1;k>0;k--)
		{
			//for(int x=i-j;x<=i;x++)
				cout<<a[i-k];
				a[i-k]=b[k];
				cout<<" "<<a[i-k];

		}*/
		result(a);
	}
}

void choice()
{
	clrscr();
	i=nor;
	movt=0;
	int ch;
	cout<<"1.FCFS\n2.SSTF\n3.SCAN\n4.Exit\nEnter Choice : ";
	cin>>ch;
	switch(ch)
	{
		case 1:fcfs();
			break;
		case 2:sstf();
			break;
		case 3:scan();
			break;
		default:exit(1);
	}
}

void quest()
{
	int ch;
	while(1)
	{
		cout<<endl<<"New Process? (0/1): ";
		cin>>ch;
		switch(ch)
		{
			case 0: nor=i;
					choice();
					break;
			case 1:
			cout<<"Enter cylinder no : ";
				cin>>proc[i];
				i++;
				break;
		}
	}
}

void main()
{
	clrscr();
	cout<<"Enter the total number of cylinders : ";
	cin>>tot;
	cout<<"Cylinders are labeled from 0 to "<<tot-1<<endl;
	cout<<"Enter current postion of the head : ";
	cin>>curr;
	cout<<"Current Head Location : "<<curr<<endl;
	proc[i++]=curr;
	quest();
	getch();
}

