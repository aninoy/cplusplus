#include<conio.h>
#include<process.h>
#include<string.h>
#include<fstream.h>

int x,y;

struct node
{
	node *next,*prev;
	char sent[80];
	int i,y;
};

node* head=NULL;
node* tail=head;

node* insert(node* tail)
{
	node* temp=new node;
	temp->next=NULL;
	temp->prev=tail;
	temp->sent[0]='\0';
	temp->i=strlen(temp->sent);
	tail->next=temp;
	tail=temp;
	return tail;
}

void setxy()
{
	int e=wherex(),t=wherey();
	textbackground(WHITE);
	textcolor(BLACK);
	gotoxy(64,48);
	cprintf("               ");
	gotoxy(64,48);
	cprintf("LINE: %d COL: %d",t-3,e-1);
	textbackground(BLUE);
	gotoxy(e,t);
}
void textarea();
void display(node* head)
{
	textarea();
	int x=4;
	node* cur=head;
	for(;cur!=NULL;cur=cur->next)
	{
		gotoxy(2,x);
		cprintf("%s",cur->sent);
		x++;
	}
	return;
}
int save();
int open()
{
	int rew=1;
	if(head->i!=0)
	{
		window(20,22,60,27);
		textbackground(WHITE);
		clrscr();
		gotoxy(2,2);
		cprintf("%c",218);
		for(int i=0;i<37;i++)
			cprintf("%c",196);
		cprintf("%c",191);
		for(i=3;i<5;i++)
		{
			gotoxy(40,i);
			cprintf("%c",179);
		}
		gotoxy(40,5);
		cprintf("%c",217);
		gotoxy(2,5);
		cprintf("%c",192);
		for(i=0;i<37;i++)
			cprintf("%c",196);
		char yn;
		for(i=3;i<5;i++)
		{
			gotoxy(2,i);
			cprintf("%c",179);
		}
		textcolor(BLACK);
		cprintf("DO YOU WANT TO SAVE NOW(Y/N): ");
		yn=getche();
		if(yn=='y')
			rew=save();
		if(!rew)
			return 0;
	}
	char str[20];
	char strl[80];
	window(20,22,60,27);
	textbackground(WHITE);
	clrscr();
	gotoxy(2,2);
	cprintf("%c",218);
	for(int i=0;i<37;i++)
		cprintf("%c",196);
	cprintf("%c",191);
	for(i=3;i<5;i++)
	{
		gotoxy(40,i);
		cprintf("%c",179);
	}
	gotoxy(40,5);
	cprintf("%c",217);
	gotoxy(2,5);
	cprintf("%c",192);
	for(i=0;i<37;i++)
		cprintf("%c",196);
	for(i=3;i<5;i++)
	{
		gotoxy(2,i);
		cprintf("%c",179);
	}
	textcolor(BLACK);
	gotoxy(19,2);
	cprintf("OPEN");
	gotoxy(3,4);
	cprintf("Enter the file name: ");
	cscanf("%s",str);
	getch();
	ifstream in(str);
	gotoxy(3,4);
	if(!in)
	{
		gotoxy(3,4);
		cprintf("                                     ");
		gotoxy(3,4);
		cprintf("Cannot open the %s file!",str);
		getch();
		in.close();
		return 0;
	}
	node* cur;
	int y=0;
	while(in)
	{
		in.getline(strl,80);
		if(in)
		{
			cur=new node;
			if(!y)
			{
				head=tail=cur;
				y=4;
			}
			strcpy(cur->sent,strl);
			cur->i=strlen(cur->sent);
			cur->y=y++;
			cur->prev=tail;
			tail->next=cur;
			tail=cur;
			cur->next=NULL;
		}
	}
	in.close();
	display(head);
	setxy();
	return 1;
}
int save()
{
	char str[20];
	char strl[80];
	window(20,22,60,27);
	textbackground(WHITE);
	clrscr();
	gotoxy(2,2);
	cprintf("%c",218);
	for(int i=0;i<37;i++)
		cprintf("%c",196);
	cprintf("%c",191);
	for(i=3;i<5;i++)
	{
		gotoxy(40,i);
		cprintf("%c",179);
	}
	gotoxy(40,5);
	cprintf("%c",217);
	gotoxy(2,5);
	cprintf("%c",192);
	for(i=0;i<37;i++)
		cprintf("%c",196);
	for(i=3;i<5;i++)
	{
		gotoxy(2,i);
		cprintf("%c",179);
	}
	textcolor(BLACK);
	gotoxy(19,2);
	cprintf("SAVE");
	gotoxy(3,4);
	cprintf("Enter the file name: ");
	cscanf("%s",str);
	getch();
	ofstream of;
	of.open(str,ios::trunc);
	if(!of)
	{
		gotoxy(3,4);
		cprintf("                                     ");
		gotoxy(3,4);
		cprintf("Cannot save to the %s file!",str);
		getch();
		of.close();
		return 0;
	}
	for(node* cur=head;cur!=NULL;cur=cur->next)
		of<<cur->sent<<endl;
	of.close();
	textarea();
	display(head);
	return 1;
}
int search_array[20][2];
int s_pos=-1;
void search()
{
	char sub[20];
	window(20,22,60,27);
	textbackground(WHITE);
	clrscr();
	gotoxy(2,2);
	cprintf("%c",218);
	for(int i=0;i<37;i++)
		cprintf("%c",196);
	cprintf("%c",191);
	for(i=3;i<5;i++)
	{
		gotoxy(40,i);
		cprintf("%c",179);
	}
	gotoxy(40,5);
	cprintf("%c",217);
	gotoxy(2,5);
	cprintf("%c",192);
	for(i=0;i<37;i++)
		cprintf("%c",196);
	for(i=3;i<5;i++)
	{
		gotoxy(2,i);
		cprintf("%c",179);
	}
	textcolor(BLACK);
	gotoxy(19,2);
	cprintf("SEARCH");
	gotoxy(3,4);
	cprintf("Enter the search keywords: ");
	cscanf("%s",sub);
	getch();
	char strl[80];
	node *cur=head;
	int cur_pos=4;
	while(cur)
	{
		strcpy(strl,cur->sent);
		int fl=1;
		for(int i=0;i<strlen(strl);i++)
		{
			if(strl[i]==sub[0])
			{
				fl=1;
				for(int j=0;strl[i+j]!='\0'&&sub[j]!='\0';j++)
					if(strl[i+j]!=sub[j])
						fl=0;
				if(fl)
				{
					search_array[++s_pos][0]=i+2;
					search_array[s_pos][1]=cur_pos;
				}
			}
		}
		cur=cur->next;
		cur_pos++;
	}
	textarea();
	display(head);
	if(s_pos!=-1)
		gotoxy(search_array[0][0],search_array[0][1]);
	setxy();
}

