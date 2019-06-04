.386
.model flat, stdcall
option casemap: none

	include /masm32/include/masm32.inc
	includelib /masm32/lib/masm32.lib

	include /masm32/include/user32.inc
	includelib /masm32/lib/user32.lib
	
	include /masm32/include/kernel32.inc
	includelib /masm32/lib/kernel32.lib
	
	include /masm32/include/fpu.inc
	includelib /masm32/lib/fpu.lib
	
	extrn denominator@0:near
	public ARRAY_A, ARRAY_D
	
.data?
	ARRAY_R		DT 	  5d DUP(?)
	OUTPUT		DW 1024d DUP(?)
	BUFFER1		DW	128d DUP(?)
	BUFFER2		DW	128d DUP(?)
.const		
	ARRAY_A		DQ  -5.0,  3.0, -12.0, 25.0, 36.0
	ARRAY_B		DQ	 4.0,  6.0,  40.0,  5.0, 35.0
	ARRAY_C		DQ  -2.0, -5.0,  20.0, -7.0, 29.0
	ARRAY_D		DQ	34.0,-45.0,  12.0, 67.0, -5.0
	
	NUMBER1		DQ  2.0
	NUMBER2     DQ 51.0
	
	MSG_TITLE	DB "Khilchenko Yehor LAB7", 0, 13
	FORMAT 		DB "Result%d: %s", 10, 0
.code

print macro arr
local L1
	xor esi, esi
	xor edi, edi
L1:
	invoke FpuFLtoA, addr arr[esi], 10, addr BUFFER1, SRC1_REAL
	invoke wsprintf, addr BUFFER2, addr FORMAT,edi, addr BUFFER1
	invoke szCatStr, addr OUTPUT, addr BUFFER2
	inc edi
	add esi, 10d
	cmp edi, 5d
	jne L1
	invoke MessageBox, 0, addr OUTPUT, addr MSG_TITLE, 0
endm

first proc	
	fld qword ptr [eax + esi * 8]			; eax <- c	
	fld qword ptr [ebx]						; ebx <- 2
	
	fmul 									; ST(0) <- 2*c
	ret 
first endp

second proc
;	пролог процедуры
	push ebp
	mov ebp, esp
;	пролог процедуры
	xor eax, eax
	mov eax, [ebp + 12]
	xor ebx, ebx
	mov ebx, [ebp + 8]
	
	fld1
	fld qword ptr [eax + esi * 8]			; ST(2) <- 2*C, ST(1) <- 1, ST(0) <- b
	fyl2x									; ST(1) <- 2*c, ST(0) <- 1*log(2, b) 
	
	FLDL2T									; ST(2) <- 2*c, ST(1) <- 1*log(2, b), ST(0) <- log(2, 10) 
	fdiv 									; ST(1) <- 2*c, ST(0) <- lg(b)
	fld qword ptr [ebx]
	fmul 									; ST(1) <- 2*c, ST(0) <- lg(b) * 51
	fadd
;	эпилог процедуры
	pop ebp
;	эпилог процедуры
	ret 8
second endp

formula macro
local L2
	finit
	xor esi, esi
	xor edi, edi
L2:
	mov eax, offset ARRAY_C	
	mov ebx, offset NUMBER1	
	call first								; вызов первой процедуры с регистрами			
	
	push offset ARRAY_B		
	push offset NUMBER2		
	call second								; вызов второй процедуры со стэком			
	
	call denominator@0						; вызов третьей процедуры с общей областью памяти		
	fdiv									; ST(0) <- (2*c + lg(b) * 51) / ( d - a - 1)
	
	fstp ARRAY_R[edi]
	
	add edi, 10d
	inc esi
	cmp esi, 5d
	jne L2
endm

start:
	formula									; вызов макроса моей формулы
	print ARRAY_R							; вывод результата на экран
	invoke ExitProcess, 0 					; завершение работы 
end start