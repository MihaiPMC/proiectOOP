#ifndef ZOO_EXCEPTIONS_H
#define ZOO_EXCEPTIONS_H

#include <exception>
#include <string>

class ZooException : public std::exception {
private:
    std::string m_message;
public:
    explicit ZooException(const std::string& message);
    
    const char* what() const noexcept override;
};

#endif // ZOO_EXCEPTIONS_H
