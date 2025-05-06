#include "../include/Game.hpp"
#include "../include/ZooExceptions.hpp"
#include "../include/BudgetException.hpp"
#include "../include/HabitatException.hpp"
#include "../include/AnimalException.hpp"
#include <iostream>

int main()
{
    try {
        Game game;
        game.run();
        return 0;
    }
    catch (const BudgetException& e) {
        std::cerr << "BUDGET ERROR: " << e.what() << std::endl;
    }
    catch (const HabitatException& e) {
        std::cerr << "HABITAT ERROR: " << e.what() << std::endl;
    }
    catch (const AnimalException& e) {
        std::cerr << "ANIMAL ERROR: " << e.what() << std::endl;
    }
    catch (const ZooException& e) {
        std::cerr << "ZOO ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "UNEXPECTED ERROR: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR OCCURRED" << std::endl;
    }
    
    return 1;
}
