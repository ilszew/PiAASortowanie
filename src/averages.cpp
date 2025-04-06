#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <numeric>
#include <iomanip>

namespace fs = std::filesystem;

double average_from_file(const fs::path& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku: " << file_path << std::endl;
        return -1.0;
    }

    std::vector<double> times;
    double time;
    while (file >> time) {
        times.push_back(time);
    }

    if (times.empty()) return -1.0;

    return std::accumulate(times.begin(), times.end(), 0.0) / times.size();
}

int main() {
    std::vector<std::string> algorithms = {"mergesort", "introsort", "quicksort"};
    std::vector<std::string> sizes = {"10000", "50000", "100000", "500000", "1000000"};
    std::vector<std::string> options = {
        "reverse_sorted",
        "sorted_99_7",
        "sorted_99",
        "sorted_95",
        "sorted_75",
        "sorted_50",
        "sorted_25",
        "random_100"
    };

    std::ofstream output("average_times.csv");
    output << "Algorithm,ArraySize,Option,AverageTime\n";

    for (const auto& algo : algorithms) {
        for (const auto& size : sizes) {
            for (const auto& option : options) {
                fs::path file_path = fs::path("results") / algo / size / (option + ".txt");
                double avg_time = average_from_file(file_path);
                if (avg_time >= 0.0) {
                    output << algo << ";" << size << ";" << option << ";" << std::fixed << std::setprecision(6) << avg_time << "\n";
                }
            }
        }
    }

    output.close();
    std::cout << "Script was finished";
    return 0;
}