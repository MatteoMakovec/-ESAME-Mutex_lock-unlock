#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <pthread.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void * thread_function(void * arg) {
	int s;

  s = pthread_mutex_lock(&mutex);
  if (s != 0) {
    perror("pthread_mutex_lock");
    exit(EXIT_FAILURE);
  }

  // zona critica

  s = pthread_mutex_unlock(&mutex);
  if (s != 0) {
    perror("pthread_mutex_lock");
    exit(EXIT_FAILURE);
  }

  return NULL;
}



int main() {
	pthread_t t1;
	pthread_t t2;
	void * res;
	int s;

	s = pthread_create(&t1, NULL, thread_function, NULL);
	if (s != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	s = pthread_create(&t2, NULL, thread_function, NULL);
	if (s != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t1, &res);
	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t2, &res);
	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}


	return 0;
}
