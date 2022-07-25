#include "mbed.h"
#include "N5110.h"

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
AnalogIn temp(PA_0);

char buffer[14] = {0};
float temp_reading, temp_sensor_vout, temperature;
float peak = 0.0;

int main(){
    lcd.init(LPH7366_1);

    while(1) {
        temp_reading = temp.read();                 //read the raw sensor output value (Between 0 and 1)
        temp_sensor_vout = temp_reading * 3.3;      //Convert the raw output into a output voltage
        temperature = temp_sensor_vout * 100;       //Convert the output voltage into a temperature reading, the sensor outputs 10mV per 'C therefore 260mv = 26'C

        if(temperature > peak){
            peak = temperature;
        }

        lcd.clear();
        sprintf(buffer, "Temp: %.2f .C", temperature);
        lcd.printString(buffer, 0, 1);
        sprintf(buffer, "Peak: %.2f .C", peak);
        lcd.printString(buffer, 0, 2);
        lcd.refresh();
        
        ThisThread::sleep_for(1s);
    }
}