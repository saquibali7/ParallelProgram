#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, numProcess, n, lower, upper, max, local_max,local_size;
    int *nums;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcess);

    if(rank==0){
        printf("Enter a number:");
        scanf("%d",&n);

        nums = (int *)malloc(n*sizeof(int));

        for(int i=0;i<n;i++){
            nums[i] = i+1;
        }
    }

    local_size = n/numProcess;
    int* dataRecv1=(int*)malloc(sizeof(int)*local_size);

    MPI_Scatter(nums, 
               local_size, 
               MPI_INT, 
               dataRecv1, 
               local_size, 
               MPI_INT, 
               0, 
               MPI_COMM_WORLD);
    for(int i=0;i<local_size;i++){
        if(dataRecv1[i]>local_max){
            local_max = dataRecv1[i];
        }
    }

    MPI_Reduce(&local_max, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); 
    if(rank==0){
        printf("The max element of %d is %d, and was calculated using %d processes\n",n,max,numProcess);
    }

    MPI_Finalize();
    return 0;
}