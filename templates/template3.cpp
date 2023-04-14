#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class my_list {
public:
    struct Node { 
        T data;
        Node* next;
        Node* prev;
        Node () {} 
        Node (T data_) { 
            data = data_;
            next = nullptr;
            prev = nullptr;
        }
    };

    Node* head;
    Node* ass;
    int count;

    my_list() { 
        head = nullptr;
        ass = nullptr;
        count = 0;
    }

    my_list (const vector<T> &v) { 
        if (v.size() == 0) {
            my_list();
        }
        else {
            head = new Node(v[0]);
            ass = new Node();
            ass = head;
            for (int i = 1; i < v.size(); i++) {
                Node *tmp = new Node(v[i]);
                ass->next = tmp;
                tmp->prev = ass;
                ass = tmp;
            }
            count = v.size();
        }
    }

    void push_back(T arg) { 
        Node* cur = new Node(arg);
        if (count == 0) {
            ass = cur;
            head = ass;
            count++;
        }

        else {
            ass->next = cur;
            cur->prev = ass;
            ass = cur;
            count++;
        }
    }

    void push_front(T arg) { 
        Node* cur = new Node(arg);
        if (count == 0) {
            head = cur;
            ass = head;
            count++;
        }

        else {
            head->prev = cur;
            cur->next = head;
            head = cur;
            count++;
        }
    }

    void pop_back() { 
        Node* cur = ass->prev;
        cur->next = nullptr;
        delete ass;
        ass = cur;
        count--;
    }

    void pop_front() { 
        Node* cur = head->next;
        cur->prev = nullptr;
        delete head;
        head = cur;
        count--;
    }

    void print() { 
        if (count == 0) {
            cout << "empty list" << endl;
        }
        else {
            Node *cur = head;
            while (cur != nullptr) {
                cout << cur->data << " -> ";
                cur = cur->next;
            }
            cout << "nullptr" << endl;
        }
    }

    my_list& operator = (const my_list& l) { 
        head = l.head;
        ass = l.ass;
        count = l.count;
        return *this;
    }

    bool operator != (const my_list& l) { 
        bool flag = false;
        if (count == l.count) {
            Node* cur = head;
            Node* curl = l.head;
            for (int i = 0; i < count; i++) {
                if (cur->data != curl->data) {
                    flag = true;
                    break;
                }
                cur = cur->next;
                curl = curl->next;
            }
        } else {
            flag = true;
        }
        return flag;
    }

    bool operator == (const my_list& l) { 
        bool flag = true;
        if (count == l.count) {
            Node* cur = head;
            Node* curl = l.head;
            for (int i = 0; i < count; i++) {
                if (cur->data != curl->data) {
                    flag = false;
                    break;
                }
                cur = cur->next;
                curl = curl->next;
            }
        } else {
            flag = false;
        }
        return flag;
    }
    int list_size() {
        return count;
    }

    class Iterator { 
    public:
        Node* node;
        Iterator() {} 
        Iterator(Node* node_) { 
            node = new Node;
            node = node_;
        }

        my_list::Iterator& operator++() { 
            node = node->next;
            return *this;
        }

        my_list::Iterator operator++(T) { 
            Iterator temp = *this;
            ++*this;
            return temp;
        }

        my_list::Iterator& operator--() {
            node = node->prev;
            return *this;
        }

        my_list::Iterator operator--(T) { 
            Iterator temp = *this;
            --*this;
            return temp;
        }

        bool operator== (const Iterator& x) { 
            Node* temp = x.node;
            if ((node->next == temp->next) && (node->prev == temp->prev) && (node->data == temp->data)) {
                return true;
            }
            return false;
        }

        bool operator!= (const Iterator& x) { 
            Node* temp = x.node;
            if ((node->next == temp->next) && (node->prev == temp->prev) && (node->data == temp->data)) {
                return false;
            }
            return true;
        }

        my_list::Iterator operator+(int x) { 
            for(int i = 0; i < x; i++) {
                if (node->next == nullptr) {
                    return node;
                } else {
                    node = node->next;
                }
            }
            return node;
        }

        my_list::Iterator operator-(int x) { 
            for(int i = 0; i < x; i++) {
                if (node->prev == nullptr) {
                    return node;
                } else {
                    node = node->prev;
                }
            }
            return node;
        }

        T& operator*() {
            return node->data;
        }
    };

    my_list::Iterator insert(my_list<T>::Iterator after, const T& value) { 
        Node* cur;
        cur = new Node(value);
        Node* insert_after = after.node;
        if (insert_after->next == nullptr) {
            insert_after->next = cur;
            cur->prev = insert_after;
            ass = cur;
            count++;
            return Iterator(cur);
        } else if(insert_after->prev == nullptr) {
            insert_after->prev = cur;
            cur->next = insert_after;
            head = cur;
            count++;
            return Iterator(cur);
        } else {
            Node* next_after_inserted = insert_after->next;
            insert_after->next = cur;
            cur->prev = insert_after;
            cur->next = next_after_inserted;
            next_after_inserted->prev = cur;
            count++;
            return Iterator(next_after_inserted);
        }
    }

    my_list::Iterator erase(my_list<T>::Iterator del) { 
        Node* cur = del.node;
        if (cur->next == nullptr) {
            Node* previous = cur->prev;
            previous->next = nullptr;
            ass = previous;
            delete cur;
            count--;
            return Iterator(previous);

        } else if (cur->prev == nullptr) {
            Node* first = cur->next;
            head = first;
            delete cur;
            count--;
            return Iterator(first);

        } else {
            Node* previous = cur->prev;
            Node* add = cur->next;
            previous->next = add;
            add->prev = previous;
            delete cur;
            return Iterator(add);
        }
    }

    my_list::Iterator begin() {
        return Iterator(head);
    }

    my_list::Iterator end() {
        return Iterator(ass);
    }
};


