#include "lfo.h"

extern unsigned int sineLUT[];

//Master clock - why? Because if i reset lfo phase, it will cause clock out
//signal to delay(judder). I need that to be constant and independant of lfo re-trigger status
unsigned long masterClock = 0;



void InitLfo(LFO *lfoPtr){
    lfoPtr->inc = 255 << 12;
}

void LfoReset(LFO *lfoPtr){
    lfoPtr->acc = 0;
    
    //Required for 1 shot mode
    lfoPtr->status = 1;     
    lfoPtr->periodRepeatCounter = 0;
}


void UpdateLfoAndMasterClock(LFO *lfoPtr){
    
    UpdateLfo(lfoPtr);
    masterClock += lfoPtr->inc;
}

volatile unsigned int min = 199;
volatile unsigned int max = 0;

void UpdateLfo(LFO *lfoPtr){

	//lfoPtr->inc = lfoPtr->rate*512+64;			//65500*2;
    
    #ifdef LFO_RATE_NU
   lfoPtr->inc = lfoPtr->rate<<8;	
#else
      lfoPtr->inc = lfoPtr->rate*8000+64;	
#endif
 

	lfoPtr->acc += lfoPtr->inc;
    
    lfoPtr->overflowFlag = 0;
    if(lfoPtr->acc < lfoPtr->inc){
        lfoPtr->overflowFlag = 1;
    }
    
    //this is purely for debugging. triggered just before top of peak
    long temoy = lfoPtr->acc+lfoPtr->inc;
    if(temoy < lfoPtr->inc){
        lfoPtr->overflowFlag = 0;
    }
    
    unsigned int waveform = lfoPtr->waveform;
    if(lfoPtr->waveformBank==1){
        waveform+=8;
    }
    
    unsigned long ac = lfoPtr->acc;
    if(lfoPtr->offset==90){
        ac += ((unsigned long)64<<24);
    }
    else     if(lfoPtr->offset==180){
        ac += ((unsigned long)128<<24);
    }
    else if(lfoPtr->offset==270){
        ac += ((unsigned long)192<<24);
    }

	switch(waveform){

		case WAVEFORM_RAMP:{
			lfoPtr->output = ac >> 16;
		}break;
        
        case WAVEFORM_SAW:{
			lfoPtr->output = (~(ac)) >> 16;
		}break;
        
        case WAVEFORM_SQUARE:{
			if(ac & 0x80000000) lfoPtr->output = 0xffff;
			else lfoPtr->output = 0;
		}break;
        
		case WAVEFORM_TRI:{
			unsigned long value1 = ac;
			if (ac & 0x80000000) {
                value1 = (~value1);
            }
			lfoPtr->output = (value1<<1) >> 16;
		}break;
        
        case WAVEFORM_SINE:{
            unsigned int acc8Bit = ac >> 24;
            unsigned int sine8Bit = sineLUT[acc8Bit];
			lfoPtr->output = sine8Bit << 8;
		}break;
   


        

        
        case WAVEFORM_SINE_DOUBLE:{
            
            if(ac < 0x7FFFFFFF){
                unsigned int acc8Bit = ac >> 24;
                unsigned int sine8Bit = sineLUT[acc8Bit<<1];
                lfoPtr->output = sine8Bit << 8;
            }
            else if(ac < 0xBFFFFFFE){
                unsigned int acc8Bit = (ac-0x7FFFFFFF) >> 24;
                unsigned int sine8Bit = sineLUT[acc8Bit<<2];
                lfoPtr->output = sine8Bit << 8;
            }
            else {
                unsigned int acc8Bit = (ac-0xBFFFFFFE) >> 24;
                unsigned int sine8Bit = sineLUT[acc8Bit<<2];
                lfoPtr->output = sine8Bit << 8;
            }
   
        }break;
        
                
        case WAVEFORM_SQUARE_DOUBLE:{
            
            if(ac < 0x3FFFFFFF){

                lfoPtr->output = 0xffff;
            }
            else if(ac < 0x7FFFFFFF){
                lfoPtr->output = 0;
            }
            else if(ac < 0x9FFFFFFF){
                lfoPtr->output = 0xffff;
            }
            else if(ac < 0xBFFFFFFF){
                lfoPtr->output = 0;
            }  
            else if(ac < 0xDFFFFFFF){
                lfoPtr->output = 0xffff;
            }            
            else {
                lfoPtr->output = 0;
            }
            
        }break;
        
                
        case WAVEFORM_GATE_EFFECT1:{
            
                        
            if(ac < 0x1FFFFFFF){

                lfoPtr->output = 0xffff;
            }
            else if(ac < 0x3FFFFFFF){

                lfoPtr->output = 0;
            }
            
            else if(ac < 0x5FFFFFFF){

                lfoPtr->output = 0xc000;
            }
            
            else if(ac < 0x7FFFFFFF){
                lfoPtr->output = 16384;
            }
            else if(ac < 0x9FFFFFFF){
                lfoPtr->output = 0xc000;
            }
            else if(ac < 0xBFFFFFFF){
                lfoPtr->output = 16384;
            }  
            else if(ac < 0xDFFFFFFF){
                lfoPtr->output = 0xc000;
            }            
            else {
                lfoPtr->output = 16384;
            }
            
        }break;
        
        
        case WAVEFORM_GATE_EFFECT2:{
            
                        
            if(ac < 0x3FFFFFFF){

                lfoPtr->output = 0xffff;
            }
            
            else if(ac < 0x7FFFFFFF){

                lfoPtr->output = 0x0000;
            }
            
            else if(ac < 0xBFFFFFFF){
                lfoPtr->output = 0xc000;
            }
    
            else {
                lfoPtr->output = 0x4000;
            }
            
        }break;
        
        
        
               
        case WAVEFORM_GATE_EFFECT3:{
            
                        
            if(ac < 0x1FFFFFFF){

                lfoPtr->output = 0xffff;
            }
            else if(ac < 0x3FFFFFFF){

                lfoPtr->output = 0x0000;
            }
            
            else if(ac < 0x5FFFFFFF){

                lfoPtr->output = 0xdfff;
            }
            
            else if(ac < 0x7FFFFFFF){
                lfoPtr->output = 0x2000;
            }
            else if(ac < 0x9FFFFFFF){
                lfoPtr->output = 0xbfff;
            }
            else if(ac < 0xBFFFFFFF){
                lfoPtr->output = 0x4000;
            }  
            else if(ac < 0xDFFFFFFF){
                lfoPtr->output = 0x9fff;
            }            
            else {
                lfoPtr->output = 0x6000;
            }
            
        }break;
        
        
              
        case WAVEFORM_GATE_EFFECT4:{
            
                        
            if(ac < 0x1FFFFFFF){

                lfoPtr->output = 0xffff-(unsigned int)(ac>>16);         //lfoPtr->output = ac >> 16;
            }
            else if(ac < 0x3FFFFFFF){

                lfoPtr->output = 0x0000;
            }
            
            else if(ac < 0x5FFFFFFF){

                lfoPtr->output = 0xffff-(unsigned int)(ac>>16);  
            }
            
            else if(ac < 0x7FFFFFFF){
                lfoPtr->output = 0x0000;
            }
            else if(ac < 0x9FFFFFFF){
                lfoPtr->output = 0xffff-(unsigned int)(ac>>16);  
            }
            else if(ac < 0xBFFFFFFF){
                lfoPtr->output = 0x0000;
            }  
            else if(ac < 0xDFFFFFFF){
                lfoPtr->output = 0xffff-(unsigned int)(ac>>16);  
            }            
            else {
                lfoPtr->output = 0x0000;
            }
            
        }break;



		case WAVEFORM_PULSE25:{
			//output
			if(ac & 0xc0000000) lfoPtr->output = 0xffff;
			else lfoPtr->output = 0;
		}break;


        case WAVEFORM_RAMP_QAUNT:{
			lfoPtr->output = 0xE000 & (ac >> 16);              //E0 - 8 levels. F0 - 16 levels
		}break;
        
        
        case WAVEFORM_RAMP_QAUNT2:{
			lfoPtr->output = 0xC000 & (ac >> 16);              //E0 - 8 levels. F0 - 16 levels
		}break;
        
        case WAVEFORM_SAW_QUANT:{
			//output
			lfoPtr->output = 0xE000 & ((~(ac)) >> 16);
		}break;
        
        case WAVEFORM_SAW_QUANT2:{
			lfoPtr->output = 0xC000 & ((~(ac)) >> 16);
		}break;
        
        		
        case WAVEFORM_TRI_INV:{       
            
			unsigned long value1 = ac;
			if (ac & 0x80000000) {
                value1 = (~value1);
            }
			lfoPtr->output = ((value1<<1) >> 16);
            
            lfoPtr->output = ~lfoPtr->output;
		}break;
        
        	
        case WAVEFORM_SQUARE_INV:{
			//output
			if(ac & 0x80000000) lfoPtr->output = 0;
			else lfoPtr->output = 0xffff;
		}break;


		case 101:{
			//output
			if(ac & 0xc0000000) lfoPtr->output = 0;
			else lfoPtr->output = 0xffff;
		}break;
        
        
        

		default: lfoPtr->output = ac >> 16;
	}


}



