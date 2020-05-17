#pragma once

#include "SDL.h";

class Time
{
public:
    //Initializes variables
    Time();

    //The various clock actions
    void Start();
    void Stop();
    void Pause();
    void Unpause();

    //Gets the timer's time
    int GetTicks();

    //Checks the status of the timer
    bool IsStarted();
    bool IsPaused();

private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

};

