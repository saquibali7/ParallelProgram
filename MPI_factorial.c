#include <stdio.h>
#include "mpi.h"


int main(int argc, char *argv[]){
    int rank, numProcess, n, lower, upper;
    double local_result, result;

    MPI_INIT(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        printf("Enter a number:");
        scanf("%d",&n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    lower = rank * (n / numProcess) + 1;
    upper = (rank + 1) * (n / numProcess);

    local_result = 1.0;

    for(i=lower;i<=upper;i++){
        local_result = local_result * (double)i;
    }

    
    MPI_Reduce(&local_result, &total, 1, MPI_DOUBLE, MPI_PROD, 0MPI_COMM_WORLD); 

    if(rank==0){
        printf("The factorial of %d is %lf, and was calculated using %d processes\n",fact,total,size);
    }

    MPI_Finalize();

    return 0;
}





