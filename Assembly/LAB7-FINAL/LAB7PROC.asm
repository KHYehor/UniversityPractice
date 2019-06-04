.386
.model flat, stdcall
option casemap: none
.data
	public denominator
	extrn ARRAY_D:QWORD, ARRAY_A:QWORD
.code
denominator proc
	fld ARRAY_D[esi * 8]					
	fld ARRAY_A[esi * 8]					; ST(1) <- d, ST(0) <- a
	fsub									; ST(0) <- d - a
	fld1									; ST(1) <- d - a, ST(0) <- 1
	fsub									; ST(0) <- d - a - 1
	ret
denominator endp
end

