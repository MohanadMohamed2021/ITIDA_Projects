#include <iostream>

using namespace std;
class Employee
{
private:
    string name;
    int age;
public:
    Employee(string cp_name,int cp_age):name(cp_name),age(cp_age){}
    virtual void printPosition()
    {
        cout<<"Iam Employee"<<endl;
    }
    void Display()const
    {
        cout<<name<<" "<<age<<endl;
    }
};
class Engineer : public Employee
{
public:
    Engineer(string cp_name,int cp_age): Employee(cp_name,cp_age){}
    void printPosition()override
    {
        cout<<"iam engineer"<<endl;
    }
};
class Manager:public Employee
{
public:
   Manager(string cp_name,int cp_age):Employee(cp_name,cp_age){}
   void printPosition()override
    {
        cout<<"iam manager"<<endl;
    }
};
class Salesman:public Employee
{
public:
   Salesman(string cp_name,int cp_age): Employee(cp_name,cp_age){}
   void printPosition()override
    {
        cout<<"iam salesman"<<endl;
    }
};
int main()
{
    Employee obj1("mohanad",20);
    Engineer obj2("mohamed",25);
    Manager  obj3("abdelghany",30);
    Salesman obj4("ahmed",35);
    Employee *ptr=&obj1;
    ptr->Display();
    ptr->printPosition();
    ptr = &obj2;
    ptr->Display();
    ptr->printPosition();
    ptr=&obj3;
    ptr->Display();
    ptr->printPosition();
    ptr=&obj4;
    ptr->Display();
    ptr->printPosition();
    return 0;
}
