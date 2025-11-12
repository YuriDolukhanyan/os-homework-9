#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 5000

int arr[ARR_SIZE];
long partial_sums[2];

void* sum_arr(void* arg) {
	int thread_number = (int)(long)arg;

	long sum = 0;

	for (int i = (thread_number - 1) * (ARR_SIZE / 2); i < thread_number * (ARR_SIZE / 2); ++i)
		sum += arr[i];

	printf("thread %d partial sum: %ld\n", thread_number, sum);

	partial_sums[thread_number] = sum;
	return NULL;
}

int main() {
	for (int i = 0; i < ARR_SIZE; ++i) arr[i] = 1;

	pthread_t thread_1, thread_2;

	if (pthread_create(&thread_1, NULL, sum_arr, (void*)1) != 0) {
		perror("error: failed to create thread 1");
		return 1;
	}

	if (pthread_create(&thread_2, NULL, sum_arr, (void*)2) != 0) {
		perror("error: failed to create thread 2");
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

	return 0;
}
