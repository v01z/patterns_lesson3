#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include <cassert> //assert()

int main() {
    //*************** task1 ******************
    TextEditor textEditor("Some text");

    //Пользователь выбирает и применяет нужную ему стратегию
    DivideStrategy *divideStrategy = new DivideByUserWidth;
    textEditor.setStrategy(divideStrategy);
    textEditor.useStrategy();

    //Смотрит результат
    textEditor.PrintText();

    delete divideStrategy;

    //*************** task2 ******************

    //----------------- Проверка ListIterator --------------
    std::list<std::string> list { "первый", "второй", "третий" };

    ListIterator<std::string> iterator(&list);

    std::cout << iterator.currentItem() << std::endl; // "первый"

    iterator.next(); // "второй"
    std::cout << iterator.currentItem() << std::endl;

    ++iterator; // "третий"
    iterator++; //Вышли за границы листа
    iterator--; //Вернулись назад к элементу "третий"
    std::cout << iterator.currentItem() << std::endl;

    //----------------- Проверка ArrayIterator --------------
    std::array<std::string, 3> array
     { "first", "second", "third" };

    ArrayIterator<std::string, 3> arrayIterator(&array);

    arrayIterator++; //"second"

    assert(arrayIterator.currentItem() == array[1]);
    std::cout << arrayIterator.currentItem() << std::endl;

    //----------------- Проверка VectorIterator --------------
    std::vector<int> vector { 77, 112, 18, 1028 };

    VectorIterator<int> vectorIterator(&vector);

    vectorIterator.next();
    vectorIterator++; //18

    assert(vector.at(2) == vectorIterator.currentItem()); //18 == 18
    std::cout << vectorIterator.currentItem() << std::endl;

    //----------------- Проверка DequeIterator --------------
    std::deque<char> deque { 'b', 'i', 'n', 'a', 'r', 'y' };

    DequeIterator<char> dequeIterator(&deque);

    dequeIterator++; // 'i'
    dequeIterator++; // 'n'
    dequeIterator++; // 'a'
    dequeIterator++; // 'r'

    assert(dequeIterator.currentItem() == deque.at(4));
    std::cout << dequeIterator.currentItem();

    //*************** task3 ******************

    IShape *figure = new Figure(5,5);

    Text *text = new Text{ "Some text", 20, 115, false };
    IShape *textView = new TextView(text);

    ClientForTest clientArray[2] { figure, textView };
    for (auto &elem : clientArray)
    {
        elem.shape->scale(55);
        elem.shape->rotate(17);
        elem.shape->flip();
    }

    delete text; //figure и textView удаляюятся деструктором ~ClientForTest()

    return 0;
}
