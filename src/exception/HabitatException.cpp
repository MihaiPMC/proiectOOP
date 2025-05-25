#include "../../include/exception/HabitatException.hpp"

HabitatException::HabitatException(const std::string &message)
    : ZooException("Habitat Error: " + message)
{
}
