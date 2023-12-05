#include <iostream>
#include <stdexcept>
using namespace std;
template<class T,int size>
class SafeArray
{
private:
    T data[size];

public:

    SafeArray()
    {
        for (T i = 0; i < size; i++)
        {
            data[i] = 0;
        }
    }


    T& operator[](T index)
    {
        if(!((index >=0)&&(index <size)))
        {
             cout<<"Out of range"<<endl;
             int x=0xff;
             return x;
        }
        return data[index];
    }
};
int main()
{
    SafeArray<int,size> arr1;
    arr1[5]=10;
    cout<<arr1[5]<<endl;
    return 0;
}
