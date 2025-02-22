/*
 * =======================================================================
 *                   反射模式  优缺点分析
 * =======================================================================
 *
 * 2. 反射模式（Reflection Pattern）：
 *    - **优点**：
 *      - **高度灵活**：反射模式通过动态注册和查询，允许在运行时根据需求动态加载新的类型，不需要提前定义所有类型。
 *      - **扩展性强**：反射模式使得新类型可以在运行时动态注册，程序运行时可以灵活地加入新的类而不需要修改源代码。
 *      - **解耦合**：反射将类型创建逻辑与具体类型解耦，允许我们根据字符串等信息来动态选择创建哪个对象。
 *      - **适合插件机制**：反射非常适合用于实现插件架构，能够在运行时加载并使用新的模块或插件。
 *    - **缺点**：
 *      - **复杂性高**：反射的实现和使用比工厂模式复杂，需要更多的额外代码来处理动态类型注册、查找、调用等操作。
 *      - **性能开销**：由于反射涉及到运行时动态查找和创建对象，可能会有一定的性能损失。频繁的反射操作可能导致性能瓶颈。
 *      - **易出错**：使用字符串来注册和查询类型时容易出错，如拼写错误、类型不匹配等。
 *      - **难以调试**：由于反射是在运行时动态创建类型和调用方法，调试起来比传统的静态代码更加困难。
 *
 * =======================================================================
 * 总结：
 *    - **反射模式**适合那些需要动态扩展类型、方法或者插件系统的场景，尤其是在运行时必须能够添加新功能的场合。它提供了极大的灵活性，但也带来了复杂性和性能上的挑战。
 * =======================================================================
 */

#include <iostream>
#include <string>
#include <map>
#include <functional>  // 用于 std::function

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

// 工厂类 AnimalFactory，支持反射机制，通过字符串注册类并动态创建对象
class AnimalFactory
{
public:
    // 动态注册动物类及其创建函数，使用 std::function 来存储创建函数
    static void registerAnimal(const std::string& name, std::function<Animal* ()> creator)
    {
        creators[name] = creator;  // 将类名与创建函数的映射关系存入 map
    }

    // 动态创建动物对象
    static Animal* createAnimal(const std::string& name)
    {
        auto it = creators.find(name);  // 查找与给定名称匹配的创建函数
        if (it != creators.end())
        {
            return it->second();  // 调用相应的创建函数，返回对应的对象
        }
        return nullptr;  // 如果没有找到匹配的类型，返回 nullptr
    }

private:
    // 使用 map 来存储类名与创建函数的映射关系
    static std::map<std::string, std::function<Animal* ()>> creators;
};

#pragma endregion

#pragma region 静态成员定义

// 在外部定义静态成员变量 creators
std::map<std::string, std::function<Animal* ()>> AnimalFactory::creators;

#pragma endregion

#pragma region main 函数

int main()
{
    // 动态注册 Dog 和 Cat 类的创建函数
    AnimalFactory::registerAnimal("dog", []() -> Animal* { return new Dog(); });
    AnimalFactory::registerAnimal("cat", []() -> Animal* { return new Cat(); });

    // 动态创建一个狗的实例，并调用它的 speak 方法
    Animal* dog = AnimalFactory::createAnimal("dog");  // 使用反射模式创建一个 Dog 对象
    if (dog)
    {
        dog->speak();  // 输出 "汪汪！"
        delete dog;  // 动态分配的内存需要手动删除
    }

    // 动态创建一个猫的实例，并调用它的 speak 方法
    Animal* cat = AnimalFactory::createAnimal("cat");  // 使用反射模式创建一个 Cat 对象
    if (cat)
    {
        cat->speak();  // 输出 "喵喵！"
        delete cat;  // 动态分配的内存需要手动删除
    }

    return 0;  // 程序结束，释放资源
}

#pragma endregion
