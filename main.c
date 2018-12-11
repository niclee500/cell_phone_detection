#include <c8051_SDCC.h>
#include <stdio.h>
#include <stdlib.h>

/*

The following code is used for the Passive Frequency Detection Project, by converting the 
LED output to a seven segment display output. This was done in order to make the board
more user-friendly. 

The C code uses a 8051 Microcontroller along with the circuit schematic outlined for the 
Frequency Detection project. The code works by converting the voltage value (0V-2.4V) to 
a digital reading range (0-255). After that conversion is finished, another conversion can be 
made to convert the 0-255 value to a correct cell-phone frequency range.

*/ 

void Port_Init(void);  // Port Initialization used across Ports 0 and 1.
void ADC_Init(void);  // ADC Initialization uses 2.4V ref voltage and gain of 1.
void PCA_Init(void);

unsigned char read_AD_input(void); // Converts between voltage to digital value.
void PCA_ISR(void) __interrupt 9;
unsigned int RangetoFreq(unsigned char range);

unsigned char AD_Value; // Holds the AD value from 0-256.
unsigned char display_flag = 0; // Times conversions.
unsigned int counter; // global counter.
unsigned int range;  //AD range
unsigned int FREQUENCY_MAX = 3000;

void main(void)
{
	if (display_flag)
	{
		display_flag = 0;
		AD_Value = read_AD_input();

	}
}

//-----------------------------------------------------------
// AD Range to frequency
//-----------------------------------------------------------

unsigned int RangetoFreq(unsigned char range)
{
	unsigned int calculation;
	unsigned int ZerotoNine;
	calculation = (float)((float)range/(float)256) * FREQUENCY_MAX;
	ZerotoNine = FREQUENCY_MAX/10;

	if (ZerotoNine < )
}

//-----------------------------------------------------------
// Port Initialization
//-----------------------------------------------------------

void Port_Init(void)
{
	P0MDOUT |= 0xFF;   // Seven Segment requires 8 lines from the EVB as digital output.
	P1MDIN &= ~0x01;   // Will use Port 1 Pin 0 as analog input mode.
	P1MDOUT &= ~0x01;  // Sets Port 1 Pin 0 to input (open-drain mode).
	P1 |= 0x01;        // Sets impedence on 1.0 to high.
}

//-----------------------------------------------------------
// ADC Initialization
//-----------------------------------------------------------

void ADC_Init(void)
{
	REF0CN = 0x03;  // Set Vref to 2.4V.
	ADC1CN = 0x80;  // Enables AD conversion.
	ADC1CF = 0x01;  // Sets AD converter gain to 1.
}

//-----------------------------------------------------------
// PCA Initialization
//-----------------------------------------------------------

void PCA_Init(void)
{
	PCA0MD = 0x89;  // Enables CF interrupt & SYSCLK.
	PCA0CN = 0x40;  // Enable PCA counter.
	EIE1 |= 0x08;   // Enable PCA interrupt.
	EA = 1;			// Enable global interrupts.
}

//-----------------------------------------------------------
// ADC Conversion
//-----------------------------------------------------------

unsigned char read_AD_input(void)
{
	AMX1SL = 0;       // Sets P1.0 for analog conversion
    ADC1CN &= ~0x20;  // Clear the “Conversion Completed” flag 
    ADC1CN |= 0x10;   // Initiate A/D conversion 
    while ((ADC1CN & 0x20) == 0x00) { printf(""); }  //Wait for conversion to complete 
    return ADC1;  // Return digital value in ADC1 register 
}

//-----------------------------------------------------------
// PCA Conversion
//-----------------------------------------------------------

void PCA_ISR(void)
{
	if (CF)
	{
		CF = 0;  //Must clear flag by software
		counter++;  // global counter running on 20ms/overflow
		if (counter >= 4) // 80ms timer
		{
			display_flag = 1;  //Starts main AD conversion
			counter = 0;
		}
	}
	PCA0CN &= 0x40;
}