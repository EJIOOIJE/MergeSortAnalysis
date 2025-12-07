#pragma once
#ifndef EQUATIONDATA_H
#define EQUATIONDATA_H

#include <vector> 
#include <chrono> 
#include <random>  

/**
    \brief Класс для оценивания связи между временем выполнения сортировки и размером массива 

    Данный класс предоставляет функционал для оценивания связи между временем выполнения программного алгоритма (временной параметр T) и размером задачи (емкостной параметр V).
*/
class EquationData {
private:
    long long N;
    std::vector<long long> time;
    std::vector<long long> size;
    std::vector<long long> sqx;
    std::vector<long long> xmulty;
    std::vector<long long> graphTime;
    std::vector<long long> graphSize;

    double a0;
    double a1;
    double corr;
    double det;
    double elast;
    double beta;

    long long totalTimeMsSum = 0;
    long long totalSizeSum = 0;
    long long totalSqxSum = 0;
    long long totalXmultySum = 0;

    std::mt19937 rng;
    std::uniform_int_distribution<long long> distN;        
    std::uniform_int_distribution<int> distAC;            
    std::uniform_int_distribution<long long> distNCount;

public:
    /**
        \brief Путь к файлу с графиком
    */
    std::string imagePath;

    /**
        \brief Функция генерирующая данные экспериментов

        \warning Функция должна быть использованна первой, после создания экземаляра класса
    */
    void generateSample();

    /**
        \brief Функция вычисляющая свободный и выборочный коэффициенты уравнения связи

        \warning Функция должна быть использованна после вызова generateSample
    */
    void calculateLinearCoefficients();

    /**
        \brief Функция вычисляющая коэффициент парной корреляции уравнения связи

        \warning Функция должна быть использованна после вызова generateSample
    */
    void computeCorrelation();

    /**
        \brief Функция вычисляющая коэффициент детерминации уравнения связи

        \warning Функция должна быть использованна после вызова generateSample
    */
    void computeCoefficientOfDetermination();

    /**
        \brief Функция вычисляющая коэффициент эластичности уравнения связи

        \warning Функция должна быть использованна после вызова generateSample и calculateLinearCoefficients
    */
    void computeElastacity();

    /**
        \brief Функция вычисляющая бета коэффициент уравнения связи

        \warning Функция должна быть использованна после вызова generateSample и calculateLinearCoefficients
    */
    void computeBeta();

    /**
        \brief Функция подготавливающая данные к отображению

        \warning Функция должна быть использованна после вызова generateSample, calculateLinearCoefficients, computeCorrelation, computeCoefficientOfDetermination, computeElastacity, computeBeta
    */
    void prepareData();

    /**
        \brief Конструктор класса, принимающий минимальное и максимальное значение числа элементов в эксперементе, парамтеров масштаба и формы, числа эксперементов

        \param [in] Na минимальное число элементов в эксперементе

        \param [in] Nb максимальное число элементов в эксперементе

        \param [in] ACa минимальное значение парамтеров масштаба и формы

        \param [in] ACb максимальное значение парамтеров масштаба и формы

        \param [in] Counta минимальное число эксперементов

        \param [in] Countb максимальное число эксперементов
    */
    EquationData(
        int Na = 10000,
        int Nb = 40000,
        int ACa = 2,
        int ACb = 10,
        int Counta = 10,
        int Countb = 15
    );

    /**
        \brief Функция получения количества эксперементов

        \return Количество эксперементов
    */
    long long getN() const;

    /**
        \brief Функция устанавливающая количество эксперементов

        \param [in] value количество эксперементов
    */
    void setN(long long value);

    /**
        \brief Функция получения списка значений времени выполнения для каждого эксперемента

        \return Список значений времени выполнения для каждого эксперемента
    */
    std::vector<long long> getTime() const;

    /**
        \brief Функция устанавливающая список значений времени выполнения для каждого эксперемента

        \param [in] value список значений времени выполнения для каждого эксперемента
    */
    void setTime(const std::vector<long long>& value);

    /**
        \brief Функция получения списка значений количества элементов для каждого эксперемента

        \return Список значений количества элементов для каждого эксперемента
    */
    std::vector<long long> getSize() const;

    /**
        \brief Функция устанавливающая список значений количества элементов для каждого эксперемента

        \param [in] value список значений количества элементов для каждого эксперемента
    */
    void setSize(const std::vector<long long>& value);

    /**
        \brief Функция получения списка значений квадрата количества элементов для каждого эксперемента

        \return Список значений квадрата количества элементов для каждого эксперемента
    */
    std::vector<long long> getSqx() const;

    /**
        \brief Функция устанавливающая список значений квадрата количества элементов для каждого эксперемента

        \param [in] value список значений квадрата количества элементов для каждого эксперемента
    */
    void setSqx(const std::vector<long long>& value);

    /**
        \brief Функция получения списка значений времени выполнения на количество элементов для каждого эксперемента

        \return Список значений времени выполнения на количество элементов для каждого эксперемента
    */
    std::vector<long long> getXmulty() const;

    /**
        \brief Функция устанавливающая список значений времени выполнения на количество элементов для каждого эксперемента

        \param [in] value список значений времени выполнения на количество элементов для каждого эксперемента
    */
    void setXmulty(const std::vector<long long>& value);

    /**
        \brief Функция получения свободного коэффициента уравнения связи

        \return Свободный коэффициент уравнения связи
    */
    double getA0() const;

    /**
        \brief Функция устанавливающая свободный коэффициент уравнения связи

        \param [in] value свободный коэффициент уравнения связи
    */
    void setA0(double value);

    /**
        \brief Функция получения выборочного коэффициента уравнения связи

        \return Выборочный коэффициент уравнения связи
    */
    double getA1() const;

    /**
        \brief Функция устанавливающая выборочный коэффициент уравнения связи

        \param [in] value выборочный коэффициент уравнения связи
    */
    void setA1(double value);

    /**
        \brief Функция получения коэффициента парной корреляции уравнения связи

        \return Коэффициент парной корреляции уравнения связи
    */
    double getCorr() const;

    /**
        \brief Функция устанавливающая коэффициент парной корреляции уравнения связи

        \param [in] value коэффициент парной корреляции уравнения связи
    */
    void setCorr(double value);

    /**
        \brief Функция получения коэффициента детерминации уравнения связи

        \return Коэффициент детерминации уравнения связи
    */
    double getDet() const;

    /**
        \brief Функция устанавливающая коэффициент детерминации уравнения связи

        \param [in] value коэффициент детерминации уравнения связи
    */
    void setDet(double value);

    /**
        \brief Функция получения коэффициента эластичности уравнения связи

        \return Коэффициент эластичности уравнения связи
    */
    double getElast() const;

    /**
        \brief Функция устанавливающая коэффициент эластичности уравнения связи

        \param [in] value коэффициент эластичности уравнения связи
    */
    void setElast(double value);

    /**
        \brief Функция получения бета коэффициента уравнения связи

        \return Бета коэффициент уравнения связи
    */
    double getBeta() const;

    /**
        \brief Функция устанавливающая бета коэффициент уравнения связи

        \param [in] value бета коэффициент уравнения связи
    */
    void setBeta(double value);

    /**
        \brief Функция подготавливающая график с данными к отображению

        \warning Функция должна быть использованна после вызова prepareData
    */
    void plotDataAndRegression();
};

#endif // EQUATIONDATA_H