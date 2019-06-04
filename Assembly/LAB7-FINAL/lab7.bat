ml /Fl lab7.asm LAB7PROC.asm
ml /c /coff LAB7PROC.asm lab7.asm
link /subsystem:windows lab7.obj LAB7PROC.obj
lab7.exe