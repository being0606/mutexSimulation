#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_ITERATIONS 1000000
#define NUM_THREADS 4

int counter = 0;
pthread_mutex_t lock;

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&lock);
        counter--;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t producer_threads[NUM_THREADS], consumer_threads[NUM_THREADS];
    
    pthread_mutex_init(&lock, NULL);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(producer_threads[i], NULL);
        pthread_join(consumer_threads[i], NULL);
    }
    
    printf("Final counter value: %d\n", counter);
    
    pthread_mutex_destroy(&lock);
    
    return 0;
}
