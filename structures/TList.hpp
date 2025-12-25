#pragma once
#include <iostream>
#include <fstream>
#include <functional>
#include <stdexcept>
#include "TVector.hpp"

template <typename T>
struct TListNode
{
  T data;
  TListNode<T>* next;
  TListNode<T>* prev;

  TListNode(const T& value);
};

template<typename T>
class TList
{
private:
  size_t size;
  TListNode<T>* head;

public:
  TList();
  TList(const TVector<T>& vector);
  TList(const TList<T>& other);
  TList(TList<T>&& other);
  ~TList();

  size_t GetSize() const;
  TListNode<T>* GetHead() const;
  TListNode<T>* GetTail() const;
  bool IsEmpty() const;
  bool IsFull() const;

  void PushFront(const T& value);
  void PushBack(const T& value);
  T PopFront();
  T PopBack();
  
  void InsertAfter(TListNode<T>* node, const T& value);
  void Remove(TListNode<T>* node);
  void Clear();

  TList<T>& operator=(const TList<T>& other);
  TList<T>& operator=(TList<T>&& other);

  bool operator==(const TList<T>& other) const;
  bool operator!=(const TList<T>& other) const;

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  TList<T> operator+(const TList<T>& other) const;

  size_t Count(const T& value) const;
  TList<TListNode<T>*> FindAll(const T& value) const;
  void Apply(std::function<void(T&)> func);
  
  void SaveToFile(const std::string& filename) const;
  void LoadFromFile(const std::string& filename);

  class Iterator
  {
  private:
    TListNode<T>* current;
    TListNode<T>* start;
    bool first_iteration;

  public:
    Iterator(TListNode<T>* node);
    T& operator*();
    Iterator& operator++();
    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;
    TListNode<T>* GetNode() const;
  };

  Iterator begin();
  Iterator end();

  template<typename U>
  friend std::ostream& operator<<(std::ostream& os, const TList<U>& list);
  
  template<typename U>
  friend std::istream& operator>>(std::istream& is, TList<U>& list);
};

template<typename T>
TListNode<T>::TListNode(const T& value) : data(value), next(nullptr), prev(nullptr)
{
}
template<typename T>
TList<T>::TList() : size(0), head(nullptr)
{
}

template<typename T>
TList<T>::TList(const TVector<T>& vector) : size(0), head(nullptr)
{
  for (size_t i = 0; i < vector.GetSize(); i++)
  {
    PushBack(vector[i]);
  }
}

template<typename T>
TList<T>::TList(const TList<T>& other) : size(0), head(nullptr)
{
  if (!other.IsEmpty())
  {
    TListNode<T>* current = other.head;
    do
    {
      PushBack(current->data);
      current = current->next;
    } while (current != other.head);
  }
}

template<typename T>
TList<T>::TList(TList<T>&& other) : size(other.size), head(other.head)
{
  other.size = 0;
  other.head = nullptr;
}

template<typename T>
TList<T>::~TList()
{
  Clear();
}

template<typename T>
size_t TList<T>::GetSize() const
{
  return size;
}

template<typename T>
TListNode<T>* TList<T>::GetHead() const
{
  return head;
}

template<typename T>
TListNode<T>* TList<T>::GetTail() const
{
  return head ? head->prev : nullptr;
}

template<typename T>
bool TList<T>::IsEmpty() const
{
  return size == 0;
}

template<typename T>
bool TList<T>::IsFull() const
{
  return false;
}

template<typename T>
void TList<T>::PushFront(const T& value)
{
  TListNode<T>* newNode = new TListNode<T>(value);
  
  if (IsEmpty())
  {
    head = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
  }
  else
  {
    TListNode<T>* tail = head->prev;
    newNode->next = head;
    newNode->prev = tail;
    head->prev = newNode;
    tail->next = newNode;
    head = newNode;
  }
  size++;
}

