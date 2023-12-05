#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

int main()
{
    cout<<"iam child "<<getpid()<<" for parent "<<getppid()<<endl;
    sleep(5);
    kill(getppid(), SIGUSR1);
    return 0;
}