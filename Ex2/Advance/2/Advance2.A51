		ORG 00H ; start address is 0
		MOV DPTR, #TABLE ; DPTR point to TABLE
START: 	MOV R0, #4 ; 4 LED
		MOV R1, #0 ; table index
		MOV R2, #0FEH ; LED drive pin
LOOP: 	MOV P2, R2 ; select LED
		MOV A, R1 ; move R1 to A
		MOVC A, @A+DPTR ; get value from table
		MOV P1, A ; move value to P1
		CALL DELAY ; delay 0.5 ms
		INC R1 ; increase R1
		MOV A, R2 ; move R2 to A
		RL A ; rotate A
		MOV R2, A ; move A back to R2
		DJNZ R0, LOOP ; decrement R0 until 0
		SJMP START ; jump to start
		
DELAY: 	MOV R3, #250 ; loop 250 times
		MOV R4, #250
		MOV R5, #4
DELAY1:	DJNZ R5, DELAY1
DELAY2:	MOV R5, #4
		DJNZ R4, DELAY1	
DELAY3:	MOV R5, #4
		MOV R4, #250
		DJNZ R3, DELAY1 ; decrement R3 until 0
		RET ; return from subroutine
		
TABLE: 	DB 082H ; 6
		DB 0C0H ; 0
		DB 082H ; 6
		DB 0F8H ; 7
		END ; end of program