/*
    Developed by João Zanetti
    https://github.com/joao-zanetti
*/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define nt 5
#define N 10000
#define seed 10000

int main(int argc,char **argv){
    double wtime;
    int range,i,minlocal,v[N],min,my_id,start,end;

    //generate the numbers of vector with 
	for (i = 0; i < N; i++) {
        v[i] = rand()%seed;
        //printf("%d ",v[i]);
	}

    //initialize global min
    min=v[0];

    //lock for min access
    omp_lock_t mylock;
	omp_init_lock(&mylock);

    //range of iterations of each thread
    range=N/nt;

    wtime = omp_get_wtime();
    #pragma omp parallel private(i,minlocal,end,start,my_id) shared(min) num_threads(nt) 
    {
        my_id = omp_get_thread_num();
        
        start=my_id*range;
        //if is the last thread sum N%nt
        //because if N%nt!=0  -> the last thread must sum N%nt
        if (my_id==nt-1){
            range+=N%nt;
        }
        end=start+range;
        minlocal=v[start];
        
        //you can comment this directive of omp parallel for 
        //the openmp create more threads to iteractions of this for
        #pragma omp parallel for 
            for(i=start; i<end; i++)
            {
                if(v[i]<minlocal){
                    minlocal=v[i];
                }
            }
        printf("T%d:FINISHED minlocal:%d\n",my_id,minlocal);

        //just one thread can access min at the same time
        //against overwriting
        omp_set_lock(&mylock);
		if (minlocal<min)
			min= minlocal;
		omp_unset_lock(&mylock);
    }

    wtime = omp_get_wtime()-wtime;
    printf("time: %lf\nmin:%d \n",wtime,min);
    return 0;
}
