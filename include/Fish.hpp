#pragma once
#include "Animal.hpp"
#include <memory>
#include <iostream>
#include <string>

class Fish : public Animal {
private:
    std::string m_finType;
public:
    Fish(const std::string &name, const std::string &species, int age, float weight, float height, const std::string &finType, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);
    const std::string &getFinType() const;
    void setFinType(const std::string &finType);
    virtual void performBehavior() const override;
    virtual float interact(int visitorCount) const override;
    virtual std::shared_ptr<Animal> clone() const override;
};