template<typename T>
void TList<T>::PushBack(const T& value)
{
  TListNode<T>* newNode = new TListNode<T>(value);
  
  if (IsEmpty())
  {
    head = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
  }
  else
  {
    TListNode<T>* tail = head->prev;
    newNode->next = head;
    newNode->prev = tail;
    head->prev = newNode;
    tail->next = newNode;
  }
  size++;
}

template<typename T>
T TList<T>::PopFront()
{
  if (IsEmpty())
  {
    throw std::runtime_error("List is empty");
  }

  T value = head->data;
  TListNode<T>* nodeToDelete = head;

  if (size == 1)
  {
    head = nullptr;
  }
  else
  {
    TListNode<T>* tail = head->prev;
    head = head->next;
    head->prev = tail;
    tail->next = head;
  }

  delete nodeToDelete;
  size--;
  return value;
}

template<typename T>
T TList<T>::PopBack()
{
  if (IsEmpty())
  {
    throw std::runtime_error("List is empty");
  }

  TListNode<T>* tail = head->prev;
  T value = tail->data;

  if (size == 1)
  {
    head = nullptr;
  }
  else
  {
    TListNode<T>* newTail = tail->prev;
    newTail->next = head;
    head->prev = newTail;
  }

  delete tail;
  size--;
  return value;
}

template<typename T>
void TList<T>::InsertAfter(TListNode<T>* node, const T& value)
{
  if (!node || IsEmpty())
  {
    return;
  }

  TListNode<T>* newNode = new TListNode<T>(value);
  newNode->next = node->next;
  newNode->prev = node;
  node->next->prev = newNode;
  node->next = newNode;
  size++;
}

template<typename T>
void TList<T>::Remove(TListNode<T>* node)
{
  if (!node || IsEmpty())
  {
    return;
  }

  if (size == 1)
  {
    head = nullptr;
  }
  else
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (node == head)
    {
      head = node->next;
    }
  }

  delete node;
  size--;
}

template<typename T>
void TList<T>::Clear()
{
  while (!IsEmpty())
  {
    PopFront();
  }
}

template<typename T>
TList<T>& TList<T>::operator=(const TList<T>& other)
{
  if (this != &other)
  {
    Clear();
    if (!other.IsEmpty())
    {
      TListNode<T>* current = other.head;
      do
      {
        PushBack(current->data);
        current = current->next;
      } while (current != other.head);
    }
  }
  return *this;
}

template<typename T>
TList<T>& TList<T>::operator=(TList<T>&& other)
{
  if (this != &other)
  {
    Clear();
    size = other.size;
    head = other.head;
    other.size = 0;
    other.head = nullptr;
  }
  return *this;
}

template<typename T>
bool TList<T>::operator==(const TList<T>& other) const
{
  if (size != other.size)
  {
    return false;
  }

  if (IsEmpty())
  {
    return true;
  }

  TListNode<T>* current1 = head;
  TListNode<T>* current2 = other.head;
  
  do
  {
    if (current1->data != current2->data)
    {
      return false;
    }
    current1 = current1->next;
    current2 = current2->next;
  } while (current1 != head);

  return true;
}

template<typename T>
bool TList<T>::operator!=(const TList<T>& other) const
{
  return !(*this == other);
}

template<typename T>
T& TList<T>::operator[](size_t index)
{
  if (index >= size)
  {
    throw std::out_of_range("Index out of range");
  }

  TListNode<T>* current = head;
  for (size_t i = 0; i < index; i++)
  {
    current = current->next;
  }
  return current->data;
}

template<typename T>
const T& TList<T>::operator[](size_t index) const
{
  if (index >= size)
  {
    throw std::out_of_range("Index out of range");
  }

  TListNode<T>* current = head;
  for (size_t i = 0; i < index; i++)
  {
    current = current->next;
  }
  return current->data;
}

