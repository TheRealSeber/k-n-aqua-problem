# k-n-aqua-problem

Finding the minimum cost assignment of houses to water sources using flow networks.

## Windows quick start

For quick check run: `run_example.bat`

```powershell
.\run_example
```

It will:

- run the solver on `examples/example1.txt`,
- generate a random input file,
- run the solver on the generated input.

You can also run the programs manually as explained below.

## Build

Linux / macOS / Git Bash:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
g++ -std=c++17 -O2 -Wall -Wextra -pedantic generate_input.cpp -o generate_input
```

Windows PowerShell / MinGW / MSYS2:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -pedantic .\main.cpp -o .\main.exe
g++ -std=c++17 -O2 -Wall -Wextra -pedantic .\generate_input.cpp -o .\generate_input.exe
```

## Run solver

Linux / macOS / Git Bash:

```bash
./main < examples/example1.txt
```

Windows PowerShell:

```powershell
Get-Content .\examples\example1.txt | .\main.exe
```

Windows CMD:

```cmd
main.exe < examples\example1.txt
```

Output:

```text
Koszt: ...
S1 d...
S2 d...
```

## Generate random input

Linux / macOS / Git Bash:

```bash
./generate_input [k] [n] [max_coord] [seed] > input.txt
```

Windows PowerShell:

```powershell
.\generate_input.exe [k] [n] [max_coord] [seed] > input.txt
```

Defaults:

```text
k = 2
n = 2
max_coord = 100
seed = current time
```

## Example

Linux / macOS / Git Bash:

```bash
./generate_input 2 3 100 42 > examples/generated.txt
./main < examples/generated.txt
```

Windows PowerShell:

```powershell
.\generate_input.exe 2 3 100 42 > .\examples\generated.txt
Get-Content .\examples\generated.txt | .\main.exe
```

Windows CMD:

```cmd
generate_input.exe 2 3 100 42 > examples\generated.txt
main.exe < examples\generated.txt
```
