			ORG 0 ; start from0000H
			MOV DPTR, #TABLE ; DPTR point to TABLE
START: 		MOV R0, #0 ; initialize typed signal
			MOV R1, #3 ; set 3 row
			MOV R2, #11110111B ; set first row
SCAN: 		MOV A, R2 ; move R2 to A
			MOV P2, A ; input scanned signal
			JNB P2.7, KEYIN ; scan column 1
			INC R0 ; add #01 into R0
			JNB P2.6, KEYIN ; scan column 2
			INC R0 ; add #01 into R0
			JNB P2.5, KEYIN ; scan column 3
			INC R0 ; add #01 into R0
			RR A ; nextrow
			MOV R2, A ; move A to R2
			DJNZ R1, SCAN ; scan 3 rows
			SJMP START ; jump to scan keypad again
KEYIN: 		CALL DEBOUNCE ; call debounce function
			MOV A, R0 ; get typed signal
			MOVC A, @A+DPTR ; accordingA, getsignal fromTABLE
			MOV P1, A ; output displayed signal
			SJMP START ; jump to scan keypad again
DEBOUNCE: 	MOV R4, #50 ; move 50 times intoR4
DE_500_us: 	MOV R3, #250 ; move 250 times intoR3
			DJNZ R3, $ ; jump to itself R3 times
			DJNZ R4, DE_500_us ; delay 25ms
			RET ; return to main code
TABLE: 		DB 10011111B
			DB 00100101B
			DB 00001101B
			DB 10011001B
			DB 01001001B
			DB 01000001B
			DB 00011011B
			DB 00000001B
			DB 00001001B
			END