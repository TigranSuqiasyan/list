/**
 * @file list.cpp
 * this files defines the implementation
 * of the class list declared in the 
 * namespace my
 */

#include "list.hpp"

// ---------------------------------- NODE

template <typename T>
my::list<T>::Node::Node(const T& val) : prev{}, value{val}, next{} {}

template <typename T>
my::list<T>::Node::Node(Node* p, const T& val, Node* n) 
  : prev{p}, value{val}, next{n} {}

template <typename T>
my::list<T>::Node::Node(Node* p, Node* n) : prev{p}, value{}, next{n} {}

template <typename T>
my::list<T>::Node::Node(const my::list<T>::Node& oth) 
  : prev{oth.prev}, value{oth.value}, next{oth.next} {
}

template <typename T>
my::list<T>::Node::Node(my::list<T>::Node&& oth) 
  : prev{std::move(oth.prev)}, value{std::move(oth.value)}, next{std::move(oth.next)} {
}

template <typename T>
typename my::list<T>::Node& my::list<T>::Node::operator=(const my::list<T>::Node& rhs) {
  prev = rhs.prev;
  value = rhs.value;
  next = rhs.value;
}

template <typename T>
typename my::list<T>::Node& my::list<T>::Node::operator=(my::list<T>::Node&& rhs) {
  prev = std::move(rhs.prev);
  value = std::move(rhs.value);
  next = std::move(rhs.next);
}

// ------------------------------------------ LIST
// --------------------- THE CONSTRUCTORS AND THE DESTRUCTOR

template <typename T>
my::list<T>::list(size_t count) : _head{}, _tail{} {
  if (count) {
    _head = new Node();
    auto cur = _head;
    for (int i{}; i < count - 1; ++i) {
      cur->next = new Node(cur, nullptr);
      cur->next->prev = cur;
      cur = cur -> next;
    }
    _tail = cur;
  }
}

template <typename T>
my::list<T>::list(size_t count, const T& val) {
  if (count) {
    _head = new Node(val);
    auto cur = _head;
    for (int i{}; i < count - 1; ++i) {
      cur->next = new Node(cur, val, nullptr);
      cur->next->prev = cur;
      cur = cur -> next;
    }
    _tail = cur;
  }
}

template <typename T>
my::list<T>::list(std::initializer_list<T> ilist) {
  auto begin = ilist.begin();
  auto end = ilist.end();
  _head = new Node(*(begin++));
  auto cur = _head;
  for (; begin != end; ++begin) {
    cur->next = new Node(cur, *begin, nullptr);
    cur = cur->next;
  }
  _tail = cur;
}

template <typename T>
my::list<T>::list(const my::list<T>& oth) {
  if (oth._head) {
    _head = new Node(oth._head->value);
    auto cur1 = _head;
    auto cur2 = oth._head;
    while (cur2) {
      cur1 -> next = new Node(cur1, cur2 -> value, nullptr);
      cur1 = cur1 -> next;
      cur2 = cur2 -> next;
    }
    _tail = cur1;
  }
} 

template <typename T>
my::list<T>::list(my::list<T>&& oth) 
    : _head{oth._head}, _tail{oth._tail} {
  oth._head = nullptr;
  oth._tail = nullptr;
}

template <typename T>
my::list<T>::~list() {
  this -> clear();
}

// ------------------------------------------- ASSIGNMENT

template <typename T>
my::list<T>& my::list<T>::operator=(const my::list<T>& rhs) {
  my::list<T> temp = rhs;
  std::swap(*this, temp);
  return *this;
}

template <typename T>
my::list<T>& my::list<T>::operator=(my::list<T>&& rhs) {
  this -> clear();
  _head = rhs._head;
  _tail = rhs._tail;
  rhs._head = nullptr;
  rhs._tail = nullptr;
  return *this;
}

template <typename T>
my::list<T>& my::list<T>::operator=(std::initializer_list<T> ilist) {
  my::list<T> temp(ilist);
  std::swap(*this, temp);
  return *this;
}

template <typename T>
my::list<T>& my::list<T>::assign(size_t count, const T& val) {
  my::list<T> temp(count, val);
  std::swap(*this, temp);
  return *this;
}

template <typename T>
my::list<T>& my::list<T>::assign(std::initializer_list<T> ilist) {
  return this -> operator=(ilist);
}

// ------------------------------------------- MEMBER ACCESS

template <typename T>
T& my::list<T>::front() {
  return _head -> value;
}

template <typename T>
const T& my::list<T>::front() const {
  return _head -> value;
}

template <typename T>
T& my::list<T>::back() {  
  return _tail -> value;
}

template <typename T>
const T& my::list<T>::back() const {  
  return _tail -> value;
}

// ------------------------------------------- NON MODIFYING OPERATIONS 

