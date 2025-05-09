#ifndef ZOO_H
#define ZOO_H

#include <string>
#include <vector>
#include <iostream>
#include "Animal.hpp"
#include "Habitat.hpp"
#include "ZooExceptions.hpp"

class Zoo {
private:
    std::string m_name;
    std::vector<Habitat> m_habitats;
    int m_visitorCount;
    bool m_isOpen;
    float m_budget;
public:
    Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float budget = 100000);
    ~Zoo() = default;
    Zoo(const Zoo &other);
    Zoo(Zoo &&other) noexcept;
    Zoo &operator=(const Zoo &other);
    Zoo &operator=(Zoo &&other) noexcept;
    [[nodiscard]] const std::string &getName() const;
    void setName(const std::string &newName);
    [[nodiscard]] const std::vector<Habitat> &getHabitats() const;
    void addHabitats(const std::vector<Habitat> &newHabitats);
    void addHabitats(const Habitat &habitat);
    [[nodiscard]] int getVisitorCount() const;
    void setVisitorCount(int visitor_count);
    [[nodiscard]] bool getIsOpen() const;
    void setIsOpen(bool is_open);
    [[nodiscard]] float getBudget() const;
    void setBudget(float newBudget);
    bool spendMoney(float amount);
    bool buildHabitatAt(const std::string& type, int gridX, int gridY, int gridWidth, int gridHeight);
    bool canBuildAt(int gridX, int gridY, int gridWidth, int gridHeight) const;
    int findHabitatAt(int gridX, int gridY) const;
    bool addAnimalTo(int habitatIndex, const std::string& animalType);
    friend std::ostream &operator<<(std::ostream &os, const Zoo &zoo);
};

#endif //ZOO_H
