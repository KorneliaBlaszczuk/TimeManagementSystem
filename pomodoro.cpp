#include "pomodoro.h"
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>

Countdown::Countdown(int min) : hours(min / 60), minutes(min % 60), seconds(0){};

void Countdown::timer()
{
    bool go = true;
    // system call to clean terminal window
    // so the user will be focused on time only
    system("clear");
    while (go)
    {
        // calls to display correct clock on display
        displayTimer();
        // sleep system call for 1 sec
        //  it only stops the execution of current thread
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // counting down by one second
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
        // it informs time is up and make a sound (\7) depending on compiler and emulator
        {
            go = false;
            std::cout << std::endl
                      << std::setfill(' ') << std::setw(35);
            std::cout << "Time is up.\7" << std::endl;
        }
    }
};

void Countdown::displayTimer()
{
    system("clear");
    std::cout << std::setfill(' ') << std::setw(35) << "COUNTDOWN" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << "--------------------------" << std::endl;
    std::cout << std::setfill(' ') << std::setw(25);
    std::cout << "| " << std::setfill('0') << std::setw(2) << hours << " hrs | ";
    std::cout << std::setfill('0') << std::setw(2) << minutes << " min | ";
    std::cout << std::setfill('0') << std::setw(2) << seconds << " sec |" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << " --------------------------" << std::endl;
};

std::string Countdown::getTime()
{
    return std::to_string(hours) + "h " + std::to_string(minutes) + "m";
};

Break::Break(int min) : Countdown(min){};

void Break::displayTimer()
{
    // system call to clean terminal window
    // so the user will be focused on time only
    system("clear");
    std::cout << std::setfill(' ') << std::setw(35) << "BREAK" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << "--------------------------" << std::endl;
    std::cout << std::setfill(' ') << std::setw(25);
    std::cout << "| " << std::setfill('0') << std::setw(2) << hours << " hrs | ";
    std::cout << std::setfill('0') << std::setw(2) << minutes << " min | ";
    std::cout << std::setfill('0') << std::setw(2) << seconds << " sec |" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << " --------------------------" << std::endl;
};

Block::Block(int min) : Countdown(min){};

void Block::displayTimer()
{
    // system call to clean terminal window
    // so the user will be focused on time only
    system("clear");
    std::cout << std::setfill(' ') << std::setw(40) << "SESSION BLOCK" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << "--------------------------" << std::endl;
    std::cout << std::setfill(' ') << std::setw(25);
    std::cout << "| " << std::setfill('0') << std::setw(2) << hours << " hrs | ";
    std::cout << std::setfill('0') << std::setw(2) << minutes << " min | ";
    std::cout << std::setfill('0') << std::setw(2) << seconds << " sec |" << std::endl;
    std::cout << std::setfill(' ') << std::setw(50) << " --------------------------" << std::endl;
};

Pomodoro::Pomodoro(unsigned int t, int dur, int br) : times(t), block(dur), breaks(br)
{
    if (breaks <= 0, block <= 0)
    {
        throw std::invalid_argument("Time of session blocks and breaks need to be positive.");
    }
    if (times == 0)
    {
        throw std::invalid_argument("Pomodoro session needs to have at least one repetition.");
    }
};

void Pomodoro::start()
{
    for (int i = 0; i < times; i++)
    {
        Countdown *ses_ptr = new Block(block);
        sequence.push_back(ses_ptr);
        if (i != times)
        {
            Countdown *br_ptr = new Break(breaks);
            sequence.push_back(br_ptr);
        }
    }
};

int Pomodoro::stop()
{
    int choice;
    std::cout << "Are you ready to start new session block?\n"
              << "Press 1 to start new block or 2 to end Pomodoro mode.\n";
    std::cin >> choice;

    while (choice != 1 and choice != 2)
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Invalid input. Please enter a number between 1 and 2.\n";
        std::cin >> choice;
    };
    return choice;
};

void Pomodoro::go()
{
    int choice;

    // print information to user about Pomodoro mode
    std::cout << "You are starting Pomodoro mode.\n"
              << "The set parameters are:\n"
              << times << " repetitions\n"
              << block << " minutes session block\n"
              << breaks << " minutes breaks.\n"
              << "Do you want to start? Press 1 - yes or 2 - no.";
    std::cin >> choice;

    while (choice != 1 and choice != 2)
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Invalid input. Please enter a number between 1 and 2.\n";
        std::cin >> choice;
    };
    if (choice == 2)
        return;
    else
    {
        // creating a sequence
        start();
        // running and displaying pomodoro
        int i = 1;
        // for better usage we stop for 2 sec
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // sequence with possibility to stop in the middle
        for (auto ptr : sequence)
        {
            if (i % 2 == 1)
            {
                ((Block *)ptr)->timer();
                // checking if user wants to continue in pomodoro mode
                if (stop() == 2)
                {
                    break;
                }
            }
            else
            {
                ((Break *)ptr)->timer();
            };
            i++;
        }
        std::cout << "You finished your Pomodoro session. Good job!";
    }
    return;
};

void PomodoroRun()
{
    int choice;
    std::cout << "You are entering Pomodoro mode.\n"
              << "Possible modes to choose from are: \n"
              << "1 - short: 3 repetitions, 30 minutes blocks, 5 minutes breaks;\n"
              << "2 - medium: 4 repetitions, 30 minutes blocks, 7 minutes breaks;\n"
              << "3 - long: 6 repetitions, 30 minutes blocks, 10 minutes breaks;\n"
              << "4 - intense: 5 repetitions, 45 minutes blocks, 10 minutes breaks;\n"
              << "5 - exam: 4 repetitions, 75 minutes blocks, 15 minutes breaks."
              << "Which one do you choose?\n";
    std::cin >> choice;
    while (choice != 1 and choice != 2 and choice != 3 and choice != 4 and choice != 5)
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
        std::cin >> choice;
    };
    switch (choice)
    {
    case 1:
    {
        Pomodoro pm(3, 30, 5);
        pm.go();
        break;
    }
    case 2:
    {
        Pomodoro pm(4, 30, 7);
        pm.go();
        break;
    }
    case 3:
    {
        Pomodoro pm(6, 30, 10);
        pm.go();
        break;
    }
    case 4:
    {
        Pomodoro pm(5, 45, 10);
        pm.go();
        break;
    }
    case 5:
    {
        Pomodoro pm(4, 75, 15);
        pm.go();
        break;
    }
    };
    return;
}