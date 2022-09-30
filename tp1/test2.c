#include <sys/sem.h>
#include <stdio.h>

void seminit (int idsem, int numsem, int initval){
    printf("%d***\n",numsem);
    if(numsem!=-1){
    printf("onest dans le if \n");
    int zz= semctl(idsem, numsem, SETVAL, initval);
    printf("onest dans le if \n");
    perror("semctl");
    }
    else{
        printf("le cas de else\n");
       // int tab[4]={initval,initval,initval,initval};
        int n ; 
        printf("donner ne nombre de semaphore \n");
        scanf("%d",&n);
        int tab[n];
        /*
        // on cree la table qui contient les valeur 
        for(int i=0; i<n ; i++) tab[i]=initval;
        */
        int zz= semctl(idsem, 0, SETALL, tab);
        perror("semctl");
    }
}

int z (int semid ,int numsem){
    struct sembuf op;
    op.sem_flg=0;
    op.sem_num=numsem;
    op.sem_op=0; //pour l'initialisaiton 

}
int p(int semid ,int numsem){
    struct sembuf op;
    op.sem_flg=0;
    op.sem_num=numsem;
    op.sem_op=-1;

    return semop(0,&op, 1);
}

int v(int semid ,int numsem){
    struct sembuf op;
    op.sem_flg=0;
    op.sem_num=numsem;
    op.sem_op=+1;

    return semop(0,&op, 1);
}

int semdestroy(int semid){
    return semctl(semid, 0, IPC_RMID,0);
}

void main(int argc , char *argv[] ){
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'t');
    int id = semget(key, 4 , 0);
    printf("id : %d\n",id);
 

   /* int zz=semctl(id, 0, SETVAL,666 );
    printf("%d\n",zz);
    perror("semctl");*/
    /* 
    unsigned short tab[4]={11,22,33,44};
    int z=semctl(id,0,SETALL,tab);
    printf("%d \n",z);
    perror("semctl");
    unsigned short tab2[4];
    int y = semctl(id,0,GETALL,tab2);
    for(int i =0;i<4;i++){
        printf("%d\n",tab2[i]);
    }
    perror("semctl");
    */

   // creation de semop pour le p et v 
   
    /*
    struct sembuf op;
    
    
    op.sem_flg=0;
    op.sem_num=1;
    op.sem_op=+1;// pour l'utiliser comme un P()


    int returnn =semop(0,&op, 1);
    printf(" la valeur de retour de notre semop est %d \n",returnn);
    */
   
 

    int killsem=semdestroy(id);
    printf(" la valeur de retour de semdestroy est %d \n",killsem);

    

}