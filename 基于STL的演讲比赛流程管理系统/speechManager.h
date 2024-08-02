#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <numeric>
#include <iomanip>
#include <fstream>
using namespace std;

class SpeechManager {
private:
	vector<int> v1;
	vector<int> v2;
	vector<int> champions;
	map<int, Speaker> speakers;
	int index;
	map<int, vector<string>> record;
	bool isEmpty;

public:
	
	SpeechManager();

	void showMenu();

	void exitSystem();

	void init_speech();

	void createSpeakers();

	void startSpeech();

	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	void loadRecord();

	void showRecord();

	void clearRecord();

	~SpeechManager();

};