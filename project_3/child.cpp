#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <csignal>

int main(int argc,char* argv[])
{
    wiringPiSetup();
    int fd,pipe_write;
    char data;

    pipe_write = atoi(argv[1]);

    fd = serialOpen("/dev/serial0", 115200);
    char str[10];
    
    while (true)
    {
        if (serialDataAvail(fd))
        {
            data = serialGetchar(fd);
            std::cout << "Data => " << data << std::endl;
            std::cout.flush();
            str[0] = data;
            write(pipe_write,str,sizeof(str));
        }
    }
    return 0;
}