void UpdateLfo_1ShotMode(LFO *lfoPtr){
    
    if(lfoPtr->status==0){
        lfoPtr->output = 0;
        return;
    }
    

    
  

	//lfoPtr->inc = lfoPtr->rate*512+64;			//65500*2;
    lfoPtr->inc = lfoPtr->rate*8000+64;	

	lfoPtr->acc += lfoPtr->inc;
    
    lfoPtr->overflowFlag = 0;
    if(lfoPtr->acc < lfoPtr->inc){
        lfoPtr->overflowFlag = 1;
        
            lfoPtr->periodRepeatCounter++;
            if(lfoPtr->periodRepeatCounter == lfoPtr->periodRepeatPreload){
                lfoPtr->periodRepeatCounter = 0;
                lfoPtr->status = 0;
            }
        
    }

	switch(lfoPtr->waveform){
        
        case WAVEFORM_TRI_DOUBLE:{
           
            if(lfoPtr->periodRepeatCounter==0){
                unsigned long value1 = lfoPtr->acc;
                if (lfoPtr->acc & 0x80000000) {
                    value1 = (~value1);
                }
                lfoPtr->output = (value1<<1) >> 16;
            }
            else {
                unsigned long value0 = lfoPtr->acc<<1;
                unsigned long value1 = lfoPtr->acc<<1;      //2x fast?
                if (value0 & 0x80000000) {
                    value1 = (~value1);
                }
                lfoPtr->output = (value1<<1) >> 16;
            }

		}break;

   

		case WAVEFORM_RAMP:{
			lfoPtr->output = lfoPtr->acc >> 16;
		}break;

		case WAVEFORM_TRI:{
			//output
			unsigned long value1 = lfoPtr->acc;
			if (lfoPtr->acc & 0x80000000) {
                value1 = (~value1);
            }
			lfoPtr->output = (value1<<1) >> 16;
		}break;

		case WAVEFORM_SAW:{
			//output
			lfoPtr->output = (~(lfoPtr->acc)) >> 16;
		}break;

		case WAVEFORM_SQUARE:{
			//output
			if(lfoPtr->acc & 0x80000000) lfoPtr->output = 0xffff;
			else lfoPtr->output = 0;
		}break;


		case WAVEFORM_PULSE25:{
			//output
			if(lfoPtr->acc & 0xc0000000) lfoPtr->output = 0xffff;
			else lfoPtr->output = 0;
		}break;


        case WAVEFORM_RAMP_QAUNT:{
			lfoPtr->output = 0xFFF0 & (lfoPtr->acc >> 16);
		}break;
        
        case WAVEFORM_SAW_QUANT:{
			//output
			lfoPtr->output = 0xFFF0 & ((~(lfoPtr->acc)) >> 16);
		}break;
        
        		
        case WAVEFORM_TRI_INV:{       
            
			unsigned long value1 = lfoPtr->acc;
			if (lfoPtr->acc & 0x80000000) {
                value1 = (~value1);
            }
			lfoPtr->output = ((value1<<1) >> 16);
            
            lfoPtr->output = ~lfoPtr->output;
		}break;
        
        	
        case WAVEFORM_SQUARE_INV:{
			//output
			if(lfoPtr->acc & 0x80000000) lfoPtr->output = 0;
			else lfoPtr->output = 0xffff;
		}break;


		case 101:{
			//output
			if(lfoPtr->acc & 0xc0000000) lfoPtr->output = 0;
			else lfoPtr->output = 0xffff;
		}break;
        
        
        

		default: lfoPtr->output = lfoPtr->acc >> 16;
	}


}