template <typename T>
void my::list<T>::print() const {
  auto cur = _head;
  while (cur) {
    std::cout << cur->value << " ";
    cur = cur->next;
  }
}

template <typename T>
bool my::list<T>::empty() const {
  return !_head;
}

template <typename T>
size_t my::list<T>::size() const {
  size_t size{};
  if (_head) {
    auto cur = _head;
    while (cur) {
      ++size;
      cur = cur -> next;
    }
  }
  return size;
}

template <typename T>
size_t my::list<T>::max_size() const {
  return (sizeof(size_t) - 4) ? UINT32_MAX : UINT64_MAX;
}


namespace my {

template <typename E>
bool operator!=(const list<E>& lhs, const list<E>& rhs) {
  auto cur1 = lhs._head;
  auto cur2 = rhs._head;
  while (cur1 && cur2) {
    if (cur1 -> value != cur2 -> value) 
      return true;
    cur1 = cur1 -> next;
    cur2 = cur2 -> next;
  }
  if (cur1 || cur2)
    return true;
  return false;
}

template <typename E>
bool operator==(const list<E>& lhs, const list<E>& rhs) {
  return !(lhs != rhs);
}

template <typename E>
bool operator <(const list<E>& lhs, const list<E>& rhs) {
  auto cur1 = lhs._head;
  auto cur2 = rhs._head;
  while (cur1 && cur2) {
    if (cur1 -> value < cur2 -> value)
      return true;
    if (cur1 -> value > cur2 -> value)
      return false;
    cur1 = cur1 -> next;
    cur2 = cur2 -> next;
  }
  if(cur1)
    return false;
  else if (cur2)
    return true;
  return false;
}

template <typename E>
bool operator >(const list<E>& lhs, const list<E>& rhs) {
  auto cur1 = lhs._head;
  auto cur2 = rhs._head;
  while (cur1 && cur2) {
    if (cur1 -> value > cur2 -> value)
      return true;
    if (cur1 -> value < cur2 -> value)
      return false;
    cur1 = cur1 -> next;
    cur2 = cur2 -> next;
  }
  if(cur2)
    return false;
  else if (cur1)
    return true;
  return false;
}

template <typename E>
bool operator<=(const list<E>& lhs, const list<E>& rhs) {
  return !(lhs > rhs);
}

template <typename E>
bool operator>=(const list<E>& lhs, const list<E>& rhs) {
  return !(lhs < rhs);
}

} // my

// ----------------------------------------- MODIFYING OPERATIONS

template <typename T>
void my::list<T>::clear() {
  if ((_head == _tail) && _head) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    return;
  }
  if ((_head != _tail)) {
    auto cur = _head;
    while (cur -> next) {
      cur = cur -> next;
      delete cur -> prev;
    }
    delete cur;
    _head = nullptr;
    _tail = nullptr;
  }
}

template <typename T>
void my::list<T>::insert(size_t pos, const T& val) {
  size_t size = this->size();
  if (pos < 0 || pos > size - 1) {
    return;
  }
  if (pos == 0) {
    this->push_front(val);
    return;
  }
  if (pos == size - 1) {
    this->push_back(val);
    return;
  }
  auto cur = _head;
  while (--pos) {
    cur = cur->next;
  }
  auto tmp{cur->next};
  cur->next = new Node(cur, val, nullptr);
  cur->next->next = tmp;
  tmp->prev = cur->next;
  tmp = nullptr;
}

template <typename T>
void my::list<T>::insert(size_t pos, std::initializer_list<T> ilist) {
  size_t size = this->size();
  auto begin = ilist.begin();
  auto end = ilist.end();
  if (pos < 0 || pos > size) {
    return;
  }
  if (!pos) {
    auto tmp = _head;
    _head = new Node(*begin++);
    auto cur = _head;
    for (; begin != end; ++begin) {
      cur->next = new Node(cur, *begin, nullptr);
      cur = cur->next;
    }
    cur->next = tmp;
    tmp->prev = cur;
    tmp = nullptr;
    if (size == 1) {
      _tail = cur->next;
    }
    return;
  }
  if (pos == size) {
    auto cur = _tail;
    for (; begin != end; ++begin) {
      cur->next = new Node(cur, *begin, nullptr);
      cur = cur->next;
    }
    _tail = cur;
    return;
  }
  auto cur = _head;
  while (--pos) {
    cur = cur->next;
  }
  auto tmp = cur->next;
  for (; begin != end; ++begin) {
    cur->next = new Node(cur, *begin, nullptr);
    cur = cur->next;
  }
  cur->next = tmp;
  tmp->prev = cur;
}

template <typename T>
void my::list<T>::erase(size_t pos) {
  size_t size = this->size();
  if (pos <= 0 || pos > size - 1) {
    return;
  }
  if (!pos) {
    this->pop_front();
    return;
  }
  if (pos = size - 1) {
    this->pop_back();
  }
  auto cur = _head;
  while (--pos) {
    cur = cur->next;
  }
  auto tmp = cur->next->next;
  delete cur->next;
  cur->next = tmp;
  tmp->prev = cur;
  tmp = nullptr;
}

