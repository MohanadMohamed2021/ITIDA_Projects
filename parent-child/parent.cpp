#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

void signal_handler(int sig)
{
    cout<<"signal has arrived "<<sig<<endl;
}
int main(int argc,char* argv[])
{
    signal(SIGUSR1,signal_handler);
    cout<<"iam code before fork "<<getpid()<<endl;
    if(fork()==0)
    {
        char *arg[]={"/home/mohanad/Documents/test/test2/child",NULL};
        execv(arg[0],arg);
    }
    else
    {
        cout<<"iam code after fork "<<getpid()<<endl;
        cout<<"waitting for signal...."<<endl;
        while(1);
    }
    return 0;
}