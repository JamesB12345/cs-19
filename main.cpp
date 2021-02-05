


#ifndef LINKED_LIST_RAW_POINTERS_ITERABLE_H_
#define LINKED_LIST_RAW_POINTERS_ITERABLE_H_
#include <initializer_list>
#include <iostream>

namespace cs19 {

template <typename T>

class LinkedList {

    struct Node;

public:

LinkedList(std::initializer_list init_list) {

        this->operator = (init_list);

    }

    ~LinkedList() {

        this->clear();

    }

    LinkedList() {

        this->head_ = nullptr;

        this->tail_ = nullptr;

        this->size_ = 0;

    }

    LinkedList(const LinkedList &another) {

        this->head_ = another.head_;

        this->tail_ = another.tail_;

        this->size_ = another.size_;

    }

    std::size_t size() const {

        return this->size_;

    }

    T& back() const {

        return this->tail_->data;

    }

    void unique() {

        if (this->head_ == nullptr) {

            return;

        } else {

            Node *curr = this->head_;

            Node *aux;

            while (curr->next != nullptr) {

                if (curr->data == curr->next->data) {

                    aux = curr->next->next;

                    delete curr->next;

                    curr->next = aux;

                } else {

                    curr = curr->next;

                }

            }

        }

        return;

    }

    bool empty() const {

        if(this->head_ == nullptr) {

            return true;

        } else {

            return false;

        }

    }

    T& front()const {

        return this->head_->data;

    }

    void remove(const T &val) {

        Node* temp = nullptr;

        temp = this->head_;

        if (this->head_ == this->tail_) {

            if (this->head_->data != val) {

                return;

            }

            this->head_ = nullptr;

            this->tail_ = nullptr;

            delete temp;

            return;

        }

        if (this->head_->data == val) {

            this->head_ = this->head_->next;

            this->head_->prev = nullptr;

            delete temp;

            return;

        } else if (this->tail_->data == val) {

            temp = this->tail_;

            this->tail_ = this->tail_->prev;

            this->tail_->next = nullptr;

            delete temp;

            return;

        }

        while (temp->data != val) {

            temp = temp->next;

            if (temp == nullptr) {

                return;

            }

        }

        temp->next->prev = temp->prev;

        temp->prev->next = temp->next;

        delete temp;

    }

    void reverse() {

        Node *temp = nullptr;

        Node *current = this->head_;

        while(current != nullptr) {

            temp = current->prev;

            current->prev = current->next;

            current->next = temp;

            current = current->prev;

        }

        if(temp != nullptr)

            this->head_ = temp->prev;

    }

    void pop_front() {

        if(this->head_ == nullptr) {

        } else {

            Node* cur = this->head_;

            if (this->head_ == this->tail_) {

                this->head_ = nullptr;

                this->tail_ = nullptr;

            } else {

                this->head_ = this->head_->next;

                this->head_->prev = NULL;

            }

            delete cur;

            this->size_--;

        }

    }

    bool operator!= (const LinkedList &another) {

        return !(*this == another);

    }

    LinkedList& operator = (const LinkedList &another) {

        if(this->head_ == another.head_) {

            return *this;

        }

        if(this->head_) {

            this->clear();

        }

        Node* pNode = another.head_;

        Node* pCurNode = nullptr;

        Node* pPrevNode = nullptr;

        if(pNode) {

            pCurNode = new Node(*pNode);

            this->head_ = pCurNode;

            pNode = pNode->next;

        }

        while(pNode) {

            pPrevNode = pCurNode;

            pCurNode = new Node(*pNode);

            pCurNode->prev = pPrevNode;

            pPrevNode->next = pCurNode;

            pNode = pNode->next;

        }

        this->tail_ = pCurNode;

        return *this;

    }

    void clear() {

        Node* pToDelete;

        Node* pCurNode = this->head_;

        while (pCurNode) {

            pToDelete = pCurNode;

            pCurNode = pCurNode->next;

            delete pToDelete;

        }

        this->head_ = nullptr;

        this->tail_ = nullptr;

    }

