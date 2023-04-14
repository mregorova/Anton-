#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>

using namespace std;

template <typename T>
bool f1 (vector <T> v, T x) {
    bool f = false;
    for (auto i : v) {
        if (i == x) f = true;
    }

    return f;
}

template <typename T1, typename T2>
bool f1 (map <T1, T2> m, T2 x) {
    bool f = false;
    for (auto i : m) {
        if (i.second == x) f = true;
    }

    return f;
}

template<typename T1>
bool f2 (vector <T1> v, T1 x) {
    int n = 0;
    for (auto i : v) {
        if (i == x) n++;
    }

    return (n % 2 == 0);
}

template <typename T1, typename T2>
bool f2 (map <T1, T2> m, T2 x) {
    int n = 0;
    for (auto i : m) {
        if (i.second == x) n++;
    }

    return (n % 2 == 0);
}

class checker {
public:
    int counter = 0;

    template <class foo, typename T1, typename T2>
    void check (foo f, vector<T1> v, T2 x) {
        for (auto i : v) {
            bool a = f(i, x);
            if (a) counter++;
        }
    }
    ~checker() {
        cout << counter << endl;
    }
};

int main() {
    checker a;
    vector <vector <int>> vv = {{'a', 'b', 'c'}, {'k', 'l', 'd'}, {'x', 'y', 'z'}};
    vector <map <char, int>> mm = {{{'1', 2}, {'3', 4}}, {{'5', 6}, {'7', 8}}, {{'9', 10}, {'1', 12}}};

    a.check(f1<int>, vv, 'a');
    a.check(f1<char, int>, mm, 1);
    a.check(f2<int>, vv, 'd');
    a.check(f2<char, int>, mm, 1);
}