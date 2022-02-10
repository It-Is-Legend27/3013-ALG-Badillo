#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <initializer_list>

using namespace std;

/**
 * @brief Simple Node class for use in Singlely Linked List (of strings)
 *
 */
class wordNode
{
public:
    string word{string()};   // Data value
    wordNode *next{nullptr}; // Points to next node on list

    /**
     * @brief Construct a new wordNode object.
     *
     */
    wordNode();

    /**
     * @brief Construct a new wordNode object with params.
     *
     * @param _data string value to in the wordNode .
     * @param _next wordNode pointer link to next item in list.
     */
    wordNode(string _data, wordNode *_next);
};

/**
 * @brief Construct a new wordNode object.
 *
 */
inline wordNode::wordNode() {}

/**
 * @brief Construct a new wordNode object with params.
 *
 * @param _data string value to in the wordNode .
 * @param _next wordNode pointer link to next item in list.
 */
inline wordNode::wordNode(string _data, wordNode *_next = nullptr) : word{_data}, next{next} {}

/**
 * @brief Singely Linked List of words
 * 
 */
class List
{
private:
    wordNode *front{nullptr}; // Head of the list
    wordNode *back{nullptr};  // Tail of the list
    size_t list_size{0};      // Size of list
protected:
    wordNode *prev_Node(wordNode *ptr);

public:
    List();

    List(initializer_list<string> S);

    List(const List &other);

    ~List();

    void resize(size_t _size, string _data);

    bool empty();

    void fill(string _data);

    void clear();

    void push_front(string _data);

    void push_front(const List &other);

    void push_back(string _data);

    void push_back(const List &other);

    string &at(size_t n);

    string &at(size_t n) const;

    void pop_front();

    void pop_back();

    void erase(size_t n);

    void remove(string _value);

    const size_t find(string _value);

    void print(ostream &os);

    size_t size() const;

    size_t max_size() const;

    void swap(List &other);

    friend ostream &operator<<(ostream &os, const List &L);

    string &operator[](size_t n);

    string &operator[](size_t n) const;

    List &operator=(const List &rhs);

    List operator=(const initializer_list<string> S);
};

inline List::List() {}

inline wordNode *List::prev_Node(wordNode *ptr)
{
    wordNode *prev = front;
    for (size_t i = 0; i < list_size; i++)
    {
        if (prev->next == back)
        {
            return prev;
        }
        prev = prev->next;
    }
    return nullptr;
}

inline List::List(initializer_list<string> L)
{
    for (string x : L)
    {
        this->push_back(x);
    }
}

inline List::List(const List &other)
{
    wordNode *temp = other.front;
    while (temp)
    {
        this->push_back(temp->word);
        temp = temp->next;
    }
}

inline List::~List()
{
    this->clear();
}

inline void List::resize(size_t _size, string _data = string())
{
    if (this->list_size == _size || (int)_size < 0) // If same size, or invalid value, no resize needed
    {
        return;
    }
    else if (this->list_size > _size) // If new size is smaller, remove values
    {
        size_t removeAmount = this->list_size - _size;
        for (size_t i = 0; i < removeAmount; i++)
            this->pop_back();
    }
    else if (list_size < _size) // If new size is greater, add default values
    {
        size_t removeAmount = _size - this->list_size;
        for (size_t i = 0; i < removeAmount; i++)
            this->push_back(_data);
    }
}

inline bool List::empty()
{
    return this->list_size == 0;
}

inline void List::fill(string _data)
{
    if (!(this->empty())) // If not empty
    {
        wordNode *travel = this->front; // travel points to front

        while (travel) // Travels until travel == nullptr
        {
            travel->word = _data;  // Replace value
            travel = travel->next; // Move to next node
        }
    }
}

inline void List::clear()
{
    while (!(this->empty()))
        this->pop_back();
}

inline void List::push_front(string _data)
{
    if (this->empty()) // If empty list
    {
        this->front = this->back = new wordNode(_data); // 1 item, so front & back are same
    }
    else if (list_size == 1) // If one item
    {
        this->front = new wordNode(_data, this->back);
    }
    else
    {
        this->front = new wordNode(_data, this->front); // New front->next points to old front
    }
    this->list_size++;
}

inline void List::push_front(const List &other)
{
    for (size_t i = other.list_size - 1; i >= 0; i++)
    {
        this->push_front(other[i]);
    }
}

