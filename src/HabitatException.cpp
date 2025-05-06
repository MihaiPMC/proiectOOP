#include "../include/HabitatException.hpp"

HabitatException::HabitatException(const std::string& message) 
    : ZooException("Habitat Error: " + message) {}
