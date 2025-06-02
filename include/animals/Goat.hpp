#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Goat : public Animal
{
private:
    float m_hornLength;
    bool m_isClimber;

public:
    Goat(const std::string &name, const std::string &species, int age, float weight, float height,
         float hornLength, bool isClimber, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getHornLength() const;
    bool getIsClimber() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
