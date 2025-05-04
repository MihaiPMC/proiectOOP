#ifndef VISITOR_H
#define VISITOR_H

#include <string>
#include <iostream>
#include <vector>
class Visitor {
private:
    std::string m_name;
    int m_age;
    float m_money;
    std::string m_type;
public:
    Visitor(const std::string &name, int age, float money, const std::string &type);
    ~Visitor() = default;
    Visitor(const Visitor &other);
    Visitor(Visitor &&other) noexcept;
    Visitor &operator=(const Visitor &other);
    Visitor &operator=(Visitor &&other) noexcept;
    [[nodiscard]] const std::string &getName() const;
    void setName(const std::string &NewName);
    [[nodiscard]] int getAge() const;
    void setAge(int newAge);
    [[nodiscard]] float getMoney() const;
    void setMoney(float newMoney);
    [[nodiscard]] const std::string &getType() const;
    void setType(const std::string &newType);
    friend std::ostream &operator<<(std::ostream &os, const Visitor &visitor);
};

#endif //VISITOR_H
