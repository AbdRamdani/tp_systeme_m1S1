#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*
int main(){
    printf("programme pid : %d \n",getpid());
    printf("debut de la boucle infinie:\n");

    while(2>1) pause();
}
*/
void handler_sigint(int sig){
    printf("Hello ! I am here");
}

void main(){
    signal(SIGINT,handler_sigint);
    printf("debut programme : %d \n",getpid());
    while(2>1){
        printf("*\n");
        sleep(1);
    }
}