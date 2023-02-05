#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 9  

double a(double x_j, double x_k, double y_j, double y_k, double m){
	return  (m*(x_k-x_j))/(pow(pow(x_k-x_j,2)+pow(y_k-y_j,2),1.5));
}

int main(){
	
double k1_x[M], k2_x[M], k3_x[M], k4_x[M], l1_x[M], l2_x[M], l3_x[M], l4_x[M], k1_y[M], k2_y[M], k3_y[M], k4_y[M], l1_y[M], l2_y[M], l3_y[M], l4_y[M];
double x_1[M], y_1[M], v_x_1[M], v_y_1[M], x_2[M], y_2[M], v_x_2[M], v_y_2[M],x_3[M], y_3[M], v_x_3[M], v_y_3[M]; 
double m[M]={39.21390206, 0.00000649604, 0.00009565815, 0.0001184339, 0.0000126752, 0.03762950198, 0.01184339062, 0.00171709359, 0.0020795251};
double T[M]={0.0,0.001461538, 0.0037307692, 0.006076923, 0.0114230769, 0.071923076, 0.178846153, 0.51153846, 1.0};
double x[M]={0.0, 0.012867, 0.024, 0.03311, 0.05067, 0.17289, 0.3178, 0.6378, 1};
double y[M]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double v_x[M]={0.0, 0.05652977778, 0.04046755556, 0.03441244444, 0.02781422222, 0.01508, 0.01113955556, 0.00786933333, 0.00627466666};
double v_y[M]={0.0,2*M_PI*x[1]/T[1],2*M_PI*x[2]/T[2],2*M_PI*x[3]/T[3],2*M_PI*x[4]/T[4],2*M_PI*x[5]/T[5],2*M_PI*x[6]/T[6],2*M_PI*x[7]/T[7],2*M_PI*x[8]};

int i, j, k, N;
double T_nep, dt, a_x, a_y;

dt=0.000016615384; //el pas de temps més petit que podem agafar sense que el metode divergeixi, equival a 1 dia terrestre
T_nep=1; // periode orbital de Neptú normalitzat
N = T_nep/dt;


for(i=1; i<N; i++){
    for(j=0; j<M; j++){
    	
		k1_x[j]=v_x[j];
        k1_y[j]=v_y[j];
		a_x=0;
        a_y=0;
		
		for(k=0; k<M; k++){
            if(k==j){
            }
            else{
                a_x+=a(x[j],x[k],y[j],y[k],m[k]);
				a_y+=a(y[j],y[k],x[j],x[k],m[k]);
            }
        }		

       	l1_x[j]=a_x;
       	l1_y[j]=a_y;
		x_1[j]=x[j]+0.5*dt*k1_x[j];
        y_1[j]=y[j]+0.5*dt*k1_y[j];
		v_x_1[j]=v_x[j]+0.5*dt*l1_x[j];
		v_y_1[j]=v_y[j]+0.5*dt*l1_y[j];
		
    }
    
    for(j=0; j<M; j++){

        k2_x[j]= v_x_1[j];
        k2_y[j] = v_y_1[j];
        a_x=0;
        a_y=0;

        for(k=0; k<M; k++){
            if(k==j){
            }
            else{
            	a_x+=a(x_1[j],x_1[k],y_1[j],y_1[k],m[k]);
				a_y+=a(y_1[j],y_1[k],x_1[j],x_1[k],m[k]);
            }
        }

        l2_x[j]=a_x;
        l2_y[j]=a_y;
		x_2[j]=x[j]+0.5*dt*k2_x[j];
        y_2[j]=y[j]+0.5*dt*k2_y[j];
        v_x_2[j]=v_x[j]+0.5*dt*l2_x[j];
       	v_y_2[j]=v_y[j]+0.5*dt*l2_y[j];
    }
    
	for(j=0; j<M; j++){

        k3_x[j]=v_x_2[j];
        k3_y[j]=v_y_2[j];
        a_x=0;
        a_y=0;

        for(k=0; k<M; k++){
            if(k==j){
        	}
            else{
                a_x+=a(x_2[j],x_2[k],y_2[j],y_2[k],m[k]);
				a_y+=a(y_2[j],y_2[k],x_2[j],x_2[k],m[k]);
        	}
        }

        l3_x[j]=a_x;
        l3_y[j]=a_y;
        x_3[j]=x[j]+dt*k3_x[j];
        y_3[j]=y[j]+dt*k3_y[j];
        v_x_3[j]=v_x[j]+dt*l3_x[j];
        v_y_3[j]=v_y[j]+dt*l3_y[j];
    }
    
    for(j=0; j<M; j++){

        k4_x[j]=v_x_3[j];
        k4_y[j]=v_y_3[j];
        a_x=0;
        a_y=0;

        for(k=0; k<M; k++){
            if(k==j){
            }
            else{
                a_x+=a(x_3[j],x_3[k],y_3[j],y_3[k],m[k]);
				a_y+=a(y_3[j],y_3[k],x_3[j],x_3[k],m[k]);
            }
    }

    l4_x[j]=a_x;
    l4_y[j]=a_y;
    x[j]+=(dt/6)*(k1_x[j]+2.0*k2_x[j]+2.0*k3_x[j]+k4_x[j]);
    y[j]+=(dt/6)*(k1_y[j]+2.0*k2_y[j]+2.0*k3_y[j]+k4_y[j]);
    v_x[j]+=(dt/6)*(l1_x[j]+2.0*l2_x[j]+2.0*l3_x[j]+l4_x[j]);
    v_y[j]+=(dt/6)*(l1_y[j]+2.0*l2_y[j]+2.0*l3_y[j]+l4_y[j]);
    		}
			printf("%lf \t %lf \t %lf \t %lf \n", x[0], y[0], v_x[0], v_y[0]);

	}

	return 0;
	
}
