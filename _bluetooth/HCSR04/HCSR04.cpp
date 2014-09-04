#include "HCSR04.h"
#include "mbed.h"


HCSR04::HCSR04(PinName t, PinName e) : trig(t), echo(e) {}

//      Trigger          Echo
//      _______           _____________,,,,,,,,,
// ____|  10us |_________| 150us-25ms, or 38ms if no obstacle
// 

//return echo duration in us (refer to digram above)
long HCSR04::echo_duration() {
    timer.reset();
    trig = 0;
    wait_us(2);
    trig = 1;
    wait_us(10);
    trig = 0;
    wait_us(250);
    while(echo == 0);
    timer.start();
    while(echo == 1);
    timer.stop();
    return timer.read_us();
}

//return distance to nearest obstacle or returns 255 in cm
//if no obstacle within range
uint8_t HCSR04::distance(){
    duration = echo_duration();
    if(duration >= 14790){
        distance_cm = 255;
    }
    else{
        distance_cm = duration / 58;
    }
    return distance_cm;
}
