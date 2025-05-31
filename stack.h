#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    static const int MAX = 100;
    T data[MAX];
    int top;

public:
    Stack() : top(-1) {}
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX - 1; }

    void push(T value) {
        if (isFull()) return;
        data[++top] = value;
    }

    T pop() {
        if (isEmpty()) throw std::out_of_range("Stack kosong");
        return data[top--];
    }

    T peek() {
        if (isEmpty()) throw std::out_of_range("Stack kosong");
        return data[top];
    }
};

#endif
