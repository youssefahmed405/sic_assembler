start	START	500
		LDA 	X
		ADD 	7
		COMP	10
		JEQ		loop
loop	ADD 	Y
		MUL Z
		STA E
		COMP	30
		JLT 	loop
X WORD 3
Y WORD 14
E RESW 16
Z WORD 192
	END start



