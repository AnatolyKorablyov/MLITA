rem @echo off
SET program="%1"
if %program% == "" goto err

echo 1
%program% "input.txt" "output.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo 2
%program% "input1.txt" "output2.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo 3
%program% "input2.txt" "output3.txt"
if NOT ERRORLEVEL 1 goto testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program>