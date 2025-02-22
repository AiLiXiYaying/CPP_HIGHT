/*
 * =======================================================================
 *                   工厂模式 优缺点分析
 * =======================================================================
 *
 * 1. 工厂模式（Factory Pattern）：
 *    - **优点**：
 *      - **简单易懂**：工厂模式的代码结构简单直观，适合对类型有明确预定义且类型数量不频繁变化的场景。
 *      - **集中管理**：所有的对象创建都集中在工厂类中，易于修改和维护。增加新类型时，只需要修改工厂类，而无需修改其他代码。
 *      - **提高代码可读性**：每种类型的创建逻辑被封装在工厂方法中，不会污染其他业务逻辑。
 *    - **缺点**：
 *      - **不够灵活**：工厂模式是在编译时就决定了哪些类型可以被创建。所有可能的类型必须事先在代码中硬编码，不支持动态变化。
 *      - **类型扩展困难**：如果需要新增类型，必须修改工厂类并重新编译，扩展性差。
 *      - **耦合性高**：工厂方法与具体类的实现耦合度较高。如果增加新的类，需要修改工厂类，违反了开闭原则（Open/Closed Principle）。
 *
 * =======================================================================
 * 总结：
 *    - **工厂模式**适合那些类型明确、且不频繁变化的场景。它简单易懂，适合用在类型固定的项目中。
 * =======================================================================
 */

#include <iostream>
#include <string>
#include <memory>  // 用于 std::unique_ptr

#pragma region 基类与派生类定义

 // 基类 Animal：所有动物类的基类，包含一个虚函数 speak()
class Animal
{
public:
    virtual void speak() const = 0;  // 纯虚函数，所有动物都要实现自己的 speak()
    virtual ~Animal() = default;  // 虚析构函数，确保删除派生类对象时正确析构
};

// 派生类 Dog：实现 Animal 类的 speak() 方法
class Dog : public Animal
{
public:
    void speak() const override
    {
        std::cout << "汪汪！" << std::endl;  // 输出狗叫的声音
    }
};

// 派生类 Cat：实现 Animal 类的 speak() 方法
class Cat : public Animal
{
public:
    void speak() const override
    {
        std::cout << "喵喵！" << std::endl;  // 输出猫叫的声音
    }
};

#pragma endregion

#pragma region 工厂类定义

// 工厂类 AnimalFactory，用来创建动物对象
class AnimalFactory
{
public:
    // 静态方法，根据传入的类型字符串返回对应的动物对象
    static std::unique_ptr<Animal> createAnimal(const std::string& animalType)
    {
        // 根据输入的动物类型选择创建哪种动物对象
        if (animalType == "dog")
        {
            return std::make_unique<Dog>();  // 创建并返回一个 Dog 对象
        }
        else if (animalType == "cat")
        {
            return std::make_unique<Cat>();  // 创建并返回一个 Cat 对象
        }
        return nullptr;  // 如果类型不匹配，返回 nullptr
    }
};

#pragma endregion

#pragma region main 函数

int main()
{
    // 创建一个狗的实例，并调用它的 speak 方法
    auto dog = AnimalFactory::createAnimal("dog");  // 使用工厂模式创建一个 Dog 对象
    if (dog)
    {
        dog->speak();  // 输出 "汪汪！"
    }

    // 创建一个猫的实例，并调用它的 speak 方法
    auto cat = AnimalFactory::createAnimal("cat");  // 使用工厂模式创建一个 Cat 对象
    if (cat)
    {
        cat->speak();  // 输出 "喵喵！"
    }

    return 0;  // 程序结束，自动释放资源
}

#pragma endregion
