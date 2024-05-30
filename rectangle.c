#include<iostream>
#include<cmath>
using namespace std;

class rectangle{
	public:
		struct point{
			int x;
			int y;
		};
	       struct edge{
			int length;
			int breadth;
		};
		
	public:
		struct point rec[4];
		void print();
		struct edge *ed;
		struct edge  maxmin();
		int perimeter(rectangle::edge e);
		int area(rectangle::edge e);
};

void rectangle::print (){
	int i;
	cout<<"the coordinates of the rectangle are:"<<endl;
	for(i=0;i<4;i++){
		cout<<"x :"<<rec[i].x<<endl<<"y :"<<rec[i].y<<endl;
	}
}

rectangle::edge   rectangle::maxmin(){
	int i,x,y;
	float d;
	int m[4];
	for(i=0;i<4;i++){
		x=rec[i+1].x-rec[i].x;
		y=rec[i+1].y-rec[i].y;
		d=sqrt(((x*x)+(y*y)));
		m[i]=d;
	}
	int l,b;
	l=m[0];
	b=m[0];
	for(i=0;i<3;i++){
		if(m[i]>l){
			l=m[i];
		}
	}
	for(i=0;i<3;i++){
		if(m[i]<b){
			b=m[i];
		}
	}
	for(i=0;i<3;i++){
		if(m[i] != l && m[i] != b){
			l=m[i];
		}
           }
	struct edge  e;
	e.length=l;
	e.breadth=b;
	cout<<"length is:"<<l<<endl<<"breadth is:"<<b<<endl;
	return e;

}

int rectangle::perimeter(rectangle::edge e){
	int l,b,p;
	l=e.length;
	b=e.breadth;
	p=(2*l) +(2*b);
	return p;
}

int rectangle::area(rectangle::edge e){
	int l,b,a;
	l=e.length;
	b=e.breadth;
	a=l*b;
	return a;
}


int main(){
	int i,perimeter,area;
	rectangle r;
	for(i=0;i<4;i++){
		cout<<"enter the point:"<<endl;
		cin>>r.rec[i].x>>r.rec[i].y;
	}
	r.print();
	rectangle::edge ed = r.maxmin();
	perimeter=r.perimeter(ed);
	cout<<"Perimeter:"<<perimeter<<endl;
        area=r.area(ed);
	cout<<"area is:"<<area<<endl;

	return 0;
}
