#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void* thread1_function(void *ptr);
void* thread2_function(void *ptr);
char str1[] = "hello from thread1";
char str2[] = "hello from thread2";

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, &thread1_function, NULL);
    pthread_create(&thread2, NULL, &thread2_function, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}

void* thread1_function(void *ptr) {
    FILE *file1 = fopen("thread1.txt", "w");
    while (1) 
    {
        fprintf(file1, "%s\n", str1);
        fflush(file1);
        sleep(1);
    }

    fclose(file1); 
}

void* thread2_function(void *ptr) {
    FILE *file2 = fopen("thread2.txt", "w");
    while (1) 
    {
        fprintf(file2, "%s\n", str2); 
        fflush(file2);
        sleep(1);
    }

    fclose(file2); 
}