#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <iostream>
#include <vector>

class Staff
{
private:
    std::string name;
    std::string position;
    int age;
    float salary;

public:
    Staff(const std::string &name, const std::string &position, int age, float salary);
    ~Staff() = default;
    Staff(const Staff &other);
    Staff(Staff &&other) noexcept;
    Staff &operator=(const Staff &other);
    Staff &operator=(Staff &&other) noexcept;

    [[nodiscard]] const std::string &getName() const;
    void setName(const std::string &newName);
    [[nodiscard]] const std::string &getPosition() const;
    void setPosition(const std::string &newPosition);
    [[nodiscard]] int getAge() const;
    void setAge(int newAge);
    [[nodiscard]] float getSalary() const;
    void setSalary(float newSalary);

    friend std::ostream &operator<<(std::ostream &os, const Staff &staff);
};

#endif //STAFF_H
