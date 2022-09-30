#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main(){
    int a[3],x, resul,i=0;
    for(i;i<3;i++){
        //creation des 3 fils
        printf("creation de fils %d\n",i+1);
        int pid=fork();
        if(pid==0){
            /*printf("donner la valeur numero %d : ",i+1);
            scanf("%d",&x);
            exit(x);
            */
            exit(2);




            /* ou bien on verifie les fils a la base de i 
            if (i=0) //fils 1 
            exit(la valeur de l'exo );
            if (i=1) //fils 2
            else fils 3
            */
        }
        else{
            //on est dans le pere
            waitpid(pid,&x,0);
            a[i]=WEXITSTATUS(x);
        }
        
    }
    for(int j=0;j<3;j++){
        printf("la valeur de fils %d est %d\n",j+1,a[j]);
    }
    int calcul=a[2]*a[1]+a[0];
    printf("le resultat de calcul est %d \n",calcul);
    printf("fin");
    exit(0);
}