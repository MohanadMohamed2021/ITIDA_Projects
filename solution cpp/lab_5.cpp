#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;


int main()
{
    string str;
    cout<<"enter string of digits"<<endl;
    cin>>str;
    int i,size=str.length();
    for(i=size-3;i>0;i-=3)
    {
        str = str.insert(i,",");
    }
    cout<<str<<endl;
    return 0;
}
