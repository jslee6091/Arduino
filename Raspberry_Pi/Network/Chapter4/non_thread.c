// compile : gcc -o non_thread non_thread.c -lpthread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void PrintHello(void);

int main(int argc, char *argv[]){
	printf("In main: process %d\n", getpid());
	PrintHello();
	// pthread_self() gets thread number
	printf("Main process = thread die # %d\n", pthread_self());
}

void PrintHello(void){
	printf("Hello World! It's me. process # %d thread # %d!\n", getpid(), pthread_self());
	sleep(5);
}

