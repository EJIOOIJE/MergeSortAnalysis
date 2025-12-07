#pragma once
#include "SortAlgorithms.h"
#include "Generators.h"

/**
    \brief Класс для операций с числами

    Данный класс предоставляет функционал для различных операций с числами.
*/
class Algorithm {
public:
    virtual ~Algorithm() = default;
    
    /**
        \brief Функция генерации числа с распределением fisk

        \param [in] alpha парамтер масштаба

        \param [in] c параметр формы

        \return Число с распределением fisk

        \code{cpp}
        Algorithm::generateFisk(a, c)
        \endcode
    */
    static double generateFisk(double alpha, double c);

    /**
        \brief Функция генерации вектора чисел с распределением fisk

        \param [in] size размер вектора

        \param [in] alpha парамтер масштаба

        \param [in] c параметр формы

        \return Вектор чисел с распределением fisk

        \code{cpp}
        Algorithm::generateFiskArray(n, a, c)
        \endcode
    */
    static std::vector<double> generateFiskArray(long long size, double alpha, double c);

    /**
        \brief Функция сортировки слиянием для вектора<double>

        \param [in,out] arr вектор<double>

        \return Структура SortResult с параметрами сортировки

        \code{cpp}
        Algorithm::mergeSort(vector);
        \endcode
    */
    static SortResult mergeSort(std::vector<double>& arr);
};

/*
#pragma once
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "SortResult.h"

class Algorithm {
public:
    static double generateFisk(double alpha, double c);

    static std::vector<double> generateFiskArray(long long size, double alpha, double c);

    static SortResult mergeSort(std::vector<double>& arr);

private:
    static void mergeSortRecursive(std::vector<double>& arr, long long left, long long right, SortResult& result);

    static void mergeSortmerge(std::vector<double>& arr, long long left, long long mid, long long right, SortResult& result);
};

#endif // ALGORITHM_H
*/