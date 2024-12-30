ORG 0; code start from 0000H
MOV A, #64H; move 64H into ACC
MOV B, #0DH; move 0DH into B
ADD A, B; A+B, then save into ACC
MOV B, #06H; move divisor 06H into B
DIV AB; A/B
END