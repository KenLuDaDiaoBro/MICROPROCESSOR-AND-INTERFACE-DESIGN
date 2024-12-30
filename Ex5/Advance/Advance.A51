		ORG 0000h
		MOV R3, #0
		JMP SETT ;jump into loop
		ORG 0030h
SETT:	MOV SP, #32h ;SP = #32H
		MOV A, #00111111B
		MOV R1, #8D
LOOP:	SETB P1.0
		SETB P1.4
		MOV P2, A
		CALL DELAY
		JNB P1.0, PSHH
		JNB P1.4, POPP
		RR A
		DJNZ R1, LOOP
		JMP SETT

NTOH:	CALL DELAY
		JNB P1.0, NTOH
		RET
		
DELAY: 	MOV R0, #4 ; loop 4 times
LOOP1: 	MOV R1, #250 ; loop 250 times
LOOP2: 	MOV R2, #250 ; loop 250 times
		DJNZ R2, $ ; decrement R2 until 0
		DJNZ R1, LOOP2 ; decrement R1 until 0
		DJNZ R0, LOOP1 ; decrement R0 until 0
		RET ; return from
		
PSHH:	CALL DELAY
		MOV R0, A
		PUSH 00h
		INC R3
		CALL NTOH
		JMP LOOP
POPP:	CALL DELAY
		POP 00h
		MOV A, R0
		MOV P2, A
		DJNZ R3, POPP
		CALL NTOH
		JMP SETT
		END