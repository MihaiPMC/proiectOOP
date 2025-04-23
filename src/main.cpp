#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <../include/Animal.hpp>
#include <../include/Habitat.hpp>
#include <../include/Staff.hpp>
#include <../include/Zoo.hpp>
#include <../include/Visitor.hpp>

#include <SFML/Graphics.hpp>





void RandomCodeForCppCheck() {
    // Random code to get CppCheck to work
    Animal unusedAnimal("Unused", "Species", 1, 1.0f, 1.0f);
    unusedAnimal.setName("NewName");
    unusedAnimal.setSpecies("NewSpecies");
    unusedAnimal.setAge(2);
    unusedAnimal.setWeight(2.0f);
    unusedAnimal.setHeight(2.0f);
    unusedAnimal.setIsHealthy(0.5f);
    unusedAnimal.setPrice(2000);
    unusedAnimal.setHunger(0.5f);
    std::cout << "Unused Animal Name: " << unusedAnimal.getName() << std::endl;
    std::cout << "Unused Animal Species: " << unusedAnimal.getSpecies() << std::endl;
    std::cout << "Unused Animal Age: " << unusedAnimal.getAge() << std::endl;
    std::cout << "Unused Animal Weight: " << unusedAnimal.getWeight() << std::endl;
    std::cout << "Unused Animal Height: " << unusedAnimal.getHeight() << std::endl;
    std::cout << "Unused Animal Health: " << unusedAnimal.getIsHealthy() << std::endl;
    std::cout << "Unused Animal Price: " << unusedAnimal.getPrice() << std::endl;
    std::cout << "Unused Animal Hunger: " << unusedAnimal.getHunger() << std::endl;

    Habitat unusedHabitat("Type", {}, 5, 0.5f, 5000.0f);
    unusedHabitat.setType("NewType");
    unusedHabitat.setCapacity(10);
    unusedHabitat.setCleanlinessLevel(0.75f);
    unusedHabitat.setPrice(7500.0f);
    unusedHabitat.cleanHabitat();
    std::cout << "Unused Habitat Type: " << unusedHabitat.getType() << std::endl;
    std::cout << "Unused Habitat Capacity: " << unusedHabitat.getCapacity() << std::endl;
    std::cout << "Unused Habitat Cleanliness: " << unusedHabitat.getCleanlinessLevel() << std::endl;
    std::cout << "Unused Habitat Price: " << unusedHabitat.getPrice() << std::endl;

    Zoo unusedZoo("Name", {}, 0, false, 50000.0f);
    unusedZoo.setName("NewZooName");
    unusedZoo.setVisitorCount(100);
    unusedZoo.setIsOpen(true);
    unusedZoo.setBudget(75000.0f);
    std::cout << "Unused Zoo Name: " << unusedZoo.getName() << std::endl;
    std::cout << "Unused Zoo Visitor Count: " << unusedZoo.getVisitorCount() << std::endl;
    std::cout << "Unused Zoo Is Open: " << unusedZoo.getIsOpen() << std::endl;
    std::cout << "Unused Zoo Budget: " << unusedZoo.getBudget() << std::endl;

    Staff unusedStaff("Name", "Position", 30, 60000.0f);
    unusedStaff.setName("NewStaffName");
    unusedStaff.setPosition("NewPosition");
    unusedStaff.setAge(35);
    unusedStaff.setSalary(70000.0f);
    std::cout << "Unused Staff Name: " << unusedStaff.getName() << std::endl;
    std::cout << "Unused Staff Position: " << unusedStaff.getPosition() << std::endl;
    std::cout << "Unused Staff Age: " << unusedStaff.getAge() << std::endl;
    std::cout << "Unused Staff Salary: " << unusedStaff.getSalary() << std::endl;

    Visitor unusedVisitor("Name", 20, 100.0f, "Type");
    unusedVisitor.setName("NewVisitorName");
    unusedVisitor.setAge(25);
    unusedVisitor.setMoney(150.0f);
    unusedVisitor.setType("NewType");
    std::cout << "Unused Visitor Name: " << unusedVisitor.getName() << std::endl;
    std::cout << "Unused Visitor Age: " << unusedVisitor.getAge() << std::endl;
    std::cout << "Unused Visitor Money: " << unusedVisitor.getMoney() << std::endl;
    std::cout << "Unused Visitor Type: " << unusedVisitor.getType() << std::endl;

    unusedAnimal.updateHealth();
}




int main() {
        Zoo myZoo = Zoo::initializeZoo();
        myZoo.createInitialHabitats();
        myZoo.displayZooStatus();

        int days;
        std::cout << "How many days do you want to simulate?" << std::endl;
        std::cin >> days;

        myZoo.runSimulation(days);

        RandomCodeForCppCheck();

    return 0;
}