int main() {

    cout << "Check ctor: " << endl;
    vector <int> v = {1, 2 ,4};
    vector <int> w = {};
    my_list<int> test_1(v);
    my_list<int> test_2(w);
    cout << endl;

    cout << "Check output: " << endl;
    test_1.print();
    test_2.print();
    cout << endl;

    cout << "Check size: " << endl;
    cout << test_1.list_size() << endl;
    cout << test_2.list_size() << endl;
    cout << endl;

    cout << "Add elements: " << endl;
    test_1.print();
    test_1.push_back(81);
    test_1.push_front(115);
    test_1.print();
    cout << endl;

    cout << "Check with empty vector: " << endl;
    test_2.print();
    test_2.push_back(1);
    test_2.print();
    cout << endl;

    cout << "Delete elements: " << endl;
    test_1.print();
    test_1.pop_back();
    test_1.pop_front();
    test_1.print();
    cout << endl;

    cout << "Assignment: " << endl;
    vector <int> n = {5,4,3,2,1};
    my_list <int> test(n);
    my_list <int> test_3;
    test_3 = test;
    test.print();
    test_3.print();
    cout << endl;

    cout << "Beginning iterator: " << endl;
    test_3.print();
    cout << *test_3.begin() << endl;
    cout << endl;

    cout << "Finishing iterator: " << endl;
    test_3.print();
    cout << *test_3.end() << endl;
    cout << endl;

    cout << "Iterator adding x = 1: " << endl;
    int x = 1;
    test_3.print();
    cout << *(test_3.begin() + x) << endl;
    cout << endl;

    cout << "Iterator substracting y = 1: " << endl;
    int y = 1;
    test_3.print();
    cout << *(test_3.end() - y) << endl;
    cout << endl;

    cout << "Check on a big shift z = 10: " << endl;
    int z = 10;
    test_3.print();
    cout << *(test_3.begin() + z) << endl;
    cout << endl;

    cout << "Check comparison iterator: " << endl;
    if (test_3 == test_3) cout << "same" << endl;
    if (test_3 != test_2) cout << "different" << endl;
    cout << endl;

    cout << "Adding to the beginning with iterator: " << endl;
    my_list <int>:: Iterator elem1;
    cout << "Was: " << endl;
    test_3.print();
    elem1 = test_3.insert(test_3.begin(),6);
    cout << "Added element: " << endl;
    cout << *elem1 << endl;
    cout << "Now: " << endl;
    test_3.print();
    cout << endl;

    cout << "Adding to the ending with iterator:" << endl;
    my_list <int>::Iterator elem2;
    cout << "Was: " << endl;
    test_3.print();
    elem2 = test_3.insert(test_3.end(), 0);
    cout << "Deleted element: " << endl;
    cout << *elem2 << endl;
    cout << "Now: " << endl;
    test_3.print();
    cout << endl;

    cout << "Deleting from the beginning with iterator: " << endl;
    cout << "Was: " << endl;
    test_3.print();
    cout << "Deleted element: " << endl;
    cout << *test_3.begin() << endl;
    test_3.erase(test_3.begin());
    cout << "Now: " << endl;
    test_3.print();
    cout << endl;

    cout << "Deleting from the end with iterator: " << endl;
    cout << "Was: " << endl;
    test_3.print();
    cout << "Deleted element: " << endl;
    cout << *test_3.end() << endl;
    test_3.erase(test_3.end());
    cout << "Now: " << endl;
    test_3.print();
    cout << endl;

    cout << "Comparison with iterator " << endl;
    if (test_1.begin() == test_1.begin()) cout << "same" << endl;
    if (test_1.begin() != test_2.begin()) cout << "different" << endl;
    cout << endl;

    cout << "Iterator assigment " << endl;
    my_list <int>:: Iterator elem3 = elem2;
    if (elem3 == elem2) cout << "Ok" << endl;
    cout << endl;

    return 0;
}