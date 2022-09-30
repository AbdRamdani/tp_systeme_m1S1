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
    int id=semcreat(key,4); /// pour avoid le pid de la semaphore
    int shmid=shmget(key,sizeof(datatab),0);
    int prd,indexx;
    datatab *sd=NULL;
    sd=shmat(shmid,sd,0);


    while(1){
        // on prend le mutexpour le producteur 
        p(id,2);
        //p (vide)
        p(id,1);
        //produire  
        //recuperer la case
        indexx=sd->indp;
        prd=rand()%50+indexx;
        printf("producteur 1:produire de la case numero %d valeur %d\n",indexx,prd);
        sd->tab[indexx]=prd;
        sd->indp=(sd->indp+1)%10;
        //v(plein)
        v(id,0);
        //on libere le mutex pris par ce producteur 
        v(id,2);
        sleep(rand()%5);
        
    }
}