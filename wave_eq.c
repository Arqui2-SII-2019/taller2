#include<stdio.h>
#include<math.h>
#include<omp.h>

#define X 1000
#define T 1000

double fun(int x){
    return x*x*(5-x);
}

int main(){
	double start_time, run_time;
    double u[X+1][T+1],square_of_c, ut, ue;
    int i,j,average=1000;
	square_of_c=16;//setting a value to c^2
	ut=0;//setting a value to ut
	ue=0;//setting a value to ue
	for(int tt=0;tt<average;tt++){	
		#pragma omp parallel
		{
			start_time = omp_get_wtime();
			#pragma omp for
			for(j=0;j<=T;j++){
				u[0][j]=ut;
				u[X][j]=ue;
			}
			
			#pragma omp for
			for(i=1;i<=X-1;i++){
				double tt=i*i*(5-i);
				u[i][1]=tt;
				u[i][0]=tt;
			}
			
			#pragma omp for private(i)
			for(j=1;j<=T-1;j++){
				for(i=1;i<=X-1;i++){
					u[i][j+1]=u[i-1][j]+u[i+1][j]-u[i][j-1];
				}
			}
		}
		run_time +=( omp_get_wtime() - start_time);
	}
	run_time = run_time/average;
	printf("\n %f seconds \n", run_time);
	/**
    printf(" The values of u[i][j] are: \n");
    for(j=0;j<=T;j++)
    {
        for(i=0;i<=X;i++)
        printf("%6.1f",u[i][j]);
        printf("\n");

    }*/
	return 0;
}
