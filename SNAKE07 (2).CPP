#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<process.h>
#include<stdlib.h>

struct snake
{
 int x,y,dir[10][3],n,score;
 snake* p;
};

snake *head;
int direction,key_pressed_x,key_pressed_y,food_x,food_y;

void snake_init()
{
 snake *cur;
 for(int i=0;i<5;i++)
 {
  snake* temp = new snake;
  if(i!=0) cur->p=temp;
  temp->x=10-i;
  temp->y=10;
  temp->n=0;
  temp->dir[0][0]=77;
  temp->dir[0][1]=-1;
  temp->dir[0][2]=-1;
  for(int j=1;j<10;j++)
   cur->dir[j][0]=cur->dir[j][1]=cur->dir[j][2]=-1;
  cur=temp;
  if(i==0)
  {
   head=temp;
   head->score=0;
  }
 }
 cur->p=NULL;
}

void snake_display()
{
 clrscr();
 gotoxy(food_x,food_y);
 cout<<"*";
 snake *cur;
 cur=head;
 while(cur!=NULL)
 {
  gotoxy(cur->x,cur->y);
  cout<<"*";
  cur=cur->p;
 }
 gotoxy(head->x,head->y);
}

void get_key()
{
 int ch=getch();
 if(ch==0)
 {
  int ch1=getch();
  direction=ch1;
  key_pressed_x=wherex();
  key_pressed_y=wherey();
 }
 if(ch==120)
  exit(0);
}

void game_over()
{
 gotoxy(35,12);
 cout<<"GAME OVER !!!";
 gotoxy(33,13);
 cout<<"Your score is: "<<head->score;
 gotoxy(31,14);
 cout<<"Press Any Key To Exit";
 getch();
 exit(0);
}

void snake_elongate()
{
 snake *cur1;
 snake *temp1=new snake;
 cur1=head;
 head->score++;
 while(cur1->p!=NULL)
  cur1=cur1->p;
 cur1->p=temp1;
 temp1->p=NULL;
 temp1->x=cur1->x;
 temp1->y=cur1->y;
 switch(cur1->dir[0][0])
 {
  case 77: temp1->x--; break;
  case 75: temp1->x++; break;
  case 80: temp1->y--; break;
  case 72: temp1->y++; break;
 }
 for(int i=0;i<10;i++)
 {
  temp1->dir[i][0]=cur1->dir[i][0];
  temp1->dir[i][1]=cur1->dir[i][1];
  temp1->dir[i][2]=cur1->dir[i][2];
 }
 temp1->n=cur1->n;
}

void snake_update()
{
 snake *cur;
 cur=head;
 while(cur!=NULL)
 {
  if(cur->x==cur->dir[0][1] && cur->y==cur->dir[0][2])
  {
   for(int i=0;i<cur->n;i++)
   {
	cur->dir[i][0]=cur->dir[i+1][0];
	cur->dir[i][1]=cur->dir[i+1][1];
	cur->dir[i][2]=cur->dir[i+1][2];
   }
   cur->dir[cur->n][0]=cur->dir[cur->n][1]=cur->dir[cur->n][2]=-1;
   cur->n--;
  }
  switch(cur->dir[0][0])
  {
   case 72: if(cur->y==0) cur->y=25;
		else cur->y--;
		break;
   case 80: if(cur->y==25) cur->y=0;
		else cur->y++;
		break;
   case 75: if(cur->x==0) cur->x=80;
		else cur->x--;
		break;
   case 77: if(cur->x==80) cur->x=0;
		else cur->x++;
		break;
  }
  cur=cur->p;
 }
 cur=head->p;
 while(cur!=NULL)
 {
  if(head->x==cur->x && head->y==cur->y)
   game_over();
  cur=cur->p;
 }
 if(head->x==food_x && head->y==food_y)
 {
  snake_elongate();
  regenerate: food_x=random(80)+1;
  food_y=random(25)+1;
  cur=head;
  while(cur!=NULL)
  {
   if(food_x==cur->x && food_y==cur->y)
	goto regenerate;
   cur=cur->p;
  }
 }
}

void main()
{
 clrscr();
 randomize();
 head = new snake;
 food_x=50;
 food_y=20;
 snake_init();
 snake_display();
 while(1)
 {
  if(kbhit())
  {
   get_key();
   snake *cur;
   cur=head;
   while(cur!=NULL)
   {
	if(!((cur->dir[cur->n][0]==77 && direction==75) || (cur->dir[cur->n][0]==75 && direction==77) || (cur->dir[cur->n][0]==72 && direction==80) || (cur->dir[cur->n][0]==80 && direction==72)))
	{
	 cur->n++;
	 cur->dir[cur->n][0]=direction;
	 cur->dir[cur->n-1][1]=key_pressed_x;
	 cur->dir[cur->n-1][2]=key_pressed_y;
	}
	cur=cur->p;
   }
  }
  snake_update();
  snake_display();
  delay(65);
 }
}