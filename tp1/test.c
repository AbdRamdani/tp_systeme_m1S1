#include <sys/sem.h>
#include <stdio.h>

int semcreat(key_t key , int n ){
     int semit = semget(key , n, IPC_CREAT| IPC_EXCL| 0666);
     
    if(semit>=0){
        
        printf("le semaphore n'existe pas , son ID de est : %d\n",semit);
        return semit;
        
    }else {
        int id = semget(key, n , 0);
        printf("le semaphore %d existe deja \n",id);
        return id;
    } 
}

void main(){

    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'t');
    int z=semcreat(key,4);
    printf("la valeur de retour est %d\n",z);
}   