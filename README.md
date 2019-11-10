# (Openmp) Found minimum element in vector with lock

## pthreadmin.c:<br/>
With OpenMP directives, found the min of vector with size N in parallel. The search will split in nt threads. <br/>
Each thread will search in N/nt elements of vector. <br/>
If u not comment the directive "#pragma omp parallel for" inside each thread, OpenMP will create more threads for each thread, to run all iterations.<br/>

## To compile the code:
gcc -o ompmin -fopenmp ompmin.c<br/>

## Details:
Inside the code, edit the numbers of defines at the beginning of the file, with numbers whatever you want.<br/>

### example:<br/>
```
#define nt 4    //is the number of threads is created in execution.
#define nt 1000 //is the number of elements(N) of vector
#define seed 100 //is the  seed of rand(), or seed ==100 ->  numbers between 0 - 100 in vector
```

### Performance:<br/>
For better load balancing, the numbers of threads (nt) selected in define must be higher or equal than number of processors:<br/> nt>= number of processors.<br/>
This improve lowest idleness of processors<br/>
