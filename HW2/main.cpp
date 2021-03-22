#include "mbed.h"
#include "mbed.h"
#include "uLCD_4DGL.h"
DigitalOut myled(LED1);
DigitalIn button(PC_5);//up
DigitalIn button2(PC_4);//down
DigitalIn button3(PC_3);//reset
uLCD_4DGL uLCD(D1, D0, D2);

int main()
{
   /*while(1) {
        myled.write(button.read());    /* read the state of input  pin P1_14 and write it to output port pin LED1*/
    //}
    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    int Frequency[5] = {100,200,300,400,500};
    int i = 2;
    while(1){
        
        if(button.read()){
            if(i == 4)
                i = 0;
            else
                i++;
        }
        if(button2.read()){
            if(i == 0)
                i = 4;
            else
                i--;
        }
        if(button3.read()){
            i = 2;
        }
        uLCD.locate(3,4);
        uLCD.printf("%2d",Frequency[i]);
        uLCD.locate(3,2);
        if(i != 0)
            uLCD.printf("%2d",Frequency[i-1]);
        else
            uLCD.printf("%2d",Frequency[4]);
        uLCD.locate(3,6);
        if(i != 4)
            uLCD.printf("%2d",Frequency[i+1]);
        else
            uLCD.printf("%2d",Frequency[0]);
        uLCD.line(0, 50, 160, 50, 0xFF0000);
        uLCD.line(0, 90, 160, 90, 0xFF0000);
        
        ThisThread::sleep_for(200ms);
    }
}