#pragma once
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

class Countdown
/*
This class takes care of creating a countdown timer.
Timer will be used in pomodoro sessions.
*/
{
    int hours;
    int minutes;
    int seconds;

    void displayTimer();

public:
    // constructor
    Countdown(int min = 15);
    // main function to run countdown
    void timer();
};
