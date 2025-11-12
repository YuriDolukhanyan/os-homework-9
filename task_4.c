#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LENGTH 5

int arr[ARR_LENGTH];

void* arr_square(void* arg) {
	int thread_number = (int)(long)arg;
	int a = arr[thread_number];
	printf("square of %d is %d\n", a, a * a);
	return NULL;
}

int main() {
	pthread_t threads[ARR_LENGTH];
	for (int i = 0; i < ARR_LENGTH; ++i) {
		arr[i] = i + 1;
		if (pthread_create(&threads[i], NULL, arr_square, (void*)(long)i) != 0 ) {
			perror("error: failed to create thread");
			return 1;
		}
	}

	for (int i = 0; i < ARR_LENGTH; ++i) {
		if (pthread_join(threads[i], NULL) != 0) {
			perror("error: failed to join thread");
			return 1;
		}
	}

	return 0;
}
