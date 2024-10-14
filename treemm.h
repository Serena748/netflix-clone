#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <list>
#include <iostream>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    
  public:
    class Iterator
    {
      public:
        Iterator() : m_isValid(false) {}
        
        Iterator(typename std::list<ValueType>::iterator it,
                 typename std::list<ValueType>::iterator end)
            : m_isValid(true), m_iterator(it), m_end(end) {
            }

        ValueType& get_value() const { return *m_iterator; }

        bool is_valid() const { return m_isValid; }

        void advance()
        {
            m_iterator++;
            if (m_iterator == m_end) m_isValid = false;
        }

      private:
        typename std::list<ValueType>::iterator m_iterator;
        typename std::list<ValueType>::iterator m_end;
        bool m_isValid;
    };

    TreeMultimap() : m_root(nullptr) {}

    ~TreeMultimap() { deleteNodes(m_root); }

    void insert(const KeyType& key, const ValueType& value)
    {
        
        // if we don't have a head, create one
        if (!m_root) {
            m_root = new Node(key, value);
            return;
        }
        
        // find the correct place to insert
        Node* curr = m_root;
        while(true) {
            if (key < curr->key) {
                if (curr->less == nullptr) {
                    curr->less = new Node(key, value);
                    return;
                }
                curr = curr->less;
            }
            else if (key == curr->key) {
                curr->append(value);
                return;
            }
            else {
                if (curr->greater == nullptr) {
                    curr->greater = new Node(key, value);
                    return;
                }
                curr = curr->greater;
            }
        }
        
    }

    Iterator find(const KeyType& key) const
    {
        Node* curr = m_root;
        
        // go down tree until correct location is found
        while (curr != nullptr) {
            if (key == curr->key)
                return Iterator(curr->values.begin(), curr->values.end());
            else if (key < curr->key)
                curr = curr->less;
            else
                curr = curr->greater;
        }
        
        // value not found; return invalid iterator
        return Iterator();
    }

  private:
    struct Node {
        Node(KeyType k, ValueType v) : less(nullptr), greater(nullptr), key(k), values({v}) {}
        void append(ValueType value) { values.push_back(value); }
        KeyType key;
        std::list<ValueType> values;
        Node* less;
        Node* greater;
    };
    
    Node* m_root;
    
    void deleteNodes(Node* current) {
        if (!current) return;
        deleteNodes(current->less);
        deleteNodes(current->greater);
        delete current;
    }
};

#endif // TREEMULTIMAP_INCLUDED
