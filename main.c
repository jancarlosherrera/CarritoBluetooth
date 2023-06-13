#include<stdbool.h>
#include<stdint.h>
#include "inc/tm4c1294ncpdt.h"

uint32_t i, Cta,DF,DA,t, DD,DI,l;
int SensorFrontal();
int SensorTrasero();
int SensorDerecho();
int SensorIzquierdo();
//void delayMs(uint_32);


int main(void) {
SYSCTL_RCGCGPIO_R = 0x3F18; //habilita Reloj del PTO. P, E Y N
i = SYSCTL_PRGPIO_R;        //retardo para que el reloj se habilite

HC05_init();
Bluetooth_Write_String("BIENVENIDO\n");
SysCtlDelay(10000);
Bluetooth_Write_String("Cargando\n");
SysCtlDelay(1000000);
Bluetooth_Write_String("[==");
SysCtlDelay(100000);
Bluetooth_Write_String("===");
SysCtlDelay(100000);
Bluetooth_Write_String("===");
SysCtlDelay(100000);
Bluetooth_Write_String("===");
SysCtlDelay(100000);
Bluetooth_Write_String("===]");
SysCtlDelay(100000);


GPIO_PORTN_DIR_R |= 0x03;
GPIO_PORTN_DEN_R |= 0x03;
GPIO_PORTE_AHB_DIR_R =  0B000111;
GPIO_PORTE_AHB_DEN_R |= 0B111111;
GPIO_PORTP_DIR_R |= 0x01;
GPIO_PORTP_DEN_R |= 0x03;
GPIO_PORTN_DATA_R &= ~0x03;     // Apaga LED's
GPIO_PORTE_AHB_DATA_R &=~ 0x07; //apago la señal de disparo del sensor
GPIO_PORTL_DIR_R |= 0x0F;
GPIO_PORTL_DEN_R |= 0x0F;

//Declarar puerto L para motores
//Declarar puerto D luces y emergencia
l=0;
while(1){

//Posición inicial.

Posicion();


/*
char c = Bluetooth_Read();
        switch(c){
        case 'A':
            AVANZA();
            break;
        case 'R':
            RETROCEDE();
            break;
        case 'D':
            GiroDer();
            break;
        case 'I':
           GiroIzq();
           break;
        case 'F':
           find();
           break;
        case 'E':
            luces();
            break;

        }

*/






}}

int AVANZA(){
while (DF>25){

//----PULSO DE DISPARO  ------------
      GPIO_PORTE_AHB_DATA_R |= 0x01;  //nivel alto en trig
      SysCtlDelay(100);  //  Retardo > 10us
      GPIO_PORTE_AHB_DATA_R &=~ 0x01; //nivel bajo en trig
//----------------------------------

while ((GPIO_PORTE_AHB_DATA_R & 0x08) == 0);    //espero nivel alto de echo

//---- CUENTA ANCHO DE PULSO  ----------
  Cta = 0;
  do{
             Cta++;
             t++;
             DF=(Cta*10)/(292/2);
             GPIO_PORTL_DATA_R = 0X0A;
         }while ( ((GPIO_PORTE_AHB_DATA_R & 0x08)==0x08) & (Cta  < 0x0000FFFF));

}
GPIO_PORTL_DATA_R = 0X00;
}

int RETROCEDE(){
while (DA>20){

    GPIO_PORTN_DATA_R ^= 0X01;  //FLASH LED D2 (PN0)
    SysCtlDelay(2666666);

    //----PULSO DE DISPARO  ------------
    GPIO_PORTP_DATA_R |= 0x01;  //nivel alto en trig
    SysCtlDelay(100);  //  Retardo > 10us
    GPIO_PORTP_DATA_R &=~ 0x01; //nivel bajo en trig
    //----------------------------------

    while ((GPIO_PORTP_DATA_R & 0x02) == 0);    //espero nivel alto de echo

    //---- CUENTA ANCHO DE PULSO  ----------
    Cta = 0;
    do{
     Cta++;
     t++;
     DA=(Cta*10)/(292/2);
     GPIO_PORTL_DATA_R = 0X05;
    }while ( ((GPIO_PORTP_DATA_R & 0x02)==0x02) & (Cta  < 0x0000FFFF));

}
GPIO_PORTL_DATA_R = 0X00;
}


