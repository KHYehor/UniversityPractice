.386
.model flat, stdcall
option casemap: none
COMMENT <com>
	Поключение необходимых библиотек:
	---------------------------------
<com>

	include /masm32/include/masm32.inc
	includelib /masm32/lib/masm32.lib

	include /masm32/include/user32.inc
	includelib /masm32/lib/user32.lib
	
	include /masm32/include/kernel32.inc
	includelib /masm32/lib/kernel32.lib
	
	include /masm32/include/fpu.inc
	includelib /masm32/lib/fpu.lib
	
COMMENT <com>
	---------------------------------
<com>
.data
	RESULT		DT 0
.data?
	OUTPUT		DW 1024d DUP(?)
	
	RESULT_1	DB 25 DUP (?)
	RESULT_2	DB 25 DUP (?)
	RESULT_3	DB 25 DUP (?)
	RESULT_4	DB 25 DUP (?)
	RESULT_5	DB 25 DUP (?)
	
.const	
	ARRAY_1		DQ  -5.0,  4.0, -2.0,  34.0
	ARRAY_2 	DQ   3.0,  6.0, -5.0, -45.0
	ARRAY_3		DQ -12.0, 40.0, 20.0,  12.0
	ARRAY_4		DQ  25.0,  5.0, -7.0,  67.0
	ARRAY_5		DQ  36.0, 35.0, 29.0,  -5.0

	NUMBER1		DQ  2.0
	NUMBER2     DQ 51.0
	
	MSG_TITLE	DB "Khilchenko Yehor LAB6", 0, 13
	FORMAT 		DB  "Res1: %s", 10, "Res2: %s", 10, "Res3: %s", 10, "Res4: %s", 10, "Res5: %s", 0
.code
 
start:


formula macro ARR
	fld [ARR + 8 * 2]
	fmul NUMBER1						; ST(0) <- 2*c
	
	fld1								
	fld [ARR + 8 * 1]					; ST(2) <- 2*C, ST(1) <- 1, ST(0) <- b
	fyl2x								; ST(1) <- 2*c, ST(0) <- 1*log(2, b) 
	
	FLDL2T								; ST(2) <- 2*c, ST(1) <- 1*log(2, b), ST(0) <- log(2, 10) 
	fdiv 								; ST(1) <- 2*c, ST(0) <- lg(b)
	
	fmul NUMBER2						; ST(1) <- 2*c, ST(0) <- lg(b) * 51
	fadd								; ST(0) <- 2*c + lg(b) * 51
	
	fld [ARR + 8 * 3]					
	fld [ARR + 8 * 0]					; ST(2) <- 2*c + lg(b) * 51, ST(1) <- d, ST(0) <- a
	fsub								; ST(1) <- 2*c + lg(b) * 51, ST(0) <- d - a
	fld1								; ST(2) <- 2*c + lg(b) * 51, ST(1) <- d - a, ST(0) <- 1
	fsub								; ST(1) <- 2*c + lg(b) * 51, ST(1) <- d - a - 1
	
	fdiv								; ST(0) <- (2*c + lg(b) * 51) / ( d - a - 1)
	
	fstp RESULT							; RESULT <- ST(0)
endm

	formula ARRAY_1
	invoke FpuFLtoA,addr RESULT,8,addr RESULT_1, SRC1_REAL
	
	formula ARRAY_2
	invoke FpuFLtoA,addr RESULT,8,addr RESULT_2, SRC1_REAL
	
	formula ARRAY_3
	invoke FpuFLtoA,addr RESULT,8,addr RESULT_3, SRC1_REAL
	
	formula ARRAY_4
	invoke FpuFLtoA,addr RESULT,8,addr RESULT_4, SRC1_REAL
	
	formula ARRAY_5
	invoke FpuFLtoA,addr RESULT,8,addr RESULT_5, SRC1_REAL

	invoke wsprintf, addr OUTPUT, addr FORMAT,addr RESULT_1, addr RESULT_2, addr RESULT_3, addr RESULT_4, addr RESULT_5
	invoke MessageBox, 0, addr OUTPUT, addr MSG_TITLE,0
	invoke ExitProcess, 0    
	
end start