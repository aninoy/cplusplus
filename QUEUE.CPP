#include<iostream.h>
#include<conio.h>
const int max=3;
class queue
{
int front,rear,data[max];
public:
queue(int x=0,int y=0)
{
rear=x;
front=y;
}
void put_queue(int n)
{
if((rear+1)%max==front)

{
cout<<"queue full";
}
else
{
rear=(rear+1)%max;
data[rear]=n;
}
}
int getdata()
{
int val;
if(front==rear)
{
cout<<"queue is empty";
val=-1;
}
else
{
front=(front+1)%max;
val=data[front];
}
return val;
}
};
void main()
{
clrscr();
queue q;
q.put_queue(10);
q.put_queue(11);
//q.put_queue(12);
cout<<q.getdata();
cout<<q.getdata();
//cout<<q.getdata();
getch();
}





