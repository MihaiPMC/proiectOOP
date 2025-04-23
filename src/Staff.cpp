#include "../include/Staff.hpp"

Staff::Staff(const std::string &name, const std::string &position, int age, float salary)
    : name(name),
      position(position),
      age(age),
      salary(salary)
{
}

Staff::Staff(const Staff &other)
    : name(other.name),
      position(other.position),
      age(other.age),
      salary(other.salary)
{
}

Staff::Staff(Staff &&other) noexcept
    : name(std::move(other.name)),
      position(std::move(other.position)),
      age(other.age),
      salary(other.salary)
{
}

Staff &Staff::operator=(const Staff &other)
{
    if (this == &other)
        return *this;
    name = other.name;
    position = other.position;
    age = other.age;
    salary = other.salary;
    return *this;
}

Staff &Staff::operator=(Staff &&other) noexcept
{
    if (this == &other)
        return *this;
    name = std::move(other.name);
    position = std::move(other.position);
    age = other.age;
    salary = other.salary;
    return *this;
}

const std::string &Staff::getName() const
{
    return name;
}

void Staff::setName(const std::string &newName)
{
    this->name = newName;
}

const std::string &Staff::getPosition() const
{
    return position;
}

void Staff::setPosition(const std::string &newPosition)
{
    this->position = newPosition;
}

int Staff::getAge() const
{
    return age;
}

void Staff::setAge(int newAge)
{
    this->age = newAge;
}

float Staff::getSalary() const
{
    return salary;
}

void Staff::setSalary(float newSalary)
{
    this->salary = newSalary;
}

std::ostream &operator<<(std::ostream &os, const Staff &staff)
{
    os << "Staff: " << staff.name << "\n"
       << "  Position: " << staff.position << "\n"
       << "  Age: " << staff.age << " years\n"
       << "  Salary: $" << staff.salary;
    return os;
}