int newf()
{
	int rew=1;
	window(20,22,60,27);
	textbackground(WHITE);
	clrscr();
	gotoxy(2,2);
	cprintf("%c",218);
	for(int i=0;i<37;i++)
		cprintf("%c",196);
	cprintf("%c",191);
	for(i=3;i<5;i++)
	{
		gotoxy(40,i);
		cprintf("%c",179);
	}
	gotoxy(40,5);
	cprintf("%c",217);
	gotoxy(2,5);
	cprintf("%c",192);
	for(i=0;i<37;i++)
		cprintf("%c",196);
	char yn;
	for(i=3;i<5;i++)
	{
		gotoxy(2,i);
		cprintf("%c",179);
	}
	textcolor(BLACK);
	cprintf("DO YOU WANT TO SAVE NOW(Y/N): ");
	yn=getche();
	if(yn=='y')
		rew=save();
	if(!rew)
		return 0;
	head=new node;
	tail=head;
	head->next=NULL;
	head->prev=NULL;
	head->sent[0]='\0';
	head->y=4;
	head->i=strlen(head->sent);
	textarea();
	return 1;
}

int file()
{
	int ch,rew;
	window(2,3,10,10);
	textbackground(WHITE);
	clrscr();
	gotoxy(3,3);
	highvideo();
	textcolor(RED);
	cprintf("N");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("ew");
	gotoxy(3,4);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("O");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("pen");
	gotoxy(3,5);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("S");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("ave");
	gotoxy(3,6);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("C");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("lose");
	gotoxy(3,7);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("E");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("xit");
	textbackground(BLUE);
	while(1)
	{
		ch=getch();
		if(!ch)
			ch=getch();
		switch(ch)
		{
			case 120:
				exit(0);
				break;
			case 111:
				rew=open();
				return rew;
			case 115:
				rew=save();
				return rew;
			case 99:
			     //	close();
				return 0;
			case 110:
				newf();
				return 1;
			case 27:
				return 0;
		}
	}
}