int GiroIzq(){
   Posicion();
   while(DD>(DF-5)){
    SensorDerecho();
   GPIO_PORTL_DATA_R = 0X09;
   }
   GPIO_PORTL_DATA_R = 0X00;
}

int GiroDer(){
   Posicion();
   while(DI>(DF-5)){
   SensorIzquierdo();
   GPIO_PORTL_DATA_R = 0X06;
   }
   GPIO_PORTL_DATA_R = 0X00;
}

int find(){
    int aux=0;
    while(aux<50){
   GPIO_PORTD_AHB_DATA_R = 0x03;
   SysCtlDelay(10000);
    GPIO_PORTD_AHB_DATA_R = 0x00;
    SysCtlDelay(10000);
    aux++;
    }
GPIO_PORTD_AHB_DATA_R = 0x00;
}

int luces(int l){
    switch(l){
    case 0:
        GPIO_PORTD_AHB_DATA_R = 0x02;
        l=1;
        break;
    case 1:
        GPIO_PORTD_AHB_DATA_R = 0x00;
        l=0;
        break;
    }
    GPIO_PORTD_AHB_DATA_R = 0x02;
}
int SensorFrontal(){
    while (t<2000){

                      GPIO_PORTN_DATA_R ^= 0X01;  //FLASH LED D2 (PN0)
                      SysCtlDelay(2666666);

    //----PULSO DE DISPARO  ------------
                      GPIO_PORTE_AHB_DATA_R |= 0x01;  //nivel alto en trig
                      SysCtlDelay(100);  //  Retardo > 10us
                      GPIO_PORTE_AHB_DATA_R &=~ 0x01; //nivel bajo en trig
    //----------------------------------

              while ((GPIO_PORTE_AHB_DATA_R & 0x08) == 0);    //espero nivel alto de echo

    //---- CUENTA ANCHO DE PULSO  ----------
                  Cta = 0;
                  do{
                             Cta++;
                             t++;
                             DF=(Cta*10)/(292/2);
                         }while ( ((GPIO_PORTE_AHB_DATA_R & 0x08)==0x08) & (Cta  < 0x0000FFFF));

              }

}

int SensorIzquierdo(){
    while (t<2000){

                      GPIO_PORTN_DATA_R ^= 0X01;  //FLASH LED D2 (PN0)
                      SysCtlDelay(2666666);

    //----PULSO DE DISPARO  ------------
                      GPIO_PORTE_AHB_DATA_R |= 0x02;  //nivel alto en trig
                      SysCtlDelay(100);  //  Retardo > 10us
                      GPIO_PORTE_AHB_DATA_R &=~ 0x02; //nivel bajo en trig
    //----------------------------------

              while ((GPIO_PORTE_AHB_DATA_R & 0x10) == 0);    //espero nivel alto de echo

    //---- CUENTA ANCHO DE PULSO  ----------
                  Cta = 0;
                  do{
                             Cta++;
                             t++;
                             DI=(Cta*10)/(292/2);
                         }while ( ((GPIO_PORTE_AHB_DATA_R & +0x10)==0x10) & (Cta  < 0x0000FFFF));

              }

}

int SensorDerecho(){
    while (t<2000){

                      GPIO_PORTN_DATA_R ^= 0X01;  //FLASH LED D2 (PN0)
                      SysCtlDelay(2666666);

    //----PULSO DE DISPARO  ------------
                      GPIO_PORTE_AHB_DATA_R |= 0x04;  //nivel alto en trig
                      SysCtlDelay(100);  //  Retardo > 10us
                      GPIO_PORTE_AHB_DATA_R &=~ 0x04; //nivel bajo en trig
    //----------------------------------

              while ((GPIO_PORTE_AHB_DATA_R & 0x20) == 0);    //espero nivel alto de echo

    //---- CUENTA ANCHO DE PULSO  ----------
                  Cta = 0;
                  do{
                             Cta++;
                             t++;
                             DD=(Cta*10)/(292/2);
                         }while ( ((GPIO_PORTE_AHB_DATA_R & 0x20)==0x20) & (Cta  < 0x0000FFFF));

              }

}

