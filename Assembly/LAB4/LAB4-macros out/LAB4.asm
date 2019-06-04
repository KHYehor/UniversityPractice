.586 
.model flat, stdcall

; ml /c /coff /Cp lab3.asm
; link /SUBSYSTEM:WINDOWS lab3.obj
; через консоль lab3.exe password...

	include /masm32/include/user32.inc
	include /masm32/include/kernel32.inc
	
	includelib /masm32/lib/user32.lib
	includelib /masm32/lib/kernel32.lib
	
	include /masm32/macros/macros.asm 
	include lab4.inc 
.data
	PASS_LOG	DD	14 DUP (?)
	TITLE_INFO	DB  "Student Personal DATA", 0
	TITLE_ERR	DB	"Password error", 0
.const
	STRING_INFO1	DB	"KHilchenko Yehor Andreevich", 0, 13 
	STRING_INFO2	DB	"Birth: 12.03.2000", 0, 13
	STRING_INFO3	DB  "Student book: IP-7426", 0, 13
	XOR_KEY	   EQU 	4h
	STRING_ERR	DB	'Your password is incorrect!', 0, 13
	PASS_SYS	DB  '56701'
.code

console proc far
	call GetCommandLine 				; процедура 
	mov edi, eax						; считывания 
    mov esi, OFFSET PASS_LOG			; пароля
    xor ecx, ecx               			; с 
	mov ebx, 10							; консоли
consoleLoop:							;
    mov eax, [edi + ebx]     			;
    mov [esi + ecx], eax   				;
    inc ecx								;
	inc ebx								;
    cmp ebx, 13							;
    jne	consoleLoop						;
	ret
console endp 							;

success proc far
	message TITLE_INFO, STRING_INFO1	; процедура вывода 	
	message TITLE_INFO, STRING_INFO2	; информации про
	message TITLE_INFO, STRING_INFO3	; студента
	call finish							;
success endp							;

fail proc far
	message TITLE_ERR, STRING_ERR		; процедура
	call MessageBox						; вывода сообщения
	call finish							; об ошибке
fail endp								;

finish proc far							; процедура  
	push 0								; завершения
	call ExitProcess					; программы
finish endp 							;

start:
	call console

	hash PASS_LOG, XOR_KEY, EDI	
	compare eax, ebx, offset PASS_LOG, offset PASS_SYS, ecx

end start