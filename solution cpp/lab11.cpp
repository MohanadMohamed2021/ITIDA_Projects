#include <iostream>
#include <stdexcept>

// Define the fixed size of the array
#define ARRAY_SIZE 10
using namespace std;

class SafeArray {
private:
    int data[ARRAY_SIZE];

public:

    SafeArray()
    {
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            data[i] = 0;
        }
    }


    int operator[](int index)
    {
        if(!((index >=0)&&(index <ARRAY_SIZE)))
        {
             cout<<"Out of range"<<endl;
             return 0xff;
        }
        return data[index];
    }
};

int main()
{
    int index=2;
    SafeArray arr1;

    cout<<arr1[index]<<endl;
    return 0;
}
