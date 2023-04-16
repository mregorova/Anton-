#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <class animal> animals;

class food {
public:
    int kkal;
    string type;
    food() {
        kkal = 0;
    }

    food(int kkal_) {
        kkal = kkal_;
    }
};

class animal {
public:
    int age;
    string name;
    int satiety;
    int max;
    string type;

    animal() {
        age = 0;
        name = "";
        satiety = 50;
        max = 100;
    }

    animal(int age_, string name_, int satiety_, int max_) {
        age = age_;
        name = name_;
        satiety = satiety_;
        max = max_;
    }

    void run(int time, vector <class animal> &animals) {
        if (satiety > time) {
            satiety -= time;
        }

        else {
            cout << type << " " << name << " has died after running" << endl;
            for (int i = 0; i < animals.size(); i++) {
                if(animals[i].name == name){
                    animals.erase(animals.begin() + i);
                }
            }
        }
    }

    void eat(food &b) {
        if ((type == "cat" && b.type == "meat") || (type == "parrot" && b.type == "fruit")) {
            if (max - satiety >= b.kkal) {
                satiety += b.kkal;
            }

            else {
                cout << type << " " << name << " has died after overeating" << endl;
                for (int i = 0; i < animals.size(); i++){
                    if(animals[i].name == name){
                        animals.erase(animals.begin() + i);
                    }
                }
            }
        }

        else {
            cout << "You can't eat this kind of food" << endl;
        }
    }

    void have_sex(animal &a, vector <class animal> &animals) {
        if (a.type != type) {
            if (a.type == "cat") {
                cout << a.type << " " << a.name << " has eaten " << type << " " << name << endl;
                for (int i = 0; i < animals.size(); i++) {
                    if(animals[i].name == name){
                        animals.erase(animals.begin() + i);
                    }
                }
            }

            else {
                cout << type << " " << name << " has eaten " << a.type << " " << a.name << endl;
                for (int i = 0; i < animals.size(); i++){
                    if(animals[i].name == a.name){
                        animals.erase(animals.begin() + i);
                    }
                }
            }
        } 

        else {
            if (a.name == name) {
                cout << "You can't do it" << endl;
            }

            else{
                cout << type << " " << name << " and " << a.type << " " << a.name << " satisfied" << endl;
            }
        }
    }
};

class cat: public animal {
public:
    cat() : animal() {
        type = "cat";
    }

    cat(int age_, string name_, int satiety_, int max_) : animal(age_, name_, satiety_, max_) {
        type = "cat";
    }
};

class parrot: public animal {
public:
    string voice1;
    parrot() : animal() {
        type = "parrot";
        voice1 = "";
    }

    parrot(int age_, string name_, int satiety_, int max_, string voice1_) : animal(age_, name_, satiety_, max_) {
        type = "parrot";
        voice1 = voice1_;
    }

    void voice() {
        cout << voice1 << endl;
    }
};

class meat : public food {
public:
    int protein;
    meat() : food() {
        type = "meat";
        protein = 0;
    }

    meat(int kkal_, int protein_) : food(kkal_) {
        type = "meat";
        protein = protein_;
    }
};

class fruit : public food {
public:
    fruit() : food() {
        type = "fruit";
    }
    
    fruit(int kkal_) : food(kkal_) {
        type = "fruit";
    }
};

int main() {
    cat A(2, "Cat1", 10, 20);
    cat B(3, "Cat2", 5, 50);
    parrot C(4, "Kesha1", 3, 40, "a");
    parrot D(5, "Kesha2", 7, 15, "b");

    animals.push_back(A);
    animals.push_back(B);
    animals.push_back(C);
    animals.push_back(D);

    C.voice();
    A.have_sex(A, animals);
    A.have_sex(B, animals);
    A.have_sex(C, animals);

    meat beef(25, 5);
    fruit apple (5);

    A.eat(beef);
    B.eat(beef);
    D.eat(beef);
    D.run(15, animals);

    for (auto i: animals){
        cout << i.name << ' ' << endl;
    }

    return 0;
}