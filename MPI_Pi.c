#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    double myPi, pi;
    int rank, numProcess, n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcess);

    while(1){
        if(rank==0){
            printf("Enter a number:");
            scanf("%d",&n);
        }
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if(n==0){
            break;
        } else {
            h=1.0/(double)n;
            sum=0.0;
            for(i=rank+1;i<=n;i+=numProcess){
                x=h*((double)i+0.5);
                sum+=4.0/(1.0+x*x);
            }
            myPi = h*sum;
            MPI_Reduce(&myPi, 
                      &pi, 
                      1, 
                      MPI_DOUBLE, 
                      MPI_SUM, 
                      0, 
                      MPI_COMM_WORLD);
            if(rank==0){
                printf("The value of pi is %lf\n",pi);
            }
        }
    }
    MPI_Finalize();
    return 0;

}