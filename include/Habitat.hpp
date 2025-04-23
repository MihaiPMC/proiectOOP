#ifndef HABITAT_H
#define HABITAT_H

#include <string>
#include "Animal.hpp"
#include <iostream>
#include <vector>
#include <map>

class Habitat
{
private:
    std::string type;
    std::vector<Animal> animals;
    int capacity;
    float cleanlinessLevel;
    float price;
    static std::map<std::string, std::vector<std::string>> habitatSpecies;

public:
    Habitat(const std::string &type, const std::vector<Animal> &animals, int capacity = 5, float cleanlinessLevel = 1.0f,
            float price = 10000.0f);
    ~Habitat() = default;
    Habitat(const Habitat &other);
    Habitat(Habitat &&other) noexcept;
    Habitat &operator=(const Habitat &other);
    Habitat &operator=(Habitat &&other) noexcept;

    [[nodiscard]] const std::string &getType() const;
    void setType(const std::string &newType);
    [[nodiscard]] const std::vector<Animal> &getAnimals() const;
    void addAnimals(const std::vector<Animal> &newAnimals);
    void addAnimals(const Animal &animal);
    [[nodiscard]] int getCapacity() const;
    void setCapacity(int newCapacity);
    [[nodiscard]] float getCleanlinessLevel() const;
    void setCleanlinessLevel(float level);
    [[nodiscard]] float getPrice() const;
    void setPrice(float new_price);
    void cleanHabitat();
    void updateCleanliness(float deltaTime);

    static std::map<std::string, std::vector<std::string>> getHabitatSpecies();
    static std::string selectHabitatType();
    void addRandomAnimals(int count, float& budget);

    friend std::ostream &operator<<(std::ostream &os, const Habitat &habitat);
};

#endif //HABITAT_H
