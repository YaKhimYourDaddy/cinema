#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../Model/Comparable.h"
#include <concepts>
#include <iostream>
using namespace std;

template <typename T>
concept ComparableClass = std::derived_from<T, Comparable> && requires(T t, string s) {
    { t.isMatch(s) } -> std::same_as<bool>;
};

// Node template class
template <typename T>
    requires ComparableClass<T>
class Node
{
private:
    T data;
    Node *next;

public:
    Node() : next(nullptr) {}
    explicit Node(const T &value) : data(value), next(nullptr) {}

    // Getters
    T &getData() { return data; }
    const T &getData() const { return data; }
    Node *getNext() const { return next; }

    // Setters
    void setData(const T &value) { data = value; }
    void setNext(Node *node) { next = node; }

    // Friendship declaration
    template <typename U>
        requires ComparableClass<U>
    friend class LinkedList;
};

template <typename T>
    requires ComparableClass<T>
class LinkedList
{
private:
    Node<T> *head;
    size_t size;

public:
    void clear()
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            Node<T> *next = current->getNext();
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;
    }

    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList()
    {
        clear();
    }

    LinkedList(const LinkedList &other) : head(nullptr), size(0)
    {
        Node<T> *current = other.head;
        while (current != nullptr)
        {
            push_back(current->getData());
            current = current->getNext();
        }
    }

    LinkedList &operator=(const LinkedList &other)
    {
        if (this != &other)
        {
            clear();
            Node<T> *current = other.head;
            while (current != nullptr)
            {
                push_back(current->getData());
                current = current->getNext();
            }
        }
        return *this;
    }

    vector<T *> toVector()
    {
        vector<T *> result;
        Node<T> *current = head;
        while (current)
        {
            result.push_back(&(current->getData()));
            current = current->getNext();
        }
        return result;
    }

    void push_front(const T &value)
    {
        Node<T> *newNode = new Node<T>(value);
        newNode->setNext(head);
        head = newNode;
        size++;
    }

    void push_back(const T &value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node<T> *current = head;
            while (current->getNext())
            {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
        size++;
    }

    T *find(const std::string &keyword)
    {
        Node<T> *current = head;
        while (current)
        {
            if ((current->getData()).isMatch(keyword))
            {
                return &(current->getData());
            }
            current = current->getNext();
        }
        return nullptr;
    }

    T *getLast()
    {
        if (!head)
        {
            return nullptr; // Return nullptr if list is empty
        }

        Node<T> *current = head;
        while (current->getNext())
        {
            current = current->getNext();
        }
        return &(current->getData());
    }

    // vector<T *> find(const string &keyword)
    // {
    //     vector<T *> results;
    //     Node<T> *current = head;
    //     while (current)
    //     {
    //         if (current->getData().isMatch(keyword))
    //         {
    //             results.push_back(&(current->getData()));
    //         }
    //         current = current->getNext();
    //     }
    //     return results;
    // }

    bool remove(const T &value)
        requires std::equality_comparable<T>
    {
        if (!head)
            return false;

        if (head->getData() == value)
        {
            Node<T> *temp = head;
            head = head->getNext();
            delete temp;
            size--;
            return true;
        }

        Node<T> *current = head;
        while (current->getNext() && !(current->getNext()->getData() == value))
        {
            current = current->getNext();
        }

        if (current->getNext())
        {
            Node<T> *temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
            size--;
            return true;
        }

        return false;
    }

    size_t getSize() const { return size; }
    // bool empty() const { return size == 0; }

    // Iterator implementation with concepts
    class Iterator
    {
    private:
        Node<T> *current;

    public:
        explicit Iterator(Node<T> *node) : current(node) {}

        T &operator*()
        {
            return current->getData();
        }

        const T &operator*() const
        {
            return current->getData();
        }

        Iterator &operator++()
        {
            if (current)
                current = current->getNext();
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

#endif // LINKEDLIST_H
