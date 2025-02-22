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
        std::cout << "��ã��ҽ� " << name << "������ " << age << " �ꡣ" << std::endl;
    }

    void showAge()
    {
        std::cout << "�ҵ������� " << age << " �ꡣ" << std::endl;
    }

    // ʹ�÷�����ƣ�ע�᷽��
    void callMethod(const std::string& methodName)
    {
        auto it = methodMap.find(methodName);
        if (it != methodMap.end())
        {
            // ������Ӧ�ķ���
            it->second();  // ���ú���ָ��
        }
        else
        {
            std::cout << "δ֪�ķ���: " << methodName << std::endl;
        }
    }

    // ע�ắ����������
    void registerMethods()
    {
        methodMap["greet"] = [this]() { this->greet(); };  // ע�� greet ����
        methodMap["showAge"] = [this]() { this->showAge(); };  // ע�� showAge ����
    }

private:
    std::string name;
    int age;

    // �洢�������Ͷ�Ӧ�ĺ���ָ��
    std::map<std::string, std::function<void()>> methodMap;
};

int main()
{
    Person p("����˿", 30);

    p.registerMethods();  // ע�᷽��

    // ʹ�÷�����Ƶ��ú���
    p.callMethod("greet");  // ��̬���� greet ����
    p.callMethod("showAge");  // ��̬���� showAge ����

    // ʹ�÷������һ�������ڵķ���
    p.callMethod("unknownMethod");

    return 0;
}
