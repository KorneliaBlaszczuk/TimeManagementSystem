#include <iostream>
#include <ctime>
#include <vector>

enum class PlanType {
    TASK,
    EVENT,
    REMINDER
};


class Plan
{
    std::string name;
    time_t main_date;
    PlanType type; // changing the type is not necessary in my opinion
    //reference to the detailed plan object???

    public:
    Plan(const std::string& n, std::time_t d, PlanType t)
        : name(n), main_date(d), type(t) {}

    virtual std::string get_name() const
    {
        return name;
    }
    virtual time_t get_main_date() const
    {
        return main_date;
    }
    virtual PlanType get_type() const
    {
        return type;
    }

    virtual void set_name(const std::string& new_name)
    {
        if(new_name.empty())
            throw std::invalid_argument("Empty name");
        else if(new_name == name)
            return;
        else
            name = new_name;
    }
    virtual void set_main_date(std::time_t new_date)
    {
        // time_t could be modified arbitrarily (I think)
        main_date = new_date;
    }
};

class Task: public Plan
{
    struct subtask
    {
        std::string name;
        int priority;
        bool is_done;
    };

    bool is_done;
    int priority; //1-5?
    std::string progress_note;
    int progress_status; //0-100(%) it does not have to be overly accurate
    std::vector<subtask> subtasks;

    public:
    // @todo methods
};