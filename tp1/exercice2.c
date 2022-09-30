
#include <sys/sem.h>
#include <stdio.h>


void seminit (int idsem, int numsem, int initval){
    if(numsem!=-1){
    int zz= semctl(idsem, numsem, SETVAL, initval);
    perror("semctl");
    }
    else{
        printf("donner le nombre  de semaphore\n");
        int n ; 
        scanf("%d",&n);
        int tab[n];
        for(int i=0;i<n ; i++) tab[i]=initval;
        int zz= semctl(idsem, 0, SETALL, tab);
        int z=semctl(idsem, 0, GETALL, tab);
        perror("semctl");
    }
}

void main(){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'t');
    int id = semget(key, 4, 0);
    printf("le id est %d\n",id);
    seminit(id,3 ,1);
}