/* 
 * File:   Initialisation.h
 * Author: Michael
 *
 * Created on 24 June 2021, 12:39
 */

#ifndef INITIALISATION_H
#define	INITIALISATION_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h>

//#include <p30f2010.h>
   
void ADC_InitPoo(){
    
	AD1CON1 = 0;
	AD1CON2 = 0;	
	AD1CON3 = 0;
    
}

#define AN0_ENABLED
#define AN1_ENABLED
#define AN4_ENABLED
#define AN5_ENABLED

//icsp..!
//#define DISABLED_ICSP_ADC_LINES

#ifndef DISABLED_ICSP_ADC_LINES
#define AN2_ENABLED
#define AN3_ENABLED
#endif

void ADC_Init(){
    
    //changes:  ADCON1 becomes ADxCON1, etc
    //          ADCSSL becomes AD1CSSL
    //         CSSL0 ->  CSS0
    
    //ADPCFG becomes ANSELA,ANSELB, etc
    
    
	AD1CON1 = 0;
	AD1CON2 = 0;	
	AD1CON3 = 0;
    
    //Currently doing Automatic Sample and Automatic Conversion Sequence

	AD1CON2bits.CSCNA = 1; // Enable Channel Scanning


	AD1CON1bits.ASAM = 1;   // Enable Automatic Sampling
                            //Sampling begins immediately after last conversion. SAMP is set automatically

	/*	Conversion Time
		Must be a minium of 	TCONV = 12 ? TAD
	*/
	AD1CON1bits.SSRC = 0b111;		//111: Internal counter ends sampling and starts conversion (auto-convert)
    
    	/*
	If automatic sampling is enabled, the sampling time (TSMP) 
	taken by the ADC module is equal to the number of 
	TAD cycles defined by the SAMC<4:0> bits (ADxCON3<12:8>), 
	as shown by:	TSMP = SAMC<4:0> ? TAD
	*/

	AD1CON3bits.SAMC = 0b11111;	
	//11111 = 31 TAD ... ... 00000 = 0 TAD

	AD1CON3bits.ADCS = 0b00111111;	//1 TAD = 64 * Tcy
	//0b00111111 = 64*Tcy ... ... 0b00000000 = 1*Tcy

	//in effect, these are both prescalers

    
    #define ANSEL_0     ANSELAbits.ANSA0
    #define ANSEL_1     ANSELAbits.ANSA1
    
    #define ANSEL_2     ANSELBbits.ANSB0
    #define ANSEL_3     ANSELBbits.ANSB1
    #define ANSEL_4     ANSELBbits.ANSB2
    #define ANSEL_5     ANSELBbits.ANSB3


    #define AN_TRIS_0   TRISAbits.TRISA0
    #define AN_TRIS_1   TRISAbits.TRISA1
    #define AN_TRIS_2   TRISBbits.TRISB0
    #define AN_TRIS_3   TRISBbits.TRISB1
    #define AN_TRIS_4   TRISBbits.TRISB2
    #define AN_TRIS_5   TRISBbits.TRISB3
    

    #define ANALOG_ON 1

    //SMPI - specifies the number of sample/conversion operations that get completed before an interruption is generated. 
    //eg. So for 5 samples, we set SMPI to 5-1 = 4
    
    
#ifdef AN0_ENABLED
    //TRISBbits.TRISB0 = 1;
    AN_TRIS_0 = 1;
    
    ANSEL_0 = ANALOG_ON;
    
	AD1CSSLbits.CSS0=1; // Enable AN0 for scan
	AD1CON2bits.SMPI = 0; // Select 4 conversions between interrupt
	//(only 1 channel -> n-1)
#endif
    
#ifdef AN1_ENABLED
	//TRISBbits.TRISB1 = 1;
    AN_TRIS_1 = 1;
    ANSEL_1 = ANALOG_ON;
	AD1CSSLbits.CSS1=1; // Enable AN1 for scan
	AD1CON2bits.SMPI += 1;
#endif
	
#ifdef AN2_ENABLED    
	//TRISBbits.TRISB2 = 1;
    AN_TRIS_2 = 1;
    ANSEL_2 = ANALOG_ON;
	AD1CSSLbits.CSS2=1; // Enable AN2 for scan
	AD1CON2bits.SMPI += 1;
#endif

#ifdef AN3_ENABLED	
	//TRISBbits.TRISB3 = 1;
    ANSEL_3 = ANALOG_ON;
    AN_TRIS_3 = 1;
	AD1CSSLbits.CSS3=1; // Enable AN3 for scan
	AD1CON2bits.SMPI += 1;
#endif
	
#ifdef AN4_ENABLED    
	//TRISBbits.TRISB4 = 1
    ANSEL_4 = ANALOG_ON;;
    AN_TRIS_4 = 1;
	AD1CSSLbits.CSS4=1; // Enable AN4 for scan
	AD1CON2bits.SMPI += 1;
#endif
    
    
    #ifdef AN5_ENABLED    
	//TRISBbits.TRISB4 = 1
    ANSEL_5 = ANALOG_ON;;
    AN_TRIS_5 = 1;
	AD1CSSLbits.CSS5=1; // Enable AN5 for scan
	AD1CON2bits.SMPI += 1;
#endif



	IFS0bits.AD1IF = 0; 	// Clear the A/D interrupt flag bit
	IEC0bits.AD1IE = 1; 	// Do Not Enable A/D interrupt
	AD1CON1bits.ADON = 1; 	// Turn on the A/D converter
}






