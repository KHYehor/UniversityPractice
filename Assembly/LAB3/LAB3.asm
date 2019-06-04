.586 
.model flat, stdcall

; ml /c /coff /Cp lab3.asm
; link /SUBSYSTEM:WINDOWS lab3.obj
; через консоль lab3.exe password...

;	include /masm32/include/windows.inc
	include /masm32/include/user32.inc
	include /masm32/include/kernel32.inc
	
	includelib /masm32/lib/user32.lib
	includelib /masm32/lib/kernel32.lib
	
	include /masm32/macros/macros.asm 
	uselib masm32, comctl32, ws2_32 

.data
	PASS_LOG	DD	14 DUP (?)
.const
	STRING_INFO	DB	"KHilchenko Yehor Andreevich", 0DH, 0AH, "Birth: 12.03.2000", 0DH, 0AH, "Student book: IP-7426", 0, 13
	XOR_KEY	   EQU 	4h
	STRING_ERR	DB	'Your password is incorrect!', 0, 13
	PASS_SYS	DB  '56701'
.code	
start:
	call GetCommandLine ; console goes to eax 
	
	mov edi, eax
    mov esi, OFFSET PASS_LOG
    xor ecx, ecx               
	mov ebx, 10
@CONSOLE:
    mov eax, [edi + ebx]     
    mov [esi + ecx], eax   
    inc ecx
	inc ebx
    cmp ebx, 13
    jne	@CONSOLE

	MOV EDI, 0
@HASH:
    XOR PASS_LOG[EDI], XOR_KEY
    INC EDI
    CMP EDI, 5
    JNE @HASH
	
	mov edi, offset PASS_LOG
    mov esi, OFFSET PASS_SYS
    xor ecx, ecx
@COMPARE:
	mov eax, [edi + ecx]
	mov ebx, [esi + ecx]
	cmp eax, ebx
	jne @FAILED
	inc ecx
	cmp ecx, 5
	jne @COMPARE
	
	je @SUCCESS
	jne @FAILED
@SUCCESS:
	push 0
	push chr$("Student Personal DATA")
	push offset STRING_INFO
	push 0
	call MessageBox
	jmp @EXIT
@FAILED:
	push 0
	push chr$("Password error")
	push offset STRING_ERR
	push 0
	call MessageBox
	jmp @EXIT
@EXIT:
	push 0	
	call ExitProcess

end start