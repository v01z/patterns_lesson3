//
// Created by bcat on 2022-03-28.
//

class IShape{
public:
    virtual void scale(double scale_percentage) = 0;// Масштабируем фигуру
    virtual void rotate(double angle) = 0;          // Поворачиваем фигуру
    virtual void flip() = 0;                        // Отражаем фигуру

    //Так как при проверке работы в main.cpp будем создавать указатель
    //на этот класс, то крайне желательно наличие виртуального деструктора
    virtual ~IShape(){};
};

class Figure: public IShape{
private:
    int width;
    int height;
    double angle;
    bool isFlipped;
public:
    Figure(int width, int height) : width(width), height(height), angle(0.0), isFlipped(false) {}

    void scale(double scale_percentage) override {
        width *= scale_percentage;
        height *= scale_percentage;
    }

    void rotate(double angle) override {
        angle += angle;
    }

    void flip() override {
        isFlipped = !isFlipped;
    }
};

class IText{
    virtual void newSize(int size) = 0;   // Изменяем размер шрифта текста
    virtual void rotate(double angle) = 0;   // Поворачиваем текст
    virtual void reverse() = 0;              // Изменяем направление текста
};

class Text: IText{
private:
    int size;
    double angle;
    bool isReversed;
    std::string text;
public:
    Text(const std::string text, int size, double angle, bool isReversed) : text(text), size(size), angle(0.0), isReversed(false) {}

    void newSize(int newSize) override {
        size = newSize;
    }

    //Метод rotate() у класса Text отличается от "тёзки" из класса Figure:
    //в первом случае поле 'angle' (угол поворота) инкрементируется на размер
    //входного параметра, а во втором приравнивается этому параметру. И, хоть
    //наш адаптер TextView будет наследоваться не от класса Figure, а от интерфейса
    //IShape (в котором такое правило поведения не обозначено), выдвинем предположение,
    //что задумывался именно такой способ реализации метода rotate() для всех
    //производных от IShape, так как единообразное поведение всех фигур выглядит
    //более логичным. Опираясь на изложенное, далее ниже в этом классе придётся
    //добавить геттер для поля 'angle', а для класса TextView - переменную-член для
    //хранения текущего значения угла поворота (назовём её тоже 'angle').
    void rotate(double newAngle) override {
        angle = newAngle;
    }

    void reverse() override {
        for (int i = 0; i < text.size()/2; ++i) {
            char c = text[i];
            text[i] = text[text.size() - 1 - i];
            text[text.size() - 1 - i] = c;
        }

        //В классе есть приватное поле 'isReversed', но в техзадании оно
        //нигде не меняет своего значения. Будет правильным сделать это здесь:
        isReversed = !isReversed;
    }

    double getAngle()const{
        return angle;
    }

    //Для реализации TextView::scale() нам потребуется геттер для 'size'
    int getSize()const{
        return size;
    }
};

//Класс "Адаптер"
class TextView: public IShape{
private:
    Text *_text;
    double angle;
public:
    TextView(Text *text): _text { text }, angle { text->getAngle() } {}

    void scale(double scale_percentage) override{
        _text->newSize(_text->getSize() * scale_percentage);
    }

    void rotate(double angle) override{
        angle += angle;
        _text->rotate(angle);
    }

    void flip() override{
       _text->reverse();
    }
};

//Класс-клиент для проверки адаптера
class ClientForTest{
public:
    IShape *shape;

    ClientForTest(IShape *shape): shape { shape } {}

    ~ClientForTest(){
        if (shape != nullptr)
            delete shape;
    }
};

