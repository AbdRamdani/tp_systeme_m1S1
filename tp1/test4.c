#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>


void main(){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'w');
    int shmid = shmget(key,sizeof(int),IPC_CREAT|IPC_EXCL|0666);
    if(shmid==-1){
        printf("la memoire partagé existe deja \n");
        shmid=shmget(key,sizeof(int),0);
        printf("son id est %d\n",shmid);
    }else printf("le id de la memoire partagé est %d\n",shmid);

    int *ad ;// valeur pour acceder a la memoire partagé
    ad=shmat(shmid,ad,0);
    //*ad=777;
    printf(" la valeur dans la memoire pargtage est %d\n",*ad);

}