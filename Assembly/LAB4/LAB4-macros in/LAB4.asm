.586 
.model flat, stdcall
.LALL
; ml /c /coff /Cp lab4.asm
; link /SUBSYSTEM:WINDOWS lab4.obj
; через консоль lab4.exe password...

	include /masm32/include/user32.inc
	include /masm32/include/kernel32.inc
	
	includelib /masm32/lib/user32.lib
	includelib /masm32/lib/kernel32.lib
	
	include /masm32/macros/macros.asm 
	
	
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

	message	macro titile, mesg					; макрос для
		push 0									; вывода
		push offset titile						; сообщения 	 
		push offset mesg						;; на экран
		push 0									; с помощью	
		call MessageBox							;; функции библиотеки
	endm										

	hash macro password, key, register 			;; макрос
	local hashloop								; для хэширования
		xor register, register					; пароля
	hashloop:	
		XOR password[register], key
		INC register
		CMP register, 5
		JNE hashloop
	endm

	compare macro reg1, reg2, pass1, pass2, indx	; макрос для сравнения пароля 
	local comp, match, notmatch						;; системы и вводимого 
		xor indx, indx								;;
		mov edi, pass1
		mov esi, pass2
	comp:	
		mov reg1, [pass1 + indx]
		mov reg2, [pass2 + indx]
		cmp reg1, reg2
		jne not_match
		inc indx
		cmp indx, 5
		jne comp
		
		je match
		jne not_match
	match:
		call success
	not_match:
		call fail	
	endm


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
	ret									;
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
