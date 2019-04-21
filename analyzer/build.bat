@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:bin\x64\analyzer.exe
cl.exe %compilerflags% analyzer\src\main.cpp /link %linkerflags%
del bin\x64\*.ilk *.obj *.pdb