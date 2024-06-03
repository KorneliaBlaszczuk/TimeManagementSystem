#include "pomodoro.h"
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include <cmath>

Countdown::Countdown(int min) : hours(min / 60), minutes(min % 60), seconds(0){};

void Countdown::timer()
{
    bool go = true;
    while (go)
    {
        // calls to display correct clock on display
        displayTimer();
        // sleep system call for 1 sec
        //  it only stops the execution od current thread
        sleep(1);
        // counting down by one secend
        seconds--;
        if (seconds == -1)
        {
            // decrement minutes
            minutes--;

            // if hours decrement needed
            if (minutes == -1)
            {
                // decrement hours
                hours--;
                minutes = 59;
            }
            seconds = 59;
        }
        if (hours == 0 and minutes == 0 and seconds == 0)
        {
            go = false;
            std::cout << "Time is up." << std::endl;
        }
    }
};

void Countdown::displayTimer()
{
    // system call to clean terminal window
    // so the user will be focused on time only
    system("clear");
    std::cout << std::setfill(' ') << std::setw(30) << "COUNTDOWN" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << "--------------------------" << std::endl;
    std::cout << std::setfill(' ') << std::setw(24);
    std::cout << "| " << std::setfill('0') << std::setw(2) << hours << " hrs | ";
    std::cout << std::setfill('0') << std::setw(2) << minutes << " min | ";
    std::cout << std::setfill('0') << std::setw(2) << seconds << " sec |" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << " --------------------------" << std::endl;
}
