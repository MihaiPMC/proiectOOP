#ifndef HABITAT_EXCEPTION_H
#define HABITAT_EXCEPTION_H

#include "ZooExceptions.hpp"
#include <string>

class HabitatException : public ZooException {
public:
    explicit HabitatException(const std::string& message);
};

#endif // HABITAT_EXCEPTION_H
