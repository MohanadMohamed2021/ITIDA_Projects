#include <iostream>
using namespace std;

long hms_to_secs(long hours, long minutes, long seconds)
{
    return ((hours* 3600) + (minutes * 60) + seconds);
}

int main()
{
    int hours, minutes, seconds;
    char sym1, sym2;

    cout << "Enter a time value in the format (hh:mm:ss) or 'q' to quit: ";
    cin >> hours >> sym1 >> minutes >> sym2 >> seconds;

    if (sym1 == ':' && sym2 == ':' && hours >= 0 && minutes >= 0 && seconds >= 0)
    {
        long total_seconds = hms_to_secs(hours, minutes, seconds);
        cout << hours << sym1 << minutes << sym2 << seconds << " is equivalent to " << total_seconds << " seconds." << endl;
    }
    else
    {
        cout << "Wrong input time in the format (hh:mm:ss)." << endl;
    }
    return 0;
}
