#include <iostream>
#include <vector>
#include <map>

enum State
{
    play,
    paused,
    stop
};

enum Trigger
{
    pressed_play,
    pressed_pause,
    pressed_stop
};

void printState(State state)
{
    switch (state)
    {
    case State::play:
        std::cout << "Current State: Play\n";
        break;
    case State::paused:
        std::cout << "Current State: Paused\n";
        break;
    case State::stop:
        std::cout << "Current State: Stop\n";
        break;
    }
}

int main()
{
    State current_state = State::play;
    int input;

    std::map<State, std::vector<std::pair<Trigger, State>>> sm;

    sm[State::play] = {
        {Trigger::pressed_pause, State::paused},
        {Trigger::pressed_stop, State::stop}
    };

    sm[State::paused] = {
        {Trigger::pressed_stop, State::stop},
        {Trigger::pressed_play, State::play}
    };

    sm[State::stop] = {
        {Trigger::pressed_play, State::play}
    };

    while (true)
    {
        printState(current_state);

        std::cout << "Enter trigger (0: pressed_play, 1: pressed_pause, 2: pressed_stop): ";
        std::cin >> input;

        if (input < 0 || input > 2)
        {
            std::cout << "Invalid input. Please enter a number between 0 and 2.\n";
        }
        else
        {
            Trigger current_trigger = (Trigger)(input);
            auto v = sm[current_state];
            for (auto p : v)
            {
                if (p.first == current_trigger)
                {
                    current_state = p.second;
                    break;
                }
            }
        }
    }

    return 0;
}
