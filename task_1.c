#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_msg(void* arg) {
	char* msg = (char*)arg;
	int thread_id = pthread_self();
	printf("%s%d\n", msg, thread_id);
	return NULL;
}

int main() {
	pthread_t thread_1, thread_2, thread_3;
	char* msg = "hello from thread: ";

	if (pthread_create(&thread_1, NULL, print_msg, (void*)msg) != 0) {
		perror("error: failed thread 1 creation");
		return 1;
	}

	if (pthread_create(&thread_2, NULL, print_msg, (void*)msg) != 0) {
		perror("error: failed thread 2 creation");
		return 1;
	}

	if (pthread_create(&thread_3, NULL, print_msg, (void*)msg) != 0) {
		perror("error: failed thread 3 creation");
		return 1;
	}

	if (pthread_join(thread_1, NULL) != 0) {
		perror("error: failed to join thread 1");
		return 1;
	}

	if (pthread_join(thread_2, NULL) != 0) {
		perror("error: failed to join thread 2");
		return 1;
	}

	if (pthread_join(thread_3, NULL) != 0) {
		perror("error: failed to join thread 3");
		return 1;
	}

	printf("main thread: all threads have been completed\n");

	return 0;
}
