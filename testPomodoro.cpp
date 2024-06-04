#include <gtest/gtest.h>
#include "pomodoro.h"

TEST(pomodoro, countdown_ctor)
{
    Countdown cd(123);
    ASSERT_EQ(cd.getTime(), "2h 3m");
}

TEST(pomodoro, countdown_ctor_error)
{
    ASSERT_THROW(Countdown(-1), std::invalid_argument);
    ASSERT_THROW(Countdown(-117), std::invalid_argument);
    ASSERT_THROW(Countdown(0), std::invalid_argument);
}

TEST(pomodoro, break_ctor)
{
    Break br(115);
    ASSERT_EQ(br.getTime(), "1h 55m");
}

TEST(pomodoro, break_ctor_error)
{
    ASSERT_THROW(Break(-90), std::invalid_argument);
    ASSERT_THROW(Break(-345), std::invalid_argument);
}

TEST(pomodoro, block_ctor)
{
    Block bl(115);
    ASSERT_EQ(bl.getTime(), "1h 55m");
}

TEST(pomodoro, block_ctor_error)
{
    ASSERT_THROW(Block(-90), std::invalid_argument);
    ASSERT_THROW(Block(-345), std::invalid_argument);
}

TEST(pomodoro, pomodoro_ctor)
{
    Pomodoro pm(1, 1, 2);
    ASSERT_EQ(pm.getInfo(), "r 1 bl 1 br 2");
}

TEST(pomodoro, pomodoro_ctor_error)
{
    ASSERT_THROW(Pomodoro(0, 1, 1), std::invalid_argument);
    ASSERT_THROW(Pomodoro(7, 1, 0), std::invalid_argument);
    ASSERT_THROW(Pomodoro(9, 0, 1), std::invalid_argument);
}