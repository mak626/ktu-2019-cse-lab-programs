DATA1 SEGMENT
	NUM1 DW 1234H
	NUM2 DW 0F242H
	PROD DW 2 DUP (0)
DATA1 ENDS

CODE1 SEGMENT
	ASSUME CS: CODE1, DS: DATA1
	START: 
		MOV AX, DATA1
		MOV DS, AX
		MOV AX, NUM1
		MUL NUM2
		MOV PROD, AX
		MOV PROD+2,DX
		MOV AH, 4CH
		INT 21H
CODE1 ENDS
	END START