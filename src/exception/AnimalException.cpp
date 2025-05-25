#include "../../include/exception/AnimalException.hpp"

AnimalException::AnimalException(const std::string& message) 
    : ZooException("Animal Error: " + message) {}