template <typename T>
void my::list<T>::erase(size_t pos1, size_t pos2) {
  size_t size = this->size();
  if (pos1 < 0 || pos1 > pos2 || pos2 > size - 1) {
    return;
  }
  for (size_t i{pos1}; i < pos2; ++i) {
    this->erase(i);
  }
}

template <typename T>
void my::list<T>::push_back(const T& val) {
  if (!_head) {
    _head = new Node(val);
    _tail = _head;
    return;
  }
  _tail->next = new Node(_tail, val, nullptr);
  _tail = _tail->next;
}

template <typename T>
void my::list<T>::pop_back() {
  if (!_head) {
    return;
  }
  if (this->size() == 1) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
  }
  auto tmp = _tail;
  _tail->prev->next = nullptr;
  _tail = _tail->prev;
  delete tmp;
}

template <typename T>
void my::list<T>::push_front(const T& val) {
  if (!_head) {
    _head = new Node(val);
    _tail = _head;
    return;
  }
  _head->prev = new Node(nullptr, val, _head);
  _head = _head->prev;
}

template <typename T>
void my::list<T>::pop_front() {
  if (!_head) {
    return;
  }
  if (this->size() == 1) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
  }
  auto tmp = _head;
  _head->next->prev = nullptr;
  _head = _head->next;
  delete tmp;
}

template <typename T>
void my::list<T>::resize(size_t count) {
  size_t size = this->size();
  if (count == size || count < 0) {
    return;
  }
  if (count > size) {
    T temp{};
    for (size_t i{}; i < count - size; ++i) {
      this->push_back(temp);
    }
    return;
  }
  for (size_t i{}; i < size - count; ++i) {
    this->pop_back();
  }
}

template <typename T>
void my::list<T>::resize(size_t count, const T& val) {
  size_t size = this->size();
  if (count == size || count < 0) {
    return;
  }
  if (count > size) {
    T temp{val};
    for (size_t i{}; i < count - size; ++i) {
      this->push_back(temp);
    }
    return;
  }
  for (size_t i{}; i < size - count; ++i) {
    this->pop_back();
  }
}

template <typename T>
void my::list<T>::swap(my::list<T>& oth) {
  Node* temp;

  temp = _head;
  _head = oth._head;
  oth._head = temp;

  temp = _tail;
  _tail = oth._tail;
  oth._tail = temp;
}

// ----------------------- MORE OR LESS DIFFICULT OPERATIONS

// template <typename T>
// void my::list<T>::merge(my::list<T>& oth) {
//   if (!oth._head) {
//     return;
//   }
//   if (!_head) {
//     this->swap(oth);
//   }
//   auto cur1 = _head;
//   auto cur2 = oth._head;
//   my::list<T> temp;
//   while (cur1 && cur2) {
//     if (cur1->value < cur2->value) {
//       temp.push_back(cur1->value);
//       cur1 = cur1->next;
//     }
//     else {
//       temp.push_back(cur2->value);
//       cur2 = cur2->next;
//     }
//   }
//   while (cur1) {
//     temp.push_back(cur1->value);
//     cur1 = cur1->next;
//   }
//   while (cur2) {
//     temp.push_back(cur2->value);
//     cur2 = cur2->next;
//   }
//   oth.clear();
//   this->swap(temp);
//   temp.clear();
// }

// template <typename T>
// void my::list<T>::splice(size_t pos, my::list<T>& oth) {
//   size_t size = this->size();
//   if (pos < 0 || pos > size) {
//     return;
//   }
//   if (!_head) {
//     this->swap(oth);
//     return;
//   }
//   if (!oth._head) {
//     return;
//   }
//   if (pos == 0) {
//     auto cur = oth._head;
//     auto tmp = _head;
//     _head = oth._head;
//     oth._tail->next = tmp;
//     tmp->prev = oth._tail;
//     oth._head = nullptr;
//     oth._tail = nullptr;
//   }
//   auto cur = _head;
//   for (size_t i{}; i < pos - 1; ++i) {
//     cur = cur->next;
//   }
//   auto tmp = cur->next;
//   cur->next = oth._head;
//   oth._head->prev = cur;
//   if (tmp) {
//     oth._tail->next = tmp;
//     tmp->prev = oth._tail;
//   }
//   else {
//     _tail = oth._tail;
//     _head = oth._head;
//   }
//   oth._head = nullptr;
//   oth._tail = nullptr;
//  }

// template <typename T>
// void my::list<T>::remove(const T& val) {
//   auto cur = _head;
//   while (cur->next) {
//     if (cur->value == val) {
//       auto tmp = cur->next;
