#include "speechManager.h"

void printList(vector<int>& list) {
	for (int i = 0; i < list.size(); i++) {
		cout << list[i] << " ";
	}
	cout << endl;
}

SpeechManager::SpeechManager() {
	this->init_speech();
	this->createSpeakers();
}

void SpeechManager::showMenu() {
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem() {
	cout << "��лʹ��" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::init_speech() {
	this->champions.clear();
	this->speakers.clear();
	this->v1.clear();
	this->v2.clear();
	this->index = 1;
	this->record.clear();
}

void SpeechManager::createSpeakers() {
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp(name);
		this->v1.push_back(i + 10001);
		this->speakers.insert({ i + 10001, sp });
	}
}

void SpeechManager::startSpeech() {
	// Draw
	this->speechDraw();
	// ��һ��
	this->speechContest();

	this->showScore();

	this->index++;

	this->speechDraw();

	this->speechContest();

	this->showScore();

	this->saveRecord();

	cout << "���������ϣ�" << endl;

	this->init_speech();

	this->createSpeakers();

	this->loadRecord();

	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	system("cls");
	cout << "�� << " << this->index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->index == 1) {
		random_shuffle(v1.begin(), v1.end());

		printList(v1);
	}
	else {
		vector<int> list = this->v2;
		random_shuffle(v2.begin(), v2.end());

		printList(v2);
	}

	cout << "---------------------" << endl;
	system("pause");
	system("cls");
	cout << endl;	
}

void SpeechManager::speechContest() {
	srand((unsigned int)time(nullptr));
	cout << "------------- ��" << this->index << "����ʽ������ʼ��------------- " << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;

	vector<int> v_Src;
	if (this->index == 1) {
		v_Src = this->v1;
	}
	else {
		v_Src = this->v2;
	}
	for (int i = 0; i < v_Src.size(); i++) {
		num++;

		deque<double>d;
		// Get all the scores from judgers.
		for (int i = 0; i < 10; i++) {
			// rand()�����һ���������
			double score = (rand() % 401 + 600) / 10.f;
			// cout << score << " ";
			d.push_back(score);
		}
		// Sort the scores from judgers.
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();
		// Get the average score.
		// accumulate����һ��������Ķ�����ӣ������������ǳ�ʼֵ��
		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();

		this->speakers[v_Src[i]].setScore(avg, index);

		groupScore.insert({ avg, v_Src[i] });

		// ����Ѿ����������6�������ߣ�Ҳ����ζ��һ�顣
		if (num % 6 == 0) {

			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (auto it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second << " ������ " << this->speakers[(*it).second].getName() << " �ɼ��� " << fixed << setprecision(2) << this->speakers[(*it).second].getScore(index) << endl;
			}

			int count = 0;
			for (auto it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (this->index == 1)
				{
					v2.push_back((*it).second);
				}
				else {
					champions.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "------------- ��" << this->index << "�ֱ������  ------------- " << endl;
	system("pause");
	system("cls");
}

void SpeechManager::showScore() {
	if (this->index == 1) {
		cout << "---------��" << this->index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
		sort(v2.begin(), v2.end(), [&](int a, int b) {
			return this->speakers[a].getScore(index) >= this->speakers[b].getScore(index);
			});
		for (auto num : this->v2) {
			cout << "ѡ�ֱ�ţ�" << num << " ������ " << this->speakers[num].getName() << " �÷֣� " << this->speakers[num].getScore(index) << endl;
		}
	}
	else {
		cout << "---------�ý�ѡ����Ϣ���£�-----------" << endl;
		for (auto num : this->champions) {
			cout << "ѡ�ֱ�ţ�" << num << " ������ " << this->speakers[num].getName() << " �÷֣� " << this->speakers[num].getScore(index) << endl;
		}
	}
	cout << endl;

	system("pause");
	system("cls");
}

void SpeechManager::saveRecord() {
	fstream iofs;
	// д�ļ�����ÿ�δ򿪲����
	iofs.open("speech.csv", ios::out | ios::app);
	for (int i = 0; i < this->champions.size(); i++) {
		iofs << this->champions[i] << ","
			<< fixed << setprecision(2) << speakers[this->champions[i]].getScore(index) << ",";
	}
	iofs << endl;
	iofs.close();
	cout << "��¼�Ѿ�����" << endl;
	this->isEmpty = false;
}

void SpeechManager::loadRecord() {
	fstream iofs;
	iofs.open("speech.csv", ios::in);

	if (!iofs.is_open()) {
		this->isEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		iofs.close();
		return;
	}
	if (iofs.peek() == fstream::traits_type::eof()) {
		cout << "��¼Ϊ�գ�" << endl;
		this->isEmpty = true;
		iofs.close();
		return;
	}

	this->isEmpty = false;
	string record;
	int index = 0;

	while (getline(iofs, record)) {
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true) {
			pos = record.find(",", start);
			if (pos == -1) {
				break;
			}
			string temp = record.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->record.insert({ index, v });
		index++;
	}
	iofs.close();
}

void SpeechManager::showRecord() {
	this->loadRecord();
	if (this->isEmpty) {
		cout << "û�����������Ϣ��" << endl;
	}
	for (int i = 0; i < this->record.size(); i++)
	{
		cout << "��" << i + 1 << "�� " <<
			"�ھ���ţ�" << this->record[i][0] << " �÷֣�" << this->record[i][1] << " "
			"�Ǿ���ţ�" << this->record[i][2] << " �÷֣�" << this->record[i][3] << " "
			"������ţ�" << this->record[i][4] << " �÷֣�" << this->record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int choice = 0;
	cin >> choice;

	if (choice == 1) {
		/*ofstream ofs;
		ofs.open("speech.csv", ios::trunc);*/

		fstream iofs;
		iofs.open("speech.csv", ios::trunc);

		iofs.close();

		//��ȡ�����¼
		this->record.clear();
		this->isEmpty = true;

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {

}