#include "FiskGenerator.h"

FiskGenerator::FiskGenerator()
    : gen(rd()), dis(0.0, 1.0)
{
}

double FiskGenerator::generateFisk(double alpha, double c) {
    double u = dis(gen);
    // избегать u == 0 или u == 1, чтобы избежать деления на 0
    if (u < 1e-15) u = 1e-15;
    if (u > 1 - 1e-15) u = 1 - 1e-15;

    // обратная функция преобразования
    double x = alpha * pow(u / (1 - u), 1.0 / c);

    return x;
}

std::vector<double> FiskGenerator::generateFiskArray(long long size, double alpha, double c) {
    std::vector<double> data(size);
    for (long long i = 0; i < size; ++i) {
        data[i] = generateFisk(alpha, c);
    }
    return data;
}