#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <functional>

template<typename T>
class AnimalInventory {
private:
    std::vector<std::shared_ptr<T> > items;
    size_t maxCapacity;
    std::string inventoryName;

public:
    AnimalInventory(const std::string &name, size_t capacity = 100)
        : maxCapacity(capacity), inventoryName(name) {
    }

    bool addItem(const std::shared_ptr<T> &item) {
        if (items.size() >= maxCapacity) {
            std::cout << "Inventory " << inventoryName << " is full! Cannot add more items." << std::endl;
            return false;
        }
        items.push_back(item);
        std::cout << "Added item to " << inventoryName << " inventory. Total items: " << items.size() << std::endl;
        return true;
    }

    bool removeItem(const std::shared_ptr<T> &item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
            std::cout << "Removed item from " << inventoryName << " inventory. Total items: " << items.size() <<
                    std::endl;
            return true;
        }
        return false;
    }

    bool removeItemIf(std::function<bool(const std::shared_ptr<T> &)> predicate) {
        auto it = std::find_if(items.begin(), items.end(), predicate);
        if (it != items.end()) {
            items.erase(it);
            std::cout << "Removed item from " << inventoryName << " inventory. Total items: " << items.size() <<
                    std::endl;
            return true;
        }
        return false;
    }

    std::shared_ptr<T> findItem(std::function<bool(const std::shared_ptr<T> &)> predicate) const {
        auto it = std::find_if(items.begin(), items.end(), predicate);
        return (it != items.end()) ? *it : nullptr;
    }

    std::vector<std::shared_ptr<T> > findAllItems(std::function<bool(const std::shared_ptr<T> &)> predicate) const {
        std::vector<std::shared_ptr<T> > result;
        for (const auto &item: items) {
            if (predicate(item)) {
                result.push_back(item);
            }
        }
        return result;
    }

    size_t getCount() const { return items.size(); }
    size_t getCapacity() const { return maxCapacity; }
    const std::vector<std::shared_ptr<T> > &getItems() const { return items; }
    const std::string &getName() const { return inventoryName; }
    bool isEmpty() const { return items.empty(); }
    bool isFull() const { return items.size() >= maxCapacity; }

    void displayInventory() const {
        std::cout << "\n=== " << inventoryName << " Inventory ===" << std::endl;
        std::cout << "Items: " << items.size() << "/" << maxCapacity << std::endl;
        if (items.empty()) {
            std::cout << "Inventory is empty." << std::endl;
        } else {
            for (size_t i = 0; i < items.size(); ++i) {
                std::cout << i + 1 << ". " << *items[i] << std::endl;
            }
        }
        std::cout << "=========================" << std::endl;
    }

    void clear() {
        items.clear();
        std::cout << "Cleared " << inventoryName << " inventory." << std::endl;
    }

    template<typename Func>
    void forEachItem(Func operation) const {
        for (const auto& item : items) {
            operation(item);
        }
    }

    template<typename Predicate>
    std::vector<std::shared_ptr<T>> filterItems(Predicate condition) const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& item : items) {
            if (condition(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};
