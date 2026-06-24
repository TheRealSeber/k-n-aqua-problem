# k-n-aqua-problem

Finding the minimum cost assignment of houses to water sources using flow networks.

This repository now contains equivalent implementations in:

- C++ (`main.cpp`, `generate_input.cpp`)
- Python (`main.py`, `generate_input.py`)
- MATLAB (`main.m`, `generate_input.m`)

## Input / output format

Input format used by all solvers:

```text
k n
w1x w1y
...
wnx wny
h1x h1y
...
h(k*n)x h(k*n)y
```

- `k` - houses assigned per source
- `n` - number of sources
- `k*n` houses follow

Solver output format:

```text
Koszt: <value with 4 decimals>
S1 d...
S2 d...
...
```

## Windows quick start (C++)

For quick check run: `run_example.bat`

```powershell
.\run_example
```

It will:

- run the C++ solver on `examples/example1.txt`,
- generate a random input file,
- run the C++ solver on the generated input.

## C++

### Build

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

### Run solver

Linux / macOS / Git Bash:

```bash
./main < examples/example1.txt
```

Windows CMD:

```cmd
main.exe < examples\example1.txt
```

### Generate random input

```bash
./generate_input [k] [n] [max_coord] [seed] > input.txt
```

Defaults: `k=2`, `n=2`, `max_coord=100`, `seed=current time`.

When `seed` is omitted, each implementation uses its language runtime clock source, so unseeded random streams are not expected to match across languages.

### Reproducible example

```bash
./generate_input 2 3 100 42 > examples/generated.txt
./main < examples/generated.txt
```

## Python

Dependencies: Python 3.x (standard library only).

### Run solver

```bash
python3 main.py < examples/example1.txt
```

### Generate random input

```bash
python3 generate_input.py [k] [n] [max_coord] [seed] > input.txt
```

Defaults and validation rules match C++.

### Reproducible example

```bash
python3 generate_input.py 2 3 100 42 > examples/generated_py.txt
python3 main.py < examples/generated_py.txt
```

## MATLAB

Dependencies: MATLAB (no extra toolboxes required).

Programs are provided as functions and can read either redirected stdin or an input file path argument.

### Run solver

Using stdin redirection:

```bash
matlab -batch "main" < examples/example1.txt
```

Using file path argument:

```bash
matlab -batch "main('examples/example1.txt')"
```

### Generate random input

```bash
matlab -batch "generate_input(2,3,100,42)" > examples/generated_matlab.txt
```

Defaults match C++ when arguments are omitted:

```bash
matlab -batch "generate_input"
```

### Reproducible example

```bash
matlab -batch "generate_input(2,3,100,42)" > examples/generated_matlab.txt
matlab -batch "main('examples/generated_matlab.txt')"
```

## Cross-language consistency check

For the same input file, all three solvers should print the same assignment format and the same cost (within floating-point formatting to 4 decimals).

Example with a single input file:

```bash
./main < examples/example1.txt
python3 main.py < examples/example1.txt
matlab -batch "main('examples/example1.txt')"
```