int SensorTrasero(){
    while (t<2000){

                      GPIO_PORTN_DATA_R ^= 0X01;  //FLASH LED D2 (PN0)
                      SysCtlDelay(2666666);

    //----PULSO DE DISPARO  ------------
                      GPIO_PORTP_DATA_R |= 0x01;  //nivel alto en trig
                      SysCtlDelay(100);  //  Retardo > 10us
                      GPIO_PORTP_DATA_R &=~ 0x01; //nivel bajo en trig
    //----------------------------------

              while ((GPIO_PORTP_DATA_R & 0x02) == 0);    //espero nivel alto de echo

    //---- CUENTA ANCHO DE PULSO  ----------
                  Cta = 0;
                  do{
                             Cta++;
                             t++;
                             DA=(Cta*10)/(292/2);
                         }while ( ((GPIO_PORTP_DATA_R & 0x02)==0x02) & (Cta  < 0x0000FFFF));

              }

}
int Posicion(){
    t=0;
    SensorFrontal();
    t=0;
    SensorTrasero();
    t=0;
    SensorIzquierdo();
    t=0;
    SensorDerecho();
}

/*void  delayMs ( uint32_t ui32Ms) {

    // 1 ciclo de reloj = 1 / SysCtlClockGet() segundo
    // 1 SysCtlDelay = 3 ciclo de reloj = 3 / SysCtlClockGet() segundo
    // 1 segundo = SysCtlClockGet() / 3
    // 0.001 segundo = 1 ms = SysCtlClockGet() / 3 / 1000

    SysCtlDelay (ui32Ms * ( SysCtlClockGet ()/ 3 / 1000 ));
}*/

void HC05_init(void)
{


    SYSCTL_RCGCUART_R |= 0x10;  /* enable clock to UART4 */
   //SYSCTL_RCGCGPIO_R |= 0x200;  /* enable clock to PORTK for PK0/Rx and RK1/Tx */
    Delay(1);
    /* UART0 initialization */
            UART4_CTL_R = 0;         /* UART4 module disable */
           UART4_IBRD_R = 104;      /* for 9600 baud rate, integer = 104 */
           UART4_FBRD_R = 11;       /* for 9600 baud rate, fractional = 11*/
           UART4_CC_R = 0;          /*select system clock*/
           UART4_LCRH_R = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
           UART4_CTL_R = 0x301;     /* Enable UART4 module, Rx and Tx */
          // UART4_DR_R = 0;
           /* UART4 TX4 and RX4 use PK0 and PK1. Configure them digital and enable alternate function */
                   GPIO_PORTK_DEN_R    = 0x03;      /* set PK0 and PK1 as digital */
                   GPIO_PORTK_AFSEL_R = 0x03;    /* Use PK0,PK1 alternate function */
                   GPIO_PORTK_AMSEL_R  = 0;    /* Turn off analg function*/
                   GPIO_PORTK_PCTL_R = 0x00000011;     /* configure PK0 and PK1 for UART */
}

char Bluetooth_Read(void)
{
    char data;
      while((UART4_FR_R & (1<<4)) != 0); /* wait until Rx buffer is not full */

    data = UART4_DR_R ;      /* before giving it another byte */
    return (unsigned char) data;
}

void Bluetooth_Write(unsigned char data)
{
    while((UART4_FR_R & (1<<5))!= 0); /* wait until Tx buffer not full */
    UART4_DR_R = data;                  /* before giving it another byte */
}

void Bluetooth_Write_String(char *str)
{
  while(*str)
    {
        Bluetooth_Write(*(str++));
    }
}

void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for(i=0; i< counter; i++);
}
