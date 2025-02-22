#include <iostream>
#include <string>
#include <map>
#include <functional>

class Person
{
public:
    Person(const std::string& name, int age) : name(name), age(age) {}

    void greet()
    {
        std::cout << "你好，我叫 " << name << "，今年 " << age << " 岁。" << std::endl;
    }

    void showAge()
    {
        std::cout << "我的年龄是 " << age << " 岁。" << std::endl;
    }

    // 使用反射机制：注册方法
    void callMethod(const std::string& methodName)
    {
        auto it = methodMap.find(methodName);
        if (it != methodMap.end())
        {
            // 调用相应的方法
            it->second();  // 调用函数指针
        }
        else
        {
            std::cout << "未知的方法: " << methodName << std::endl;
        }
    }

    // 注册函数到方法名
    void registerMethods()
    {
        methodMap["greet"] = [this]() { this->greet(); };  // 注册 greet 方法
        methodMap["showAge"] = [this]() { this->showAge(); };  // 注册 showAge 方法
    }

private:
    std::string name;
    int age;

    // 存储方法名和对应的函数指针
    std::map<std::string, std::function<void()>> methodMap;
};

int main()
{
    Person p("艾丽丝", 30);

    p.registerMethods();  // 注册方法

    // 使用反射机制调用函数
    p.callMethod("greet");  // 动态调用 greet 方法
    p.callMethod("showAge");  // 动态调用 showAge 方法

    // 使用反射调用一个不存在的方法
    p.callMethod("unknownMethod");

    return 0;
}
