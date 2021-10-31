/*
 * GccApplication1.c
 *
 * Created: 5/3/2021 6:34:40 PM
 * Author : 8th
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define PWM_MIN 57					//need updating to 40% - 75%
#define PWM_MAX 122

int PWM, Mduty;	  // Control signal & state var

float kp = 0.0052615, ki = 627.5959, kd =  1.1652E-7;		   // PID gain 627.5959
float setpoint = 15, adc_value	= 0.0; 
float feedback = 0.0, error = 0.0, error1 = 0.0, last_error = 0.0;	  // PID var
float integral = 0.0, derivative = 0.0, proptional = 0.0;

void init_PLL(){
	PLLCSR |=(1<<PLLE);	   // PLL enable
	
	while ((PLLCSR & (1<<PLOCK)) == 0x00)
	{
		// WAIT FOR PLOCK SS 
	}
	PLLCSR |=(1<<PCKE);	   //Enable asynchronous mode
}

void init_PWM(){
		PORTB = 0;
		DDRB |= (1<< PB1)|(1<<PB3)|(0<<PB2);	   // PB0 AS PWM OUTPUT PIN
		TCCR1 = (1<<CTC1)|(1<<PWM1A)|(1<<COM1A1);
		OCR1C = 159;		   //set 400kHz	fsw
		TCCR1 |=(1<<CS10);	  //Start the timer
}

void setupADC(){
		ADMUX  = (1 << REFS0)|(1<<MUX0);
		ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
		DIDR0  = (1<< ADC1D);
}

void StartConversion(){
		ADCSRA |=(1<<ADSC);
}

void PID(){
	adc_value=ADC;
	feedback = (adc_value*20.0)/1023.0;
	
	error =  setpoint - feedback;
	error1 = error/500;
	
	if( abs(error1) > 0.196){
		error1 = 0;
	}else{
		integral = integral + error1;
		if(integral>0.18) integral = 0.18;
	}
	proptional = kp*error1;						  
	derivative = error1 - last_error;
	
	PWM =  proptional + ki*integral + kd*derivative;
	Mduty = PWM; 
	
	if (PWM > PWM_MAX) PWM = PWM_MAX;
	else if (PWM < PWM_MIN) PWM = PWM_MIN;
	
	OCR1A = PWM;
	last_error = error1;
}

int main(void)
{	
	cli();
	init_PLL();
	init_PWM();
	setupADC();
	
	while(1){
		StartConversion();
		PID();
	}
}