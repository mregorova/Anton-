#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include <exception>
#include <stdexcept>

using namespace std;

class student {

public:
	int get_age() return age;
	
	string get_name() return name;
	
	double get_grage() return grade;
	
	void set_student(string name_, int age_, double grade_)	{
		if ((age_ <= 50 ) && (age_ > 0) && (grade > 2)) {
			age = age_;
			grade = grade_;
			name = name_;
		}
	}

	void botat() {
		cout << name << " botaet" << " ";
		grade++;
	}

	student() {
		age = 19;
		name = "Mary";
		grade = 3.0;
	}

	~student() cout << "sdoh" << endl;


private:
	string name;
	int age;
	double grade;

};

int main()
{
	vector<student> group(3);
	double sum = 0;

	group[0].set_student("Mary", 19, 6);
	group[1].set_student("Vitek", 18, 3);
	group[2].set_student("Sanya", 45, 9);

	for (int i = 0; i < 3; i++)	cout << group[i].get_name() << " " << group[i].get_age() << " " <<group[i].get_ball()<< " ";
	cout << endl;

	group[0].botat();
	cout << group[0].get_ball() << endl;

	group[1].botat();
	cout << group[1].get_ball() << endl;

	for (int i = 0; i < 3; i++) sum = sum + group[i].get_ball();
	cout << sum/3 << endl;

	return 0;
}