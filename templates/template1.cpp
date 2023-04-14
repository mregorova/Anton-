#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

template <typename T1, typename T2>
ostream& operator<< (ostream& os, pair <T1,T2> &v) {
    return os << '(' << v.first << ' ' << v.second << ')';
}

template <typename T>
string to_string(T &v, char a) {
    stringstream ss;
    bool flag = false;
    for (auto i : v) {
        if (!flag) {
            ss << i;
            flag = true;
        }

        else {
            ss << a << i;
        }
    }
    return ss.str();
}

template <typename T>
ostream& operator<< (ostream& os, vector <T> &v) {
    return os << to_string(v, ' ');
}

template <typename T1, typename T2>
ostream& operator<< (ostream& os, map <T1,T2> &v) {
    return os <<"{"<< to_string(v, ';')<<"}"<<endl;
}

int main() {
    ofstream fout("/home/mregorova/Documents/skubach/templates/res.txt" , ios::in);
    pair <int, int> a = {3, 2};
    map <int, int> b = {{1,5}, {2,7}, {3,6}, {4,3}, {5,4}, {6,6}};
    vector <int> v = {1, 2, 3, 4, 5};

    fout << a << endl;
    fout << b << endl;
    fout << v << endl;

    return 0;
}
