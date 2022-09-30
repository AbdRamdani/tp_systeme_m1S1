#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handlerStop(int sigg){
    printf("Hello ! I am here")
} 

int main(){
    signal(SIGINT,handlerStop);
    printf("debut de la boucle infinie:\n");
    while(2>1) pause();
}
