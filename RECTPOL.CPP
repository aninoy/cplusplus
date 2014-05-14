#include<iostream.h>
#include<conio.h>
#include<math.h>
class rect;
class polar
{
float ra,theta;
public: polar()
		{
		ra=0.0;
		theta=0.0;
		}
		polar(float a, float b)
		{
		ra=a;
		theta=b;
		}
		operator rect();
		void put()
		{
		cout<<" the co-ordinates in polar form are..."<<"\n";
		cout<<ra<<"\t"<<theta<<"\n";
		}
		};
class rect
{
float x,y;
public:  rect()
		 {
		 x=0.0;
		 y=0.0;
		 }
		 rect(float a,float b)
		 {
		 x=a;
		 y=b;
		 }
		 void put_data()
		 {
		 cout<<" the co-ordinates in rectangular form are:"<<"\n";
		 cout<<x<<"\t"<<y<<"\n";

		 }
		 operator polar()
		 {
		 float r1=sqrt(x*x+y*y);
		 float t=atan(y/x);
		 return polar(r1,t);
		 }
		 };
	   polar::operator rect()
	   {
	   float x1=ra*cos(theta);
	   float y1=ra*sin(theta);
	   return rect(x1,y1);
	   }

	   void main()
	   {
	   clrscr();
	   rect r1,r2(3,4);
	   polar p1,p2(5,0.927295) ;
	   p1=r2;
	   p1.put();
	   r1=p2;
	   r1.put_data();
	   getch();
	   }

