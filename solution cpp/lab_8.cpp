#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str1="abcd";
    string str2="ef";
    int temp;
    cout << str1.length() <<" "<< str2.length() <<endl;
    cout << str1+str2 << endl;
    temp=str1[0];
    str1[0]=str2[0];
    str2[0]=temp;
    cout<<str1<<" "<<str2<<endl;
    return 0;
}
