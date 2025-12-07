#pragma once
#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include "JsonSerializator.h"

/**
    \brief Интерфейс для сериализации

    Данный интерфейс предоставляет функционал для сериализации.
*/
class Serializator : public JsonSerializator {
public:
    virtual ~Serializator() = default;
};

#endif // SERIALIZATOR_H
