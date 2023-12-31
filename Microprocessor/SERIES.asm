DATA1 SEGMENT
	LIST DB 7FH,12H,26H,0F1H,79H
	COUNT EQU 05H
	SUM DW 1 DUP(0)
DATA1 ENDS

CODE1 SEGMENT
	ASSUME CS: CODE1, DS: DATA1
	START: 
		MOV AX, DATA1
		MOV DS, AX
		MOV CX,COUNT
		MOV AX,0000H
		MOV SI, OFFSET LIST
		L2:
			ADD AL,[SI]
			JNC L1
			INC AH
		L1: 
			INC SI
			LOOP L2
		MOV SUM,AX
		MOV AH, 4CH
		INT 21H
CODE1 ENDS
	END START