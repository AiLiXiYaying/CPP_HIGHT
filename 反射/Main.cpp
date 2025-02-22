/*
 * =======================================================================
 *                   ����ģʽ  ��ȱ�����
 * =======================================================================
 *
 * 2. ����ģʽ��Reflection Pattern����
 *    - **�ŵ�**��
 *      - **�߶����**������ģʽͨ����̬ע��Ͳ�ѯ������������ʱ��������̬�����µ����ͣ�����Ҫ��ǰ�����������͡�
 *      - **��չ��ǿ**������ģʽʹ�������Ϳ���������ʱ��̬ע�ᣬ��������ʱ�������ؼ����µ��������Ҫ�޸�Դ���롣
 *      - **�����**�����佫���ʹ����߼���������ͽ���������Ǹ����ַ�������Ϣ����̬ѡ�񴴽��ĸ�����
 *      - **�ʺϲ������**������ǳ��ʺ�����ʵ�ֲ���ܹ����ܹ�������ʱ���ز�ʹ���µ�ģ�������
 *    - **ȱ��**��
 *      - **�����Ը�**�������ʵ�ֺ�ʹ�ñȹ���ģʽ���ӣ���Ҫ����Ķ������������̬����ע�ᡢ���ҡ����õȲ�����
 *      - **���ܿ���**�����ڷ����漰������ʱ��̬���Һʹ������󣬿��ܻ���һ����������ʧ��Ƶ���ķ���������ܵ�������ƿ����
 *      - **�׳���**��ʹ���ַ�����ע��Ͳ�ѯ����ʱ���׳�����ƴд�������Ͳ�ƥ��ȡ�
 *      - **���Ե���**�����ڷ�����������ʱ��̬�������ͺ͵��÷��������������ȴ�ͳ�ľ�̬����������ѡ�
 *
 * =======================================================================
 * �ܽ᣺
 *    - **����ģʽ**�ʺ���Щ��Ҫ��̬��չ���͡��������߲��ϵͳ�ĳ�����������������ʱ�����ܹ�����¹��ܵĳ��ϡ����ṩ�˼��������ԣ���Ҳ�����˸����Ժ������ϵ���ս��
 * =======================================================================
 */

#include <iostream>
#include <string>
#include <map>
#include <functional>  // ���� std::function

#pragma region �����������ඨ��

 // ���� Animal�����ж�����Ļ��࣬����һ���麯�� speak()
class Animal
{
public:
    virtual void speak() const = 0;  // ���麯�������ж��ﶼҪʵ���Լ��� speak()
    virtual ~Animal() = default;  // ������������ȷ��ɾ�����������ʱ��ȷ����
};

// ������ Dog��ʵ�� Animal ��� speak() ����
class Dog : public Animal
{
public:
    void speak() const override
    {
        std::cout << "������" << std::endl;  // ������е�����
    }
};

// ������ Cat��ʵ�� Animal ��� speak() ����
class Cat : public Animal
{
public:
    void speak() const override
    {
        std::cout << "������" << std::endl;  // ���è�е�����
    }
};

#pragma endregion

#pragma region �����ඨ��

// ������ AnimalFactory��֧�ַ�����ƣ�ͨ���ַ���ע���ಢ��̬��������
class AnimalFactory
{
public:
    // ��̬ע�ᶯ���༰�䴴��������ʹ�� std::function ���洢��������
    static void registerAnimal(const std::string& name, std::function<Animal* ()> creator)
    {
        creators[name] = creator;  // �������봴��������ӳ���ϵ���� map
    }

    // ��̬�����������
    static Animal* createAnimal(const std::string& name)
    {
        auto it = creators.find(name);  // �������������ƥ��Ĵ�������
        if (it != creators.end())
        {
            return it->second();  // ������Ӧ�Ĵ������������ض�Ӧ�Ķ���
        }
        return nullptr;  // ���û���ҵ�ƥ������ͣ����� nullptr
    }

private:
    // ʹ�� map ���洢�����봴��������ӳ���ϵ
    static std::map<std::string, std::function<Animal* ()>> creators;
};

#pragma endregion

#pragma region ��̬��Ա����

// ���ⲿ���徲̬��Ա���� creators
std::map<std::string, std::function<Animal* ()>> AnimalFactory::creators;

#pragma endregion

#pragma region main ����

int main()
{
    // ��̬ע�� Dog �� Cat ��Ĵ�������
    AnimalFactory::registerAnimal("dog", []() -> Animal* { return new Dog(); });
    AnimalFactory::registerAnimal("cat", []() -> Animal* { return new Cat(); });

    // ��̬����һ������ʵ�������������� speak ����
    Animal* dog = AnimalFactory::createAnimal("dog");  // ʹ�÷���ģʽ����һ�� Dog ����
    if (dog)
    {
        dog->speak();  // ��� "������"
        delete dog;  // ��̬������ڴ���Ҫ�ֶ�ɾ��
    }

    // ��̬����һ��è��ʵ�������������� speak ����
    Animal* cat = AnimalFactory::createAnimal("cat");  // ʹ�÷���ģʽ����һ�� Cat ����
    if (cat)
    {
        cat->speak();  // ��� "������"
        delete cat;  // ��̬������ڴ���Ҫ�ֶ�ɾ��
    }

    return 0;  // ����������ͷ���Դ
}

#pragma endregion