void edit()
{
	int ch;
	window(12,3,20,10);
	textbackground(WHITE);
	clrscr();
	gotoxy(3,3);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("C");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("ut");
	gotoxy(3,4);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("C");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("opy");
	gotoxy(3,5);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("P");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("aste");
	gotoxy(3,6);
	highvideo();
	textcolor(RED);
	textbackground(WHITE);
	cprintf("S");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("earch");
	textbackground(BLUE);
	int x;
	int y;
	int pos=1;
	while(1)
	{
		ch=getch();
		if(!ch)
			ch=getch();
		switch(ch)
		{
			case 115:
				 search();
				 break;

			case 12:
				x=wherex();
				y=wherey();
				if(s_pos!=-1)
					if(pos!=s_pos)
						gotoxy(search_array[pos][0],search_array[pos++][1]);
				break;

			case 27:
				return;
		}
	}
}

void textarea()
{
	textbackground(BLUE);
	textcolor(WHITE);
	window(1,1,80,50);
	clrscr();
	gotoxy(1,2);
	textbackground(WHITE);
	insline();
	gotoxy(1,48);
	insline();
	textbackground(BLUE);
	gotoxy(1,1);
	cprintf("%c",201);
	for(int i=0;i<79;i++)
		cprintf("%c",205);
	gotoxy(80,1);
	cprintf("%c",187);
	for(i=2;i<50;i++)
	{
		gotoxy(1,i);
		cprintf("%c",186);
	}
	gotoxy(1,49);
	cprintf("%c",200);
	for(i=0;i<79;i++)
		cprintf("%c",205);
	gotoxy(80,49);
	cprintf("%c",188);
	for(i=2;i<49;i++)
	{
		gotoxy(80,i);
		cprintf("%c",186);
	}
	gotoxy(1,3);
	cprintf("%c",204);
	for(i=0;i<78;i++)
		cprintf("%c",205);
	cprintf("%c",185);
	gotoxy(1,47);
	cprintf("%c",204);
	for(i=0;i<78;i++)
		cprintf("%c",205);
	cprintf("%c",185);
	gotoxy(34,1);
	cprintf("TEXT EDITOR");
	textbackground(WHITE);
	gotoxy(2,2);
	highvideo();
	textcolor(RED);
	cprintf("F");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("ile");
	gotoxy(12,2);
	highvideo();
	textcolor(RED);
	cprintf("E");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("dit");
	gotoxy(72,2);
	highvideo();
	textcolor(RED);
	cprintf("H");
	normvideo();
	textcolor(BLACK);
	textbackground(WHITE);
	cprintf("elp");
	gotoxy(2,4);
	setxy();
	textbackground(BLUE);
}

