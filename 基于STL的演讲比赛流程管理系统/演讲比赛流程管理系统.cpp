#include <iostream>
using namespace std;
#include "speechManager.h"


int main() {
	SpeechManager sm;
	
	int choice;
	while (true) {
		sm.showMenu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£º " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			sm.startSpeech();	
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
		default:
			system("cls");
			break;
		}
	}
		 
	system("pause");
	return 0;
}