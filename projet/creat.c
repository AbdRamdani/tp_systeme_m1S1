#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

// creation de semaphore 
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

int seminit (int idsem, int numsem, int initval){
    int zz= semctl(idsem, numsem, SETVAL, initval);
    printf("%d\n",zz);
    perror("semctl");
    return zz;
    }
typedef struct datatab {
    int oxygen,hydrogen,nbBarriere;
}datatab ; 

int shmcreat(key_t key , size_t sizeOfData ){
    int shmid = shmget(key,sizeOfData ,IPC_CREAT|IPC_EXCL|0666); // pour creer la memoire partage 
    // verification si elle est bien creer
    if(shmid==-1){
        printf("la memoire partage etait deja creer \n");
        shmid=shmget(key,sizeOfData,0);
        printf("id de la memoire partagé est %d \n",shmid);
        return shmid; 
    }
    // else shmid contient le id de la memore partagé 
    return shmid; 
}



void main(){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/projet",'f');
    //creation de semaphore
    int id=semcreat(key,4);
    //mutex , oxyQueue , hydroQueue 
    int initSemMutex=seminit(id,0,1); //mutex
    int initSemOQ=seminit(id,1,0); //semaphore oxygene
    int initSemHQ=seminit(id,2,0); //semaphore hydrogene 
    int initSemBr=seminit(id,3,0); //semaphore nb_barriere

    //creation de la memoire partagé
    int shmid = shmcreat(key,sizeof(datatab));
    //initialisation des variable
    datatab *sd=NULL;
    sd=shmat(shmid,sd,0);
    sd->oxygen=0;
    sd->hydrogen=0;
    sd->nbBarriere=0;
    printf("%d %d **",sd->oxygen,sd->nbBarriere);   
    
}