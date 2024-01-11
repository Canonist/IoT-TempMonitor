#include "mbed.h"

/*
Tämä ohjelma kalibroitu Leopardigekon lämpövaatimuksille
Oletetaan että mittaukset otetaan "ulkolämpötilasta", ei piilojen sisäpuolelta tai paistattelukiveltä
Improvisoitu ratkaisuja puuttuvaan ledimäärään.
*/

//analogitulo lämpöantureille
AnalogIn thermistor1(A0); //Oletetaan tämä Kylmä Pää
AnalogIn thermistor2(A1); //Oletetaan tämä Lämmin Pää

DigitalOut red_led(D4); //punanen ledi - Liian kuuma
DigitalOut light_led(D3); //vaalea ledi - Liian kylmä
DigitalOut green_led(D2); //vihreä ledi - OK lämmöt

int main() {
    float temp1, temp2;
    while(true) {
        /*red_led = 1;
        light_led = 1;
        green_led = 1;*/
        
        //lukublokki ja muunnos celsius asteiksi Rehellisesti: En ymmärrä tätä kunnolla... jotain jotain datasheetit. Yritys numero #5.
        temp1 = (thermistor1.read()*3.3)*((150-(-40)) / 3.3) + (-40);
        temp2 = (thermistor2.read()*3.3)*((150-(-40)) / 3.3) + (-40);
        
        //Kylmä yli 25C, kuuma yli 33C -> HOT WARNING
        if (temp1 > 25.0 || temp2 > 33.0) {
            red_led = 1;
            green_led = 0;
            light_led = 0;
        //Kylmä alle 21C, kuuma alle 32C -> COLD WARNING
        } else if (temp1 < 21.0 || temp2 < 32.0) {
            red_led = 0;
            green_led = 0;
            light_led = 1;
        //Molemmat sallituissa rajoissa -> All K
        } else {
            red_led = 0;
            green_led = 1;
            light_led = 0;
        }
        //Venataan 5 sekuntia - lämpötila ei muutu niin tiheästi elämässä!
        ThisThread::sleep_for(5000ms);
    }
}




