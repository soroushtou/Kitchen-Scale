/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 10/9/2020
Author  : 
Company : 
Comments: 


Chip type               : ATmega8A
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>
#include <delay.h>
// Declare your global variables here
#define HX711_DOUT    PINC.5
#define HX711_SCK     PORTC.4
#define tare          PINC.3
#define digit1        PORTB.0
#define digit2        PORTB.1
#define digit3        PORTB.6
#define digit4        PORTB.7
#define HX_COMPLEMENT 0x800000
#define HX_REF        0.360598//360.91549
unsigned long HX711_Read(void);
void get_scale(void);
void get_offset(void);
void sort_array(float b[], int size);
long Weight_Shiwu = 0,Weight_Maopi =0;
long HX711_Buffer = 0;
float scale = 0;
float array[41];
int b=0;
int scale_int = 0;
int segment[10] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};
void main(void)    
{
// Declare your local variables here
int i;
// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=Out 
DDRB=(1<<DDB7) | (1<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC6) | (0<<DDC5) | (1<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit6=T Bit5=0 Bit4=0 Bit3=P Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (1<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=(0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);

// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

       
      for(i = 1;i<10;i++){
      PORTD=segment[i] & 0b01111111;
      digit1 = 1;
      digit2 = 1;
      digit3 = 1;
      digit4 = 1;
      delay_ms(500);
      }    
      
get_offset();

while (1)
      {
      
      int a = 0;

      if(tare == 0){
      delay_ms(10);
      while(tare == 0);
      get_offset();
      }
      if(b>40) {sort_array(array,41);scale=array[20];if(scale < 0)scale=0;b=0;} 
      get_scale();
      scale_int = (int)scale;
      a = scale_int % 10;
      PORTD = segment[a];
      digit1 = 1;
      delay_ms(5);
      digit1 = 0;
      delay_ms(1);

      scale_int = scale_int / 10;
      a = scale_int % 10;
      PORTD = segment[a] & 0b01111111 ;
      digit2 = 1;
      delay_ms(5);
      digit2 = 0; 
      delay_ms(1);

      scale_int = scale_int / 10;
      a = scale_int % 10;
      PORTD = segment[a];
      digit3 = 1;
      delay_ms(5);
      digit3 = 0;
      delay_ms(1);

      scale_int = scale_int / 10;
      a = scale_int;
      PORTD = segment[a];
      digit4 = 1;
      delay_ms(5);
      digit4 = 0;
      delay_ms(1); 
      
      //delay_ms(250);
      b++;
}
}
unsigned long HX711_Read(void)
{
    unsigned long count;
    unsigned char i;

      HX711_DOUT=1;
      HX711_SCK=0;
      count=0;
      while(HX711_DOUT);
      for(i=0;i<24;i++)  //gain --> 128
        {
            HX711_SCK=1;
            count=count<<1;
            HX711_SCK=0;
            if(HX711_DOUT)
                count++;
        }
       HX711_SCK=1;
      count=count ^ HX_COMPLEMENT;//2,s Complement
      HX711_SCK=0;
      return(count);
}//HX711_Read

void get_scale(void)
{    
    HX711_Buffer = 0;

    HX711_Buffer = HX711_Read();
    HX711_Buffer = HX711_Buffer/100;
    Weight_Shiwu = HX711_Buffer;
    Weight_Shiwu = Weight_Shiwu - Weight_Maopi;
        
    Weight_Shiwu = ((float)Weight_Shiwu/HX_REF);

    array[b] = (float)Weight_Shiwu/3;  //weight in grams * 10
}

void get_offset(void)
{
    int i=0;

    HX711_Buffer = 0;

   	for( i = 0 ; i < 10 ; i++)
	{
		HX711_Buffer = HX711_Buffer + HX711_Read();
        delay_us(500);
	}
    HX711_Buffer = HX711_Buffer /10;     
    Weight_Maopi = HX711_Buffer/100;
}//get_offset

void sort_array(float b[], int size) {
    int i; 
    int o;
    for(i=0; i<(size-1); i++) {
        for( o=0; o<(size-(i+1)); o++) {
                if(b[o] > b[o+1]) {
                    int t = b[o];
                    b[o] = b[o+1];
                    b[o+1] = t;
                }
        }
    }
}