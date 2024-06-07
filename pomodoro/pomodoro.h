#pragma once
#include <vector>
#include <string>

class Countdown
/*
This class takes care of creating a countdown timer.
Timer will be used in pomodoro sessions.
*/
{
protected:
    int hours;
    int minutes;
    int seconds;

    virtual void displayTimer();

public:
    // constructor
    Countdown(int min = 15);
    // main function to run countdown
    void timer();
    // function returning information for how much time is set timer
    std::string getTime();
};

class Break : public Countdown
{
public:
    Break(int min);
    void displayTimer() override;
};

class Block : public Countdown
{
    void displayTimer() override;

public:
    Block(int min);
};

class Pomodoro
/*
This class takes care of creating a pomodoro session as a hole blocks and breaks.
*/
{
    // amount of repetition
    unsigned int times;
    // how long is the session block
    unsigned int block;
    // how long is the break
    unsigned int breaks;
    std::vector<Countdown *> sequence;

    // function that creates a sequence of block sessions and breaks
    void start();
    // function that allows user to stop sequence
    int stop();
    // method to clear already done sequence
    void clear_sequence();

public:
    Pomodoro(unsigned int t, unsigned int dur, unsigned int br);
    // function that starts the squance as a whole
    void go();
    // function returning basic info about set pomodoro mode
    // returns r (repetitions),bl(duration of block), br(duration of break)
    std::string getInfo();
};

// function use to run predefined pomodoro mode in project
void PomodoroRun();
