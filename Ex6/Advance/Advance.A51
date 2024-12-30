			ORG 00H ;code start from 00H
			SJMP MAIN ;jump to MAIN
			ORG 03H ;vector address for INT0
			SJMP INT0_ISR ;jump to INT0_ISR
			ORG 13H ;vector address for INT1
			SJMP INT1_ISR ;jump to INT1_ISR
			ORG 030H ;after vector table space
MAIN: 		MOV IE,#10000101B ;enable EA, EX0 and EX1
			MOV IP,#00000100B ;enable EA, EX0 and EX1
			MOV SP,#30H ;stack start from #30H
			CLR IT0 ;lower trigger
			CLR IT1
			MOV A, #00000000B ;set ACC as0000000B
LOOP: 		MOV P0,A ;P1 = A (LED output)
			CALL DELAY ;call delay function
			CPL A ;reverse A
			SETB EX0
			SETB EX1
			SJMP LOOP ;infinite loop
			
INT0_ISR: 	CLR EX0
			CALL DELAY
			PUSH PSW ;push PSW into stack
			PUSH ACC ;push ACC into stack
			SETB RS0 ;switch to RB1
			CLR RS1
			MOV A, #11110000B ;set ACC as 11111110B
			MOV R0,#24 ;loop counter = 24
			SJMP ROTATE

INT1_ISR:	CLR EX0
			CLR EX1
			CALL DELAY
			PUSH PSW ;push PSW into stack
			PUSH ACC ;push ACC into stack
			CLR RS0
			SETB RS1 ;switch to RB1
			MOV A, #11111110B ;set ACC as 11111110B
			MOV R0,#16 ;loop counter = 16
			
ROTATE: 	MOV P0,A ;P2 = A (LED output)
			CALL DELAY ;call delay function
			RL A ;rotate left
			DJNZ R0,ROTATE ;loop until R0 is 0
			CLR RS0
			CLR RS1
			POP ACC ;pop out ACC fromstack
			POP PSW ;pop out PSW fromstack
			RETI ;return from ISR
			
DELAY: 		MOV R7,#200
D1: 		MOV R6,#250
			DJNZ R6, $
			DJNZ R7,D1
			RET ;return
			END ;end the code