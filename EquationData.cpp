//#include <Python.h> 
#include "matplotlibcpp.h"
//#include <Eigen/Dense>  
#include "EquationData.h"
#include <ctime>     
#include "Algorithm.h"
#include <numeric> 
#include <cmath> 
#include <algorithm>
#include "Globals.h"
#include "functions.h"
#include <locale>
#include <clocale>
#include <thread>

namespace plt = matplotlibcpp;
namespace fs = std::filesystem;

EquationData::EquationData(
    int Na,
    int Nb,
    int ACa,
    int ACb,
    int Counta,
    int Countb  
) : rng(static_cast<unsigned int>(std::time(nullptr))),
    distN(Na, Nb),
    distAC(ACa, ACb),    
    distNCount(Counta, Countb) 
{
    generateSample();
    calculateLinearCoefficients();
    computeCorrelation();
    computeCoefficientOfDetermination();
    computeElastacity();
    computeBeta();
    prepareData();
    plotDataAndRegression();
    plt::close();
}

long long EquationData::getN() const {
    return N;
}

void EquationData::setN(long long value) {
    N = value;
}

std::vector<long long> EquationData::getTime() const {
    return time;
}

void EquationData::setTime(const std::vector<long long>& value) {
    time = value;
}

std::vector<long long> EquationData::getSize() const {
    return size;
}

void EquationData::setSize(const std::vector<long long>& value) {
    size = value;
}

std::vector<long long> EquationData::getSqx() const {
    return sqx;
}

void EquationData::setSqx(const std::vector<long long>& value) {
    sqx = value;
}

std::vector<long long> EquationData::getXmulty() const {
    return xmulty;
}

void EquationData::setXmulty(const std::vector<long long>& value) {
    xmulty = value;
}

double EquationData::getA0() const {
    return a0;
}

void EquationData::setA0(double value) {
    a0 = value;
}

double EquationData::getA1() const {
    return a1;
}

void EquationData::setA1(double value) {
    a1 = value;
}

double EquationData::getCorr() const {
    return corr;
}

void EquationData::setCorr(double value) {
    corr = value;
}

double EquationData::getDet() const {
    return det;
}

void EquationData::setDet(double value) {
    det = value;
}

double EquationData::getElast() const {
    return elast;
}

void EquationData::setElast(double value) {
    elast = value;
}

double EquationData::getBeta() const {
    return beta;
}

void EquationData::setBeta(double value) {
    beta = value;
}

void EquationData::generateSample() {
    N = distNCount(rng);

    time.resize(N);
    size.resize(N);
    sqx.resize(N);
    xmulty.resize(N);

    for (long long i = 0; i < N; ++i) {
        long long n = distN(rng);
        double A = distAC(rng);
        double C = distAC(rng);

        std::vector<double> data = Algorithm::generateFiskArray(n, A, C);
        SortResult res = Algorithm::mergeSort(data);

        long long elapsedTimeMs = static_cast<long long>(res.elapsedTimeMs.count());
        long long squx = n * n;
        long long xmuly = n * elapsedTimeMs;

        time[i] = elapsedTimeMs;
        size[i] = n;
        sqx[i] = squx;
        xmulty[i] = xmuly;

        totalTimeMsSum += elapsedTimeMs;
        totalSizeSum += n;
        totalSqxSum += squx;
        totalXmultySum += xmuly;
    }
}

void EquationData::calculateLinearCoefficients() {
    const long long n = N;
    if (n < 2) return; 

    double meanSize = totalSizeSum / n;
    double meanTime = totalTimeMsSum / n;

    double numerator = 0.0;
    double denominator = 0.0;

    for (long long i = 0; i < n; ++i) {
        double diffX = size[i] - meanSize;
        double diffY = time[i] - meanTime;
        numerator += diffX * diffY;
        denominator += diffX * diffX;
    }

    if (denominator == 0.0) {
        a0 = meanTime;
        a1 = 0.0;
    }
    else {
        a1 = numerator / denominator;
        a0 = meanTime - a1 * meanSize;
    }
}

void EquationData::computeCorrelation() {
    size_t n = N;
    if (n < 2) return;

    double meanSize = totalSizeSum / n;
    double meanTime = totalTimeMsSum / n;

    double numerator = 0.0;
    double denomX = 0.0, denomY = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double diffX = size[i] - meanSize;
        double diffY = time[i] - meanTime;
        numerator += diffX * diffY;
        denomX += diffX * diffX;
        denomY += diffY * diffY;
    }

    double denom = std::sqrt(denomX * denomY);
    if (denom == 0.0) 
        corr = 0.0;
    else
        corr = numerator / denom;
}

void EquationData::computeCoefficientOfDetermination() {
    size_t n = N;
    if (n < 2) return;

    det = corr * corr;
}

void EquationData::computeElastacity() {
    size_t n = N;
    if (n < 2) return;

    if (a1 == 0.0) 
        elast = 0.0;
    else {
        double meanSize = totalSizeSum / N;
        double meanTime = totalTimeMsSum / N;
        elast = a1 * (meanSize / meanTime);
    }
}

void EquationData::computeBeta() {
    size_t n = N;
    if (n < 2) return;

    double meanSize = totalSizeSum / n;
    double meanTime = totalTimeMsSum / n;

    double sumSqDiffX = 0.0;
    double sumSqDiffY = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double diffX = size[i] - meanSize;
        double diffY = time[i] - meanTime;
        sumSqDiffX += diffX * diffX;
        sumSqDiffY += diffY * diffY;
    }

    double sx = std::sqrt(sumSqDiffX / n);
    double sy = std::sqrt(sumSqDiffY / n);

    if (sy == 0.0) 
        beta  = 0.0;
    else
        beta = a1 * (sx / sy);
}

void EquationData::prepareData() {
    graphTime = time;
    graphSize = size;
    time.push_back(totalTimeMsSum);
    size.push_back(totalSizeSum);
    sqx.push_back(totalSqxSum);
    xmulty.push_back(totalXmultySum);
}

void EquationData::plotDataAndRegression() {
    size_t n = N;

    double minX = *std::min_element(graphSize.begin(), graphSize.end());
    double maxX = *std::max_element(graphSize.begin(), graphSize.end());

    std::vector<double> dataX(graphSize.begin(), graphSize.end());
    std::vector<double> dataY(graphTime.begin(), graphTime.end());

    int numPoints = 100;
    std::vector<double> regX, regY;
    double step = (maxX - minX) / (numPoints - 1);
    for (int i = 0; i < numPoints; ++i) {
        double x = minX + i * step;
        double y = a0 + a1 * x; 
        regX.push_back(x);
        regY.push_back(y);
    }

    if (!fs::exists(TEMP_FOLDER)) {
        fs::create_directories(TEMP_FOLDER);
    }

    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    imagePath = (fs::path(TEMP_FOLDER) / "tempGraph.png").string();

    plt::figure_size(800, 600);
    plt::scatter(dataX, dataY, 10.0);
    plt::plot(regX, regY, std::string("r-"));
    plt::xlabel(std::string("Размер (size)"));
    plt::ylabel(std::string("Время (ms)"));
    plt::title(std::string("Связь времени выполнения от размера"));
    plt::legend();
    plt::save(imagePath);

    setlocale(LC_ALL, "Russian");
    imagePath = (fs::path(TEMP_FOLDER) / "tempGraph.png").string();
}