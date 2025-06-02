#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Bear : public Animal
{
private:
    std::string m_furColor;
    float m_hibernationMonths;

public:
    Bear(const std::string &name, const std::string &species, int age, float weight, float height,
         const std::string &furColor, float hibernationMonths, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    const std::string &getFurColor() const;
    float getHibernationMonths() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
