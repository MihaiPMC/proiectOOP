#ifndef ANIMAL_EXCEPTION_H
#define ANIMAL_EXCEPTION_H

#include "ZooExceptions.hpp"
#include <string>

class AnimalException : public ZooException {
public:
    explicit AnimalException(const std::string& message);
};

#endif // ANIMAL_EXCEPTION_H
