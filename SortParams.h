#pragma once
#ifndef MYSTRUCT_H
#define MYSTRUCT_H

/**
    \brief Структура с параметрами сортировки

    Данная структура содержит параметры выполнения сортировки.
*/
struct SortParams {
    /**
        \brief Число элементов
    */
    long long N{ 0 };
    /**
        \brief Парамтер масштаба
    */
    double A{ 0.0 };
    /**
        \brief Параметр формы
    */
    double C{ 0.0 };

    SortParams() = default;

    SortParams(long long n, double a, double c)
        : N(n), A(a), C(c) {
    }
};

#endif // MYSTRUCT_H