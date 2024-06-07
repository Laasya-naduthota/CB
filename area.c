#include<iostream>
#include<math.h>
using namespace std;
#include<vector>

class vertices{
	public:
		struct vertice{
			int x;
			int y;
		};
	public:
		friend class cell;
	        int shoelace(vertice,vertice,vertice,vertice);
		int perimeter(vertice,vertice,vertice,vertice);
		int distance(vertice,vertice);
};

class cell{
	private:
		struct cel{
                       float area;
		       float perimeter;
		};
	public:
		struct cel *c;
                friend class vertice;
};



int  vertices::shoelace(struct vertice v1,struct vertice  v2,struct vertice v3,struct vertice v4){
	int i,s1=0,s2=0,sum=0;
	struct vertice temp[4]={v1,v2,v3,v4};
	for(i=0;i<3;i++){
		s1=s1+((temp[i].x)*(temp[i+1].y));
		s2=s2+((temp[i+1].x)*(temp[i].y));
	}
	sum=sum+s1+s2;
	s1=temp[3].x*temp[0].y;
	s2=temp[3].y*temp[0].x;
	sum=sum+s1+s2;
	sum=0.5*sum;
	
	return sum;
}

int vertices::perimeter(struct vertice  v1,struct vertice v2,struct vertice v3,struct vertice v4){
	int sum=0;
	sum=sum+distance(v1,v2);
	sum=sum+distance(v2,v3);
	sum=sum+distance(v3,v4);
	sum=sum+distance(v4,v1);

	return sum;
}

int vertices::distance(struct vertice v1, struct vertice v2){
	int x,y,d;
	x=(v1.x-v2.x)*(v1.x-v2.x);
	y=(v2.y-v1.y)*(v2.y-v1.y);
        d=sqrt(x+y);

	return d;
}

int main(){
	vector<vertices::vertice> v;
        int i,n,x,y,area,p,l;
	n=6;
	vertices ver;
	cell c1,c2,c3;
	cell cells[3]={c1,c2,c3};
	
	//input
	for(i=0;i<n;i++){
             cout<<"Enter the vertices:"<<endl;
	     cin>>x>>y;
	     struct vertices::vertice v1;
	     v1.x=x;
	     v1.y=y;
	     v.push_back(v1);
           }

	//printing
       for(i=0;i<n;i++){
	       cout<<"The vertices are:"<<endl;
	       cout<<"x:"<<v[i].x<<endl<<"y:"<<v[i].y<<endl;
       }

       //area
       l=(n/2)-1;
       for(i=0;i<l;i++){
           area=ver.shoelace(v[2*i],v[(2*i)+1],v[(2*i)+2],v[(2*i)+3]);
	   cells[i].c->area=area;
	   p=ver.perimeter(v[2*i],v[(2*i)+1],v[(2*i)+2],v[(2*i)+3]);
	   cells[i].c->perimeter=p;
       }

       for(i=0;i<l;i++){
	       cout<<"area:"<<cells[i].c->area<<endl<<"p:"<<cells[i].c->perimeter<<endl;
       }


  

	return 0;
}



