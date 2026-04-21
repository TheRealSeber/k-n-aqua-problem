#include <chrono>
#include <iostream>
#include <random>

int main(int argc, char** argv) {
    constexpr int DEFAULT_K         = 2;
    constexpr int DEFAULT_N         = 2;
    constexpr int DEFAULT_MAX_COORD = 100;

    if (argc > 5) {
        std::cerr << "Uzycie: " << argv[0] << " [k] [n] [max_coord] [seed]\n";
        return 1;
    }

    int k        = (argc >= 2) ? std::stoi(argv[1]) : DEFAULT_K;
    int n        = (argc >= 3) ? std::stoi(argv[2]) : DEFAULT_N;
    int maxCoord = (argc >= 4) ? std::stoi(argv[3]) : DEFAULT_MAX_COORD;

    if (k <= 0 || n <= 0 || maxCoord < 0) {
        std::cerr << "Blad: wymagane k > 0, n > 0, max_coord >= 0.\n";
        return 1;
    }

    unsigned int seed = (argc == 5)
                        ? static_cast<unsigned int>(std::stoul(argv[4]))
                        : static_cast<unsigned int>(
                              std::chrono::high_resolution_clock::now().time_since_epoch().count());

    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> coordDist(0, maxCoord);

    int houseCount = k * n;

    std::cout << k << " " << n << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << coordDist(rng) << " " << coordDist(rng) << "\n";
    }
    for (int i = 0; i < houseCount; i++) {
        std::cout << coordDist(rng) << " " << coordDist(rng) << "\n";
    }

    std::cerr << "params: k=" << k << " n=" << n << " max_coord=" << maxCoord
              << " seed=" << seed << "\n";
    return 0;
}
