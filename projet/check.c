#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

typedef struct datatab {
    int oxygen,hydrogen,nbBarriere;
}datatab ; 

void main(){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/projet",'f');
    // on recupere le id de la memoire partage et le groupe de semaphore
    int shmid=shmget(key,sizeof(datatab),0);
    datatab *sd=NULL;
    sd=shmat(shmid,sd,0);
    printf("oxygen %d , hydrogen %d , nbBarriere%d\n",sd->oxygen,sd->hydrogen,sd->nbBarriere);
}