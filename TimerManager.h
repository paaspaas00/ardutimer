#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <Arduino.h>
#include "uTimerLib.h"

#ifndef MAX_TIMERS
  #define MAX_TIMERS 10  // Maximum number of timers
#endif

#define MAX_LEN_TIMER_NAME 20

// Structure to represent a timer event
struct TimerEvent {
    unsigned long period;     // Interval between events in milliseconds
    unsigned long next;       // Timestamp when the event should trigger next
    void (*callback)();       // Pointer to the callback function for the timer event
    bool active;              // Flag to indicate if the timer is active
    char name[MAX_LEN_TIMER_NAME]; // Timer name
};

// Class to manage multiple timer events using a single hardware timer
class TimerManager {
public:
    TimerManager();
    void updateTimer();
    void addTimer(void (*callback)(), char* name, unsigned long period);
    void removeTimer(char* name);
    void disableTimer(char* name);
    void enableTimer(char* name);
    void startAll();
    void stopAll();
    static void timerCallback();



private:
    TimerEvent timers[MAX_TIMERS];  // Array to store timer events
    bool enabled;
    static TimerManager* instance;  // Static instance pointer for the singleton pattern
};

#endif
