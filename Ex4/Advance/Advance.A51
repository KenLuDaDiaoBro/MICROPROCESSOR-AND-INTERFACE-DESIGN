			ORG 0 ; start from0000H
			MOV DPTR, #TABLE ; DPTR point to TABLE
			MOV R7, #2
			
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
			MOV R0, #1 ; initialize typed signal
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
			DJNZ R7, KEYIN2
			MOV R7, #2
			MOV R6, A
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			SJMP NO_Touch ; jump to scan keypad again
KEYIN2:		MOV R5, A
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			SJMP NO_Touch ; jump to scan keypad again
NO_Touch:	CALL DEBOUNCE ; call debounce function
			MOV A, P2
			ANL A, #00000001
			JZ NO_Touch
			SJMP START ; jump to scan keypad again
			
ADD_LABLE:	CALL DEBOUNCE ; call debounce function
			MOV A, R5
			MOV B, R6
			ADD A, B
			MOV B, #10
			DIV AB
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			CALL DELAY
			MOV A, B
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			SJMP START ; jump to scan keypad again
			
SUB_LABLE:	CALL DEBOUNCE ; call debounce function
			MOV A, R5
			MOV B, R6
			SUBB A, B
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			SJMP START ; jump to scan keypad again
			
MUL_LABLE:	CALL DEBOUNCE ; call debounce function
			MOV A, R5
			MOV B, R6
			MUL AB
			MOV B, #10
			DIV AB
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			CALL DELAY
			MOV A, B
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			LJMP START ; jump to scan keypad again
			
DIV_LABLE:	CALL DEBOUNCE ; call debounce function
			MOV A, R5
			MOV B, R6
			DIV AB
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			CALL DELAY
			MOV A, B
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			LJMP START ; jump to scan keypad again
			
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
			
TABLE: 		DB 00000011B ; display 0
			DB 10011111B ; display 1
			DB 00100101B ; display 2
			DB 00001101B ; display 3
			DB 10011001B ; display 4
			DB 01001001B ; display 5
			DB 01000001B ; display 6
			DB 00011011B ; display 7
			DB 00000001B ; display 8
			DB 00001001B ; display 9
			END