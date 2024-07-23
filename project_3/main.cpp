#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <csignal>
#include <cstdlib>
#include <cerrno>

int fd;

void signal_handle(int sig)
{
    digitalWrite(0, LOW);
    serialClose(fd);
    exit(0);
}

int main()
{
    char received_data;

    // Set up signal handler for CTRL+C
    signal(SIGINT, signal_handle);

    // Initialize WiringPi and configure pin 0 as output
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi" << std::endl;
        return 1;
    }
    pinMode(0, OUTPUT);

    // Open UART device
    fd = serialOpen("/dev/serial0", 115200);
    if (fd < 0) {
        std::cerr << "Unable to open serial device: " << std::endl;
        return 1;
    }

    while (true)
    {
        if (serialDataAvail(fd))
        {
            received_data = serialGetchar(fd);
            std::cout << "Data => " << received_data << std::endl;
            std::cout.flush();

            if (received_data == 'f')
            {
                digitalWrite(0, LOW);
            }
            else if (received_data == 'o')
            {
                digitalWrite(0, HIGH);
            }
        }
    }

    return 0;
}
