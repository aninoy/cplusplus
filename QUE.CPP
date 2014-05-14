#include<iostream.h>
#include<conio.h>
#include<process.h>
 const int max=3;
 class queue
 {
 int a[max];
 int rear,front;
 public:
 queue()
 {
 rear=front=0;
 }
 void get_data();
 int put_data();
 };
 void queue::get_data()
 {
 int n;
 if(front==(rear+1)%max)
 {
 cout<<" the queue is full.. cannot add more data.."<<"\n";
 getch();

 }
 else
 {
 rear=(rear+1)%max ;
 cin>>n;
 a[rear]=n;
 }
 }
 int queue::put_data()
 {
 int val;
 if(rear==front)
 {
 cout<<" the queue is empty.."<<"\n";
 getch();
 exit(0);
 }
 else
 {
 front=(front+1)%max;
 val=a[front];
 }
 return(val);
 }

 void main()
 {
 int val;
 clrscr();
 queue q;
 char ch;
 do
 {
 cout<<" enter the data.."<<"\n";
 q.get_data();
 cout<<"do u want to pop the values.. y/n"<<"\n";
 cin>>ch;
 } while(ch=='n' || ch=='N');
 do
 {
 cout<<" printing the data.."<<"\n";
 val=q.put_data();
 cout<<val<<"\n";
 cout<<" do u want to continue.."<<"\n";
 cin>>ch;
 } while(ch=='y' || ch=='Y');
 getch();
 }
