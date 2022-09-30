#include <sys/sem.h>
#include <stdio.h>

void seminit (int idsem, int numsem, int initval){
    if(numsem!=-1){
    int zz= semctl(idsem, numsem, SETVAL, initval);
    printf("%d\n",zz);
    perror("semctl");
    }
    else{
        printf("le cas de else\n");
       // int tab[4]={initval,initval,initval,initval};
       int tab[4]={77,77,77,77};
         int zz= semctl(idsem, 0, SETALL, tab);
             printf("%d\n",zz);
        perror("semctl");
    }


}

void main(){
    //seminit (int idsem, int numsem, int initval)
    //semint();
    key_t key = ftok("/home/abd/Desktop/S7/SYS/tp/tp1",'z');
    int id = semget(key, 4, 0);
    printf("le id est %d\n",id);
    seminit(id,-1,77);
    printf("%d",id);
    
}