#include<iostream>
using namespace std;
#include<vector>
#include<math.h>


class System{
	private:
		struct api_v{
			public:
		                float xa;
			        float ya;
			        float Exa;
			        float Eya;
		};
		struct basal_v{
			public:
			        float xb;
			        float yb;
			        float Exb;
			        float Eyb;
		};

		struct vitelline_v{
			public:
				float xv;
				float yv;
		};

		struct cell{
			public:
				float Area;
				float la_edge;
				float lb_edge;
				float ll_edge1;
				float ll_edge2;
				float alpha_m;
				float alpha_a;
				float alpha_b;
				float alpha_l;
		};
		vector<api_v> va;
		vector<basal_v> vb;
		vector<vitelline_v> vv;
		vector<cell> parameter;

	public:
		void create_vertices(float x,float y,int n,float Lx,float H);
		void printlist(int n);
		void update_geometry(int n);
		float apply_PBC(int index,float x,float Lx,int n);
		void update_gradient(int n,float Lx);
		void update_energy(int n);
};

void System::create_vertices(float x,float y,int n,float Lx,float H){
	int i;
	float inc=Lx/(n-1);
	for(i=0;i<n;i++){
		va.push_back({(x+(i*inc)),(y+H),0,0});
		vb.push_back({(x+(i*inc)),y,0,0});
		vv.push_back({(x+(i*inc)),(y+H+1)});
	}

}

void System::printlist(int n){
	int i;
	for(i=0;i<n;i++){
		cout<<"position:"<<i+1<<endl;
		cout<<"xa:"<<va[i].xa<<"and ya:"<<va[i].ya<<endl;
		cout<<"xb:"<<vb[i].xb<<"and yb:"<<vb[i].yb<<endl;
		cout<<"xv:"<<vv[i].xv<<"and yv:"<<vv[i].yv<<endl;
	}
}

void System::update_geometry(int n){
	int i;
	float ll_edge2;
	for(i=0;i<n-1;i++){
		float dx=0;
		float dy=0;
        	int j2=(i+n)%n;//i
	        int j3=(i+1+n)%n;//i+1

	        float Area;
	        Area=0.5*((va[j3].xa*va[j2].ya)+(vb[j3].xb*va[j3].ya)+(vb[j2].xb*vb[j3].yb)+(va[j2].xa*vb[j2].yb)
		           -(va[j2].xa*va[j3].ya)-(va[j3].xa*vb[j3].yb)-(vb[j3].xb*vb[j2].yb)-(vb[j2].xb*va[j2].ya));

		dx=va[j3].xa-va[j2].xa;
		dy=va[j3].ya-va[j2].ya;
		float la_edge=sqrt((dx*dx)+(dy*dy));

		dx=vb[j3].xb-vb[j2].xb;
		dy=vb[j3].yb-vb[j2].yb;
		float lb_edge=sqrt((dx*dx)+(dy*dy));

		dx=va[j2].xa-vb[j2].xb;
		dy=va[j2].ya-vb[j2].yb;
		float ll_edge1=sqrt((dx*dx)+(dy*dy));
		dx=va[j3].xa-vb[j3].xb;
		dy=va[j3].ya-vb[j3].yb;
		ll_edge2=sqrt((dx*dx)+(dy*dy));
		parameter.push_back({Area,la_edge,lb_edge,ll_edge1,ll_edge2,0.00,1.00,1.00,1.00});
	}
	//for the last vertice
	parameter.push_back({3.00,0.00,0.00,ll_edge2,0.00,0.00,1.00,1.00,1.00});

        //printing values to check if they have been calculated and uploaded correctly
	/*for(i=0;i<n-1;i++){
		cout<<"Area:"<<parameter[i].Area<<endl<<"Apical edge:"<<parameter[i].la_edge<<endl<<"Basal edge:"<<parameter[i].lb_edge<<endl;
		cout<<"Lateral edge1:"<<parameter[i].ll_edge1<<"\t"<<"Lateral edge 2:"<<parameter[i].ll_edge2<<endl;
		cout<<"  "<<endl;
	}*/
}


float System::apply_PBC(int index,float x,float Lx,int n){
	if(index==n){
		return x+Lx;
	}
	else if(index== -1){
		return x-Lx;
	}
	else{
		return x;
	}
}

