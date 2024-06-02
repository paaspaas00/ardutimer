#include "TimerManager.h"

TimerManager timerManager;  // Create a timer manager instance

#ifndef MAX_TIMERS
  #define MAX_TIMERS 10  // Maximum number of timers
#endif

void blink() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // Toggle the LED state
}

void printStuff() {
  Serial.println("Hello world!");
}

void printOtherStuff() {
  Serial.println("OtherStuff");
}

void printSomethingElse() {
    Serial.println("yo yo yo");
}
 
void stopAll() {
  timerManager.stopAll(); // not working!!!
}

void gogogo() {
  timerManager.startAll();// not working!!!
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    timerManager.addTimer(blink, "timer1", 1000);  // Set up a timer to blink every 1000 ms (1 second)
    timerManager.addTimer(printStuff, "timer2", 2500);
    timerManager.addTimer(printOtherStuff, "timer3", 3432);
    timerManager.addTimer(stopAll, "stopAll", 10000);
    timerManager.addTimer(gogogo, "startAll", 20000);
    timerManager.addTimer(printSomethingElse, "timer4", 6078);

    timerManager.addTimer(printSomethingElse, "timer4", 4444);
}


void loop() {
    // Main loop does nothing, as timer events are handled in the background
   // currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
   // if (currentMillis - startMillis >= 20000 && enabled)  //test whether the period has elapsed
   // {
   //   //timerManager.removeTimer("timer2");
   //   timerManager.stopAll();
////
   //   startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
   //   enabled = false;
   // }
}