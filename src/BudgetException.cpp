#include "../include/BudgetException.hpp"

BudgetException::BudgetException(const std::string& message) 
    : ZooException("Budget Error: " + message) {}
