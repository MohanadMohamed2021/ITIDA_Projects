#include <iostream>
using namespace std;

class ccounter {
private:
    int m_count;

public:
    ccounter() : m_count(0) {}

    void increment()
    {
        m_count++;
    }

    void decrement()
    {
        m_count--;
    }

    int DisplayCount() const
    {
        cout<<"count="<<m_count<<endl;
    }
};

int main()
{
    int flag=0;
    ccounter counting;
    char choice;
    cout<<"press 'i' to inclement press 'd' to declement press 'p' to display"<<endl;

    while(1)
    {
        cin >> choice;
        switch(choice)
        {
         case'i':
            {
              counting.increment();
              break;
            }
         case'd':
            {
              counting.decrement();
              break;
            }
          case'p':
            {
              counting.DisplayCount();
              flag=1;
              break;
            }
        }
        if(flag==1)
        {
            break;
        }
    }
    return 0;
}
