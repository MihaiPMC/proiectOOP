#ifndef BUDGET_EXCEPTION_H
#define BUDGET_EXCEPTION_H

#include "ZooExceptions.hpp"
#include <string>

class BudgetException : public ZooException {
public:
    explicit BudgetException(const std::string& message);
};

#endif // BUDGET_EXCEPTION_H