inline void List::push_back(string _data)
{
    if (this->empty())
    {
        this->front = this->back = new wordNode(_data); // 1 item, so front & back are same
    }
    else if (this->list_size == 1)
    {
        this->back = new wordNode(_data);
        this->front->next = this->back;
    }
    else
    {
        wordNode *prev = this->back;      // Prev wordNode to new back wordNode
        this->back = new wordNode(_data); // New back wordNode
        prev->next = this->back;          // Prev wordNode linked to new back
    }
    this->list_size++;
}

inline void List::push_back(const List &other)
{
    for (size_t i = 0; i < other.list_size; i++)
    {
        this->push_back(other[i]);
    }
}

inline string &List::at(size_t n)
{
    if ((int)n < 0 || n >= this->list_size)
    {
        exit(1);
    }
    else
    {
        wordNode *temp = this->front;
        for (size_t i = 0; i < n; i++)
        {
            temp = temp->next;
        }
        return temp->word;
    }
}

inline string &List::at(size_t n) const
{
    if ((int)n < 0 || n >= this->list_size)
    {
        exit(1);
    }
    else
    {
        wordNode *temp = this->front;
        for (size_t i = 0; i < n; i++)
        {
            temp = temp->next;
        }
        return temp->word;
    }
}

inline void List::pop_front()
{
    if (this->empty())
    {
        return; // Cannot pop from empty list
    }
    else if (this->list_size == 1)
    {
        delete this->front;
        this->front = this->back = nullptr;
        this->list_size--;
    }
    else
    {
        wordNode *trash = front;
        front = front->next;
        delete trash;
        this->list_size--;
    }
}

inline void List::pop_back()
{
    if (this->empty()) // Cannot pop from empty list
    {
        return;
    }
    else if (this->list_size == 1) // When only one item in list
    {
        delete this->back;
        this->front = this->back = nullptr;
        this->list_size--;
    }
    else
    {
        wordNode *prev = prev_Node(this->back); // Get prev wordNode
        delete this->back;
        this->back = prev;          // Update back
        this->back->next = nullptr; // Update back->next
        this->list_size--;
    }
}

inline void List::erase(size_t n)
{
    if (this->empty()) // Cannot erase from empty list
    {
        return;
    }
    else if ((int)n < 0 || n >= this->list_size) // Cannot access out of bounds
    {
        return;
    }
    else if (n == 0) // n is frontmost item
    {
        this->pop_front();
    }
    else if (n == this->list_size - 1) // n is rearmost item
    {
        this->pop_back();
    }
    else // Travels through until it reaches index
    {
        wordNode *temp = this->front;
        wordNode *prev = nullptr;
        for (size_t i = 0; i < n; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next; // Links prev wordNode to temp->next wordNode
        delete temp;
        this->list_size--;
    }
}

inline void List::remove(string _value)
{
    size_t i = this->find(_value); // Get index of first occurence of _value

    while (i != (size_t)-1) // While index i is valid
    {
        this->erase(i);
        i = this->find(_value);
    }
}

inline const size_t List::find(string _value)
{
    wordNode *temp = this->front;
    size_t i = 0;

    while (temp)
    {
        if (_value == temp->word) // If found, return index
        {
            return i;
        }
        else // Move to next node
        {
            temp = temp->next;
            i++;
        }
    }
    return (size_t)-1; // Returns -1 if not found
}

inline void List::print(ostream &os = cout)
{
    if (!(this->empty())) // If not empty
    {
        wordNode *travel = this->front; // travel points to front

        os << "[";

        while (travel) // Travels until travel == nullptr
        {
            os << travel->word; // Print word from node
            if (travel->next)
            {
                os << ", ";
            }
            travel = travel->next; // Move to next node
        }
        os << ']';
    }
}

inline size_t List::size() const
{
    return this->list_size;
}

inline size_t List::max_size() const
{
    return INT32_MAX;
}

inline void List::swap(List &other)
{
    std::swap<List>((*this), other);
}

inline ostream &operator<<(ostream &os, const List &L)
{
    wordNode *temp = L.front;
    os << "[";
    while (temp)
    {
        os << temp->word;
        if (temp->next)
        {
            os << ", ";
        }
        temp = temp->next;
    }
    os << "]";
    return os;
}

inline string &List::operator[](size_t n)
{
    if ((int)n < 0 || n >= this->list_size)
    {
        exit(1);
    }
    else
    {
        wordNode *temp = this->front;
        for (size_t i = 0; i < n; i++)
        {
            temp = temp->next;
        }
        return temp->word;
    }
}

inline List &List::operator=(const List &rhs)
{
    if (this != &rhs)
    {
        this->clear();
        this->push_back(rhs);
    }
    return *this;
}

inline List List::operator=(const initializer_list<string> L)
{
    this->clear();

    for (string x : L)
    {
        this->push_back(x);
    }
    return *this;
}