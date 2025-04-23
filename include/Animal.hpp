//
// Created by Mihai Patru on 25.03.2025.
//

#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>
#include <vector>

class Animal
{
private:
    std::string name;
    std::string species;
    int age;
    float weight;
    float height;
    float isHealthy;
    int price;
    float foodLevel;
    static std::vector<std::string> animalNames;

public:
    Animal(const std::string &name, const std::string &species, int age, float weight, float height,
           float is_healthy = 1.0f, int price = 1000, float hunger = 0.0f);
    ~Animal() = default;

    Animal(const Animal &other);

    Animal(Animal &&other) noexcept;

    Animal &operator=(const Animal &other);

    Animal &operator=(Animal &&other) noexcept;

    [[nodiscard]] const std::string &getName() const;
    void setName(const std::string &newName);

    [[nodiscard]] const std::string &getSpecies() const;
    void setSpecies(const std::string &newSpecies);

    [[nodiscard]] int getAge() const;
    void setAge(int newAge);

    [[nodiscard]] float getWeight() const;
    void setWeight(float newWeight);

    [[nodiscard]] float getHeight() const;
    void setHeight(float newHeight);

    [[nodiscard]] float getIsHealthy() const;
    void setIsHealthy(float is_healthy);

    [[nodiscard]] int getPrice() const;
    void setPrice(int new_price);

    [[nodiscard]] float getHunger() const;
    void setHunger(float newHunger);

    void updateHealth();
    void updateHunger(float deltaTime);

    friend std::ostream &operator<<(std::ostream &os, const Animal &animal);

    static std::string getRandomName();
    static Animal createRandomAnimal(const std::string& species, int minAge = 1, int maxAge = 10);
};

#endif //ANIMAL_H

