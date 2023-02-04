#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define M 9 //El nombre de cossos que simularem sera 9, des del Sol fins a Neptú

int main(){

int i, j, k;
double dt, T_nep;

double x[N][M], y[N][M], v_x[N][M], v_y[N][M], m[M], x_2[N][M], x_3[N][M], x_4[N][M], y_2[N][M], y_3[N][M], y_4[N][M];
double v_x_2[N][M], v_x_3[N][M], v_x_4[N][M], v_y_2[N][M], v_y_3[N][M], v_y_4[N][M];
double k1_x[M], k2_x[M], k3_x[M], k4_x[M], k1_y[M], k2_y[M], k3_y[M], k4_y[M];
double l1_x[M], l2_x[M], l3_x[M], l4_x[M], l1_y[M], l2_y[M], l3_y[M], l4_y[M];
double l1_x_old[M], l2_x_old[M], l3_x_old[M], l4_x_old[M], l1_y_old[M], l2_y_old[M], l3_y_old[M], l4_y_old[M];
double l1_x_new[M], l2_x_new[M], l3_x_new[M], l4_x_new[M], l1_y_new[M], l2_y_new[M], l3_y_new[M], l4_y_new[M];


//Aquí fiquem totes les constants que necessitem per al problema

dt=0.0000166 //el pas de temps corresponent a un dia terrestre
T_nep=1 // periode orbital de Neptú normalitzat
x[0][M]={} //posició inicial en l'eix x
y[0][M]={} //posició inicial en l'eix y, suposarem que el sol esta centrat en (0,0) i la resta de planetes estan alineats verticalment
v_x[0][M]={} //velocitat inicial en l'eix x
v_y[0][M]={} //velocitat inicial en l'eix y

/*Definirem la funció de l'acceleració, ja que es una funció que invoca molts paràmetres i executar-la en cada procés del RK-4 pot ser molt
costós tant per a l'ordinador com per a nosaltres */

double a()


//Codi per a RK4

for(i=0; i<T_nep; i++){
	for (j=0; j<9; j++){
		k1_x[j]=v_x[i][j];
		k1_y[j]=v_y[i][j];
		
		for (k=0; k<9; k++){
			if (k==j){
			}
			else{
				l1_x_old[k]=(m[k]*fabs(x[i][j]-x[i][k]))/(pow((pow(x[i][j]-x[i][k], 2)+ pow(y[i][j]-y[i][k], 2)), 1.5));
				l1_y_old[k]=(m[k]*fabs(y[i][j]-y[i][k]))/(pow((pow(x[i][j]-x[i][k], 2)+ pow(y[i][j]-y[i][k], 2)), 1.5));
				
				if (k==0){
					l1_x[k]=l1_x_old[k];
					l1_y[k]=l1_x_old[k];
				}
				else{
					l1_x[k]=l1_x[k-1] + l1_x_old[k];
					l1_y[k]=l1_y[k-1] + l1_x_old[k];
				}
				
			}
		}
		
		x_2[i][j]=x[i][j] + 0.5*dt*k1_x[j];
		y_2[i][j]=x[i][j] + 0.5*dt*k1_x[j];
		
		v_x_2[i][j]=v_x[i][j] + 0.5*dt*l1_x[j];
		v_y_2[i][j]=v_x[i][j] + 0.5*dt*l1_x[j];
		
		k2_x[j]=v_x_2[i][j];
		k2_y[j]=v_y_2[i][j];
		
		for (k=0; k<9; k++){
			if (k==j){
			}
			else{
				l2_x_old[k]=(m[k]*fabs(x_2[i][j]-x_2[i][k]))/(pow((pow(x_2[i][j]-x_2[i][k], 2)+ pow(y_2[i][j]-y_2[i][k], 2)), 1.5));
				l2_y_old[k]=(m[k]*fabs(y_2[i][j]-y_2[i][k]))/(pow((pow(x_2[i][j]-x_2[i][k], 2)+ pow(y_2[i][j]-y_2[i][k], 2)), 1.5));
				
				if (k==0){
					l2_x[k]=l2_x_old[k];
					l2_y[k]=l2_x_old[k];
				}
				else{
					l2_x[k]=l2_x[k-1] + l2_x_old[k];
					l2_y[k]=l2_y[k-1] + l2_x_old[k];
				}
				
			}
		}
		
		x_3[i][j]=x[i][j] + 0.5*dt*k2_x[j];
		y_3[i][j]=x[i][j] + 0.5*dt*k2_x[j];
		
		v_x_3[i][j]=v_x[i][j] + 0.5*dt*l2_x[j];
		v_y_3[i][j]=v_x[i][j] + 0.5*dt*l2_x[j];
		
		k3_x[j]=v_x_3[i][j];
		k3_y[j]=v_y_3[i][j];
		
		for (k=0; k<9; k++){
			if (k==j){
			}
			else{
				l3_x_old[k]=(m[k]*fabs(x_3[i][j]-x_3[i][k]))/(pow((pow(x_3[i][j]-x_3[i][k], 2)+ pow(y_3[i][j]-y_3[i][k], 2)), 1.5));
				l3_y_old[k]=(m[k]*fabs(y_3[i][j]-y_3[i][k]))/(pow((pow(x_3[i][j]-x_3[i][k], 2)+ pow(y_3[i][j]-y_3[i][k], 2)), 1.5));
				
				if (k==0){
					l3_x[k]=l3_x_old[k];
					l3_y[k]=l3_x_old[k];
				}
				else{
					l3_x[k]=l3_x[k-1] + l3_x_old[k];
					l3_y[k]=l3_y[k-1] + l3_x_old[k];
				}
				
			}
		}
		
		x_4[i][j]=x[i][j] + dt*k3_x[j];
		y_4[i][j]=x[i][j] + dt*k3_x[j];
		
		v_x_4[i][j]=v_x[i][j] + dt*l3_x[j];
		v_y_4[i][j]=v_x[i][j] + dt*l3_x[j];
		
		k4_x[j]=v_x_4[i][j];
		k4_y[j]=v_y_4[i][j];
		
		for (k=0; k<9; k++){
			if (k==j){
			}
			else{
				l4_x_old[k]=(m[k]*fabs(x_4[i][j]-x_4[i][k]))/(pow((pow(x_4[i][j]-x_4[i][k], 2)+ pow(y_4[i][j]-y_4[i][k], 2)), 1.5));
				l4_y_old[k]=(m[k]*fabs(y_4[i][j]-y_4[i][k]))/(pow((pow(x_4[i][j]-x_4[i][k], 2)+ pow(y_4[i][j]-y_4[i][k], 2)), 1.5));
				
				if (k==0){
					l4_x[k]=l4_x_old[k];
					l4_y[k]=l4_x_old[k];
				}
				else{
					l4_x[k]=l4_x[k-1] + l4_x_old[k];
					l4_y[k]=l4_y[k-1] + l4_x_old[k];
				}
				
			}
		}
		
	x[i+1][j]=x[i][j]+(dt/6)*(k1_x[j]+2*k2_x[j]+2*k3_x[j]+k4_x[j]);
	y[i+1][j]=y[i][j]+(dt/6)*(k1_y[j]+2*k2_y[j]+2*k3_y[j]+k4_y[j]);
	v_x[i+1][j]=v_x[i][j]+(dt/6)*(l1_x[j]+2*l2_x[j]+2*l3_x[j]+l4_x[j]);
	v_y[i+1][j]=v_y[i][j]+(dt/6)*(l1_[j]+2*l2[j]+2*l3_y[j]+l4_y[j]);	
		
	}
	
}

}
