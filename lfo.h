/* 
 * File:   lfo.h
 * Author: Michael
 *
 * Created on 24 June 2021, 12:40
 */

#ifndef LFO_H
#define	LFO_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LFO_RATE_NU

typedef struct {

    unsigned long inc;
	unsigned long acc;
    
	unsigned long rate;
	unsigned int waveform;
	unsigned int output;

	unsigned int mode;
    unsigned int offset;        //phase, not amplitude!
    
    unsigned int overflowFlag;
    
    //Used in 1-shot mode
    unsigned int status;            
    unsigned int periodRepeatCounter;
    unsigned int periodRepeatPreload;
    
    unsigned int waveformBank;

} LFO;


#define WAVEFORM_SINE           0
#define WAVEFORM_RAMP           1
#define WAVEFORM_SAW            2
#define WAVEFORM_TRI            3
#define WAVEFORM_SQUARE         4
#define WAVEFORM_SINE_DOUBLE    5
#define WAVEFORM_RAMP_QAUNT     6
#define WAVEFORM_SAW_QUANT      7


//#define WAVEFORM_SINE_DOUBLE    5
//#define WAVEFORM_RAMP_QAUNT     6
//#define WAVEFORM_SAW_QUANT      7


#define WAVEFORM_SQUARE_DOUBLE      8
#define WAVEFORM_RAMP_QAUNT2        9
#define WAVEFORM_SAW_QUANT2         10
#define WAVEFORM_PULSE25 11
#define WAVEFORM_GATE_EFFECT1   12
#define WAVEFORM_GATE_EFFECT2   13
#define WAVEFORM_GATE_EFFECT3   14
#define WAVEFORM_GATE_EFFECT4   15

#define WAVEFORM_TRI_INV      16

#define WAVEFORM_SQUARE_INV     88











#define WAVEFORM_1SHOT_SINE_X1          0
#define WAVEFORM_1SHOT_SINE_X4          1
#define WAVEFORM_TRI_DOUBLE         31


void InitLfo(LFO *lfoPtr);
void LfoReset(LFO *lfoPtr);
void UpdateLfo(LFO *lfoPtr);


#ifdef	__cplusplus
}
#endif

#endif	/* LFO_H */

