.586 
.model flat,stdcall 
option casemap:none 

;including propriate libs
include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 
include \masm32\include\user32.inc 

includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib 

.data 
	
	;ddd EQU 1567h
	
	ABpos DB  12
	ABneg DB -12

	AWpos DW  12
	AWneg DW -12
	BWpos DW  1203
	BWneg DW -1203

	AQpos DQ  12
	AQneg DQ -12
	BQpos DQ  1203
	BQneg DQ -1203
	CQpos DQ  12032000
	CQneg DQ -12032000

	DBpos DQ  0.002
	DBneg DQ -0.002

	EBpos DQ  0.162
	EBneg DQ -0.162

	FTpos DT  1620.253
	FTneg DT -1620.253
	N     DW  7426

	MsgBoxCaption  db "LAB1 OUTPUT VARIBLES",0
	
	buffAp db 30 DUP (?)
	buffAn db 30 DUP (?)
	buffBp db 30 DUP (?)
	buffBn db 30 DUP (?)
	buffCp db 30 DUP (?)
	buffCn db 30 DUP (?)
	buffDp db 30 DUP (?)
	buffDn db 30 DUP (?)
	buffEp db 30 DUP (?)
	buffEn db 30 DUP (?)
	buffFp db 30 DUP (?)
	buffFn db 30 DUP (?)
	
	formatAp  db " A = %x",0
	formatAn  db "-A = %x",0
	formatBp  db " B = %x",0
	formatBn  db "-B = %x",0
	formatCp  db " C = %x",0
	formatCn  db "-C = %x",0
	formatDp  db " D = %x",0
	formatDn  db "-D = %x",0
	formatEp  db " E = %x%x",0
	formatEn  db "-E = %x%x",0
	formatFp  db " F = %x%x%x",0
	formatFn  db "-F = %x%x%x",0
	
	format db	"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",13,
				"%s",0
				
	buff db 128 DUP(?)

.code 
start: 
	invoke wsprintf,addr buffAp,addr formatAp,AQpos
	invoke wsprintf,addr buffAn,addr formatAn,AQneg
	invoke wsprintf,addr buffBp,addr formatBp,BQpos
	invoke wsprintf,addr buffBn,addr formatBn,BQneg
	invoke wsprintf,addr buffCp,addr formatCp,CQpos
	invoke wsprintf,addr buffCn,addr formatCn,CQneg
	invoke wsprintf,addr buffDp,addr formatDp,DBpos
	invoke wsprintf,addr buffDn,addr formatDn,DBneg
	invoke wsprintf,addr buffEp,addr formatEp,EBpos
	invoke wsprintf,addr buffEn,addr formatEn,EBpos
	invoke wsprintf,addr buffFp,addr formatFp,FTpos
	invoke wsprintf,addr buffFn,addr formatFn,FTneg
	
	invoke wsprintf,addr buff,addr format,addr buffAp,addr buffAn,addr buffBp,addr buffBn,addr buffCp,addr buffCn,addr buffDp,addr buffDn,addr buffEp,addr buffEn,addr buffFp,addr buffFn
	invoke MessageBox,0,addr buff,addr MsgBoxCaption,0
	
	mov DL, [EAX - 15D]
	mov ECX, [EDI + ESI * 4]
	;mov byte ptr [00401212], 110d
	
	invoke ExitProcess, NULL 
end start