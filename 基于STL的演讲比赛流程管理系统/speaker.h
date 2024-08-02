#pragma once
#include <iostream>
using namespace std;

class Speaker {
public:
	Speaker();

	Speaker(string& name);

	string getName();

	double getScore(int index);

	void setScore(double socre, int index);

	~Speaker();
private:
	string name;
	double scores[2];
};