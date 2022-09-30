#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
void bondOxygen(int n ){
    printf("molécule H2O formée avec %d d'hydrogen\n",n);
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
    int oxygen,hydrogen;
}datatab ; 

void main(){
    int n ; 
    printf("donner le nombre de processus d'hydrogen \n");
    scanf("%d",&n);
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/projet",'f');
    // on recupere le id de la memoire partage et le groupe de semaphore
    int shmid=shmget(key,sizeof(datatab),0);
    int semid=semget(key,3,0);
    datatab *sd=NULL;
    sd=shmat(shmid,sd,0);

    for(int i =0;i<n ; i++){
        int pid = fork();
        if(pid == -1)
        {
            perror("fork");
            exit(1);    
        }
        if(pid==0)
        {   sleep(1);
            printf("creation de la %d eme hydrogen \n",i+1);
            //traitement 
            p(semid,0);
            sd->hydrogen=sd->hydrogen+1;
            if(sd->hydrogen>=2 && sd->oxygen>=1){
                v(semid,2);
                v(semid,2);
                sd->hydrogen=sd->hydrogen-2;
                v(semid,1);
                sd->oxygen=sd->oxygen-1;

            }else{
                v(semid,0);
            }
            p(semid,2);
            //barier(3);
            //bonHydrogen(pid);
            
            exit(0);
        }
    }

    for (int i=0; i<n;i++){
        //on attend les fils 
        wait(0);
    }
    printf("fin du programme hydrogen\n"); 

}