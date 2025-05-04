#include "../include/Visitor.hpp"

Visitor::Visitor(const std::string &name, int age, float money, const std::string &type)
    : m_name(name), m_age(age), m_money(money), m_type(type)
{
}

Visitor::Visitor(const Visitor &other)
    : m_name(other.m_name), m_age(other.m_age), m_money(other.m_money), m_type(other.m_type)
{
}

Visitor::Visitor(Visitor &&other) noexcept
    : m_name(std::move(other.m_name)), m_age(other.m_age), m_money(other.m_money), m_type(other.m_type)
{
}

Visitor &Visitor::operator=(const Visitor &other)
{
    if (this == &other)
        return *this;
    m_name = other.m_name;
    m_age = other.m_age;
    m_money = other.m_money;
    m_type = other.m_type;
    return *this;
}

Visitor &Visitor::operator=(Visitor &&other) noexcept
{
    if (this == &other)
        return *this;
    m_name = std::move(other.m_name);
    m_age = other.m_age;
    m_money = other.m_money;
    m_type = other.m_type;
    return *this;
}

const std::string &Visitor::getName() const
{
    return m_name;
}

void Visitor::setName(const std::string &NewName)
{
    m_name = NewName;
}

int Visitor::getAge() const
{
    return m_age;
}

void Visitor::setAge(int newAge)
{
    m_age = newAge;
}

float Visitor::getMoney() const
{
    return m_money;
}

void Visitor::setMoney(float newMoney)
{
    m_money = newMoney;
}

const std::string &Visitor::getType() const
{
    return m_type;
}

void Visitor::setType(const std::string &newType)
{
    m_type = newType;
}

std::ostream &operator<<(std::ostream &os, const Visitor &visitor)
{
    os << "Visitor: " << visitor.m_name << "\n"
            << "  Type: " << visitor.m_type << "\n"
            << "  Age: " << visitor.m_age << " years\n"
            << "  Money: $" << visitor.m_money;
    return os;
}