//SPI1CON -> SPI1CON1

void SPI_Init(unsigned int a, unsigned int b, unsigned int c){

#ifdef PIC30FUSING
	TRISEbits.TRISE8 = 0;		//output for clock
	TRISFbits.TRISF3 = 0;		//output for SDO1
	TRISFbits.TRISF2 = 0;		//output for CS 
#else
    TRISBbits.TRISB7 = 0;		//output for clock
	TRISBbits.TRISB8 = 0;		//output for SDO1
	TRISBbits.TRISB9 = 0;		//output for CS 
    
    //RP39 sck
    //RP40 sdo
    //no need to use pps for SPI1 -> they are hard-wired to same pins! its just SPI2 that uses PPS
#endif

	SPI1CON1 = 0;


	/*
	PPRE<1:0>: Primary Prescale (Master Mode) bits
	11 = Primary prescale 1:1
	10 = Primary prescale 4:1
	01 = Primary prescale 16:1
	00 = Primary prescale 64:1

	SPRE<2:0>: Secondary Prescale (Master Mode) bits
	(Supported settings: 1:1, 2:1 through 8:1, all inclusive)
	111 = Secondary prescale 1:1
	110 = Secondary prescale 2:1
	...
	000 = Secondary prescale 8:1
	*/
	
	
	SPI1CON1bits.SPRE = 0b110;		//1:1 is 0b111	//in one place (migration notes) it says 111 is reserved, but no mention in datasheet?!
	SPI1CON1bits.PPRE = 0b10;		//1:1 is 0b11
									//110 is x2
                                    //10 is x4

	SPI1CON1bits.CKE = 1;


	

	SPI1CON1bits.MSTEN = 1; 	//Master Mode Enabled
	SPI1STATbits.SPIEN = 1; //Enable SPI Module
	
	}


/*
 Note - one big difference in output compare in dspic30f/dspic33f VS dspic33e!
 
 dspic30f/33f
  OC1RS and OC2RS set the duty cycle
  OC1R and OC2R is the duty cycle but is not written to directly. Gets loaded from OC1RS   
  
 dspic33e
 OC1R and OC2R set the duty cycle 
 OC1RS and OC2RS set the period if SYNCSEL set to OCxRS compare event
 
 */





#ifdef	__cplusplus
}
#endif

#endif	/* INITIALISATION_H */

