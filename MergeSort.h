#pragma once
#include <vector>
#include <iterator>
#include <chrono>
#include "SortResult.h"

/**
    \brief Класс сортировки слиянием

    Данный класс предоставляет функционал для сортировки слиянием различных итерируемых объектов.
*/
template<typename Iterator>
class MergeSort {
public:
    using ValueType = typename std::iterator_traits<Iterator>::value_type;

    /**
        \brief Шаблонная функция сортировки слиянием

        \tparam Iterator - любой итерируемый тип

        \param [in,out] begin начало итерируемого объекта

        \param [in,out] end конец итерируемого объекта

        \return Структура SortResult с параметрами сортировки

        \warning Не рекомендуется использовать напрямую, желательно добавлять перегрузки для отдельных типов
    */
    virtual SortResult sort(Iterator begin, Iterator end) {
        SortResult result;
        if (begin == end || std::next(begin) == end) return result;

        auto start = std::chrono::high_resolution_clock::now();
        mergeSortRecursive(begin, end, result);
        auto endTime = std::chrono::high_resolution_clock::now();

        result.elapsedTimeMs = endTime - start;
        return result;
    }

    /**
        \brief Функция сортировки слиянием для вектора<double>

        \param [in,out] vec вектор<double> 

        \return Структура SortResult с параметрами сортировки

        \code{cpp}
        MergeSort<std::vector<double>::iterator> sort;
        return sort.sort(arr);
        \endcode
    */
    SortResult sort(std::vector<double>& vec) {
        return sort(vec.begin(), vec.end());
    }

private:
    virtual void mergeSortRecursive(Iterator begin, Iterator end, SortResult& result) {
        auto distance = std::distance(begin, end);
        if (distance <= 1) return;

        auto mid = std::next(begin, distance / 2);
        mergeSortRecursive(begin, mid, result);
        mergeSortRecursive(mid, end, result);
        mergeMerge(begin, mid, end, result);
    }

    virtual void mergeMerge(Iterator begin, Iterator mid, Iterator end, SortResult& result) {
        typedef typename std::iterator_traits<Iterator>::value_type T;

        std::vector<T> left(begin, mid);
        std::vector<T> right(mid, end);

        auto itLeft = left.begin();
        auto itRight = right.begin();
        auto it = begin;

        while (itLeft != left.end() && itRight != right.end()) {
            result.comparisons++;
            if (*itLeft <= *itRight) {
                *it = *itLeft;
                ++itLeft;
            }
            else {
                *it = *itRight;
                ++itRight;
            }
            result.swaps++;
            ++it;
        }

        while (itLeft != left.end()) {
            *it = *itLeft;
            ++itLeft;
            ++it;
            result.swaps++;
        }

        while (itRight != right.end()) {
            *it = *itRight;
            ++itRight;
            ++it;
            result.swaps++;
        }
    }
};