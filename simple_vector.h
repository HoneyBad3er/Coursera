#pragma once

#include <cstdlib>
#include <algorithm>
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector();
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();

  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  T* data;
  T* end_;
  size_t size_;
  size_t capacity_;
};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) : data(new T[size]), end_(data + size), size_(size), capacity_(size){};

template<typename T>
SimpleVector<T>::SimpleVector() : data(nullptr), end_(nullptr), size_(0u), capacity_(0u){};

template <typename T>
T& SimpleVector<T>::operator[] (size_t index){
  return data[index];
};

template<typename T>
T* SimpleVector<T>::begin(){
    return data;
}

template<typename T>
const T* SimpleVector<T>::begin() const {
    return data;
}

template<typename T>
T* SimpleVector<T>::end(){
    return end_;
}

template<typename T>
const T* SimpleVector<T>::end() const {
    return end_;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return size_;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity_;
}
template<typename T>
void SimpleVector<T>::PushBack(const T& value){
    if (data == nullptr && end_ == nullptr){
        data = new T[1];
        end_ = data + 1;
        capacity_ = 1;
    }
    if (this->Size() == this->Capacity()){
        capacity_ = 2*(this->Capacity());
        T* new_data = new T[capacity_];
        std::copy(data, end_, new_data);
        delete[] data;
        data = new_data;
        end_ = data + size_ + 1;
    }
    *(data + size_) = value;
    ++size_;
    end_ = data + size_;
}

template<typename T>
SimpleVector<T>::~SimpleVector(){
    delete[] data;
}
