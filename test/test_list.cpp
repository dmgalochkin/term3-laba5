#include <gtest/gtest.h>
#include <utility>
#include "../structures/TList.hpp"
#include "../structures/TVector.hpp"

TEST(TListTest, DefaultConstructor)
{
  TList<int> list;
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_FALSE(list.IsFull());
  EXPECT_EQ(list.GetSize(), 0);
  EXPECT_EQ(list.GetHead(), nullptr);
  EXPECT_EQ(list.GetTail(), nullptr);
}

TEST(TListTest, VectorConstructor)
{
  TVector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(3);
  vec.PushBack(4);
  vec.PushBack(5);
  TList<int> list(vec);
  EXPECT_FALSE(list.IsEmpty());
  EXPECT_EQ(list.GetSize(), 5);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[4], 5);
}

TEST(TListTest, CopyConstructor)
{
  TVector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(3);
  TList<int> original(vec);
  TList<int> copy(original);
  
  EXPECT_EQ(copy.GetSize(), 3);
  EXPECT_TRUE(copy == original);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy[1], 2);
  EXPECT_EQ(copy[2], 3);
}

TEST(TListTest, MoveConstructor)
{
  TVector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(3);
  TList<int> original(vec);
  TList<int> moved(std::move(original));
  
  EXPECT_EQ(moved.GetSize(), 3);
  EXPECT_TRUE(original.IsEmpty());
  EXPECT_EQ(moved[0], 1);
  EXPECT_EQ(moved[1], 2);
  EXPECT_EQ(moved[2], 3);
}

TEST(TListTest, CopyAssignmentOperator)
{
  TVector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(3);
  TList<int> original(vec);
  TList<int> copy;
  copy = original;
  
  EXPECT_EQ(copy.GetSize(), 3);
  EXPECT_TRUE(copy == original);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy[2], 3);
}

TEST(TListTest, MoveAssignmentOperator)
{
  TVector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(3);
  TList<int> original(vec);
  TList<int> moved;
  moved = std::move(original);
  
  EXPECT_EQ(moved.GetSize(), 3);
  EXPECT_TRUE(original.IsEmpty());
  EXPECT_EQ(moved[0], 1);
  EXPECT_EQ(moved[2], 3);
}

TEST(TListTest, SelfAssignment)
{
  TVector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(3);
  TList<int> list(vec);
  list = list;
  
  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
}

TEST(TListTest, PushFrontOperation)
{
  TList<int> list;
  
  list.PushFront(1);
  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_FALSE(list.IsEmpty());
  EXPECT_EQ(list[0], 1);
  
  list.PushFront(2);
  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list[0], 2);
  EXPECT_EQ(list[1], 1);
  
  list.PushFront(3);
  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list[0], 3);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 1);
}

TEST(TListTest, PushBackOperation)
{
  TList<int> list;
  
  list.PushBack(1);
  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_FALSE(list.IsEmpty());
  EXPECT_EQ(list[0], 1);
  
  list.PushBack(2);
  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  
  list.PushBack(3);
  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
}

TEST(TListTest, PopFrontOperation)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  TList<int> list(vec);
  
  int value = list.PopFront();
  EXPECT_EQ(value, 1);
  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list[0], 2);
  EXPECT_EQ(list[1], 3);
  
  value = list.PopFront();
  EXPECT_EQ(value, 2);
  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_EQ(list[0], 3);
  
  value = list.PopFront();
  EXPECT_EQ(value, 3);
  EXPECT_EQ(list.GetSize(), 0);
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListTest, PopBackOperation)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  TList<int> list(vec);
  
  int value = list.PopBack();
  EXPECT_EQ(value, 3);
  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  
  value = list.PopBack();
  EXPECT_EQ(value, 2);
  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_EQ(list[0], 1);
  
  value = list.PopBack();
  EXPECT_EQ(value, 1);
  EXPECT_EQ(list.GetSize(), 0);
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListTest, PopFrontOnEmptyList)
{
  TList<int> list;
  EXPECT_THROW(list.PopFront(), std::runtime_error);
}

TEST(TListTest, PopBackOnEmptyList)
{
  TList<int> list;
  EXPECT_THROW(list.PopBack(), std::runtime_error);
}

TEST(TListTest, IndexOperatorAccess)
{
  TVector<int> vec;
  vec.PushBack(10); vec.PushBack(20); vec.PushBack(30);
  TList<int> list(vec);
  
  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 20);
  EXPECT_EQ(list[2], 30);
  
  list[1] = 25;
  EXPECT_EQ(list[1], 25);
}

TEST(TListTest, IndexOperatorOutOfRange)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  TList<int> list(vec);
  EXPECT_THROW(list[3], std::out_of_range);
  EXPECT_THROW(list[10], std::out_of_range);
}

TEST(TListTest, IndexOperatorOnEmptyList)
{
  TList<int> list;
  EXPECT_THROW(list[0], std::out_of_range);
}

