#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <csignal>
#include <cstdlib>
#include <cstring>

int pipefd[2];

void signal_handle(int sig)
{
    digitalWrite(0, LOW);
    close(pipefd[0]);
    exit(0);
}

void Child()
{
    if (fork() == 0)
    {
        close(pipefd[0]);
        char buffer[100];
        sprintf(buffer, "%d", pipefd[1]);
        char *arg[] = {"./child", buffer, nullptr};
        execv(arg[0], arg);
    }
}

int main()
{
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi" << std::endl;
        return 1;
    }

    signal(SIGINT, signal_handle);
    pinMode(0, OUTPUT);

    if (pipe(pipefd) == -1) {
        std::cerr << "Pipe failed" << std::endl;
        return 1;
    }

    Child();
    close(pipefd[1]);
    while (true)
    {
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        if (buffer[0] == 'o')
        {
            digitalWrite(0, HIGH);
        }
        else if (buffer[0] == 'f')
        {
            digitalWrite(0, LOW);
        }
    }

    return 0;
}
