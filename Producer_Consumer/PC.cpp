#include <iostream>
#include <queue>
#include <vector>
#include <pthread.h>

#define SIZE 5

std::queue<char> buffer;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;
std::string str;

void *producer_function(void *ptr) 
{
    int i = 0;
    while (str[i] != '\0') 
    {
        pthread_mutex_lock(&mutex);
        while (buffer.size() == SIZE) 
        {
            pthread_cond_wait(&cond_producer, &mutex);
        }
        buffer.push(str[i]);
        std::cout << "Produced: " << str[i] << std::endl;
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
        i++;
    }
    pthread_exit(nullptr);
}

void *consumer_function(void *ptr) 
{
    int i = 0;
    std::vector<char> v;
    while (str[i] != '\0') 
    {
        pthread_mutex_lock(&mutex);
        while (buffer.empty()) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        v.push_back(buffer.front());
        std::cout << "Consumed: " << buffer.front() << std::endl;
        buffer.pop();
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
        i++;
    }
    std::cout << "consumed = ";
    for (int i = 0; i < v.size(); i++) 
    {
        std::cout << v[i];
    }
    std::cout << "\n";
    pthread_exit(nullptr);
}

int main() 
{
    pthread_t Producer_object, Consumer_object;
    std::cout << "enter sentence" << std::endl;
    std::getline(std::cin,str);
    pthread_create(&Producer_object, NULL, producer_function, NULL);
    pthread_create(&Consumer_object, NULL, consumer_function, NULL);
    pthread_join(Producer_object, NULL);
    pthread_join(Consumer_object, NULL);
    return 0;
}