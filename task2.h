//
// Created by bcat on 2022-03-28.
//

#include <list>
#include <array>
#include <vector>
#include <deque>

template <class T>
class Iterator{
protected:
    size_t _currentIndex;

    void checkingForValidRange()const{
        if (isDone())
            throw std::out_of_range("Попытка чтения за пределами контейнера.");
    }

public:
    Iterator(): _currentIndex{} {}

    virtual ~Iterator(){}

    void first() {
        _currentIndex = 0;
    }

    void next() {
        _currentIndex++;
    }

    const Iterator& operator++() {
        this->next();
        return *this;
    }

    const Iterator& operator++(int) {
        this->next();
        return *this;
    }

    void previous() {
        _currentIndex--;
    }

    const Iterator& operator--() {
        this->previous();
        return *this;
    }

    const Iterator& operator--(int) {
        this->previous();
        return *this;
    }

    //Эти два метода зависят от класса контейнера, поэтому
    //реализуем их в наследниках
    virtual bool isDone() const = 0;
    virtual const T &currentItem() const = 0;
};

template <class T>
class ListIterator: public Iterator<T>{
private:
    const std::list<T> *_list;

public:
    ListIterator(const std::list<T> * list): Iterator<T>(),
        _list{ list } {};

    //Верно как для инкремента, так и для декремента, так как
    //у типа size_t нет отрицательных значений
    bool isDone()const override{
        return this->_currentIndex >= _list->size();
    }

    const T &currentItem() const override{
        this->checkingForValidRange();

        auto it { _list->begin() };
        std::advance(it, this->_currentIndex);

        return *it;
    }
};

template <class T, size_t SIZE>
        class ArrayIterator: public Iterator<T>{
        private:
            const std::array<T, SIZE> *_array;

        public:
            ArrayIterator(const std::array<T, SIZE> *array): Iterator<T>(),
                    _array { array } {}

            bool isDone()const override{
                return this->_currentIndex >= _array->size();
            }

            const T &currentItem() const override{
                this->checkingForValidRange();

                return this->_array->at(this->_currentIndex);
            }
};

template <class T>
        class VectorIterator: public Iterator<T>{
        private:
            const std::vector<T> *_vec;

        public:
            VectorIterator(const std::vector<T> *vec): Iterator<T>(),
                    _vec { vec } {}

            bool isDone()const override{
                return this->_currentIndex >= _vec->size();
            }

            const T &currentItem() const override{
                this->checkingForValidRange();

                return _vec->at(this->_currentIndex);
            }
};

template <class T>
        class DequeIterator: public Iterator<T>{
        private:
            const std::deque<T> *_deq;

        public:
            DequeIterator(const std::deque<T> *deq): Iterator<T>(),
                    _deq { deq } {}

            bool isDone()const override{
                return this->_currentIndex >= _deq->size();
            }

            const T &currentItem() const override{
                this->checkingForValidRange();

                return _deq->at(this->_currentIndex);
            }
};



