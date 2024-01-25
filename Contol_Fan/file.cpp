#include <iostream>
#include <map>
#include <vector>

enum State
{
    start,
    lvl1,
    lvl2,
    lvl3,
    stop
};
enum Trigger
{
    pressStart,
    pressLvl1,
    pressLvl2,
    pressLvl3,
    pressStop
};

int main()
{
    std::map<State,std::string> print_CurrentState = {
        {State::start,"Start State"},
        {State::lvl1,"Level_1 State"},
        {State::lvl2,"Level_2 State"},
        {State::lvl3,"Level_3 State"},
        {State::stop,"Stop State"}
    };
    std::map<State,std::vector<std::pair<Trigger,State>>> Device;
    Device[State::start] = {
        {Trigger::pressLvl1,State::lvl1},
        {Trigger::pressLvl2,State::lvl2},
        {Trigger::pressLvl3,State::lvl3}
    };
    Device[State::lvl1]= {
        {Trigger::pressStop,State::stop},
        {Trigger::pressLvl2,State::lvl2},
        {Trigger::pressLvl3,State::lvl3}
    };
    Device[State::lvl2] = {
        {Trigger::pressStop,State::stop},
        {Trigger::pressLvl1,State::lvl1},
        {Trigger::pressLvl3,State::lvl3},
    };
    Device[State::lvl3] = {
        {Trigger::pressStop,State::stop},
        {Trigger::pressLvl1,State::lvl1},
        {Trigger::pressLvl2,State::lvl2}
    };
    Device[State::stop] = {
        {Trigger::pressStart,State::start}
    };
    State currentState=State::start;
    Trigger currentTrigger;
    int currentTriggerNum;
    while(true)
    {
        std::cout<<"Current state is >> "<<print_CurrentState[currentState]<<"\n"<<std::endl;
        std::cout<<"Enter '0' to start\n"
                    "Enter '1' to pressLvl_1\n"
                    "Enter '2' to pressLvl_2\n"
                    "Enter '3' to pressLvl_3\n"
                    "Enter '4' to pressStop\n"<<std::endl;
        std::cin>>currentTriggerNum;
        currentTrigger=static_cast<Trigger>(currentTriggerNum);
        std::vector<std::pair<Trigger,State>> vec = Device[currentState];
        for(auto v:vec)
        {
            if(currentTrigger == v.first)
            {
                currentState=v.second;
                if(currentState==State::stop)
                {
                    perror("Fan has been stopped\n");
                    exit(0);
                }
            }
        }
    }
    return 0;
}