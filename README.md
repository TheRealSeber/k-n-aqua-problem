# k-n-aqua-problem
Finding the minimum cost assignment of houses to water sources using flow networks

## Build
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
g++ -std=c++17 -O2 -Wall -Wextra -pedantic generate_input.cpp -o generate_input
```

Windows (MinGW / MSYS2):
```powershell
g++ -std=c++17 -O2 -Wall -Wextra -pedantic .\main.cpp -o .\main.exe
g++ -std=c++17 -O2 -Wall -Wextra -pedantic .\generate_input.cpp -o .\generate_input.exe
```

## Run solver
```bash
./main < examples/example1.txt
```

Program output now starts with total assignment cost:
```text
Koszt: ...
S1 d...
S2 d...
```

## Generate random input
```bash
./generate_input [k] [n] [max_coord] [seed] > input.txt
```

Defaults:
- `k=2`
- `n=2`
- `max_coord=100`
- `seed` is optional (when missing, current time is used)

Example:
```bash
./generate_input 2 3 100 42 > examples/generated.txt
./main < examples/generated.txt
```

Example with defaults:
```bash
./generate_input > examples/generated_default.txt
./main < examples/generated_default.txt
```
