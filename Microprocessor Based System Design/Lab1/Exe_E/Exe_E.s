									   																													  ; Blink_LED.s   Lab #1 sample program
; This program blink the LEDs on the DE0 board

; Stack related directives
	AREA    STACK, NOINIT, READWRITE, ALIGN=4	; Name this block of code as STACK, reside in the RAM area
Stack_Size  EQU     0x200						; Stack Size = 0x200 bytes
Stack_Mem   SPACE   Stack_Size				    ; Reserve the space in RAM
TOP_STACK										; Set top of stack location

; Vector Table - link to Address 0 at Reset
	AREA    RESET, DATA, READONLY				; Name this block of code as RESET, reside in the ROM area
__Vectors   DCD     TOP_STACK           		; Vector table start here, first enty is the 'Top of stack'
			DCD		START						; second entry is the Reset vector address

; User Application
	AREA    texts, CODE, READONLY     			; Name this block of code as texts, reside in the ROM area
ENTRY                       					; Mark first instruction to execute
START   	PROC								; Declaration of subroutine/function 
			LDR     R2,=0xA0001000         		; Switches
			LDR 	R5,=0xA0004000				; 7 Segment Display

leds_on		LDR		R1,[R2,#0x00]
			LDR     R6,=0x00000009
			LDR		R0,=0x00000001

			
PushLoop	PUSH {R0}
			LSLS R0,R0,#1
			ARSS R6,R0,#1
			CMP R6,#0x00
			BNE PushLoop

			LDR     R0,=0x00000000
			PUSH {R0}
			LDR     R0,=0x00000001
			PUSH {R0}
			LDR     R0,=0x00000002
			PUSH {R0}
			LDR     R0,=0x00000004
			PUSH {R0}
			LDR     R0,=0x00000008
			PUSH {R0}
			LDR     R0,=0x00000010
			PUSH {R0}
			LDR     R0,=0x00000020
			PUSH {R0}
			LDR     R0,=0x00000040
			PUSH {R0}
			LDR     R0,=0x00000080
			PUSH {R0}
			LDR     R0,=0x00000100	
			PUSH {R0}

Loop		LDR 	R0,=0x0000003F
			LDR 	R0,=0x00000006
			LDR 	R0,=0x0000005B
			LDR 	R0,=0x0000004F
			LDR 	R0,=0x00000066
			LDR 	R0,=0x0000006D
			LDR 	R0,=0x0000007D
			LDR 	R0,=0x00000007
			LDR 	R0,=0x0000007F
			LDR 	R0,=0x00000067

			STR		R0,[R5,#0x00]

			ENDP                            	; END of this subroutine

;Delay subroutine
COUNTER 	EQU     0xFFFFF                		; Counter to be used for delay looping

DELAY		PROC                        		; Declaration of DELAY subroutine
			MOVS	R4,#3
delay0    	ldr 	R3,=COUNTER            		; Initialize R3 with delay COUNTER
delay1    	SUBS 	R3,#1           
			BNE 	delay1
			SUBS 	R4,#1
			BNE 	delay0
			BX 		LR                     		;Return to the calling function
			ENDP   
	


; The following codes are not used in this application, but their symbols are required for error-free linking by default linker setup	
	            EXPORT  __Vectors				; default symbol required by the linker, not used in this program      
				EXPORT  Reset_Handler           ; default symbol required by linker, not needed in this program
				
	AREA    texts, CODE, READONLY, ALIGN=4
Reset_Handler   PROC							; Typical code for Reset_vector handler
                LDR     R0, =START				; User Application called by Label
                BX      R0
                ENDP
	
			END   									; End of code. Assembler ignore code beyind this point    