#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Camel : public Animal
{
private:
    int m_humpsCount;

public:
    Camel(const std::string &name, const std::string &species, int age, float weight, float height,
          int humpsCount, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    int getHumpsCount() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
