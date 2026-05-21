@echo off
echo Running example input...
main.exe < examples\example1.txt

echo.
echo Generating random input...
generate_input.exe 2 3 100 42 > examples\generated.txt

echo.
echo Running generated input...
main.exe < examples\generated.txt

echo.
pause