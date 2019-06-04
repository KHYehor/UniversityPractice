.586
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
	
COMMENT <com>
	---------------------------------
<com>

.data
	
.data?
;;	Данные переменные не инициалирированные 
	RESULT_FIN 		DW    5d DUP (?)
	BUFFER	   		DW  128d DUP (?)
	OUTPUT			DW 1024d DUP (?)
;;	они будут инициалирированны позже
.const
;;	Данные числа необходимы для формулы
	NUMBER1 		DW  2d
	NUMBER2			DW	38d
	NUMBER3 		DW  5d
;;	и вычислений исходя из условия
;;	Данные массивы чисел подставляются
	ARRAY_A			DW -5d, 3d, -12d, 25d,36d
	ARRAY_B 		DW  4d, 6d, 40d, 5d, -35d
	ARRAY_C			DW -2d, -5d, 20d, -7d, 29d
;;	в формулу для вычисления результата
;;	Эти константы для вывода сообщения
	MSG_TITLE		DB "Khilchenko Yehor LAB5", 0, 13
	FORMAT_DEC      DB '%d',10, 0
	SIGN_PLUS		DB "+", 0
	SIGN_MINUS		DB "-", 0
;;	и перевода строки в десятичный формат
.code
;; Эта процедура для вычислений по формуле
;; (2b - 38c)/(b + a/b + 1)
Formula proc far 
;;	Обнуляем данный регистр
;;	он у нас индексный
	xor esi, esi
;;	Здесь будет цикл вычисления
ITERATION:
;;	Первая операция: ax <- 2 * b	
	mov ax, ARRAY_B[esi * 2]
	cwd	
	imul NUMBER1
;;	Загружаем результатат bx <- ax	
	mov bx, ax			
;;	Вторая операция	ax <- 38 * c	
	mov ax, ARRAY_C[esi * 2]
	cwd
	imul NUMBER2 	
;;	Третья операция bx <- bx(2 * b) - ax(38 * c)	
	sub bx, ax
;;	Четвертая операция 	ax <- a / c
	mov ax, ARRAY_A[esi * 2]
	cwd	
	idiv ARRAY_C[esi * 2]	
;;	Пятая операция 	ax <- b + ax (a / c)
	add ax, ARRAY_B[esi * 2]
;;	Шестая операция ax <- ax + 1	
	inc ax	
;;	Меняем в регистрах знаменатель 
	xchg ax, bx					
;;	и числитель местами
;;	Седьмая операция ax <- (...) / (...)
	cwd	
	idiv bx	
;;	Проверка на четность 	
	test ax, 1
	jnz ODD
	jz	EVN
EVN:
;;	Дополнительно делим на 2
	cwd
	idiv NUMBER1
	jmp SIGN
ODD:
;;	Дополнительно умножаем на 5
	cwd
	imul NUMBER3
	jmp SIGN
;;	Проверка на знак
SIGN:
;;	Помещаем в массив ответов наш результат
;;	Сдвиг
	mov RESULT_FIN[esi * 2], ax
	mov bx, ax	
	shl bx, 1                             
	shr bx, 1   

;;	Проверка	
	cmp bx, RESULT_FIN[esi * 2]   
	je positive
	jne negative
	
negative:
;;	Инвертируем результат
	sub RESULT_FIN[esi * 2], 1                            
    not RESULT_FIN[esi * 2]
;;	Добавляем знак минус	
	invoke szCatStr, addr OUTPUT, addr SIGN_MINUS
	jmp final
positive:
;;	Добавляем знак плюс
	invoke szCatStr, addr OUTPUT, addr SIGN_PLUS
	jmp final
final:
;;	Ложим в буфер уже переведенную в десятичную систему число	
	invoke wsprintf, addr BUFFER, addr FORMAT_DEC, RESULT_FIN[esi * 2]
;;	Добавляем её к финальной строке
	invoke szCatStr, addr OUTPUT, addr BUFFER
;;	Повышаем индекс на один
	inc esi
	cmp esi, 5d
	jne ITERATION
;;	Вывод результата
	invoke MessageBox, 0, offset OUTPUT, offset MSG_TITLE, 0 
	
	ret
Formula endp 

start:
	call Formula
	invoke ExitProcess, 0
end start