template<typename T>
TList<T> TList<T>::operator+(const TList<T>& other) const
{
  TList<T> result = *this;
  if (!other.IsEmpty())
  {
    TListNode<T>* current = other.head;
    do
    {
      result.PushBack(current->data);
      current = current->next;
    } while (current != other.head);
  }
  return result;
}

template<typename T>
size_t TList<T>::Count(const T& value) const
{
  size_t count = 0;
  if (!IsEmpty())
  {
    TListNode<T>* current = head;
    do
    {
      if (current->data == value)
      {
        count++;
      }
      current = current->next;
    } while (current != head);
  }
  return count;
}

template<typename T>
TList<TListNode<T>*> TList<T>::FindAll(const T& value) const
{
  TList<TListNode<T>*> result;
  if (!IsEmpty())
  {
    TListNode<T>* current = head;
    do
    {
      if (current->data == value)
      {
        result.PushBack(current);
      }
      current = current->next;
    } while (current != head);
  }
  return result;
}

template<typename T>
void TList<T>::Apply(std::function<void(T&)> func)
{
  if (!IsEmpty())
  {
    TListNode<T>* current = head;
    do
    {
      func(current->data);
      current = current->next;
    } while (current != head);
  }
}

template<typename T>
void TList<T>::SaveToFile(const std::string& filename) const
{
  std::ofstream file(filename, std::ios::binary);
  if (!file)
  {
    throw std::runtime_error("Cannot open file for writing");
  }

  file.write(reinterpret_cast<const char*>(&size), sizeof(size));
  
  if (!IsEmpty())
  {
    TListNode<T>* current = head;
    do
    {
      file.write(reinterpret_cast<const char*>(&current->data), sizeof(T));
      current = current->next;
    } while (current != head);
  }
}

template<typename T>
void TList<T>::LoadFromFile(const std::string& filename)
{
  Clear();
  std::ifstream file(filename, std::ios::binary);
  if (!file)
  {
    throw std::runtime_error("Cannot open file for reading");
  }

  size_t fileSize;
  file.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
  
  for (size_t i = 0; i < fileSize; i++)
  {
    T value;
    file.read(reinterpret_cast<char*>(&value), sizeof(T));
    PushBack(value);
  }
}

template<typename T>
TList<T>::Iterator::Iterator(TListNode<T>* node) : current(node), start(node), first_iteration(true)
{
}

template<typename T>
T& TList<T>::Iterator::operator*()
{
  return current->data;
}

template<typename T>
typename TList<T>::Iterator& TList<T>::Iterator::operator++()
{
  if (current)
  {
    current = current->next;
    first_iteration = false;
  }
  return *this;
}

template<typename T>
bool TList<T>::Iterator::operator!=(const Iterator& other) const
{
  if (!current || !other.current)
  {
    return current != other.current;
  }
  return first_iteration || current != start;
}

template<typename T>
bool TList<T>::Iterator::operator==(const Iterator& other) const
{
  return !(*this != other);
}

template<typename T>
TListNode<T>* TList<T>::Iterator::GetNode() const
{
  return current;
}

template<typename T>
typename TList<T>::Iterator TList<T>::begin()
{
  return Iterator(head);
}

template<typename T>
typename TList<T>::Iterator TList<T>::end()
{
  return Iterator(nullptr);
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const TList<U>& list)
{
  os << "List[" << list.size << "]: ";
  if (list.IsEmpty())
  {
    os << "(empty)";
  }
  else
  {
    os << "[";
    TListNode<U>* current = list.head;
    bool first = true;
    do
    {
      if (!first) os << ", ";
      os << current->data;
      current = current->next;
      first = false;
    } while (current != list.head);
    os << "]";
  }
  return os;
}

template<typename U>
std::istream& operator>>(std::istream& is, TList<U>& list)
{
  list.Clear();
  size_t numElements;
  
  is >> numElements;
  
  for (size_t i = 0; i < numElements; i++)
  {
    U element;
    is >> element;
    list.PushBack(element);
  }
  
  return is;
}