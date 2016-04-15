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
if NOT ERRORLEVEL 0 goto testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program>