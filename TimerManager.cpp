#include "TimerManager.h"
#include <string.h>


/*
** Returns a boolean value that indicates whether the current time, t, is later than some prior 
** time, t0, plus a given interval, dt.  The condition accounts for timer overflow / wraparound.
*/
//bool it_is_time(uint32_t t, uint32_t t0, uint16_t dt) {
//  return ((t >= t0) && (t - t0 >= dt)) ||         // The first disjunct handles the normal case
//            ((t < t0) && (t + (~t0) + 1 >= dt));  //   while the second handles the overflow case
//}


#define ULONG_MAX 4294967295UL

TimerManager* TimerManager::instance = nullptr;

// Constructor
TimerManager::TimerManager() {
    instance = this;  // Assign the current instance to the static pointer
    for (int i = 0; i < MAX_TIMERS; i++) {
        timers[i].active = false;  // Initialize all timers as inactive
    }
    instance->enabled = true;

    TimerManager::timerCallback();
}

void TimerManager::startAll() {
//  enabled = true; 
}
//
void TimerManager::stopAll() {
//  enabled = false;
}

void TimerManager::updateTimer() {
    unsigned long now = millis();
    unsigned long nearest = ULONG_MAX;  // Use the maximum unsigned long value
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (timers[i].active && timers[i].next < nearest) {
            nearest = timers[i].next;
        }
    }
    if (nearest == ULONG_MAX) return; // No active timers

    // todo: account for overflow?
    TimerLib.setTimeout_us(timerCallback, (nearest > now) ? (nearest - now) * 1000 : 0);
    
}

// Adds a new timer event to the manager
void TimerManager::addTimer(void (*callback)(), char* name, unsigned long period) {
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (!timers[i].active) {
            timers[i].callback = callback;
            timers[i].period = period;

            // todo: account for overflow?
            timers[i].next = millis() + period;
            timers[i].active = true;
            strcpy(timers[i].name, name);
            updateTimer();
            return;
        }
    }
}

// Removes a timer
void TimerManager::removeTimer(char* name) {
    for (int i = 0; i < MAX_TIMERS; i++) {
      if (strcmp(name, timers[i].name) == 0) {
            timers[i].callback = nullptr;
            timers[i].period = 0;
            timers[i].next = 0;
            timers[i].active = false;
            memset(timers[i].name, 0, MAX_LEN_TIMER_NAME);

        }
    }

    updateTimer();
    return;
}

// Callback function triggered by the hardware timer
void TimerManager::timerCallback() {
    unsigned long now = millis();
    for (int i = 0; i < MAX_TIMERS; i++) {
        // Access the timers array through the instance pointer
        if (instance->timers[i].active && instance->timers[i].next <= now) {
            //if (instance->enabled) {
              instance->timers[i].callback();  // Call the event's callback function
           // }

            // todo: account for overflow?
            instance->timers[i].next = now + instance->timers[i].period;  // Schedule the next occurrence
        }
    }
    instance->updateTimer();
}


void TimerManager::disableTimer(char* name) {
  // check if timer is present
  for (int i = 0; i < MAX_TIMERS; i++) {
    if (strcmp(timers[i].name, name) == 0) {
      // found timer with that name
      timers[i].active = false;
    }
  }
  updateTimer();
}

void TimerManager::enableTimer(char* name) {
  // check if timer is present
  for (int i = 0; i < MAX_TIMERS; i++) {
    if (strcmp(timers[i].name, name) == 0) {
      // found timer with that name
      timers[i].active = true;
    }
  }
  updateTimer();
}
