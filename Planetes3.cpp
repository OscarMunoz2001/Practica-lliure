#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define M 9 //El nombre de cossos que simularem sera 9, des del Sol fins a Neptú

int main(){

int i, j, k, l, N;
double dt, T_nep;

//Aquí fiquem totes les constants que necessitem per al problema

dt=0.00056; //el pas de temps més petit que podem agafar sense que el metode divergeixi, equival a 33,71 dies terrestres
T_nep=1; // periode orbital de Neptú normalitzat
N = T_nep/dt;

//printf("%d", N);

double x[N][M], y[N][M], v_x[N][M], v_y[N][M], x_2[N][M], x_3[N][M], x_4[N][M], y_2[N][M], y_3[N][M], y_4[N][M], l1_xa;
double v_x_2[N][M], v_x_3[N][M], v_x_4[N][M], v_y_2[N][M], v_y_3[N][M], v_y_4[N][M];
double k1_x[M], k2_x[M], k3_x[M], k4_x[M], k1_y[M], k2_y[M], k3_y[M], k4_y[M];
double l1_x, l2_x, l3_x, l4_x, l1_y, l2_y, l3_y, l4_y;
double l1_x_old[M], l2_x_old[M], l3_x_old[M], l4_x_old[M], l1_y_old[M], l2_y_old[M], l3_y_old[M], l4_y_old[M];

double a[M] = {0.0, 0.012867, 0.024, 0.03311, 0.05067, 0.17289, 0.3178, 0.6378, 1};
double b[M] = {0.0, 0.05652977778, 0.04046755556, 0.03441244444, 0.02781422222, 0.01508, 0.01113955556, 0.00786933333, 0.00627466666};

double m[M]={39.21390206, 0.00000649604, 0.00009565815, 0.0001184339, 0.0000126752, 0.03762950198, 0.01184339062, 0.00171709359, 0.0020795251};

for(j=0; j<M; j++){
	y[0][j]=0;
	x[0][j]=a[j];
	v_y[0][j]=b[j];
	v_x[0][j]=0;
}

for(i=0; i<N; i++){
	for(j=0; j<M; j++){
		k1_x[j]=v_x[i][j];
		k1_y[j]=v_y[i][j];
		
		for(k=0; k<M; k++){
			if(k!=j){
				l1_x_old[k]=(m[k]*(x[i][k]-x[i][j]))/(pow((pow(x[i][j]-x[i][k], 2)+ pow(y[i][j]-y[i][k], 2)), 1.5));
				l1_y_old[k]=(m[k]*(y[i][k]+y[i][j]))/(pow((pow(x[i][j]-x[i][k], 2)+ pow(y[i][j]-y[i][k], 2)), 1.5));
				}
			else{
				l1_x_old[k]=0;
				l1_y_old[k]=0;
			}
			l1_x+=l1_x_old[k];
			l1_y+=l1_y_old[k];
		}
		
		k2_x[j]=v_x[i][j]+0.5*dt*l1_x;
		k2_y[j]=v_y[i][j]+0.5*dt*l1_y;

		
		for(k=0; k<M; k++){
			if(k!=j){
				l2_x_old[k]=(m[k]*(x[i][k]+0.5*dt*k1_x[k]-(x[i][j]+0.5*dt*k1_x[j])))/(pow((pow(x[i][j]+0.5*dt*k1_x[j]-(x[i][k]+0.5*dt*k1_x[k]), 2)+ pow(y[i][j]+0.5*dt*k1_y[j]-(y[i][k]+0.5*dt*k1_y[k]), 2)), 1.5));
				l2_y_old[k]=(m[k]*(y[i][k]+0.5*dt*k1_y[k]-(y[i][j]+0.5*dt*k1_y[j])))/(pow((pow(x[i][j]+0.5*dt*k1_x[j]-(x[i][k]+0.5*dt*k1_x[k]), 2)+ pow(y[i][j]+0.5*dt*k1_y[j]-(y[i][k]+0.5*dt*k1_y[k]), 2)), 1.5));
			}
			else{
				l2_x_old[k]=0;
				l2_y_old[k]=0;
			}
			l2_x+=l2_x_old[k];
			l2_y+=l2_y_old[k];
		}
		
		
		k3_x[j]=v_x[i][j]+0.5*dt*l2_x;
		k3_y[j]=v_y[i][j]+0.5*dt*l2_y;

		
		for(k=0; k<M; k++){
			if(k!=j){
				l3_x_old[k]=(m[k]*(x[i][k]+0.5*dt*k2_x[k]-(x[i][j]+0.5*dt*k2_x[j])))/(pow((pow(x[i][j]+0.5*dt*k2_x[j]-(x[i][k]+0.5*dt*k2_x[k]), 2)+ pow(y[i][j]+0.5*dt*k2_y[j]-(y[i][k]+0.5*dt*k2_y[k]), 2)), 1.5));
				l3_y_old[k]=(m[k]*(y[i][k]+0.5*dt*k2_y[k]-(y[i][j]+0.5*dt*k2_y[j])))/(pow((pow(x[i][j]+0.5*dt*k2_x[j]-(x[i][k]+0.5*dt*k2_x[k]), 2)+ pow(y[i][j]+0.5*dt*k2_y[j]-(y[i][k]+0.5*dt*k2_y[k]), 2)), 1.5));
			}
			else{
				l3_x+=l3_x_old[k];
				l3_y+=l3_y_old[k];
			}
		}
		
		k4_x[j]=v_x[i][j]+dt*l3_x;
		k4_y[j]=v_y[i][j]+dt*l3_y;

		
		for(k=0; k<M; k++){
			if(k!=j){
				l4_x_old[k]=(m[k]*(x[i][k]+0.5*dt*k3_x[k]-(x[i][j]+0.5*dt*k3_x[j])))/(pow((pow(x[i][j]+0.5*dt*k3_x[j]-(x[i][k]+0.5*dt*k3_x[l]), 2)+ pow(y[i][j]+0.5*dt*k3_y[j]-(y[i][k]+0.5*dt*k3_y[k]), 2)), 1.5));
				l4_y_old[k]=(m[k]*(y[i][k]+0.5*dt*k3_y[k]-(y[i][j]+0.5*dt*k3_y[j])))/(pow((pow(x[i][j]+0.5*dt*k3_x[j]-(x[i][k]+0.5*dt*k3_x[l]), 2)+ pow(y[i][j]+0.5*dt*k3_y[j]-(y[i][k]+0.5*dt*k3_y[k]), 2)), 1.5));
			}
			else{
				l4_x+=l4_x_old[k];
				l4_y+=l4_y_old[k];
			}
		}
		
		x[i+1][j]=x[i][j]+(dt/6)*(k1_x[j]+2*k2_x[j]+2*k3_x[j]+k4_x[j]);
		y[i+1][j]=y[i][j]+(dt/6)*(k1_y[j]+2*k2_y[j]+2*k3_y[j]+k4_y[j]);
		v_x[i+1][j]=v_x[i][j]+(dt/6)*(l1_x+2*l2_x+2*l3_x+l4_x);
		v_y[i+1][j]=v_y[i][j]+(dt/6)*(l1_y+2*l2_y+2*l3_y+l4_y);
		
		l1_x=l2_x=l3_x=l4_x=l1_y=l2_y=l3_y=l4_y=0;
		
	}
printf("%lf \t %lf \t %lf \t %lf \t %d\n", x[i][0], y[i][0], v_x[i][0], v_y[i][0], i);	
}
return 0;
	}
//printf("\n");




