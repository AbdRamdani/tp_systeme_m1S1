#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

void main(){
    
    printf("le pid de programme principale : %d , de pere %d\n",getpid(),getppid());
    for(int i=0;i<3;i++){
    int pid = fork();
    if(pid == -1)
    {   
        perror("fork");
        exit(1);
    }
    if(pid==0)
    {
        printf("%d * fils de pid %d , le pid de mon pere est %d \n",i+1,getpid(),getppid());
        sleep(6);
        if(i==0){
            for(int j =0 ; j<2; j++){
                int pid2 = fork();
                if(pid2== -1){
                    perror("fork");
                    exit(0);
                }
                if(pid2==0){
                    printf ("%d%d : ici fils %d , de pere %d \n",i+1,j+1,getpid(),getppid());
                    sleep(6);
                    exit(0); //fin des fils f3 f4
                }
        }}
        sleep(6); wait(0);exit(0); //le wait des fils p3 et p4 de f1
       
    }
     sleep(6);
    if(i!=0){
        if(i==2)
        {wait(0);wait(0); // wait pour le fils F1 et F2}
        }
        else wait(0); //de fils F5
       
    
}
    sleep(1);
    printf("fin .. pere de pid= %d , est ppid= %d   \n",getpid(),getppid());
    
}

