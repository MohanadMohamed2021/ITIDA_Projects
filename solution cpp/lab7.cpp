#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i=0,j;
    string sub;
    string str;
    string str2=" .,?!:;";
    getline(cin,str);
    while(str2[i]!='\0')
    {
        j=0;
        while(str[j]!='\0')
        {
            if(str[j]==str2[i])
            {
              sub = str.substr(0,j);
              cout<<sub<<endl;
              str.erase(0,j+1);
              j=0;
            }
            j++;
        }
        i++;
    }
    cout<<str<<endl;
    return 0;
}
