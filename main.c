
/* 

 * I dont think GetEnvOutputExpo is working quite correctly so i have left it out for now. the envelope output for Mode C, subMode 0 and 1 output a linear wav
 
    ---			MCLR		1		28	AVdd				---
 	LFO Rate	AN0/RA0		2		27	AVss				---
 	LFO Wave	AN1/RA1		3		26	RB15                Input: Reset LFO		
    Att     	AN2/RB0		4		25	RB14				Input: Clock Div
 	Rel 		AN3/RB1		5		24	RB13				Input: Clock Div 
 	Mode		AN4/RB2		6		23	RB12				Input: Switch Outputs
 	Sub-Mode	AN5/RB3		7		22	RB11				unused
	---			Vss			8		21	RB10				LED Out
	---			OSC			9		20	Vcap				---
	--- 		OSC			10		19	Vss					---
	Gate In		RB4 		11		18	RB9					CS
	Clock Out	RA4         12		17	RB8/SDO1			SDO					
	---			Vdd			13		16	RB7/SCK				SCK
	unused		RB5/OC2		14		15	RB6/OC1				unused
 
 * AN0 to AN5 used as Analogue Inputs
 */ 

        
      
// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect Bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSS2 = OFF               // Boot Segment Control Bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect Bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect Bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = DISABLE        // Alternate Interrupt Vector Table Disable Bit  (Disable Alternate Vector Table)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Code Flash Page Address Limit Bits (Boot Segment Flash Page Address Limit (0-0x1FFF))

// FOSCSEL
#pragma config FNOSC = PRIPLL           // Initial oscillator Source Selection Bits (Primary Oscillator with PLL module (XT + PLL, HS + PLL, EC + PLL))
#pragma config IESO = OFF               // Two Speed Oscillator Start-Up Bit (Start up device with user selected oscillator source)

// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Mode Select Bits (XT Crystal Oscillator mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin I/O Function Enable Bit (OSC2 is clock output)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration Bit (Allow Multiple reconfigurations)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode Bits (Both Clock Switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = ON              // PLL Lock Enable Bit (Clock switch to PLL source will wait until the PLL lock signal is valid)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler Bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler Bit (1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable Bits (WDT and SWDTEN Disabled)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable Bit (Watchdog timer in Non-Window Mode)
#pragma config WDTWIN = WIN25           // Watchdog Window Select Bits (WDT Window is 25% of WDT period)

// FPOR
#pragma config BOREN0 = ON              // Brown Out Reset Detection Bit (BOR is Enabled)

// FICD
#pragma config ICS = PGD2               // ICD Communication Channel Select Bits (Communicate on PGEC3 and PGED3)

// FDMTINTVL
#pragma config DMTIVTL = 0xFFFF         // Lower 16 Bits of 32 Bit DMT Window Interval (Lower 16 bits of 32 bit DMT window interval (0-0xFFFF))

// FDMTINTVH
#pragma config DMTIVTH = 0xFFFF         // Upper 16 Bits of 32 Bit DMT Window Interval (Upper 16 bits of 32 bit DMT window interval (0-0xFFFF))

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF))

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF))

// FDMT
#pragma config DMTEN = DISABLE          // Dead Man Timer Enable Bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config PWMLOCK = ON             // PWM Lock Enable Bit (Certain PWM registers may only be written after key sequence)
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pins Selection Bit (I2C1 mapped to SDA1/SCL1 pins)

// FALTREG
#pragma config CTXT1 = NONE             // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 1 (Not Assigned)
#pragma config CTXT2 = NONE             // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 2 (Not Assigned)

#include <xc.h>
#include <p33EV32GM102.h>

#include "Initialisation.h"
#include <limits.h>

#include "lfo.h"
#include "ar_envelope.h"
#include "eventgenerator.h"

#define FOSC    80
#define FCY     FOSC/2

#define INPUT_LFO_RESET             PORTBbits.RB15
#define INPUT_CLOCK_OUT_DIV_0       PORTBbits.RB14
#define INPUT_CLOCK_OUT_DIV_1       PORTBbits.RB13
#define INPUT_SWAP_OUTPUTS          PORTBbits.RB12

