#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>



void bondOxygen(int n ){
    printf("molécule H2O formée avec le processus %d d'oxygen\n",n);
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
    int oxygen,hydrogen,nbBarriere;
}datatab ; 

void barriere (int n,int semid,datatab *sd){
   // arrive d'un nv processus
   sd->nbBarriere=sd->nbBarriere+1;
   if(sd->nbBarriere==3){
       // on libere les 2 bloque par semaphore de barriere
       sd->nbBarriere=0;
       for(int i=0; i<n-1;i++)
           v(semid,3);
   }else //on bloque le processus
       p(semid,3);
}


void main(){
    int n ; 
    printf("donner le nombre de processus d'oxygen \n");
    scanf("%d",&n);
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/projet",'f');
    // on recupere le id de la memoire partage et le groupe de semaphore
    int shmid=shmget(key,sizeof(datatab),0);
    int semid=semget(key,4,0);
    datatab *sd=NULL;
    sd=shmat(shmid,sd,0);
    for(int i =0;i<n ; i++){
        sleep((i+1)%3);
        int pid = fork();
        if(pid == -1)
        {
            perror("fork");
            exit(1);    
        }
        if(pid==0)
        {   
            
            //traitement 
            p(semid,0); // mutex
            sd->oxygen=sd->oxygen+1;
            printf("creation de oxygene pid %d $(O:%d H:%d)$\n",getpid(),sd->oxygen,sd->hydrogen);
            if(sd->hydrogen>=2){
                printf("*(O:%d H:%d)* debut molécule\n",sd->oxygen,sd->hydrogen);
                v(semid,2);
                v(semid,2);
                sd->hydrogen=sd->hydrogen-2;
                v(semid,1);
                sd->oxygen=sd->oxygen-1;

            }else{
                v(semid,0);
                
            }
            p(semid,1);
            barriere(3,semid,sd);
            bondOxygen(getpid());
            v(semid,0);
            exit(0);
        }
    }

    for (int i=0; i<n;i++){
        //on attend les fils 
        wait(0);
    }
    printf("fin du programme oxygene\n"); 

}