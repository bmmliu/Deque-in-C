#ifndef DEQUE_H
#define DEQUE_H
#include <cstddef>
#include <algorithm>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <cassert>

template<typename T>
class Deque {
public:
    //
    // @@@ The class's public API below should _not_ be modified @@@
    //

    // Constructor
    Deque();
    //: deq(std::unique_ptr<T[]>(new T[capacity])){

    //}
    // { }
    // Destructor
    ~Deque();
    //= default;


    //
    // Capacity
    //

    // Return true if empty, false otherwise
    // Complexity: O(1)
    bool Empty () const noexcept;
    // Return number of items in deque
    // Complexity: O(1)
    size_t Size () const noexcept;

    // Resize internal data structure to fit precisely the number of items and
    // free unused memory
    // Complexity: O(N)
    void ShrinkToFit();


    //
    // Element access
    //

    // Return item at pos @pos
    // Complexity: O(1)
    T& operator[](size_t pos);
    // Return item at front of deque
    // Complexity: O(1)
    T& Front();
    T& Back();


    //
    // Modifiers
    //

    // Clear contents of deque (make it empty)
    // Complexity: O(1)
    void Clear(void) noexcept;
    // Push item @value at front of deque
    // Complexity: O(1) amortized
    void PushFront(const T &value);
    // Push item @value at back of deque
    // Complexity: O(1) amortized
    void PushBack(const T &value);
    // Remove item at front of deque
    // Complexity: O(1) amortized
    void PopFront();
    // Remove item at back of deque
    // Complexity: O(1) amortized
    void PopBack();


private:
    unsigned int capacity = 0;
    std::unique_ptr<T[]> deq;

    unsigned int cur_size = 0;
    int head = 0;
    int tail = 0;
    //
    // @@@ The class's internal members below can be modified @@@
    //
    void Resize(unsigned int new_cap) {
        assert(new_cap && new_cap >= cur_size);

        std::unique_ptr<T[]> new_items(new T[new_cap]);
        std::move(deq.get(),
                  std::next(deq.get(), cur_size),
                  new_items.get());
        std::swap(deq, new_items);
        capacity = new_cap;
    }
    // Private member variables
    // ...To be completed...

    // Private constants
    // ...To be completed (if any)...

    // Private methods
    // ...To be completed (if any)...
};


//
// Your implementation of the class should be located below
//

template<typename T>
Deque<T>::Deque() : deq(std::unique_ptr<T[]>(new T[capacity])){

}

template<typename T>
Deque<T>::~Deque() = default;

template<typename T>
bool Deque<T>::Empty () const noexcept{
    return 0 == cur_size;
}

template<typename T>
size_t Deque<T>::Size () const noexcept{
    return cur_size;
}

template<typename T>
void Deque<T>::ShrinkToFit(){
    Resize(cur_size);
}

template<typename T>
T& Deque<T>::operator[](size_t pos){
    return deq[pos];
}

template<typename T>
T& Deque<T>::Front(){
    return deq[head];
}

template<typename T>
T& Deque<T>::Back(){
    return deq[tail];
}

template<typename T>
void Deque<T>::Clear(void) noexcept{
    capacity = 0;
    std::unique_ptr<T[]> deq(new T[capacity]);
    tail = 0;
    head = 0;
    cur_size = 0;
}

template<typename T>
void Deque<T>::PushFront(const T &value){

    if (cur_size == 0){
        Resize(1);
        cur_size = cur_size + 1;
        deq[0] = value;
        head = 0;
        tail = cur_size - 1;
    } else{
        cur_size = cur_size + 1;
        if(cur_size > capacity){
            Resize(cur_size);
        }
        for (int i = tail; i >= head; i--){
            deq[i+1] = deq[i];
        }
        deq[head] = value;
        tail = tail + 1;
    }
}

template<typename T>
void Deque<T>::PushBack(const T &value){
    if(cur_size == 0){
        Resize(1);
        cur_size = cur_size + 1;
        deq[0] = value;
        head = 0;
        tail = 0;
    } else{
        cur_size = cur_size +1;
        if(cur_size > capacity){
            Resize(cur_size);
        }
        deq[tail + 1] = value;
        head = 0;
        tail = tail + 1;

    }
}

template<typename T>
void Deque<T>::PopFront(){
    if (Empty()){
        throw std::underflow_error("Empty deque");
    }
    for(unsigned int i = 0; i < cur_size ; i++){
        deq[i] = deq[i + 1];
    }
    cur_size = cur_size - 1;
    tail = tail - 1;
}

template<typename T>
void Deque<T>::PopBack(){
    if (Empty()){
        throw std::underflow_error("Empty deque");
    }
    cur_size = cur_size - 1;
    tail = tail - 1;
}

// ...To be completed...
#endif //HW2_CLION_DEQUE_H
