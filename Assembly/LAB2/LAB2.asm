.model  tiny
.stack  100h
.data
	PASS_LOG	DB	5 DUP (?)
	STRING_ASK	DB	"Enter your password: ", 0DH, 0AH, "$"
	STRING_INFO	DB	"KHilchenko Yehor Andreevich", 0DH, 0AH, "Birth: 12.03.2000", 0DH, 0AH, "Student book: IP-7426", "$"
	STRING_ERR	DB	"Your password is incorrect:", 0DH, 0AH, "$"
	PASS_SYS	DB  '56701$'
	PASS_LEN	DW  5d
	XOR_KEY	   EQU 	4h
.code
    ORG 100h
start:
@MENU:
	MOV AH, 09h  
    MOV DX, offset STRING_ASK 
    INT 21h

    MOV AH, 3FH
    MOV BX, 0
    MOV CX, 7
    MOV DX, offset PASS_LOG
    INT 21h
	
	MOV AH, 09H
	MOV DX, offset PASS_LOG
	INT 21H

	MOV DI, 0
hash:
    XOR PASS_LOG[DI], XOR_KEY
    INC DI
    CMP DI, 5
    JNE hash 	
	
	PUSH DS      
    POP  ES
    LEA  SI, PASS_LOG  
    LEA  DI, PASS_SYS    
    CLD             
    MOV  CX, PASS_LEN   
    REPE CMPSB   
    JNE  @EXC
	
	MOV AX, 03H
    INT 10H
	
    MOV AH, 09H
    MOV DX, offset STRING_INFO
	INT 21h
	
	JMP @FIN
	
@EXC:
	MOV AX, 03H
    INT 10H
	
    MOV AH, 09H 				 
    MOV DX, offset STRING_ERR
    INT 21H
    JMP @MENU 

@FIN:
	RET
end start  
 