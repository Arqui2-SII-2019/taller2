#include <stdio.h>
#include <omp.h>

int main(){
	int j,vect_size=100000,media=1000;
	double start_time, run_time=0,a=2;

	//making the arrays and filling them
	double x[vect_size],y[vect_size],z[vect_size];
	for(int dd=0; dd<vect_size; dd++){
		x[dd]=dd;
		y[dd]=dd+10;
	}
	//loop to get the average time
	for(int tt=0; tt<media;tt++){
		/*start timer */
		start_time = omp_get_wtime();
		#pragma omp parallel
		{
			for (j = 0; j < vect_size; ++j){
				z[j] = a*x[j] + y[j];
			}
		}
		run_time += (omp_get_wtime() - start_time);
	}
	run_time=run_time/media;
	printf("\n z=a*x+y has been calculated in %f seconds \n",run_time);
  
}