TEST(TListTest, EqualityOperators)
{
  TVector<int> vec1, vec2, vec3, vec4;
  vec1.PushBack(1); vec1.PushBack(2); vec1.PushBack(3);
  vec2.PushBack(1); vec2.PushBack(2); vec2.PushBack(3);
  vec3.PushBack(1); vec3.PushBack(2); vec3.PushBack(4);
  vec4.PushBack(1); vec4.PushBack(2);
  TList<int> list1(vec1);
  TList<int> list2(vec2);
  TList<int> list3(vec3);
  TList<int> list4(vec4);
  
  EXPECT_TRUE(list1 == list2);
  EXPECT_FALSE(list1 != list2);
  
  EXPECT_FALSE(list1 == list3);
  EXPECT_TRUE(list1 != list3);
  
  EXPECT_FALSE(list1 == list4);
  EXPECT_TRUE(list1 != list4);
}

TEST(TListTest, ConcatenationOperator)
{
  TVector<int> vec1, vec2;
  vec1.PushBack(1); vec1.PushBack(2); vec1.PushBack(3);
  vec2.PushBack(4); vec2.PushBack(5); vec2.PushBack(6);
  TList<int> list1(vec1);
  TList<int> list2(vec2);
  TList<int> result = list1 + list2;
  
  EXPECT_EQ(result.GetSize(), 6);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
  EXPECT_EQ(result[3], 4);
  EXPECT_EQ(result[4], 5);
  EXPECT_EQ(result[5], 6);
  
  
  EXPECT_EQ(list1.GetSize(), 3);
  EXPECT_EQ(list2.GetSize(), 3);
}

TEST(TListTest, InsertAfterOperation)
{
  TVector<int> vec;
  vec.PushBack(10); vec.PushBack(30);
  TList<int> list(vec);
  TListNode<int>* head = list.GetHead();
  
  list.InsertAfter(head, 20);
  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 20);
  EXPECT_EQ(list[2], 30);
}

TEST(TListTest, RemoveOperation)
{
  TVector<int> vec;
  vec.PushBack(10); vec.PushBack(20); vec.PushBack(30);
  TList<int> list(vec);
  TListNode<int>* head = list.GetHead();
  TListNode<int>* nodeToRemove = head->next;
  
  list.Remove(nodeToRemove);
  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 30);
}

TEST(TListTest, ClearOperation)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  vec.PushBack(4); vec.PushBack(5);
  TList<int> list(vec);
  EXPECT_EQ(list.GetSize(), 5);
  
  list.Clear();
  EXPECT_EQ(list.GetSize(), 0);
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.GetHead(), nullptr);
}

TEST(TListTest, CountMethod)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  vec.PushBack(2); vec.PushBack(4); vec.PushBack(2); vec.PushBack(5);
  TList<int> list(vec);
  
  EXPECT_EQ(list.Count(2), 3);
  EXPECT_EQ(list.Count(1), 1);
  EXPECT_EQ(list.Count(6), 0);
}

TEST(TListTest, FindAllMethod)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  vec.PushBack(2); vec.PushBack(4); vec.PushBack(2); vec.PushBack(5);
  TList<int> list(vec);
  auto found = list.FindAll(2);
  
  EXPECT_EQ(found.GetSize(), 3);
}


TEST(TListTest, CircularNature)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  TList<int> list(vec);
  TListNode<int>* head = list.GetHead();
  TListNode<int>* tail = list.GetTail();
  
  EXPECT_EQ(head->data, 1);
  EXPECT_EQ(tail->data, 3);
  EXPECT_EQ(head->prev, tail);
  EXPECT_EQ(tail->next, head);
}

TEST(TListTest, SingleElementCircular)
{
  TList<int> list;
  list.PushBack(42);
  
  TListNode<int>* head = list.GetHead();
  TListNode<int>* tail = list.GetTail();
  
  EXPECT_EQ(head, tail);
  EXPECT_EQ(head->next, head);
  EXPECT_EQ(head->prev, head);
  EXPECT_EQ(head->data, 42);
}

TEST(TListTest, DifferentDataTypes)
{
  TVector<std::string> vecStr;
  vecStr.PushBack("hello");
  vecStr.PushBack("world");
  TList<std::string> stringList(vecStr);
  EXPECT_EQ(stringList[0], "hello");
  EXPECT_EQ(stringList[1], "world");
  
  stringList.PushFront("start");
  EXPECT_EQ(stringList[0], "start");
  EXPECT_EQ(stringList[1], "hello");
  EXPECT_EQ(stringList[2], "world");
  
  TVector<double> vecDouble;
  vecDouble.PushBack(3.14);
  vecDouble.PushBack(2.71);
  TList<double> doubleList(vecDouble);
  EXPECT_DOUBLE_EQ(doubleList[0], 3.14);
  EXPECT_DOUBLE_EQ(doubleList[1], 2.71);
}


TEST(TListTest, IteratorFunctionality)
{
  TVector<int> vec;
  vec.PushBack(1); vec.PushBack(2); vec.PushBack(3);
  vec.PushBack(4); vec.PushBack(5);
  TList<int> list(vec);
  
  
  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  
  ++it;
  EXPECT_EQ(*it, 2);
  
  ++it;
  EXPECT_EQ(*it, 3);
  
  
  int count = 0;
  int expected[] = {1, 2, 3, 4, 5};
  for (auto& value : list)
  {
    EXPECT_EQ(value, expected[count]);
    count++;
    if (count >= 5) break; 
  }
  EXPECT_EQ(count, 5);
}

TEST(TListTest, EmptyListIterator)
{
  TList<int> emptyList;
  auto it = emptyList.begin();
  auto end = emptyList.end();
  
  EXPECT_EQ(it, end);
}