void System::update_energy(int n){
	int i;
	float cellrefarea=3.00;
	float beta_cell=1.00;
	float epsilon=1.00;
	float a_contribution=0,b_contribution=0,l_contribution=0,cell_contribution=0,v_contribution=0;

	for(i=0;i<n;i++){
		a_contribution +=parameter[i].alpha_a*parameter[i].la_edge;
		b_contribution +=parameter[i].alpha_b*parameter[i].la_edge;
                l_contribution +=parameter[i].alpha_l*parameter[i].ll_edge1;
		cell_contribution += beta_cell*((parameter[i].Area-cellrefarea)*(parameter[i].Area-cellrefarea));
		v_contribution +=epsilon*(((vv[i].xv-va[i].xa)*(vv[i].xv-va[i].xa))+((vv[i].yv-va[i].ya)*(vv[i].yv-va[i].ya)));
             }

	cout<<"apical contribution:"<<a_contribution<<endl;
	cout<<"basal_contribution:"<<b_contribution<<endl;
	cout<<"lateral contribution:"<<l_contribution<<endl;
	cout<<"cell contribution:"<<cell_contribution<<endl;
	cout<<"vitelline contribution:"<<v_contribution<<endl;

}
void System::update_gradient(int n,float Lx){
	int i;
	for(i=0;i<n;i++){
		int j1=(i+n)%n;
                int j2=(i-1+n)%n;
		int j3=(i+1+n)%n;
		float cellrefarea=3.00;
		float A2,ya2,ya3,yb2,yb3,xa1,xb1,xa2,xb2,xa3,xb3,la2,lb2,alpha2,ll,alpha1,la1;
                xa1=System::apply_PBC(i,va[j1].xa,Lx,n);
		xa2=System::apply_PBC(i-1,va[j2].xa,Lx,n);
		xa3=System::apply_PBC(i+1,va[j3].xa,Lx,n);
		xb1=System::apply_PBC(i,vb[j1].xb,Lx,n);
                xb2=System::apply_PBC(i-1,vb[j2].xb,Lx,n);
		xb3=System::apply_PBC(i+1,vb[j3].xb,Lx,n);

		float A1=parameter[j1].Area-cellrefarea;
		if(i==0){
			A2=parameter[n-2].Area-cellrefarea;
			ya2=va[n-1].ya;
			yb2=vb[n-1].yb;
			ya3=va[j3].ya;
			yb3=vb[j3].yb;
			la2=parameter[n-2].la_edge;
			lb2=parameter[n-2].lb_edge;
			alpha2=1.00;
		}
		else if(i==n-1){
			A1=parameter[0].Area-cellrefarea;
			ya2=va[j2].ya;
			yb2=vb[j2].yb;
			ya3=va[0].ya;
			yb3=vb[0].yb;
			ll=parameter[n-2].ll_edge2;
			alpha1=1.00;
		}
		else{
		        A2=parameter[j2].Area-cellrefarea;
			ya2=va[j2].ya;
			yb2=vb[j2].yb;
			ya3=va[j3].ya;
			yb3=vb[j3].yb;
			la2=parameter[j2].la_edge;
			lb2=parameter[j2].lb_edge;
			ll=parameter[j1].ll_edge1;
			alpha2=parameter[j2].alpha_a;
			alpha1=parameter[j1].alpha_a;
		}

		float beta_cell=1.00;
		float epsilon=1.00;

		float EG_xa1=(alpha1*((xa1-xa3)/parameter[i].la_edge));
		float EG_xa4=(alpha2*((xa1-xa2)/la2));
	        float EG_xa2=(parameter[j1].alpha_l*((xa1-xb1)/ll));
		float EG_xa3=(beta_cell*((A1*(vb[j1].yb-ya3))+(A2*(ya2-vb[j1].yb))))+epsilon*(va[j1].xa-vv[j1].xv);
		cout<<"Eg_xa:"<<EG_xa1<<"+"<<EG_xa2<<"+"<<EG_xa3<<"+"<<EG_xa4<<endl;
	}
}



int main(){
	int i,n;
	float x,y,Lx,H;

        cout<<"Enter the initial basal vertices"<<endl;
	cin>>x>>y;
	cout<<"Enter Lx,H,n"<<endl;
	cin>>Lx>>H>>n;

	System test1;
	test1.create_vertices(x,y,n,Lx,H);
	test1.printlist(n);
	test1.update_geometry(n);
	test1.update_energy(n);
	test1.update_gradient(n,Lx);
        
       return 0;
  }




