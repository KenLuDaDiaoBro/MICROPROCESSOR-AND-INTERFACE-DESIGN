ORG 0; code start from 0000H
MOV A, #32H; move 32H into ACC
MOV B, #06H; move 06H into B
SUBB A, B; A-B, then save into ACC
MOV B, #07H; move multiplier 07H into B
MUL AB; AxB
END