/**
 * main.c
 */

#include <inttypes.h>
#include <tm4c123gh6pm.h>
#include "GPIOConfig.h"

int cont = 0;
uint32_t temp_total = 0;

void InterruptSystick(void){
    cont++;
    if(cont == 100){
        cont=0;
    }
    temp_total++;
}

void PWM(int PORTA, int PINO, int taxa){

    if(cont<taxa){
        SetPino(PORTA,PINO,HIGH);
        return;
    }

    if(cont<100){
        SetPino(PORTA,PINO,LOW);
        return;
    }
}



int main(void){

    LigarPort(PORT_F);

    GPIOConfig(PORT_F, LED_RED, OUTPUT);
    GPIOConfig(PORT_F, LED_BLUE, OUTPUT);
    GPIOConfig(PORT_F, LED_GREEN, OUTPUT);

    SetDen(PORT_F, LED_GREEN);
    SetDen(PORT_F, LED_RED);
    SetDen(PORT_F, LED_BLUE);

    ConfigSysTick();
    TempoSysTick_us(20);

    SetPino(PORT_F,LED_RED,HIGH);
    SetPino(PORT_F,LED_BLUE,HIGH);


    int brilho = 0;
    uint32_t temp = 0;


    cont=0;
    while (1)
    {

        if((temp_total - temp) == 1000){
            temp = temp_total;
            brilho++;
        }

        if(brilho == 100){
            brilho=0;
        }


        PWM(PORT_F,LED_GREEN,brilho);
    }

}


