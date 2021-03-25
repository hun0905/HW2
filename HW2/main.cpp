#include "mbed.h"
#include "uLCD_4DGL.h"
#include<iostream>
using namespace std;
const double pi = 3.141592653589793238462;
const double amplitude = 0.5f;
const double offset = 65535 / 2;

// The sinewave is created on this pin
// Adjust analog output pin name to your board spec.
AnalogOut aout(PA_5);

uLCD_4DGL uLCD(D1, D0, D2);//Problem point. connect ulcd 
DigitalIn button(PC_5);//up
DigitalIn button2(PC_4);//down
DigitalIn button3(PC_3);//reset
DigitalIn mypin(USER_BUTTON);//out data
int j = 1;
float ADCdata[130];
int count;
int Time[3] = {10,50,100};//cycle time

void Display(int &i)
{
    uLCD.cls();
    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    uLCD.locate(4,4);
    uLCD.printf("%d",i);
    uLCD.line(0, 50, 160, 50, 0xFF0000);
    uLCD.line(0, 90, 160, 90, 0xFF0000);
}

int main()
{
    //double rads = 0.0;
    /*button.rise(&up);
    button2.rise(&down);
    button3.rise(&reset);*/ //cannot not use this way
    int TimeNow = Time[j];//cycle time now
    int RiseTime = TimeNow*3/5;
    int FallTime = TimeNow*2/5;
    uint16_t sample = 0;
    int count = 0;
    Display(Time[j]);
    while (1) {
        if(button){
             j = (j == 2)?0:j+1;
            Display(Time[j]);
            TimeNow = Time[j];
            RiseTime = TimeNow*3/5;
            FallTime = TimeNow*2/5;
            ThisThread::sleep_for(1ms);
        }
        else if(button2){
            j = (j == 0)?2:j-1;
            Display(Time[j]);
            TimeNow = Time[j];
            RiseTime = TimeNow*3/5;
            FallTime = TimeNow*2/5;
            ThisThread::sleep_for(1ms);
        }
        else if(button3){
            j = 2;
            Display(Time[j]);
            TimeNow = Time[j];
            RiseTime = TimeNow*3/5;
            FallTime = TimeNow*2/5;
            ThisThread::sleep_for(1ms);
        }
        else{
            for (int i = 0; i < TimeNow; i++) {
                if(i < TimeNow)   
                    sample = (uint16_t)(offset*i/RiseTime);
                else
                    sample = (uint16_t)(offset*(TimeNow-i)/FallTime);
                aout.write_u16(sample);
                ADCdata[count] = aout;
                count++;
                if(count >= 128){
                    for(int i = 0 ; i < count ; i++)
                    {
                        cout<<ADCdata[i]<<"\r\n";
                    }
                    count = 0;
                }
                ThisThread::sleep_for(1ms);
            }
        }
    
   }
}
