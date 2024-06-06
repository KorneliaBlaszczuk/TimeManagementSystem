#include "pomodoro.h"
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>

Countdown::Countdown(int min) : hours(min / 60), minutes(min % 60), seconds(0)
{
    if (hours <= 0 and minutes <= 0)
        throw std::invalid_argument("Timer cannot be set to not positive value.");
};

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

Pomodoro::Pomodoro(unsigned int t, unsigned int dur, unsigned int br) : times(t), block(dur), breaks(br)
{
    if (breaks == 0 or block == 0)
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
        Countdown *ses_ptr = new Block((int)block);
        sequence.push_back(ses_ptr);
        if (i != times)
        {
            Countdown *br_ptr = new Break((int)breaks);
            sequence.push_back(br_ptr);
        }
    }
};

void Pomodoro::clear_sequence()
{
    // deleting objects connected to ptr
    for (auto ptr : sequence)
    {
        delete ptr;
    }
    // clearing sequence
    sequence.clear();
}

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

std::string Pomodoro::getInfo()
{
    return "r " + std::to_string(times) + " bl " + std::to_string(block) + " br " + std::to_string(breaks);
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
        // deleting already done sequence
        clear_sequence();
    }
    return;
};