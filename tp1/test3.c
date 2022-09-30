#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

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
    perror("semctl");
    return zz;
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

int semdestroy(int semid){
    return semctl(semid, 0, IPC_RMID,0);
}

void main(){
    int n ; 
    //partie 1 : creation de semaphore 
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'e');
    //on cree une semaphore 
    int id=semcreat(key,1);
    printf("initialisation de semaphore\n");
    //initialisation de notre semaphore a la valeur 1
    int initsem=seminit(id,0,1);
    printf("donner la valeur de nb de fils \n");
    scanf("%d",&n);
    sleep(10);

    for(int i =0;i<n ; i++){
        int pid = fork();
        if(pid == -1)
        {
            perror("fork");
            exit(1);    
        }
        if(pid==0)
        {   sleep(1);
            printf("arrivé de fils numero %d \n",i+1);
            
            p(id,0); // reserver l'imprimante 
            printf("****acces a l'imprimante par le fils %d \n",i+1);
            sleep(5);
            printf("****fils numero %d a terminé d'utiliser l'imprimante\n",i+1);
            v(id,0); // liberer le semaphore 
            exit(0);
    
        }

    }   
        for (int i=0; i<n;i++){
            //on attend les fils 
            wait(0);
        }
        printf("fin de pere %d\n",getpid());
        
    //suppression de la semaphore apres la terminison
    int zzz=semdestroy(id);
    printf(" la valeur de retour de semdestroy est %d \n",zzz);
    exit(0);


}