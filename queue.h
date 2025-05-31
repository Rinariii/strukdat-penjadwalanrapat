#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <stdexcept>

template <typename T>
class Queue {
private:
    std::vector<T> elements;

public:
    void enqueue(const T& item) {
        elements.push_back(item);
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty. Cannot dequeue.");
        }
        T frontItem = elements.front();
        elements.erase(elements.begin()); 
        return frontItem;
    }

    T& front() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty. No front element.");
        }
        return elements.front();
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty. No front element.");
        }
        return elements.front();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }

    void displayAll() const {
        if (isEmpty()) {
            std::cout << "Queue is empty.\n";
            return;
        }
        std::cout << "Queue elements (front to back): ";
        for (const T& item : elements) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

#endif