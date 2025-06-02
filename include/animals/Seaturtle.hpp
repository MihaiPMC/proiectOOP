#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Seaturtle : public Animal
{
private:
    float m_shellHardness;
    int m_migratingDistance;

public:
    Seaturtle(const std::string &name, const std::string &species, int age, float weight, float height,
              float shellHardness, int migratingDistance, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getShellHardness() const;
    int getMigratingDistance() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
