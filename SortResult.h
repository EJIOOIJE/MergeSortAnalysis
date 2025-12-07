#pragma once
#ifndef SORTRESULT_H
#define SORTRESULT_H

#include <chrono>

/**
    \brief Структура с результатами сортировки

    Данная структура содержит характеристики выполнения сортировки.
*/
struct SortResult {
    /**
        \brief Длительность выполнения сортировки
    */
    std::chrono::duration<double, std::milli> elapsedTimeMs{ 0 };
    /**
        \brief Количество сравнений
    */
    long long comparisons{ 0 };
    /**
        \brief Количество перестановок
    */
    long long swaps{ 0 };

    SortResult() = default;
};

#endif // SORTRESULT_H