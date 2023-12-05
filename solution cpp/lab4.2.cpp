#include <iostream>

using namespace std;

class cCounter
{
private:
    int counter;
    int step;
public:
    cCounter():counter(0),step(0){}
    cCounter(int cp_step):counter(0),step(cp_step){}
    cCounter operator++()
    {
        counter+=step;
        return *this;
    }
    cCounter operator--()
    {
        counter-=step;
        return *this;
    }
    void Display()const
    {
        cout<<"counter="<<counter<<" "<<"step="<<step<<endl;
    }
    void set_step(int cp_step)
    {
        step = cp_step;
    }
};
int main()
{
    cCounter obj(2);
    char choice;
    while(1)
    {
        cout<<"enter 'i' to increment and 'd' to decrement"<<endl;
        cin>>choice;
        switch(choice)
        {
         case'i':
            {
                ++obj;
                obj.Display();
                break;
            }
         case'd':
            {
                --obj;
                obj.Display();
                break;
            }
         default:
            {
                cout<<"Wrong choice"<<endl;
            }
        }

    }
    return 0;
}

