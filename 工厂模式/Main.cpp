/*
 * =======================================================================
 *                   ����ģʽ ��ȱ�����
 * =======================================================================
 *
 * 1. ����ģʽ��Factory Pattern����
 *    - **�ŵ�**��
 *      - **���׶�**������ģʽ�Ĵ���ṹ��ֱ�ۣ��ʺ϶���������ȷԤ����������������Ƶ���仯�ĳ�����
 *      - **���й���**�����еĶ��󴴽��������ڹ������У������޸ĺ�ά��������������ʱ��ֻ��Ҫ�޸Ĺ����࣬�������޸��������롣
 *      - **��ߴ���ɶ���**��ÿ�����͵Ĵ����߼�����װ�ڹ��������У�������Ⱦ����ҵ���߼���
 *    - **ȱ��**��
 *      - **�������**������ģʽ���ڱ���ʱ�;�������Щ���Ϳ��Ա����������п��ܵ����ͱ��������ڴ�����Ӳ���룬��֧�ֶ�̬�仯��
 *      - **������չ����**�������Ҫ�������ͣ������޸Ĺ����ಢ���±��룬��չ�Բ
 *      - **����Ը�**������������������ʵ����϶Ƚϸߡ���������µ��࣬��Ҫ�޸Ĺ����࣬Υ���˿���ԭ��Open/Closed Principle����
 *
 * =======================================================================
 * �ܽ᣺
 *    - **����ģʽ**�ʺ���Щ������ȷ���Ҳ�Ƶ���仯�ĳ����������׶����ʺ��������͹̶�����Ŀ�С�
 * =======================================================================
 */

#include <iostream>
#include <string>
#include <memory>  // ���� std::unique_ptr

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

// ������ AnimalFactory�����������������
class AnimalFactory
{
public:
    // ��̬���������ݴ���������ַ������ض�Ӧ�Ķ������
    static std::unique_ptr<Animal> createAnimal(const std::string& animalType)
    {
        // ��������Ķ�������ѡ�񴴽����ֶ������
        if (animalType == "dog")
        {
            return std::make_unique<Dog>();  // ����������һ�� Dog ����
        }
        else if (animalType == "cat")
        {
            return std::make_unique<Cat>();  // ����������һ�� Cat ����
        }
        return nullptr;  // ������Ͳ�ƥ�䣬���� nullptr
    }
};

#pragma endregion

#pragma region main ����

int main()
{
    // ����һ������ʵ�������������� speak ����
    auto dog = AnimalFactory::createAnimal("dog");  // ʹ�ù���ģʽ����һ�� Dog ����
    if (dog)
    {
        dog->speak();  // ��� "������"
    }

    // ����һ��è��ʵ�������������� speak ����
    auto cat = AnimalFactory::createAnimal("cat");  // ʹ�ù���ģʽ����һ�� Cat ����
    if (cat)
    {
        cat->speak();  // ��� "������"
    }

    return 0;  // ����������Զ��ͷ���Դ
}

#pragma endregion
