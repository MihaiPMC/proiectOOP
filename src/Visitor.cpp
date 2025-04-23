#include "../include/Visitor.hpp"

Visitor::Visitor(const std::string &name, int age, float money, const std::string &type)
    : name(name),
      age(age),
      money(money),
      type(type)
{
}

Visitor::Visitor(const Visitor &other)
    : name(other.name),
      age(other.age),
      money(other.money),
      type(other.type)
{
}

Visitor::Visitor(Visitor &&other) noexcept
    : name(std::move(other.name)),
      age(other.age),
      money(other.money),
      type(other.type)
{
}

Visitor &Visitor::operator=(const Visitor &other)
{
    if (this == &other)
        return *this;
    name = other.name;
    age = other.age;
    money = other.money;
    type = other.type;
    return *this;
}

Visitor &Visitor::operator=(Visitor &&other) noexcept
{
    if (this == &other)
        return *this;
    name = std::move(other.name);
    age = other.age;
    money = other.money;
    type = other.type;
    return *this;
}

const std::string &Visitor::getName() const
{
    return name;
}

void Visitor::setName(const std::string &NewName)
{
    this->name = NewName;
}

int Visitor::getAge() const
{
    return age;
}

void Visitor::setAge(int newAge)
{
    this->age = newAge;
}

float Visitor::getMoney() const
{
    return money;
}

void Visitor::setMoney(float newMoney)
{
    this->money = newMoney;
}

const std::string &Visitor::getType() const
{
    return type;
}

void Visitor::setType(const std::string &newType)
{
    this->type = newType;
}

std::ostream &operator<<(std::ostream &os, const Visitor &visitor)
{
    os << "Visitor: " << visitor.name << "\n"
       << "  Type: " << visitor.type << "\n"
       << "  Age: " << visitor.age << " years\n"
       << "  Money: $" << visitor.money;
    return os;
}
