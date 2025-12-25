#include <iostream>
#include <string>
#include "../structures/TList.hpp"
#include "../structures/TVector.hpp"

int main()
{
    std::cout << "=== Демонстрация работы TList ===" << std::endl;
    std::cout << std::endl;
    
    TList<int> list;
    std::cout << "1. Создан пустой список: " << list << std::endl;
    
    std::cout << "\n2. Добавляем элементы в конец (10, 20, 30):" << std::endl;
    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);
    std::cout << "   Список: " << list << std::endl;
    
    std::cout << "\n3. Добавляем элементы в начало (5, 1):" << std::endl;
    list.PushFront(5);
    list.PushFront(1);
    std::cout << "   Список: " << list << std::endl;
    
    std::cout << "\n4. Доступ по индексу:" << std::endl;
    std::cout << "   list[0] = " << list[0] << std::endl;
    std::cout << "   list[2] = " << list[2] << std::endl;
    std::cout << "   list[4] = " << list[4] << std::endl;
    
    std::cout << "\n5. Размер списка: " << list.GetSize() << std::endl;
    
    std::cout << "\n6. Удаляем элемент из начала:" << std::endl;
    int front = list.PopFront();
    std::cout << "   Удален: " << front << std::endl;
    std::cout << "   Список: " << list << std::endl;
    
    std::cout << "\n7. Удаляем элемент из конца:" << std::endl;
    int back = list.PopBack();
    std::cout << "   Удален: " << back << std::endl;
    std::cout << "   Список: " << list << std::endl;
    return 0;
}
