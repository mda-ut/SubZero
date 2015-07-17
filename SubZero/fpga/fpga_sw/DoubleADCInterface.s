/*
Anthony De Caria - June 18, 2014

This code interfaces with the two AD7264 Analog-to-Digital Converters located on AquaTux's SONAR board.

It sends across the values in r4 and r5.
And stores the data collected into four arrays - with pointers passed in in r6, r7 and the first two places on the stack.
(
	Note, the value in the r4 should only be the 16 bits the AD7264 needs.
	These bits are (from 15 to 0): WR3 WR2 WR1 WR0 RD3 RD2 RD1 RD0 CAL PD2 PD1 PD0 G3 G2 G1 G0
)


*/

.data
	.equ OutBox_Data, 0x00003000
	.equ Signals, 0x00003010
	.equ DIM1_ready, 0x00003020
	.equ DIM2, 0x00003030
	.include "nios_macros.s"

.text
.global DoubleADCInterface
DoubleADCInterface:
	/*
		STORING THE DATA INTO THE SERIALIZER
		
		To do this we get the "address" of the serializer wires, and store the values in r4 and r5 to that address.
		Additionally, we set the Clock Phase and Polarity.
	*/
	movia	r8, OutBox_Data

#	mov		r9, r4
#	mov		r10, r5

	movia	r9, 0x700F
	movia	r10, 0xF00F

	slli	r10, r10, 16
	or		r9, r9, r10
	
	stwio	r9, 0(r8)
	
	/*
	
	Now that we've stored the data we want to send over, it' now time to load our serializer with data.
	
	*/
	
	movia	r8, Signals
	movi	r10, 0b10111			#	bit 4 -> ss = 1
									#	bit 3 -> CPHA = 0
									#	bit 2 -> CPOL = 1
									#	bit 1 -> DOL2 = 1
									#	bit 0 -> DOL1 = 1

	stwio	r10, 0(r8)
	
	movia	r8, DIM1_ready
	LOADINGLOOP:
		ldwio	r9, 0(r8)
		srli	r9, r9, 14
		movi	r10, 0b11
		and		r9, r9, r10
		bne		r9, r10, LOADINGLOOP
	
	movia	r8, Signals
	movi	r10, 0b00100
	stwio	r10, 0(r8)
	
	movia	r8, DIM1_ready
	WAITFORDATA:
		ldwio	r9, 0(r8)
		srli	r9, r9, 31
		andi	r9, r9, 1
		beq		r9, r0, WAITFORDATA
		
	ldwio	r9, 0(r8)
	movia	r8, DIM2
	ldwio	r10, 0(r8)
	
	movia	r8, Signals
	movi	r10, 0b10100
	stwio	r10, 0(r8)
	
	DONE:
		br		DONE
