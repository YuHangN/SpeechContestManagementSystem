#include "speaker.h"

Speaker::Speaker() {};

Speaker::Speaker(string& name) {
	this->name = name;
	this->scores[0] = 0;
	this->scores[1] = 0;
}

string Speaker::getName() {
	return this->name;
}

double Speaker::getScore(int index) {
	return this->scores[index - 1];
}

void Speaker::setScore(double score, int index) {
	this->scores[index - 1] = score;
}

Speaker::~Speaker() {

}