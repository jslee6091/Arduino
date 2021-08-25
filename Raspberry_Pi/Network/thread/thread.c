// make 5 threads
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 5 

/*
  int pthread_create(
  	pthread_t *thread,			// thread ID
	pthread_attr_t *attr;			// thread attribute
	void *(*thread_routine) (void *),	// thread routine
	void *arg				// parameter
  );

  void pthread_exit(void *retval);
*/

void *PrintHello(void *);

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	int rc, t;
	for(t = 0; t<NUM_THREADS; t++){
		printf("In main: creating thread %d th thread\n", t+1);
		// create thread
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
		if(rc){
			printf("ERROR: return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	sleep(6);
	printf("Main thread #%d die after 6 seconds....\n", pthread_self());
	// terminate thread
	pthread_exit(NULL);
}

void *PrintHello(void *threadid){
	int tid;
	tid = (int)threadid;
	printf("Hello World! It's me. process # %d thread # %d!\n", getpid(), pthread_self());
	sleep(5);
	printf("Thread #%d die after 5seconds\n", pthread_self());
	pthread_exit(NULL);
}