    bool operator== (const LinkedList &another) {

        int i = 0;

        Node* cur = this->head_;

        Node* cur2 = another.head_;

        if(this->size_ != another.size_) {

            return false;

        }

        while(i < 5) {

            i++;

            if (cur->data != cur2->data) {

                return false;

            }

            cur = cur->next;

            cur2 = cur2->next;

        }

        return true;

    }

    void resize(std::size_t n, const T &fill_value ) {

        if(this->size() < n) {

            while(this->size() < n) {

                this->push_back(fill_value);

            }

        } else {

            while(this->size() > n) {

                this->pop_back();

            }

        }

    }

    void pop_back() {

        if (this->head_ != nullptr) {

            Node* temp = this->head_;

            Node* lastNode = nullptr;

            if (this->head_->next == nullptr) {

                this->head_ = nullptr;

            } else {

                while (temp->next->next != nullptr) {

                    temp = temp->next;

                    lastNode = temp->next;

                }

                temp->next = nullptr;

                delete lastNode;

            }

            delete temp;

            --this->size_;

        }

    }

    void push_back(const T& val) {

        Node* new_node = new Node{val};

        if (this->size_ == 0) { this->head_ = this->tail_ = new_node;

        } else {

            this->tail_->next = new_node;

            new_node->prev = this->tail_;

            this->tail_ = new_node;

        }

        ++this->size_;

    }

    void push_front(const T& val) {

        Node* new_node = new Node{val};

        if (this->size_ == 0) {

            this->head_ = this->tail_ = new_node;

        } else {

            new_node->next = this->head_;

            this->head_->prev = new_node;

            this->head_ = new_node;

        }

        ++this->size_;

    }

    LinkedList& operator=(std::initializer_list init_list) {

        this->size_ = 0;

        for (auto&& val : init_list)

            this->push_back(val);

        return *this;

    }

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {

        out << '[';

        for (Node* cur = list.head_; cur; cur = cur->next) {

            out << cur->data;

            if (cur->next)

                out << ", ";

        }

        out << ']';

        return out;

    }

    template

    LinkedList(InputIterator first, InputIterator last) {

        for (; first != last; ++first) this->push_back(*first);

    }

    class Iterator {

    public:

        using iterator_category = std::bidirectional_iterator_tag;

        using value_type = T;

        using difference_type = int;

        using pointer = T*;

        using reference = T&;

        Iterator() {

            this->head_ = nullptr;

        }

        Iterator(Node* x) {

            this->head_ = x;

        }

        Iterator(const Iterator& other) {

        }

        ~Iterator() {

        }

        Iterator& operator= (const Iterator& that) {

            this->head_ = that->head_;

            return *this;

        }

        Iterator& operator++() {

            if ( this->head_ == nullptr ) {

                return *this;

            }

            Iterator operator++ (int) {

                Iterator tmp(*this);

                this->operator++();

                return tmp;

            }

            Iterator& operator-- () {

                if (this->head_ == nullptr) {

                    return *this;

                }

                this->head_ = this->head_->prev;

                return *this;

            }

            Iterator operator-- (int) {

                Iterator tmp(*this);

                this->operator--();

                return tmp;

            }

            bool operator!=(Iterator that) const { return !(this->operator==(that)); }

            bool operator==(Iterator that) const {

                return this->head_ == that.head_;

            }

            T& operator*() const {

                return this->head_->data;

            }

            Iterator* operator->() const { return const_cast(this);}

            private:

            Node*head_ = nullptr;

        };

        Iterator begin() {

            return Iterator(this->head_);

        }

        Iterator end() {

            return Iterator(this->tail_->next);

        }

    private:

        struct Node {

            T data;

            Node* next = nullptr;

            Node* prev = nullptr;

        };

        Node* head_ = nullptr;

        Node* tail_ = nullptr;

        std::size_t size_ = 0;

    };

} // namespace cs19

#endif // LINKED_LIST_RAW_POINTERS_ITERABLE_H_

