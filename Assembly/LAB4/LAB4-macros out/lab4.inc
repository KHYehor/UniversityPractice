message	macro titile, mesg 		;;  kill
	push 0						;;	me
	push offset titile			;;	please
	push offset mesg			;;	!!!
	push 0						;;
	call MessageBox				;;
endm							;;

hash macro password, key, register 
local hashloop
	xor register, register
hashloop:	
	XOR password[register], key				
    INC register
    CMP register, 5
    JNE hashloop
endm

compare macro reg1, reg2, pass1, pass2, indx
local comp, match, notmatch
    xor indx, indx
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