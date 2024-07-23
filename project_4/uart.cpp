#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
int main()
{
    wiringPiSetup();
    int fd = serialOpen("/dev/serial0", 115200);
    while (true)
    {
        if (serialDataAvail(fd))
        {
            char data = serialGetchar(fd);
            std::cout << "Data => " << data << std::endl;
            std::cout.flush();
        }
    }
    return 0;
}