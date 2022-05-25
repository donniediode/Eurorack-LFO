/* 
 * File:   eventgenerator.h
 * Author: Michael
 *
 * Created on 06 October 2021, 11:09
 */

#ifndef EVENTGENERATOR_H
#define	EVENTGENERATOR_H

#ifdef	__cplusplus
extern "C" {
#endif


         
    
    
    __attribute__((space(auto_psv))) unsigned char EventAttackCurve512[] = {
  0,  0,  1,  2,  3,  4,  5,  6,  6,  7,  8,  9,  10,  11,  11,  12,
  13,  14,  15,  16,  17,  17,  18,  19,  20,  21,  22,  22,  23,  24,  25,  26,
  26,  27,  28,  29,  30,  31,  31,  32,  33,  34,  35,  35,  36,  37,  38,  39,
  39,  40,  41,  42,  43,  43,  44,  45,  46,  46,  47,  48,  49,  50,  50,  51,
  52,  53,  53,  54,  55,  56,  56,  57,  58,  59,  59,  60,  61,  62,  62,  63,
  64,  65,  65,  66,  67,  68,  68,  69,  70,  71,  71,  72,  73,  74,  74,  75,
  76,  76,  77,  78,  79,  79,  80,  81,  81,  82,  83,  84,  84,  85,  86,  86,
  87,  88,  88,  89,  90,  91,  91,  92,  93,  93,  94,  95,  95,  96,  97,  97,
  98,  99,  99,  100,  101,  101,  102,  103,  103,  104,  105,  105,  106,  107,  107,  108,
  109,  109,  110,  111,  111,  112,  113,  113,  114,  115,  115,  116,  116,  117,  118,  118,
  119,  120,  120,  121,  121,  122,  123,  123,  124,  125,  125,  126,  126,  127,  128,  128,
  129,  129,  130,  131,  131,  132,  132,  133,  134,  134,  135,  135,  136,  137,  137,  138,
  138,  139,  139,  140,  141,  141,  142,  142,  143,  144,  144,  145,  145,  146,  146,  147,
  147,  148,  149,  149,  150,  150,  151,  151,  152,  152,  153,  154,  154,  155,  155,  156,
  156,  157,  157,  158,  158,  159,  159,  160,  161,  161,  162,  162,  163,  163,  164,  164,
  165,  165,  166,  166,  167,  167,  168,  168,  169,  169,  170,  170,  171,  171,  172,  172,
  173,  173,  174,  174,  175,  175,  176,  176,  177,  177,  178,  178,  179,  179,  179,  180,
  180,  181,  181,  182,  182,  183,  183,  184,  184,  185,  185,  186,  186,  186,  187,  187,
  188,  188,  189,  189,  190,  190,  190,  191,  191,  192,  192,  193,  193,  194,  194,  194,
  195,  195,  196,  196,  197,  197,  197,  198,  198,  199,  199,  199,  200,  200,  201,  201,
  201,  202,  202,  203,  203,  203,  204,  204,  205,  205,  205,  206,  206,  207,  207,  207,
  208,  208,  209,  209,  209,  210,  210,  210,  211,  211,  212,  212,  212,  213,  213,  213,
  214,  214,  214,  215,  215,  216,  216,  216,  217,  217,  217,  218,  218,  218,  219,  219,
  219,  220,  220,  220,  221,  221,  221,  222,  222,  222,  223,  223,  223,  224,  224,  224,
  225,  225,  225,  226,  226,  226,  227,  227,  227,  228,  228,  228,  228,  229,  229,  229,
  230,  230,  230,  231,  231,  231,  231,  232,  232,  232,  233,  233,  233,  233,  234,  234,
  234,  235,  235,  235,  235,  236,  236,  236,  237,  237,  237,  237,  238,  238,  238,  238,
  239,  239,  239,  239,  240,  240,  240,  240,  241,  241,  241,  241,  242,  242,  242,  242,
  243,  243,  243,  243,  244,  244,  244,  244,  245,  245,  245,  245,  245,  246,  246,  246,
  246,  247,  247,  247,  247,  247,  248,  248,  248,  248,  248,  249,  249,  249,  249,  250,
  250,  250,  250,  250,  251,  251,  251,  251,  251,  251,  252,  252,  252,  252,  252,  253,
  253,  253,  253,  253,  254,  254,  254,  254,  254,  254,  255,  255,  255,  255,  255,  255
};

__attribute__((space(auto_psv))) unsigned char EventDecayReleaseCurve512[] = {

  0,  	2,  4,  6,  8,  10,  12,  14,  16,  18,  20,  22,  24,  26,  28,  30,
  31,  33,  35,  37,  39,  41,  43,  44,  46,  48,  50,  52,  53,  55,  57,  59,
  60,  62,  64,  65,  67,  69,  70,  72,  74,  75,  77,  78,  80,  82,  83,  85,
  86,  88,  89,  91,  92,  94,  95,  97,  98,  100,  101,  102,  104,  105,  107,  108,
  109,  111,  112,  113,  115,  116,  117,  119,  120,  121,  123,  124,  125,  126,  128,  129,
  130,  131,  133,  134,  135,  136,  137,  138,  140,  141,  142,  143,  144,  145,  146,  147,
  148,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,  161,  162,  163,  164,
  165,  166,  167,  168,  168,  169,  170,  171,  172,  173,  174,  175,  176,  176,  177,  178,
  179,  180,  181,  182,  182,  183,  184,  185,  186,  186,  187,  188,  189,  189,  190,  191,
  192,  192,  193,  194,  194,  195,  196,  197,  197,  198,  199,  199,  200,  201,  201,  202,
  202,  203,  204,  204,  205,  206,  206,  207,  207,  208,  208,  209,  210,  210,  211,  211,
  212,  212,  213,  213,  214,  215,  215,  216,  216,  217,  217,  218,  218,  219,  219,  219,
  220,  220,  221,  221,  222,  222,  223,  223,  224,  224,  224,  225,  225,  226,  226,  226,
  227,  227,  228,  228,  228,  229,  229,  230,  230,  230,  231,  231,  231,  232,  232,  232,
  233,  233,  233,  234,  234,  234,  235,  235,  235,  236,  236,  236,  236,  237,  237,  237,
  238,  238,  238,  238,  239,  239,  239,  239,  240,  240,  240,  240,  241,  241,  241,  241,
  242,  242,  242,  242,  242,  243,  243,  243,  243,  244,  244,  244,  244,  244,  245,  245,
  245,  245,  245,  245,  246,  246,  246,  246,  246,  246,  247,  247,  247,  247,  247,  247,
  248,  248,  248,  248,  248,  248,  248,  249,  249,  249,  249,  249,  249,  249,  249,  250,
  250,  250,  250,  250,  250,  250,  250,  250,  251,  251,  251,  251,  251,  251,  251,  251,
  251,  251,  252,  252,  252,  252,  252,  252,  252,  252,  252,  252,  252,  252,  252,  253,
  253,  253,  253,  253,  253,  253,  253,  253,  253,  253,  253,  253,  253,  253,  253,  254,
  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,
  254,  254,  254,  254,  254,  254,  254,  254,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255
};

typedef struct Event {

    //Params accessible to user
    unsigned int mode; 
    unsigned int attack;            //only values 0-255 used
    unsigned int decay;             //only values 0-255 used
    
    unsigned int stage;
    unsigned long attackInc;         //derived from attack param
    unsigned long decayInc;          //derived from decay param
    unsigned long acc;
    
    unsigned int output;
    unsigned int output8Bit;
    unsigned int output16Bit;
    
    unsigned int updateRate;
    
    unsigned int waveform; 

    
} Event;

void InitEvent(Event* envIn){
    

    
    envIn->output = envIn->output8Bit = envIn->output16Bit = 0;
    envIn->acc = 0;
    
    envIn->attack= 78;
    envIn->decay = 27;
    

   
    envIn->attackInc = (envIn->attack << 16); 
    envIn->decayInc = (envIn->decay << 2); 

    
}



void EventOn(Event* envIn){
    
    if(envIn->mode==ENV_SUSTAIN_OFF){       //att-dec
        //Att-Dec
        envIn->stage = ENV_STAGE_ATT;
        envIn->acc = 0;
    }
    else {
        //Att-Rel
        envIn->stage = ENV_STAGE_ATT;
        //envIn->acc = 0;                   //lets not reset it
    }
}
//only needs to process if in sustain on mode...
void EventOff(Env* envIn){
    
    if(envIn->mode==ENV_SUSTAIN_ON){
        envIn->stage = ENV_STAGE_REL;
    }
       
}

unsigned int UpdateEvent(Event* envIn){
    
    envIn->output = 0;
    
    switch(envIn->stage){
        
        case ENV_STAGE_IDLE:{
            envIn->output = 0;
        }break;
        
        case ENV_STAGE_ATT:{
            
            envIn->acc += envIn->attackInc;
            if(envIn->acc > 16777215){
                
                if(envIn->mode==ENV_SUSTAIN_OFF){
                    envIn->stage = ENV_STAGE_DEC;
                    envIn->acc = 16777215;
                    
                }
                else {
                    envIn->stage = ENV_STAGE_SUS;
                    envIn->acc = 16777215;
                }
                
            }
        }break;
        
                
        case ENV_STAGE_DEC:{
            envIn->acc -= envIn->decayInc;
            if(envIn->acc < envIn->decayInc){           //"if gone minus"
                envIn->acc = 0;
                envIn->stage = ENV_STAGE_IDLE;
            }
            
        }break;
        
        case ENV_STAGE_SUS:{
            envIn->acc = 16777215;
        }break;
        
        case ENV_STAGE_REL:{
                        
            envIn->acc -= envIn->decayInc;
            if(envIn->acc < envIn->decayInc){           //"if gone minus"
                envIn->acc = 0;
                envIn->stage = ENV_STAGE_IDLE;
            }
        }break;
    }
    
    
    
    
    
    
    
    
    
          
    if(envIn->waveform==90){
        
        envIn->output = envIn->acc>>8;                      //if using 16777215 (2^24-1) as max range value

    }
    
    
    
    
    
    else if(envIn->waveform==0){
        
        unsigned int x = envIn->acc>>16;     
        x =  x << 1;
        envIn->output = EventDecayReleaseCurve512[x]<<8;
        
        envIn->output = (255-EventDecayReleaseCurve512[511-x])<<8;
        /*
         		temp1 = 65535-env->sustainLevel;
				unsigned int te = env->phase_acc>>23;
				unsigned int pp = DecayReleaseCurve[te] << 8;
				env->output = 65535-((temp1 * pp)>>16);
         */
    } 
    
    else if(envIn->waveform==1){

        envIn->output = (envIn->acc>>8) & 0xc000;
        
    }
    
    
    
    else if(envIn->waveform==2){            //2 decays, with gaps inbetween
        
        unsigned long a = envIn->acc;
        
        if( envIn->acc < ((16777215>>2)*1)){     //first half. eg 0-128
            
            a = a;
            a = a >> 6;
            envIn->output = a;      
        }
        else  if( envIn->acc < ((16777215>>2)*2)){     //first half. eg 0-128
            envIn->output = 0;      
        }
        if( envIn->acc < ((16777215>>2)*3)){     //first half. eg 0-128
            a =  a - ((16777215>>2)*2);
            a = a >> 8;
            envIn->output = a;         
        }
        else {
            envIn->output = 0;        
           }
        
    }
    
    
    
    
    
    
    
    
    
    
    
    else if(envIn->waveform==3){           //up,down... triangle... might be better with a rounded shape
        
        unsigned long a = envIn->acc;
        if( envIn->acc < (16777215>>1)){     //first half. eg 0-128
            a = a<<1;       //made full range now (so 0-255))
        }
        else {    
            //second half. eg 129-255
           
            
            a = 16777215 - a;
            a = a<<1;       //made full range now (so 0-255))
        }
            
            
        a = a>>8;                         //if using 65535 (2^16-1) as max range value
        envIn->output = a;                      //if using 16777215 (2^24-1) as max range value
         
    }
    
    
    
    else if(envIn->waveform==4){            //4 steps...decreasing size
        
        unsigned long a = envIn->acc;
        
        if( envIn->acc < ((16777215>>2)*1)){     //first half. eg 0-128
            
            a = a;
            a = a >> 6;
            envIn->output = a;      
        }
        else  if( envIn->acc < ((16777215>>2)*2)){     //first half. eg 0-128
            a =  a - ((16777215>>2)*1);
            a = a >> 7;
            envIn->output = a;      
        }
        if( envIn->acc < ((16777215>>2)*3)){     //first half. eg 0-128
            a =  a - ((16777215>>2)*2);
            a = a >> 8;
            envIn->output = a;         
        }
        else {

            a =  a - ((16777215>>2)*3);
            a = a >> 9;
            envIn->output = a;        

           }
    }
    
    
    else if(envIn->waveform==99){            //this sounds quite good actually... even thought it wasnt what i was aiming for!
        
        unsigned long a = envIn->acc;
        
        if( envIn->acc < ((16777215>>2)*1)){     //first half. eg 0-128
            
            a = ((16777215>>2)*1) - a;
            a = a >> 8;
            envIn->output = a;      
        }
        else  if( envIn->acc < ((16777215>>2)*2)){     //first half. eg 0-128
            a = ((16777215>>2)*2) - a;
            a = a >> 9;
            envIn->output = a;      
        }
        if( envIn->acc < ((16777215>>2)*3)){     //first half. eg 0-128
            a = ((16777215>>2)*3) - a;
            a = a >> 10;
            envIn->output = a;         
        }
        else {

            a = ((16777215>>2)*1) - a;
            a = a >> 11;
            envIn->output = a;        

           }
    }


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    else if(envIn->waveform==5){            //double wave... sounds correct
        
        unsigned long a = envIn->acc;
        if( envIn->acc < (8388607)){     //first half. eg 0-128
            a = a<<1;       //made full range now (so 0-255))
        }
        else {    
            //second half. eg 129-255
            //subtract it from 255          129-0
  
            a = (a - 8388607)<<1;
        }
        
        a = a>>8;                        
        envIn->output = a;                     
        
    }
    
    
    
    
    
   
    
        
    
   
    
    
    
    
    
 
    else if(envIn->waveform==6){
        
        
        unsigned long a = 0;
        if( envIn->acc < 16777215)
            a = 16777215-envIn->acc;
        
        envIn->output = a;                         //if using 65535 (2^16-1) as max range value
        envIn->output = a>>8;                      //if using 16777215 (2^24-1) as max range value
        
        envIn->output = envIn->output & 0xc000;
        
    }
    
    
       else if(envIn->waveform==7){
        
        unsigned long a = 0;
        if( envIn->acc < 16777215)
            a = 16777215-envIn->acc;
        
        envIn->output = a>>8;                      //if using 16777215 (2^24-1) as max range value
        
    }
    
    
    
    
    

    
 
    
    else {
        

        envIn->output = envIn->acc;                         //if using 65535 (2^16-1) as max range value
        envIn->output = envIn->acc>>8;                      //if using 16777215 (2^24-1) as max range value
    }
    
    
    
    return 1;
}

//Returns 16-bit output
unsigned int GetEventOutput(Event* envIn){
    return envIn->output;
}

unsigned int GetEventOutput8Bit(Event* envIn, unsigned int ticks){
    envIn->output8Bit = envIn->output >> 8;
    return envIn->output;
}

void UpdatEventParams(Event* envIn){
    envIn->attackInc = ((envIn->attack+1) << 7); 
    envIn->decayInc = ((envIn->decay+1) << 7); 
}




#ifdef	__cplusplus
}
#endif

#endif	/* EVENTGENERATOR_H */

