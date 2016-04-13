rem @echo off
SET program="%1"
if %program% == "" goto err

echo 0
%program% "input0.txt" "output0.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo 1
%program% "input1.txt" "output1.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo 2
%program% "input2.txt" "output2.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo 3
%program% "input3.txt" "output3.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo 4
%program% "input4.txt" "output4.txt"
if NOT ERRORLEVEL 1 goto testFailed


echo 5
%program% "input5.txt" "output5.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program>