			ORG 00H ;code start from 00H
			SJMP MAIN ;jump to MAIN
			ORG 03H ;vector address for INT0
			LJMP INT0_ISR ;jump to INT0_ISR
			ORG 13H ;vector address for INT1
			LJMP INT1_ISR ;jump to INT1_ISR
			ORG 030H ;after vector table space
				
MAIN:		MOV IE,#10000101B ;enable EA, EX0 and EX1
			MOV IP,#00000100B ;enable EA, EX0 and EX1
			MOV SP,#30H ;stack start from #30H
			CLR IT0 ;lower trigger
			CLR IT1
			MOV DPTR, #TABLE ; DPTR point to TABLE
			MOV R2, #00000000B
			MOV A, R2
			MOV P0, A
			MOV R2, #10101010B
			MOV A, R2
			MOV P1, A
			MOV R6, #0
			
START: 		MOV R2, #11110111B ; set first row
			MOV A, R2 ; move R2 to A
			MOV P2, A ; input scanned signal
			JNB P2.4, ADD_LABLE ; scan column 4
			RR A ; nextrow
			MOV P2, A ; input scanned signal
			JNB P2.4, SUB_LABLE ; scan column 4
			RR A ; nextrow
			MOV P2, A ; input scanned signal
			JNB P2.4, MUL_LABLE ; scan column 4
			RR A ; nextrow
			MOV P2, A ; input scanned signal
			JNB P2.4, DIV_LABLE ; scan column 4
			JNB P2.5, POPU
			JNB P2.6, ZERO
			MOV R0 , #1
			MOV R1, #3 ; set 3 row
			MOV R2, #11110111B ; set first row
			
SCANNUM: 	MOV A, R2 ; move R2 to A
			MOV P2, A ; input scanned signal
			JNB P2.7, KEYIN1 ; scan column 1
			INC R0 ; add #01 into R0
			JNB P2.6, KEYIN1 ; scan column 2
			INC R0 ; add #01 into R0
			JNB P2.5, KEYIN1 ; scan column 3
			INC R0 ; add #01 into R0
			RR A ; nextrow
			MOV R2, A ; move A to R2
			DJNZ R1, SCANNUM ; scan 3 rows
			SJMP START ; jump to scan keypad again
			
KEYIN1: 	CALL DEBOUNCE ; call debounce function
			MOV A, R0
			MOV R7, A
			MOV B, #5
			DIV AB
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV R0, A
			MOV A, B
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV B, A
			MOV A, R0
			MOV R0, #4
CARRY:		RL A
			DJNZ R0, CARRY
			ADD A, B
			MOV P0, A
			MOV R0, A
			PUSH 00h
			INC R6
			LJMP START
			
ADD_LABLE:	CALL DEBOUNCE ; call debounce function
			INC R7
			MOV A, R7
			MOV R0, A
			LJMP KEYIN1 ; jump to scan keypad again
			
SUB_LABLE:	CALL DEBOUNCE ; call debounce function
			DEC R7
			MOV A, R7
			MOV R0, A
			LJMP KEYIN1 ; jump to scan keypad again
			
MUL_LABLE:	CALL DEBOUNCE ; call debounce function
			MOV A, R7
			MOV B, #2
			MUL AB
			MOV R7, A
			MOV R0, A
			LJMP KEYIN1 ; jump to scan keypad again
			
DIV_LABLE:	CALL DEBOUNCE ; call debounce function
			MOV A, R7
			MOV B, #2
			DIV AB
			MOV R7, A
			MOV R0, A
			LJMP KEYIN1 ; jump to scan keypad again
			
ZERO:		MOV R7, #0
			MOV A, #11111111B
			MOV P0, A
			LJMP START
			
POPU:		CALL DEBOUNCE ; call debounce function
			CALL DELAY
			POP 00h
			MOV A, R0
			MOV P0, A
			DJNZ R6, POPU
			LJMP START	
			
INT0_ISR: 	CALL DELAY
			PUSH PSW ;push PSW into stack
			PUSH ACC ;push ACC into stack
			DEC R7
CKIN:		MOV A, R7
			MOV R0, A
			CALL KEYIN2
			CALL DELAY
			DJNZ R7, CKIN
			MOV A, #00000000B
			MOV R0, #15
LOOP: 		MOV P0, A ;P1 = A (LED output)
			CALL DELAY ;call delay function
			CPL A ;reverse A
			DJNZ R0, LOOP ;infinite loop
			POP ACC ;pop out ACC fromstack
			POP PSW ;pop out PSW fromstack
			RETI

INT1_ISR:	CALL DELAY
			CALL INT1_ISR
			RETI ;return from ISR
			
KEYIN2: 	CALL DEBOUNCE ; call debounce function
			MOV A, R0
			MOV B, #5
			DIV AB
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV R0, A
			MOV A, B
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV B, A
			MOV A, R0
			MOV R0, #4
CARRY2:		RL A
			DJNZ R0, CARRY2
			ADD A, B
			MOV P0, A
			RET
			
DEBOUNCE: 	MOV R4, #250 ; move 50 times intoR4
DE_500_us: 	MOV R3, #250 ; move 250 times intoR3
			DJNZ R3, $ ; jump to itself R3 times	
			DJNZ R4, DE_500_us ; delay 25ms
			RET ; return to main code
			
DELAY: 		MOV R3, #250 ; loop 250 times
			MOV R4, #250
			MOV R5, #4
DELAY1:		DJNZ R5, DELAY1
DELAY2:		MOV R5, #4
			DJNZ R4, DELAY1	
DELAY3:		MOV R5, #4
			MOV R4, #250
			DJNZ R3, DELAY1 ; decrement R3 until 0
			RET
			
TABLE: 		DB 00001111B ; display 0
			DB 00001110B ; display 1
			DB 00001100B ; display 2
			DB 00001000B ; display 3
			DB 00000000B ; display 4
			END