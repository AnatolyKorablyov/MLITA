rem @echo off
SET program="%1"
if %program% == "" goto err

mkdir OUT

echo 0
%program% "Input\input0.txt" "OUT\output0.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output0.txt" "standart\test0.txt"
if ERRORLEVEL 1 goto testFailed


echo 1
%program% "Input\input1.txt" "OUT\output1.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output1.txt" "standart\test1.txt"
if ERRORLEVEL 1 goto testFailed

echo 2
%program% "Input\input2.txt" "OUT\output2.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output2.txt" "standart\test2.txt"
if ERRORLEVEL 1 goto testFailed

echo 3
%program% "Input\input3.txt" "OUT\output3.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output3.txt" "standart\test3.txt"
if ERRORLEVEL 1 goto testFailed

echo 4
%program% "Input\input4.txt" "OUT\output4.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output4.txt" "standart\test4.txt"
if ERRORLEVEL 1 goto testFailed


echo 5
%program% "Input\input5.txt" "OUT\output5.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output5.txt" "standart\test5.txt"
if ERRORLEVEL 1 goto testFailed

echo 6
%program% "Input\input6.txt" "OUT\output6.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output6.txt" "standart\test6.txt"
if ERRORLEVEL 1 goto testFailed

echo 7
%program% "Input\input7.txt" "OUT\output7.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output7.txt" "standart\test7.txt"
if ERRORLEVEL 1 goto testFailed

echo 8
%program% "Input\input8.txt" "OUT\output8.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output8.txt" "standart\test8.txt"
if ERRORLEVEL 1 goto testFailed

echo 9
%program% "Input\input9.txt" "OUT\output9.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output9.txt" "standart\test9.txt"
if ERRORLEVEL 1 goto testFailed

echo 10
%program% "Input\input10.txt" "OUT\output10.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output10.txt" "standart\test10.txt"
if ERRORLEVEL 1 goto testFailed

echo 11
%program% "Input\input11.txt" "OUT\output11.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output11.txt" "standart\test11.txt"
if ERRORLEVEL 1 goto testFailed

echo 12
%program% "Input\input12.txt" "OUT\output12.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output12.txt" "standart\test12.txt"
if ERRORLEVEL 1 goto testFailed

echo 13
%program% "Input\input13.txt" "OUT\output13.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output13.txt" "standart\test13.txt"
if ERRORLEVEL 1 goto testFailed

echo 14
%program% "Input\input14.txt" "OUT\output14.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output14.txt" "standart\test14.txt"
if ERRORLEVEL 1 goto testFailed


echo 15
%program% "Input\input15.txt" "OUT\output15.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output15.txt" "standart\test15.txt"
if ERRORLEVEL 1 goto testFailed

echo 16
%program% "Input\input16.txt" "OUT\output16.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output16.txt" "standart\test16.txt"
if ERRORLEVEL 1 goto testFailed

echo 17
%program% "Input\input17.txt" "OUT\output17.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output17.txt" "standart\test17.txt"
if ERRORLEVEL 1 goto testFailed

echo 18
%program% "Input\input18.txt" "OUT\output18.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output18.txt" "standart\test18.txt"
if ERRORLEVEL 1 goto testFailed

echo 19
%program% "Input\input19.txt" "OUT\output19.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output19.txt" "standart\test19.txt"
if ERRORLEVEL 1 goto testFailed

echo 20
%program% "Input\input20.txt" "OUT\output20.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output20.txt" "standart\test20.txt"
if ERRORLEVEL 1 goto testFailed

echo 21
%program% "Input\input21.txt" "OUT\output21.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output21.txt" "standart\test21.txt"
if ERRORLEVEL 1 goto testFailed

echo 22
%program% "Input\input22.txt" "OUT\output22.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output22.txt" "standart\test22.txt"
if ERRORLEVEL 1 goto testFailed

echo 23
%program% "Input\input23.txt" "OUT\output23.txt"
if NOT ERRORLEVEL 1 goto testFailed
fc.exe "OUT\output23.txt" "standart\test23.txt"
if ERRORLEVEL 1 goto testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program>