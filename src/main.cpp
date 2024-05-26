#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000           // 반복 횟수

int counter = 0;        // 공유 변수 (초기값 0)

/**Producer 함수
 * @param arg : void 포인터
 * @return void 포인터
 */
void *producer(void *arg) {
    for (int i = 0; i < N; i++) {
        counter++;
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < N; i++) {
        counter--;
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // 2개의 Thread 생성
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Thread 종료 대기
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 최종 counter 값 출력
    printf("When N is %d, Final counter value: %d\n", N, counter);

    return 0;
}
