#pragma once
#include "Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Mammal : public Animal {
private:
    std::string m_furColor;
public:
    Mammal(const std::string &name, const std::string &species, int age, float weight, float height, const std::string &furColor, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);
    const std::string &getFurColor() const;
    void setFurColor(const std::string &color);
    virtual void performBehavior() const override;
    virtual float interact(int visitorCount) const override;
    virtual std::shared_ptr<Animal> clone() const override;
};
