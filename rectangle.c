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
		edge *ed;

		void getdata();
		void print();
		struct edge*  maxmin();
		int overlap(rectangle,int);
		int perimeter(struct edge*);
		int area(struct edge*);
		//bool operator == (rectangle r2) {
		//	if ( (rec[0].x == r2.rec[0].x ) && (rec[0].y == r2.rec[0].y) ) { return 1;}
		//}
};
void rectangle::getdata(){
	int i;
	//rectangle r;
	for(i=0;i<4;i++){
		cout<<"enter the point:"<<endl;
		cin>>this->rec[i].x>>this->rec[i].y;
	}
}
void rectangle::print (){
	int i;
	//rectangle r;
	cout<<"the coordinates of the rectangle are:"<<endl;
	for(i=0;i<4;i++){
		cout<<"x :"<<this->rec[i].x<<endl<<"y :"<<this->rec[i].y<<endl;
	}
}

rectangle::edge*   rectangle::maxmin(){
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
	ed->length=l;
	ed->breadth=b;
	cout<<"length is:"<<l<<endl<<"breadth is:"<<b<<endl;
	return ed;

}

int rectangle::perimeter(rectangle::edge *ed){
	int l,b,p;
	l=ed->length;
	b=ed->breadth;
	p=(2*l) +(2*b);
	return p;
}

int rectangle::area(rectangle::edge *ed){
	int l,b,a;
	l=ed->length;
	b=ed->breadth;
	a=l*b;
	return a;
}

int rectangle::overlap(rectangle r2,int n){
	int i,j;
	int count=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if((this->rec[i].x==r2.rec[j].x) && (this->rec[i].y==r2.rec[j].y)){
				count=count+1;
			}
		}
	}
	if(count==2){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	int i,j,p,a,s,b;
	int n=3;
	int perimeter=0;
	int area=0;
	int cedge=0;
	rectangle r1,r2,r3;
	rectangle multiple[n] = {r1,r2,r3};
//	multiple={r1,r2,r3};

	//getting and printing data
	
	for(i=0;i<n;i++){
		multiple[i].getdata();
	}
	for(i=0;i<n;i++){
		multiple[i].print();
	}
	//Calculating length and breadth of rectangles
	
	for(i=0;i<n;i++){
		multiple[i].maxmin();

	}

	//Determining overlapping edges
	//
	for(i=0;i<n;i++){
		for(j=i;j<3;j++){
			s=multiple[i].overlap(multiple[j],n);
			cedge=cedge+s;
		}
        }
        cout<<"cedge is:"<<cedge<<endl;	
	//calculating perimeter
	//
	for(i=0;i<n;i++){
		p=multiple[i].perimeter(multiple[i].ed);
		perimeter=perimeter+p;
	}
	b=r1.ed->breadth;
	cout<<"breadth is:"<<b<<endl;
	b=cedge*b;
	cout<<"b:"<<b<<endl;
	perimeter=perimeter-(2*b);
	cout<<"Perimeter:"<<perimeter<<endl;

        //calculating area
	for(i=0;i<n;i++){
		a=multiple[i].area(multiple[i].ed);
		area=area+a;
	}
	cout<<"Area:"<<area<<endl;

	return 0;
}
