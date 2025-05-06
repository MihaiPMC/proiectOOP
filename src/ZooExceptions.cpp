#include "../include/ZooExceptions.hpp"

ZooException::ZooException(const std::string& message) : m_message(message) {}

const char* ZooException::what() const noexcept {
    return m_message.c_str();
}