//Inverted Gate Outputs
#define H 0
#define L 1

#define SWITCH_B_WIRED_OPPOSITE_DIR         //cos incorrectly wired atm!


#define ACC_HALF                ULONG_MAX>>1
#define ACC_ONE_QUARTER         ULONG_MAX>>2
#define ACC_THREE_QUARTERS      3*(ULONG_MAX>>2)


#define ACC_ONE_EIGTHS          1*(ULONG_MAX>>3)
#define ACC_TWO_EIGTHS          2*(ULONG_MAX>>3)
#define ACC_THREE_EIGTHS        3*(ULONG_MAX>>3)
#define ACC_FOUR_EIGTHS         4*(ULONG_MAX>>3)
#define ACC_FIVE_EIGTHS         5*(ULONG_MAX>>3)
#define ACC_SIX_EIGTHS          6*(ULONG_MAX>>3)
#define ACC_SEVEN_EIGTHS        7*(ULONG_MAX>>3)


/*
 Three control registers are associated with the ICN
functionality of each I/O port. The CNENx registers
contain the ICN interrupt enable control bits for each of
the input pins. Setting any of these bits enables an ICN
interrupt for the corresponding pins.
 */




#define INPUT_GATE              PORTBbits.RB4
#define OUTPUT_GATE             PORTAbits.RA4

#define OUTPUT_LED             PORTBbits.RB10

#define ALT_ADC_PLACE

volatile unsigned int lastGateLevel = 0;


extern void MCP4822_DAC_Convert_A();
extern void MCP4822_DAC_Convert_B();

extern unsigned int potValuesH[];
extern unsigned int potValuesL[];

extern unsigned int incsH_lfo[];
extern unsigned int incsL_lfo[];


volatile    unsigned int USE_BIPOLAR = 1;

extern    unsigned long  masterClock;


LFO lfoMain;
LFO lfoExtra;

Env env;
Event event;

//Controlled by Panel Controls
volatile unsigned int clockOutMultiplier = 1;

volatile unsigned int envSustainOn = 1;

volatile unsigned  int lfoReset = 0;	

volatile unsigned int lfo2Synced = 0;        //only applicable when Gate/Clock In set to Clock.
                                            //I can choose to have the 2nd lfo free running

volatile unsigned int lfo2RateSynced = 0;


volatile unsigned int lfo2_rawEnvelopeOut = 0;  


unsigned int clockOutLevel = H;

volatile unsigned int lfoUpdateDivisor = 1;
volatile unsigned int envUpdateDivisor = 1;


volatile unsigned int swapAB = 0;
volatile unsigned int lfo2RateMultiplier = 2;

volatile unsigned int envelopeEnabled = 1;


#define MODE_A  0           //Master LFO mode. Output B is a unipolar copy
#define MODE_B  1           //Dual LFO mode. Output B is another lfo that can be synced
#define MODE_C  2           //Single LFO, Single 1-Shot

volatile unsigned int mode = MODE_A;
volatile unsigned int subMode = 0;


volatile signed int switchA = 0;            //3 pos (-1,0,+1))
volatile signed int switchB = 0;            //3 pos (-1,0,+1))

volatile unsigned int modulateLfoWithEnv = 0;

///////////////////////////////////////////
//Not exposed to user
unsigned int dacValueA = 4000;
unsigned int digital_highByte = 0;
unsigned int digital_lowByte = 0;


unsigned int dacValueB = 0;
unsigned int dacValueB_highByte = 0;
unsigned int dacValueB_lowByte = 0;


unsigned int e = 0;
unsigned int ff = 0;

volatile unsigned int updateFlag = 0;


void MainProcessing();
void ManualGateCheck();


void __attribute__ ((interrupt, no_auto_psv)) _DefaultInterrupt(void){
    int x = 2;
    x++;
 
    if(INTCON1bits.ADDRERR){
     
    }
}

void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void){
    
    //i only have one pin enabled for Change Notification...
    if(INPUT_GATE){
        //start env attack
        //or grab time elapsed to work out tempo for synchronisation purposes
        
        if(envelopeEnabled==1){
            //EnvOn(&env);
        }
        else {
            
        }
        
    }
    else {
        if(envelopeEnabled==1){
            //EnvOff(&env);
        }
        else {
            
        }
        //start release (if sustain off)
    }
    IFS1bits.CNIF = 0;

}

