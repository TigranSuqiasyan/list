/**
 * @file list.hpp
 * this file defines the class list
 * in the namespace my
 */

#ifndef MY_LIST_H
#define MY_LIST_H

#include <iostream>
#include <initializer_list>

namespace my {
  
template <typename T>
class list {
public:                           // done
  list() = default;
  list(size_t);
  list(size_t, const T&);
  list(std::initializer_list<T>);
  list(const list&);
  list(list&&);
  ~list();

public:                           // done
  list& operator=(const list&);
  list& operator=(list&&);
  list& operator=(std::initializer_list<T>);
  list& assign(size_t, const T&);
  list& assign(std::initializer_list<T>);

public:                          // done
  T& front();
  const T& front() const;
  T& back();
  const T& back() const;

public:                          // done
  void print() const;
  bool empty() const;
  size_t size() const;
  size_t max_size() const;
  template <typename E>
  friend bool operator==(const list<E>&, const list<E>&);
  template <typename E>
  friend bool operator!=(const list<E>&, const list<E>&);
  template <typename E>
  friend bool operator<(const list<E>&, const list<E>&);
  template <typename E>
  friend bool operator>(const list<E>&, const list<E>&);
  template <typename E>
  friend bool operator<=(const list<E>&, const list<E>&);
  template <typename E>
  friend bool operator>=(const list<E>&, const list<E>&);

public:                            // done
  void clear();                      
  void insert(size_t, const T&);       
  void insert(size_t, std::initializer_list<T>);
  void erase(size_t);                     
  void erase(size_t, size_t);           
  void push_back(const T&);                  
  void pop_back();                       
  void push_front(const T&);             
  void pop_front();                    
  void resize(size_t);                 
  void resize(size_t, const T&);                 
  void swap(list&);                              

// public:
//   void merge(list&);            // + // unoptimal
//   void splice(size_t, list&);   //
//   void remove(const T&);        //
//   void reverse();               //
//   void unique();                //
//   void sort();                  //

private:
  struct Node {                   // done
    Node() = default;
    Node(const T&);
    Node(Node*, const T&, Node*);
    Node(Node*, Node*);
    Node(const Node&);
    Node(Node&&);
    ~Node() = default;
    Node& operator=(const Node&);
    Node& operator=(Node&&);
    Node* prev;
    T value;
    Node* next;
  };

  Node* _head{};
  Node* _tail{};
};

} // namespace my

#endif // MY_LIST_H 