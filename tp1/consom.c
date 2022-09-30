#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>



int semcreat(key_t key , int n ){
    int semit = semget(key , n, IPC_CREAT| IPC_EXCL| 0666);
    int id = semget(key, n , 0);
    if(semit>=0){
        
        printf("le semaphore n'existe pas , son ID de est : %d\n",id);
        
    }else printf("le semaphore %d existe deja \n",id);
    return id;  
    
}

int p(int semid ,int numsem){
    struct sembuf op;
    op.sem_flg=0;
    op.sem_num=numsem;
    op.sem_op=-1;

    return semop(semid,&op, 1);
}

int v(int semid ,int numsem){
    struct sembuf op;
    op.sem_flg=0;
    op.sem_num=numsem;
    op.sem_op=+1;

    return semop(semid,&op, 1);
}

typedef struct datatab {
    int tab[10]; // la table de produits 
    int indp,indc;
}datatab ; 

void main(){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'f');
    int id=semcreat(key,4); // pour avoir le id de la semaphore
    int shmid=shmget(key,sizeof(datatab),0);
    int ca,indexx; 
    datatab *sd=NULL;
    sd=shmat(shmid,sd,0);

    while(1){
        // on prend le mutexpour le consemateur
        p(id,3);
        //p (plein)
        p(id,0);
        //consomer 
        //recuperer la case
        indexx=sd->indc;
        printf("consemateur 1:consomer la case %d valeur :  ",indexx);
        
        ca=sd->tab[indexx];
        printf("%d\n",ca);
        sd->indc=(sd->indc+1)%10;
        

        //v(vide)
        v(id,1);
        // on libere le muter pris par ce consemateur 
        // on prend le mutexpour le producteur 
        v(id,3);
        sleep(rand()%5);
    }
}
