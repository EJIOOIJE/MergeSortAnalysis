#pragma once
#include <vector>
#include <cmath>
#include <random>

/**
    \brief Класс генераторов чисел с распределением fisk

    Данный класс предоставляет функционал для генерации различных типов данных с распределением fisk.
*/
class FiskGenerator {
public:
    FiskGenerator();

    /**
        \brief Функция генерации числа с распределением fisk

        \param [in] alpha парамтер масштаба

        \param [in] c параметр формы

        \return Число с распределением fisk

        \code{cpp}
        FiskGenerator gen;
        return gen.generateFisk(alpha, c);
        \endcode
    */
    double generateFisk(double alpha, double c);

    /**
        \brief Функция генерации вектора чисел с распределением fisk

        \param [in] size размер вектора

        \param [in] alpha парамтер масштаба

        \param [in] c параметр формы

        \return Вектор чисел с распределением fisk

        \code{cpp}
        FiskGenerator gen;
        return gen.generateFiskArray(size, alpha, c);
        \endcode
    */
    std::vector<double> generateFiskArray(long long size, double alpha, double c);

private:    
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
};