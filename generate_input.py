#!/usr/bin/env python3
import sys
import time
import random

DEFAULT_K = 2
DEFAULT_N = 2
DEFAULT_MAX_COORD = 100


def main() -> int:
    argv = sys.argv
    if len(argv) > 5:
        print(f"Uzycie: {argv[0]} [k] [n] [max_coord] [seed]", file=sys.stderr)
        return 1

    try:
        k = int(argv[1]) if len(argv) >= 2 else DEFAULT_K
        n = int(argv[2]) if len(argv) >= 3 else DEFAULT_N
        max_coord = int(argv[3]) if len(argv) >= 4 else DEFAULT_MAX_COORD
    except ValueError:
        print("Blad: niepoprawny argument liczbowy.", file=sys.stderr)
        return 1

    if k <= 0 or n <= 0 or max_coord < 0:
        print("Blad: wymagane k > 0, n > 0, max_coord >= 0.", file=sys.stderr)
        return 1

    if len(argv) == 5:
        try:
            seed = int(argv[4])
        except ValueError:
            print("Blad: niepoprawny seed.", file=sys.stderr)
            return 1
    else:
        seed = time.time_ns()

    rng = random.Random(seed)
    house_count = k * n

    print(f"{k} {n}")
    for _ in range(n):
        print(f"{rng.randint(0, max_coord)} {rng.randint(0, max_coord)}")
    for _ in range(house_count):
        print(f"{rng.randint(0, max_coord)} {rng.randint(0, max_coord)}")

    print(f"params: k={k} n={n} max_coord={max_coord} seed={seed}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