void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void){

    updateFlag = 1;
	IFS0bits.T2IF = 0; /* Clear Left Channel Interrupt Flag */
   
}

unsigned int pots[6];

unsigned int lfoParams[6];
#define LFO_P_RATE  0
#define LFO_P_WAVE  1



void __attribute__ ((interrupt, no_auto_psv)) _AD1Interrupt(void){

	unsigned long f;
	unsigned int t;
    
    //updateFlag = 1;
    
    lfoParams[LFO_P_RATE] = pots[0] = ADC1BUF0;
    
    lfoParams[LFO_P_WAVE] = pots[1] = ADC1BUF1;;
    

    //Note - pot 3 comes before pot 2 because they are wired in the wrong order
    pots[3] = ADC1BUF2;

    pots[2] = ADC1BUF3;


    

    e = ADC1BUF4;           //temporarily changed! because only scanning 2 ATM
    f = e;

    unsigned int p = 0;
    switchA = +1;
    if(f > 1000){
        p = 100;
        switchA = 0;
    }
    else if(f > 400){
        p = 50;
        switchA = -1;
    }

    if(switchA == 0)            mode = MODE_B;
    else if(switchA == +1)      mode = MODE_C;
    else                        mode = MODE_A;


    
    ff = ADC1BUF5;           //temporarily changed! because only scanning 2 ATM
    f = ff;
    p = 0;
    switchB = +1;
    if(f > 1000){
        p = 100;
        switchB = 0;
    }
    else if(f > 400){
        p = 50;
        switchB = -1;
    }

    t = f>>2;       //510,1023,0

#ifdef SWITCH_B_WIRED_OPPOSITE_DIR
if(switchB==+1)
    switchB = -1;
else if(switchB==-1)
    switchB = +1;
#endif
      
    IFS0bits.AD1IF = 0;
    
}


unsigned int lastLevel = 0;

void MainLoop(){
       
    if(updateFlag==1){

        updateFlag = 0;
        
        ManualGateCheck();
        MainProcessing();

    }
    
}

