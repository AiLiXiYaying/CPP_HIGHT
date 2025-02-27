#include <iostream>

/*
 * ========================================================================
 * 单例模式（Singleton Pattern）
 * ========================================================================
 *
 * 单例模式确保一个类在程序生命周期内只有一个实例，并提供全局访问点。
 *
 * 优点：
 * 1. 保证了系统中对类的访问是单一实例，避免了重复创建，节省了资源。
 * 2. 懒汉式加载：实例在第一次使用时创建，提高了启动效率。
 * 3. 提供全局唯一的访问点，允许在程序中各处访问该实例。
 * 4. 可以控制类的生命周期，在特定时刻销毁实例，避免内存泄漏。
 * 5. 可以禁止类的复制，避免出现多个实例。
 *
 * 缺点：
 * 1. 单例模式使用了全局状态，可能会导致系统中的模块间隐式依赖，增加耦合度。
 * 2. 线程不安全：如果在多线程环境中使用，可能会存在竞态条件，导致多个线程同时创建实例。
 * 3. 强依赖全局访问点：使用全局访问点可能会使得代码不易测试和维护，难以进行单元测试。
 * 4. 它会隐藏类的构造函数和实现细节，可能导致类变得不透明，无法灵活控制实例创建。
 * 5. 使用不当时，可能导致系统过度依赖单例，增加代码复杂度和维护成本。
 *
 * 适用场景：
 * - 全局唯一的资源管理（如：日志系统、配置管理、数据库连接池等）
 *
 * 实现说明：
 * 1. 私有构造函数和拷贝构造函数，确保外部无法直接创建或复制实例。
 * 2. `getInstance()` 提供全局访问点，并在第一次访问时创建实例。
 * 3. 使用 `destroyInstance()` 显式销毁单例实例，释放资源。
 * 4. 采用懒汉式单例模式，仅在需要时创建实例。
 *
 * ========================================================================
 */

class Singleton
{
private:
    // 私有静态指针，指向唯一实例
    static Singleton* instance;

    // 私有构造函数，确保外部无法直接创建实例
    Singleton()
    {
        std::cout << "Singleton instance created!" << std::endl;
    }

    // 禁用拷贝构造函数和赋值运算符，防止复制实例
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // 静态方法，提供对单一实例的访问
    static Singleton* getInstance()
    {
        // 延迟初始化：只有在第一次调用时创建实例
        if (instance == nullptr)
        {
            instance = new Singleton(); // 创建唯一实例
        }
        return instance; // 返回唯一实例
    }

    // 示例方法：类的方法，展示实例的操作
    void doSomething()
    {
        std::cout << "Doing something in Singleton instance!" << std::endl;
    }

    // 可选：提供销毁实例的方法
    static void destroyInstance()
    {
        delete instance; // 释放内存
        instance = nullptr; // 将实例指针置空
    }
};

// 初始化静态成员变量
// 静态成员变量 `instance` 在类外初始化为 nullptr，表示没有创建实例
Singleton* Singleton::instance = nullptr;

int main()
{
    // 获取单例实例并调用方法
    Singleton* singleton = Singleton::getInstance();
    singleton->doSomething(); // 调用实例方法，输出信息

    // 销毁单例实例
    Singleton::destroyInstance(); // 显式销毁单例实例

    return 0;
}
