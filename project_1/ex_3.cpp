#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <csignal>
#include <map>
#include <vector>

bool flag = false;
class _7Segment
{
private:
    int A;
    int B;
    int C;
    int D;
    int E;
    int F;
    int G;
    std::map<int, std::vector<int>> segments;

public:
    _7Segment() : A(14), B(30), C(21), D(22), E(23), F(24), G(25)
    {
        pinMode(A, OUTPUT);
        pinMode(B, OUTPUT);
        pinMode(C, OUTPUT);
        pinMode(D, OUTPUT);
        pinMode(E, OUTPUT);
        pinMode(F, OUTPUT);
        pinMode(G, OUTPUT);
        segments.insert({0, {1, 1, 1, 1, 1, 1, 0}});
        segments.insert({1, {0, 1, 1, 0, 0, 0, 0}});
        segments.insert({2, {1, 1, 0, 1, 1, 0, 1}});
        segments.insert({3, {1, 1, 1, 1, 0, 0, 1}});
        segments.insert({4, {0, 1, 1, 0, 0, 1, 1}});
        segments.insert({5, {1, 0, 1, 1, 0, 1, 1}});
        segments.insert({6, {1, 0, 1, 1, 1, 1, 1}});
        segments.insert({7, {1, 1, 1, 0, 0, 0, 0}});
        segments.insert({8, {1, 1, 1, 1, 1, 1, 1}});
        segments.insert({9, {1, 1, 1, 1, 0, 1, 1}});
    }
    void Display()
    {
        std::vector<int> vec;
        for (int i = 0; i < 10; i++)
        {
            vec.clear();
            std::copy(segments[i].begin(),segments[i].end(),std::back_inserter(vec));
            digitalWrite(A,vec[0]);
            digitalWrite(B,vec[1]);
            digitalWrite(C,vec[2]);
            digitalWrite(D,vec[3]);
            digitalWrite(E,vec[4]);
            digitalWrite(F,vec[5]);
            digitalWrite(G,vec[6]);
            if((i == 9) && (flag == false))
            {
                i = 0;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    ~_7Segment()
    {
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
        digitalWrite(E,LOW);
        digitalWrite(F,LOW);
        digitalWrite(G,LOW);
    }
};
void Terminate()
{
    std::cout<<"Enter '1' to quit => ";
    std::cin>>flag;
}
int main()
{
    wiringPiSetup();
    _7Segment seg;
    std::thread T1(&_7Segment::Display,seg);
    std::thread T2(Terminate);
    T1.join();
    T2.join();
    return 0;
}