void MainProcessing(){
    
    
    
    
    if(INPUT_LFO_RESET){
        lfoReset = 1;
    }
    else {
        lfoReset = 0;
    }
    
    if(INPUT_SWAP_OUTPUTS){
        swapAB = 0; //OUTPUT_GATE = H;            //temporariyl using as overload
    }
    else {
        swapAB = 1;
    }
    
    if(INPUT_CLOCK_OUT_DIV_0 == 0){
        clockOutMultiplier = 4;
    }
    else if(INPUT_CLOCK_OUT_DIV_1 == 0){
        clockOutMultiplier = 1;
    }
    else {
        clockOutMultiplier = 2;
    }
    
    if(switchB==0){             //-1 at top. 0 at middle. +1 at bottom
        subMode = 1;
    }
    else if(switchB==+1){
        subMode = 0;
    }
    else {
        subMode = 2;
    }
    
    if(envSustainOn == 0)       env.mode = ENV_SUSTAIN_OFF;  
    else                        env.mode = ENV_SUSTAIN_ON;    
    
    
    
    event.mode = ENV_SUSTAIN_OFF;
    
    
    
    
    
    
    
    
    
    

    unsigned int qq = incsH_lfo[255-(lfoParams[LFO_P_RATE]>>2)];
    unsigned int ww = incsL_lfo[255-(lfoParams[LFO_P_RATE]>>2)];
    
    lfoMain.rate = (qq<<8) + ww;
  

    lfoMain.waveform = 7-(lfoParams[LFO_P_WAVE]>>7);    //10 bit to 3 bit (8 values))
         
    if(lfo2RateMultiplier <0 ) lfo2RateMultiplier = 1;
    else if(lfo2RateMultiplier >4 ) lfo2RateMultiplier = 4;
    
    
    unsigned int t;
    
    t = 255-(pots[2]>>2);
    env.attackInc = ((unsigned long)potValuesH[t]<<16) + potValuesL[t];

    
    t = 255-(pots[3]>>2);
    env.decayInc = ((unsigned long)potValuesH[t]<<16) + potValuesL[t];
    
    
    
    
    t = 0;
    event.attackInc = ((unsigned long)potValuesH[t]<<16) + potValuesL[t];
    t = 255-(pots[2]>>2);
    t = 255 - t;
    event.decayInc = ((unsigned long)potValuesH[t]<<16) + potValuesL[t];
    
       
    switch(mode){
        
        case MODE_A:{
            
        }break;
        
        case MODE_B:{
            
            if(subMode == 0){           //sync on
                
                lfo2Synced = 1;
                        
                //lfoExtra.rate =  lfoMain.rate * (1+((1023-pots[2])>>8));    //10 bit to 2 bit (4 values))
                
                unsigned int r =  ((1023-pots[2])>>7);          //10>>7 = 3bits = 8
                /*
                if(r==0)   rate = 0.25
                        r == 1      rate = 0.5
                        r == 2      rate = 1
                        r == 3      rate = 1 (+90)
                        r == 4      rate = 1 (+180)
                        r == 5      rate = 1 (+270)
                        r==6        rate = 2    
                        r==7        rate = 4
                 * */
                switch(r){
                    case 0:{
                        lfoExtra.offset = 0;
                        lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate >> 2;
                    }break;
                    
                   case 1:{
                       lfoExtra.offset = 0;
                       lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate >> 1;
                    }break;
                                      
                   case 2:{
                       lfoExtra.offset = 0;
                       lfo2RateSynced = 1;
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                     case 3:{
                         lfoExtra.offset = 90;
                         lfo2RateSynced = 1;
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                    case 4:{
                        lfoExtra.offset = 180;
                        lfo2RateSynced = 1;
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                    case 5:{
                        lfoExtra.offset = 270;
                        lfo2RateSynced = 1;
                   
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                    case 6:{
                        lfoExtra.offset = 0;
                        lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate << 1;
                    }break;
                                       
                    case 7:{
                        lfoExtra.offset = 0;
                        lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate << 2;
                    }break;
                }
                        
                
                
                lfoExtra.waveform = 7-(pots[3]>>7);    //10 bit to 3 bit (8 values))
                
                //lfoExtra.waveformBank = 0;  
            }
            else if(subMode == 1){      //sync off
                
                lfo2Synced = 0;
                
                unsigned int qq = incsH_lfo[255-(pots[2]>>2)];
                unsigned int ww = incsL_lfo[255-(pots[2]>>2)];

                lfoExtra.rate = (qq<<8) + ww;

                lfoExtra.waveform = pots[3]>>7;    //10 bit to 3 bit (8 values))
            }
            else {              //sync on
                
lfo2Synced = 1;
                        
                //lfoExtra.rate =  lfoMain.rate * (1+((1023-pots[2])>>8));    //10 bit to 2 bit (4 values))
                
                unsigned int r =  ((1023-pots[2])>>7);          //10>>7 = 3bits = 8
                /*
                if(r==0)   rate = 0.25
                        r == 1      rate = 0.5
                        r == 2      rate = 1
                        r == 3      rate = 1 (+90)
                        r == 4      rate = 1 (+180)
                        r == 5      rate = 1 (+270)
                        r==6        rate = 2    
                        r==7        rate = 4
                 * */
                switch(r){
                    case 0:{
                        lfoExtra.offset = 0;
                        lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate >> 2;
                    }break;
                    
                   case 1:{
                       lfoExtra.offset = 0;
                       lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate >> 1;
                    }break;
                                      
                   case 2:{
                       lfoExtra.offset = 0;
                       lfo2RateSynced = 1;
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                     case 3:{
                         lfoExtra.offset = 90;
                         lfo2RateSynced = 1;
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                    case 4:{
                        lfoExtra.offset = 180;
                        lfo2RateSynced = 1;
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                    case 5:{
                        lfoExtra.offset = 270;
                        lfo2RateSynced = 1;
                   
                        lfoExtra.rate = lfoMain.rate;
                    }break;
                    
                    case 6:{
                        lfoExtra.offset = 0;
                        lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate << 1;
                    }break;
                                       
                    case 7:{
                        lfoExtra.offset = 0;
                        lfo2RateSynced = 0;
                        lfoExtra.rate = lfoMain.rate << 2;
                    }break;
                }
                        
                
                
                lfoExtra.waveform = 8+7-(pots[3]>>7);    //10 bit to 3 bit (8 values))
                
                //if(lfoExtra.waveform>1)         //if 4,5,6,7.. make it 8,9,10,11
                //    lfoExtra.waveform+=6;
                //lfoExtra.waveformBank = 1;  
            }

        }break;
        
        case MODE_C:{
            if(subMode == 2){
                event.waveform = 7-(pots[3]>>7);
            }
        }break;
    }
    
    

    UpdateLfoAndMasterClock(&lfoMain);
    
    UpdateLfo(&lfoExtra);
    
    if(lfo2Synced==1)
        if(lfo2RateSynced==1)
            lfoExtra.acc = lfoMain.acc;             //Tricky problem here. How to keep them both in sync? I only want their accs to be equal if rates are the same
                                                        //otherwise acc 2 will equal acc 1 MULTIPLY by k.... perhaps only sync them to zero upon mode change and leave them be ?
                                                        
        
        
    UpdateEnv(&env);
    unsigned int envLevel = GetEnvOutput(&env);
    
    UpdateEvent(&event);
    
#define USE_NEW_WAY
    
   
#ifndef USE_NEW_WAY    
    if(lfoMain.overflowFlag != 0){
        clockOutLevel = H;
        OUTPUT_GATE = H;
    }
    else if(clockOutLevel == H ){
        
        if(lfoMain.acc >  (ULONG_MAX>>1) ){     //from limits.h
            
            clockOutLevel = L;
            OUTPUT_GATE = L;
        }
        
    }
#else    
    
    static unsigned int lastQuadrant = 0;
    

    
    if(mode == MODE_A){
       
        if(subMode==0){
            modulateLfoWithEnv = 1;
            envSustainOn = 1;
        }
        else if(subMode==1){
            modulateLfoWithEnv = 1;
            envSustainOn = 0;
        }
        else {
            modulateLfoWithEnv = 0;
        }
    }
    
    else if(mode == MODE_C){
       
        if(subMode==0){
            envSustainOn = 1;
        }
        else if(subMode==1){
            envSustainOn = 0;
        }
        else {
            
        }
    }
  
   

    
    

    unsigned long clockMain = masterClock;
    
    
    //Faster Rates (x1, x2, etc) - slower rates need diff approach)
    if(clockOutMultiplier == 1){
        
        if(lastQuadrant == 0){

            if(clockMain > ACC_HALF){      //0.5*ACC
                lastQuadrant = 1;
                clockOutLevel = L;
                OUTPUT_GATE = L;
                OUTPUT_LED = L;
            }

        }
        else {
            if(clockMain < ACC_HALF){
                lastQuadrant = 0;
                clockOutLevel = H;
                OUTPUT_GATE = H;
                OUTPUT_LED = H;
            }
        
        }

        
    }
    
    else if(clockOutMultiplier == 2){
        
        switch(lastQuadrant){
            
            case 0:{
                if(clockMain > ACC_ONE_QUARTER){
                    lastQuadrant = 1;
                    clockOutLevel = L;
                    OUTPUT_GATE = L;
                    OUTPUT_LED = L;
                }
     
            }break;
            
            case 1:{
                if(clockMain > ACC_HALF){
                    lastQuadrant = 2;
                    clockOutLevel = H;
                    OUTPUT_GATE = H;
                    OUTPUT_LED = H;
                }
            }break;
            
            case 2:{
              if(clockMain > ACC_THREE_QUARTERS){
                    lastQuadrant = 3;
                    clockOutLevel = L;
                    OUTPUT_GATE = L;
                    OUTPUT_LED = L;
                }
            }break;
            
            case 3:{
              if(clockMain < ACC_ONE_QUARTER){
                    lastQuadrant = 0;
                    clockOutLevel = H;
                    OUTPUT_GATE = H;
                    OUTPUT_LED = H;
                }	
            }break;
            
            //in case we switch from a higher clockOutMultiplier value, lastQuadrant could be bigger than 3
            default:{
                    lastQuadrant = 0;
                    clockOutLevel = H;
                    OUTPUT_GATE = H;
                    OUTPUT_LED = H;
            }
                
        }
        
    }
    
    
    
    
    
    else if(clockOutMultiplier == 4){
        
        switch(lastQuadrant){
            
            case 0:{
                if(clockMain > ACC_ONE_EIGTHS){
                    lastQuadrant = 1;
                    clockOutLevel = L;
                    OUTPUT_GATE = L;
                    OUTPUT_LED = L;
                }
     
            }break;
            
            case 1:{
                if(clockMain > ACC_TWO_EIGTHS){
                    lastQuadrant = 2;
                    clockOutLevel = H;
                    OUTPUT_GATE = H;
                    OUTPUT_LED = H;
                }
            }break;
            
            case 2:{
              if(clockMain > ACC_THREE_EIGTHS){
                    lastQuadrant = 3;
                    clockOutLevel = L;
                    OUTPUT_GATE = L;
                    OUTPUT_LED = L;
                }
            }break;
            
            case 3:{
              if(clockMain > ACC_FOUR_EIGTHS){
                    lastQuadrant = 4;
                    clockOutLevel = H;
                    OUTPUT_GATE = H;
                    OUTPUT_LED = H;
                }	
            }break;
            
                        
            case 4:{
              if(clockMain > ACC_FIVE_EIGTHS){
                    lastQuadrant = 5;
                    clockOutLevel = L;
                    OUTPUT_GATE = L;
                    OUTPUT_LED = L;
                }	
            }break;
            
                        
            case 5:{
              if(clockMain > ACC_SIX_EIGTHS){
                    lastQuadrant = 6;
                    clockOutLevel = H;
                    OUTPUT_GATE = H;
                    OUTPUT_LED = H;
                }	
            }break;
            
               
            case 6:{
              if(clockMain > ACC_SEVEN_EIGTHS){
                    lastQuadrant = 7;
                    clockOutLevel = L;
                    OUTPUT_GATE = L;
                    OUTPUT_LED = L;
                }	
            }break;
            
                        
            case 7:{
              if(clockMain < ACC_ONE_EIGTHS){
                    lastQuadrant = 0;
                    clockOutLevel = H;
                    OUTPUT_GATE = H;
                    OUTPUT_LED = H;
                }	
            }break;
            
            
        }
        
    }
        
#endif 



    unsigned int outA = lfoMain.output >> 4;
    unsigned int outB = 0;

    if(mode==MODE_A){
        
        if(modulateLfoWithEnv == 1){
         
            if(USE_BIPOLAR == 0){
         
                unsigned long lfoOut = ((unsigned long)lfoMain.output * envLevel)>>16;             //note... this is not bi-polar!
                outA = lfoOut >> 4;     //down to 12-bit
            }
            else {      //bipolar
                signed int tempLfoOut = lfoMain.output - 32767;
                signed long tempOut = envLevel * (signed long)tempLfoOut;     //may need to be long
                signed long tempOut2 =  tempOut>>16;
                unsigned int out = tempOut2+32767;
                outA = out >> 4;
            }

        }

        //going to output env
        
        unsigned int envOut = envLevel>>4;      //to 12 bit
        outB = (4095-envOut);    //makes it go from -5V to +5 and back to -5V.          //to make it go 0 to 5V... 4095-(env>>1) ?
    }
    else if(mode==MODE_B){
        outB = 4095-(lfoExtra.output >> 4);
    }
    else if(mode==MODE_C){
        
        if(subMode == 2){
            unsigned int eventOut = GetEventOutput(&event)>>4;
            outB = (4095-eventOut); 
            
            outB = 2048-(eventOut>>1);      //if we want uni-polar output (0 to 5V))
        }
        else {
            int getExpo = 1;
            unsigned int envOut = 0;
            if(getExpo==0){
                unsigned int expoEnv = GetEnvOutput(&env);
                envOut = expoEnv>>4;      //to 12 bit  
            }
            else {
                unsigned int expoEnv = GetEnvOutputExpo(&env);
                envOut = expoEnv>>4;      //to 12 bit  
            }
            
            outB = (4095-envOut);  
        }
    }
    
    
    if(swapAB==0){
        dacValueA = outA;
        dacValueB = outB;
    }
    else {
        dacValueA = outB;
        dacValueB = outA;
    }
    
      
    MCP4822_DAC_Convert_A();  
    MCP4822_DAC_Convert_B();
}

void ManualGateCheck(){
    
    if(lastGateLevel == 0){
        if(INPUT_GATE==0){
            
            if(envelopeEnabled==1){
                EnvOn(&env);
                EventOn(&event);
                if(lfoReset==1){
                    LfoReset(&lfoMain);
                    LfoReset(&lfoExtra);
                }
            }
            else {

            }
            
          lastGateLevel = 1;
        }
        
    }
    else {          //last level was high
        if(INPUT_GATE){
            
            if(envelopeEnabled==1){
                EnvOff(&env);
            }
            else {

            }
                        
          lastGateLevel = 0;
        }
    }
    
}

void InitOsc(){
    
    CLKDIVbits.PLLPOST = 0;	// N1 = 2

    #if(FOSC == 40)
        PLLFBDbits.PLLDIV = (32-2);     //M=2 when PLLDIV is 0x00
        CLKDIVbits.PLLPRE = (4-2);      //N2=2 when PLLPRE is 0x00       
    #elif (FOSC == 60)
        PLLFBDbits.PLLDIV = (48-2);         
        CLKDIVbits.PLLPRE = (4-2);      //N2=2 when PLLPRE is 0x00       
    #elif (FOSC == 80)
        PLLFBDbits.PLLDIV = (32-2);         
        CLKDIVbits.PLLPRE = (2-2);      //N2=2 when PLLPRE is 0x00       
    #elif (FOSC == 100)
        PLLFBDbits.PLLDIV = (40-2);         
        CLKDIVbits.PLLPRE = (2-2);      //N2=2 when PLLPRE is 0x00       
    #elif(FOSC == 120)
        PLLFBDbits.PLLDIV = (48-2);         
        CLKDIVbits.PLLPRE = (2-2);      //N2=2 when PLLPRE is 0x00       
    #elif(FOSC == 140)
        PLLFBDbits.PLLDIV = (56-2);         
        CLKDIVbits.PLLPRE = (2-2);      //N2=2 when PLLPRE is 0x00       
    #endif
    
	RCON = 0;  
    
}






void InitTimer2(unsigned int clockIn){
    
	T2CON = 0;			//16 bit, internal, 1x prescaler
    
    T2CONbits.TCKPS = 0b00;     //x1 default prescaler
    //01 - x8
    //10 - x64
    //11 - x256
    
    //if 80Mhz,40 MIPS... timer is x1=40Mhz... 1 / ( 1024 * 1 * 1/40Mhz ) = 39khz


	//PR2 = 255;			//19.5khz at 20Mhz (5 MIPS) Op Freq		8 bit res
	//PR2 = 511;		//19.5khz at 40Mhz (10 MIPS) Op Freq	9 bit res
  

    switch(clockIn){
        
        //i am keeping PR2 the same - meaning im keeping resolution the same. So it is the pwm frequency that will only change
        case 40:{
            //40mhz/2 / PRS2+1
            //20Mhz / 1024 = 19531.25hz
            PR2 = 1023;       
        }break;
        
        case 60:{
            //40mhz/2 / PRS2+1
            //20Mhz / 1024 = 29,296.8hz
            PR2 = 1023;       
        }break;
        
        case 80:{
            //80mhz/2 / PRS2+1
            //40Mhz / 2048 = 19.5khz
            PR2 = 2047;       
        }break;
        
        default:
            PR2 = 1023;	
         
    }


	IFS0bits.T2IF = 0;
	IEC0bits.T2IE = 1;

}


int main( void){
    
    InitOsc();
    
    ANSELA = ANSELB = 0;
    
    TRISA = TRISB = 0;
    
    LATA = LATB = 0;
    //TRISC= TRISD = TRISE = 0;		//All Outputs
    //LATC= LATD = LATE = 0;
    //dspic33ev: PORTA and PORTB only!
	
	//InitADSR(&eenv);
	//InitADSR2(&eenv2);		//2016
    
    
    
    /*
 Three control registers are associated with the ICN
functionality of each I/O port. The CNENx registers
contain the ICN interrupt enable control bits for each of
the input pins. Setting any of these bits enables an ICN
interrupt for the corresponding pins.
 */

    
    CNENBbits.CNIEB4 = 1;       //Interrupt Change Notification (ICN) set for PORTB4
    IEC1bits.CNIE = 1;          //Enable Interrupt 
    IFS1bits.CNIF = 0;          //Clear flag
    
    
    InitTimer2(FOSC);
    
    InitLfo(&lfoMain);
	InitLfo(&lfoExtra);
    
    InitEnv(&env);
    InitEvent(&event);

    
#ifndef SKIP_SPI
	SPI_Init(0,0,0);

    /*
	digitalValue = 4095;
	MCP4821_DAC_Convert();
    
	digitalValue = 0;
	MCP4821_DAC_Convert();
    
    	digitalValue = 4095;
	MCP4821_DAC_Convert();
    
	digitalValue = 0;
	MCP4821_DAC_Convert();
    
	digitalValue = 2047;
	MCP4821_DAC_Convert();
    
    	digitalValue = 4095;
	MCP4821_DAC_Convert();
    
	digitalValue = 0;
	MCP4821_DAC_Convert();
    
    	digitalValue = 4095;
	MCP4821_DAC_Convert();
    
	digitalValue = 0;
	MCP4821_DAC_Convert();
    
	digitalValue = 2047;
	MCP4821_DAC_Convert();
     * */
    
    dacValueA = 4095;
    OUTPUT_GATE = 1;
	MCP4822_DAC_Convert_A();
    
        OUTPUT_GATE = 1;
	dacValueA = 0;
	MCP4822_DAC_Convert_A();
    
        OUTPUT_GATE = 0;
    dacValueA = 4095;
	MCP4822_DAC_Convert_A();
    
	dacValueA = 0;
	MCP4822_DAC_Convert_A();
    
	dacValueA = 2047;
	MCP4822_DAC_Convert_A();
    
    dacValueA = 4095;
	MCP4822_DAC_Convert_A();
    
	dacValueA = 0;
	MCP4822_DAC_Convert_A();
    
    dacValueA = 4095;
	MCP4822_DAC_Convert_A();
    
	dacValueA = 0;
	MCP4822_DAC_Convert_A();
    
	dacValueA = 2047;
	MCP4822_DAC_Convert_A();
    
    
    
    
    
    
    
    dacValueB = 4095;
	MCP4822_DAC_Convert_B();
    
	dacValueB = 0;
	MCP4822_DAC_Convert_B();
    
    dacValueB = 4095;
	MCP4822_DAC_Convert_B();
    
	dacValueB = 0;
	MCP4822_DAC_Convert_B();
    
	dacValueB = 2047;
	MCP4822_DAC_Convert_B();
    
    dacValueB = 4095;
	MCP4822_DAC_Convert_B();
    
	dacValueA = 0;
	MCP4822_DAC_Convert_B();
    
    dacValueB = 4095;
	MCP4822_DAC_Convert_B();
    
	dacValueB = 0;
	MCP4822_DAC_Convert_B();
    
	dacValueB = 2047;
	MCP4822_DAC_Convert_B();
    
    
#endif
    
    
    ADC_Init();
    
    
    
    //Setup Pins
    
    //Inputs
    CNPUBbits.CNPUB11 = 1;
    CNPUBbits.CNPUB12 = CNPUBbits.CNPUB13 = 1;
    CNPUBbits.CNPUB14 = CNPUBbits.CNPUB15 = 1;
      
    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB14 = TRISBbits.TRISB15 = 1;
	TRISBbits.TRISB12 = TRISBbits.TRISB13 = 1;


    TRISBbits.TRISB10 = 0;      //LED Out
    
    TRISBbits.TRISB4 = 1;       //Gate In
    
    
    
    	
    T2CONbits.TON = 1;

    
    	
    while(1==1){
		MainLoop();
	}

    
}
