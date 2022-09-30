#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc , char *argv[]){
    if(argc >1){
    printf("signal to kill: %d\n",atoi(argv[1]));
    kill(atoi(argv[1]),SIGINT);
    }
    else printf("erreur : donner le numero de pid\n");

    exit(0);
}