void main()
{
	textarea();
	int ch,in,j,flag=0,ch1,r,u,op=0;
	char buf[100][100];
	char buff[80];
	char temp;
	node* cur;
	head=new node;
	head->next=NULL;
	head->prev=NULL;
	head->sent[0]='\0';
	head->i=strlen(head->sent);
	head->y=4;
	tail=head;
	while(1)
	{
		ch=getch();
		flag=0;
		if(!ch)
		{
			ch=getch();
			flag=1;
		}
		switch(ch)
		{
			case 8:
				if(!(wherey()==4&&wherex()==2))
				{
					in=wherey()-4;
					cur=head;
					u=wherex();
					while(in>0)
					{
						cur=cur->next;
						in--;
					}
					if(wherex()==2)
					{
						cur=cur->prev;
						gotoxy((cur->i)+2,wherey()-1);
						u=cur->i+2;
					}
					x=wherex()-3;
					while(x<strlen(cur->sent))
					{
						cur->sent[x]=cur->sent[x+1];
						x++;
					}
					cur->sent[x]='\0';
					gotoxy(2,wherey());
					cprintf("                                                                              ");
					gotoxy(2,wherey());
					cprintf("%s",cur->sent);
					cur->i=strlen(cur->sent);
					gotoxy(u-1,wherey());
				}
				setxy();
				break;
			case 27:
				break;
			case 13:
				tail->sent[tail->i]='\0';
				gotoxy(2,wherey()+1);
				tail=insert(tail);
				tail->y=wherey();
				setxy();
				break;
			case 75:
				if(flag)
				{
					cur=head;
					while(cur->y!=wherey())
						cur=cur->next;
					if(!(wherey()==4&&wherex()==2))
					{
						if(wherex()==2)
							gotoxy(cur->prev->i+2,wherey()-1);
						else
							gotoxy(wherex()-1,wherey());
					}
					setxy();
					break;
				}
			case 72:
				if(flag)
				{
					cur=head;
					while(cur->y!=wherey())
						cur=cur->next;
					if(wherey()!=4)
						if(wherex()<=cur->prev->i+2)
							gotoxy(wherex(),wherey()-1);
						else
							gotoxy(cur->prev->i+2,wherey()-1);
					setxy();
					break;
				}
			case 80:
				if(flag)
				{
					cur=head;
					while(cur->y!=wherey())
						cur=cur->next;
					if(wherey()!=(tail->y))
						if(wherex()<=cur->next->i+2)
							gotoxy(wherex(),wherey()+1);
						else
							gotoxy(cur->next->i+2,wherey()+1);
					setxy();
					break;
				}
			case 77:
				if(flag)
				{
					cur=head;
					while(cur->y!=wherey())
						cur=cur->next;
					if(!(wherey()==tail->y&&wherex()==((tail->i)+2)))
					{
						if(wherex()==((cur->i)+2))
							gotoxy(2,wherey()+1);
						else
							gotoxy(wherex()+1,wherey());
					}
					setxy();
					break;
				}
			case 71:
				if(flag)
				{
					gotoxy(2,wherey());
					setxy();
					break;
				}
			case 79:
				if(flag)
				{
					cur=head;
					while(cur->y!=wherey())
						cur=cur->next;
					gotoxy(cur->i+2,wherey());
					setxy();
					break;
				}
			case 33:
				if(flag)
				{
					gettext(2,2,80,50,buf);
					x=wherex();
					y=wherey();
					op=file();
					if(!op)
					{
						textarea();
						puttext(2,2,80,50,buf);
						gotoxy(x,y);
						setxy();
					}
					break;
				}
			case 45:
				if(flag)
				{
					exit(0);
					break;
				}
			case 18:
				if (flag)
				{
					gettext(2,2,80,50,buf);
					x=wherex();
					y=wherey();
					edit();
					textarea();
					puttext(2,2,80,50,buf);
					gotoxy(x,y);
					setxy();
					break;
				}
			default:
				in=wherey()-4;
				cur=head;
				while(in>0)
				{
					cur=cur->next;
					in--;
				}
				u=wherex();
				r=wherex()-2;
				ch1=cur->sent[r];
				cur->sent[r]=ch;
				while(cur->sent[r]!='\0')
				{
					temp=cur->sent[r+1];
					cur->sent[r+1]=ch1;
					ch1=temp;
					r++;
				}
				cur->sent[r]='\0';
				cur->i=strlen(cur->sent);
				gotoxy(2,wherey());
				cprintf("                                                                              ");
				gotoxy(2,wherey());
				cprintf("%s",cur->sent);
				j=wherey()+1;
				if(cur->i==77)
				{
					gotoxy(2,j);
					tail=insert(tail);
					tail->y=wherey();
				}
				else
					gotoxy(u+1,wherey());
				setxy();
		}
	}
}