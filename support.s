.include "xc.inc"    
.text
    
   
    
.global _MCP4821_DAC_Convert

#define	    DAC_CS	LATB,#9   

;DEBUG this... go through and check each byte sent is correct and verify byte by byte on logic analyser
_MCP4821_DAC_Convert:




	;bit15: 0=write to output A
	;bit14: dont care
	;bit13: 1=gainx1 	0=gainx2
	;bit12: 0=output buffer disabled(low power shutdown)

	;bits11-0: 12 bit number

	call	enableSD
	nop
	nop





	
	; Extract 4 msb
	mov		#0b0000111100000000,w0
	and		_digitalValue,WREG
	swap	w0
	mov		w0,_digital_highByte

	; Extract 8 lsb
	mov		#0xff,w0
	and		_digitalValue,WREG
	mov		w0,_digital_lowByte
	

	;Write instruction (gain=x1)

	;output voltage = 2.048 x gain(12 bit number / 4096)

	mov		#0b00010000,w0	    ;use 0b00110000 for dac 4922, because gain is x2 if bit 13 is clear
	ior		_digital_highByte,WREG
	mov		w0,w4
	call	writeSPI

	mov		_digital_lowByte,WREG
	mov		w0,w5
	call	writeSPI


	call	disableSD

	nop
	nop
	nop

	
	
	
	return



.global _MCP4821_DAC_Convert_DacB



_MCP4821_DAC_Convert_DacB:




	;bit15: 0=write to output A
	;bit14: dont care
	;bit13: 1=gainx1 	0=gainx2
	;bit12: 0=output buffer disabled(low power shutdown)

	;bits11-0: 12 bit number

	call	enableSD
	nop
	nop





	
	; Extract 4 msb
	mov		#0b0000111100000000,w0
	and		_digitalValue,WREG
	swap	w0
	mov		w0,_digital_highByte

	; Extract 8 lsb
	mov		#0xff,w0
	and		_digitalValue,WREG
	mov		w0,_digital_lowByte
	

	;Write instruction (gain=x1)

	;output voltage = 2.048 x gain(12 bit number / 4096)

	mov		#0b10010000,w0	    ;use 0b10110000 for dac 4922, because gain is x2 if bit 13 is 
	ior		_digital_highByte,WREG
	mov		w0,w4
	call	writeSPI

	mov		_digital_lowByte,WREG
	mov		w0,w5
	call	writeSPI


	call	disableSD

	nop
	nop
	nop

	
	
	
	return

.global _MCP4922_DAC_Convert

_MCP4922_DAC_Convert:
    
    call MCP4922_DAC_Convert_DAC_A
    call MCP4922_DAC_Convert_DAC_B
    return	

MCP4922_DAC_Convert_DAC_A:

	;bit15: 0=write to output A
	;bit14: dont care
	;bit13: 1=gainx1 	0=gainx2
	;bit12: 0=output buffer disabled(low power shutdown)

	;bits11-0: 12 bit number

	call	enableSD
	nop
	nop


	; Extract 4 msb
	mov		#0b0000111100000000,w0
	and		_digitalValue,WREG
	swap	w0
	mov		w0,_digital_highByte

	; Extract 8 lsb
	mov		#0xff,w0
	and		_digitalValue,WREG
	mov		w0,_digital_lowByte
	

	;Write instruction (gain=x1)

	;output voltage = 2.048 x gain(12 bit number / 4096)

	mov		#0b00110000,w0
	ior		_digital_highByte,WREG
	mov		w0,w4
	call	writeSPI

	mov		_digital_lowByte,WREG
	mov		w0,w5
	call	writeSPI


	call	disableSD

	nop
	nop
	nop

	return


MCP4922_DAC_Convert_DAC_B:

	;bit15: 0=write to output A
	;bit14: dont care
	;bit13: 1=gainx1 	0=gainx2
	;bit12: 0=output buffer disabled(low power shutdown)

	;bits11-0: 12 bit number

	call	enableSD
	nop
	nop

	; Extract 4 msb
	mov		#0b0000111100000000,w0
	and		_digitalValue2,WREG
	swap	w0
	mov		w0,_digital_highByte2

	; Extract 8 lsb
	mov		#0xff,w0
	and		_digitalValue2,WREG
	mov		w0,_digital_lowByte2
	

	;Write instruction (gain=x1)

	;output voltage = 2.048 x gain(12 bit number / 4096)

	mov		#0b10110000,w0
	ior		_digital_highByte2,WREG
	mov		w0,w4
	call	writeSPI

	mov		_digital_lowByte2,WREG
	mov		w0,w5
	call	writeSPI

	call	disableSD

	nop
	nop
	nop

	return

;pic30f
/*
disableSD:
	bset	 LATF,#2; = 1; 
	call	 clockSPI
	return


enableSD:
	bclr	LATF,#2
	return
*/
	
disableSD:
	bset	 DAC_CS
	call	 clockSPI
	return


enableSD:
	bclr	DAC_CS
	return







readSPI:   
	mov		#0xff,w0
	call	writeSPI
	return


writeSPI:

    mov	w0,SPI1BUF;SPI2BUF = b;	
aw:
 	btss	SPI1STAT,#SPIRBF
	goto	aw

	mov	SPI1BUF,w0

	return

	
clockSPI:
	mov		#0xff,w0
	call	writeSPI
	return




