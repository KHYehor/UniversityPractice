cls 
set filename=LAB2
set masm_path=C:\masm32\bin
set project_path=C:\Users\masm32\Desktop\masm32\LAB2
%masm_path%\ml /Bl link16.exe %filename%.asm
"C:\Users\masm32\Desktop\DOSBox.exe" -c "mount c %project_path%\ " -c c: -c %filename%.COM