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
                       float area;
		       float perimeter;
		
	public:
		//struct cel *c;
                friend class vertice;
		void getint(int a, int p){
			area=a;
			perimeter=p;
		}
		void printint(){
			cout<<"area:"<<this->area<<endl<<"perimeter:"<<this->perimeter<<endl;
		}
		int energyc(int a0){
			int beta=1;
			int ai;

			ai=this->area;
			ai=(ai-a0)*beta;
			return ai;
		}
};



int  vertices::shoelace(struct vertice v1,struct vertice  v2,struct vertice v3,struct vertice v4){
	int i,s,s1=0,s2=0,sum=0;
	struct vertice temp[4]={v1,v2,v3,v4};
	for(i=0;i<3;i++){
		s1=((temp[i].x)*(temp[i+1].y));
		s2=((temp[i+1].x)*(temp[i].y));
		s=s1-s2;
		sum=sum+s;
	}
	s1=temp[3].x*temp[0].y;
	s2=temp[3].y*temp[0].x;
	sum=sum+s1-s2;
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
	vector<vertices::vertice> va;
	vector<vertices::vertice> vb;
        int i,n,x,y,a,p,l,x1,y1;
	n=4;
	vertices ver;
	cell c1,c2,c3;
	cell cells[3]={c1,c2,c3};
	
	//input
	for(i=0;i<n;i++){
             cout<<"Enter the apical and basal vertices:"<<endl;
	     cin>>x>>y>>x1>>y1;
	     struct vertices::vertice v1;
	     v1.x=x;
	     v1.y=y;
	     va.push_back(v1);
	     v1.x=x1;
	     v1.y=y1;
	     vb.push_back(v1);
           }

	//printing
       for(i=0;i<n;i++){
	       cout<<"The apical and basal vertices are:"<<endl;
	       cout<<"x:"<<va[i].x<<endl<<"y:"<<va[i].y<<endl<<"x1:"<<vb[i].x<<endl<<"y1:"<<vb[i].y<<endl;
	   
       }

       //area
       l=n-1;
       for(i=0;i<l;i++){
           a=ver.shoelace(va[i],va[i+1],vb[i+1],vb[i]);
           p=ver.perimeter(va[i],va[i+1],vb[i+1],vb[i]);
	   cells[i].getint(a,p);

       }

       for(i=0;i<l;i++){
	      cells[i].printint();
       }


      //energy calculations
      int al=0,bl=0,ll=0,ea=0,eb=0,el=0;
      int d;
      int a_alpha=1;
      int b_alpha=1;
      int l_alpha=1;

      for(i=0;i<n-1;i++){
	      d=ver.distance(va[i],va[i+1]);
	      al=al+d;
	      d=a_alpha*d;
	      ea=ea+d;
      }
      cout<<"apical length:"<<al<<endl<<"E_apical length"<<ea<<endl;


      for(i=0;i<n-1;i++){
	      d=ver.distance(vb[i],vb[i+1]);
	      bl=bl+d;
	      d=b_alpha*d;
	      eb=eb+d;
      }
     cout<<"basal lenth:"<<bl<<endl<<"E_basal lenth"<<eb<<endl;

     for(i=0;i<n;i++){
	     d=ver.distance(va[i],vb[i]);
	     ll=ll+d;
	     d=l_alpha*d;
	     el=el+d;
     }
     cout<<"lateral edge:"<<ll<<endl<<"lateral energy:"<<el<<endl;


     int a0=(al/l)*(ll/n);
     cout<<"a0:"<<a0<<endl;
     int ec=0;

     for(i=0;i<l;i++){
	     ec=ec+cells[i].energyc(a0);
     }
     cout<<"E_cell area"<<ec<<endl;
     

	return 0;
}



