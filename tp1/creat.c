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
    int tab[10]; // la table de produits 
    int indp,indc;
}datatab ; 

void main(){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'f');
    int shmid = shmget(key,sizeof(datatab),IPC_CREAT|IPC_EXCL|0666); // pour creer la memoire partage 
    // verification si elle est bien creer
    if(shmid==-1){
        printf("la memoire partage etait deja creer \n");
        shmid=shmget(key,sizeof(datatab),0);
        printf("id de la memoire partagé est %d \n",shmid);

    }// else shmid contient le id de la memore partagé 
    //initialitation des valeur indl et indc a 0
    datatab *sd=NULL;
    sd=shmat(shmid,sd,0);
    sd->indp=0;
    sd->indc=0;
    // creation de semaphore
    int id=semcreat(key,4);
    printf("initialisation de semaphore %d\n",id);
    //initialisation des valeurs de semaphoere
    int initsemvide=seminit(id,0,0);
    int initsemplein=seminit(id,1,10);
    int initsemprod=seminit(id,2,1); // pour producteur 
    int initsemcons=seminit(id,3,1); // pour consemateur 

}