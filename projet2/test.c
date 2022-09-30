#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

typedef struct datatab {
    int oxygen,hydrogen;
}datatab ; 

int shmcreat(key_t key , size_t sizeOfData ){
    int shmid = shmget(key,sizeOfData ,IPC_CREAT|IPC_EXCL|0666); // pour creer la memoire partage 
    // verification si elle est bien creer
    if(shmid==-1){
        printf("la memoire partage etait deja creer \n");
        shmid=shmget(key,sizeof(datatab),0);
        printf("id de la memoire partagé est %d \n",shmid);
        return shmid; 

    }
    // else shmid contient le id de la memore partagé 
    return shmid; 
}


void main(){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'f');
    int a = shmcreat(key,sizeof(datatab));
    printf("** %d\n",a);
}