//
// Created by bcat on 2022-03-28.
//

#include <iostream>
#include <fstream>

class DivideStrategy{
protected:
    DivideStrategy(){};
public:
    virtual void Divide() {
        std::cout << "\nВызван метод Divide() ";
    }
    virtual ~DivideStrategy(){};
};

class DivideByScreen: public DivideStrategy{
public:
    DivideByScreen(): DivideStrategy() {};
    void Divide() override{
        //..пропущен код деления текста на строки в зависимости
        // от ширины клиентского окна
        DivideStrategy::Divide();
        std::cout << "класса DivideByScreen\n";
    }
};

class DivideByUserWidth: public DivideStrategy{
public:
    DivideByUserWidth(): DivideStrategy() {};
    void Divide() override{
        int userWidth;
        std::cout << "Введите желаемую ширину: ";
        std::cin >> userWidth;
        //..пропущен код деления текста на строки в зависимости
        // введённого пользователем значения
        DivideStrategy::Divide();
        std::cout << "класса DivideByUserWidth.\n";
        std::cout << "Размер ширины, полученный от пользователя == " << userWidth;
        std::cout << std::endl;
    }
};

class DivideBySentence: public DivideStrategy{
public:
    DivideBySentence(): DivideStrategy() {};
    void Divide() override{
        //..пропущен код деления текста на строки, рассчитанного
        // автоматически по предложениям
        DivideStrategy::Divide();
        std::cout << "класса DivideBySentence\n";
    }
};

class ITextWork{
public:
    virtual void setStrategy(DivideStrategy*) = 0;
    virtual void useStrategy() = 0;
    virtual ~ITextWork(){};
};

class TextEditor: ITextWork{
private:
    std::string all_text;
    size_t EditorWidth;
    DivideStrategy* _divideStrategy;
public:
    TextEditor(const std::string& default_text = {},
        size_t defaultWinWidth = 480,
            DivideStrategy *defaultDivideStrategy  = nullptr):
                all_text{ default_text },
                EditorWidth{ defaultWinWidth },
                _divideStrategy{ defaultDivideStrategy }
            {}

    TextEditor(std::ifstream& file): TextEditor() {
        std::string line;
        if (file.is_open()){
            while (getline(file, line))
            {
                all_text+=line;
            }
        }
    }

    inline void PrintText() const{
        std::cout << all_text << std::endl;
    }

    inline void setStrategy (DivideStrategy* divideStrategy) override{
        _divideStrategy = divideStrategy;
    }

    void useStrategy() override{
        if (_divideStrategy == nullptr)
        {
            std::cerr << "Стратегия не выбрана.\n";
            return;
        }

        _divideStrategy->Divide();
    };
};

