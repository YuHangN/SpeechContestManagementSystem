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
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem() {
	cout << "感谢使用" << endl;
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
		string name = "选手";
		name += nameSeed[i];

		Speaker sp(name);
		this->v1.push_back(i + 10001);
		this->speakers.insert({ i + 10001, sp });
	}
}

void SpeechManager::startSpeech() {
	// Draw
	this->speechDraw();
	// 第一轮
	this->speechContest();

	this->showScore();

	this->index++;

	this->speechDraw();

	this->speechContest();

	this->showScore();

	this->saveRecord();

	cout << "本届比赛完毕！" << endl;

	this->init_speech();

	this->createSpeakers();

	this->loadRecord();

	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	system("cls");
	cout << "第 << " << this->index << " >> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

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
	cout << "------------- 第" << this->index << "轮正式比赛开始：------------- " << endl;
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
			// rand()即获得一个随机数。
			double score = (rand() % 401 + 600) / 10.f;
			// cout << score << " ";
			d.push_back(score);
		}
		// Sort the scores from judgers.
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();
		// Get the average score.
		// accumulate即将一个容器里的东西相加，第三个参数是初始值。
		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();

		this->speakers[v_Src[i]].setScore(avg, index);

		groupScore.insert({ avg, v_Src[i] });

		// 如果已经往里插入了6个参赛者，也就意味着一组。
		if (num % 6 == 0) {

			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (auto it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号: " << it->second << " 姓名： " << this->speakers[(*it).second].getName() << " 成绩： " << fixed << setprecision(2) << this->speakers[(*it).second].getScore(index) << endl;
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
	cout << "------------- 第" << this->index << "轮比赛完毕  ------------- " << endl;
	system("pause");
	system("cls");
}

void SpeechManager::showScore() {
	if (this->index == 1) {
		cout << "---------第" << this->index << "轮晋级选手信息如下：-----------" << endl;
		sort(v2.begin(), v2.end(), [&](int a, int b) {
			return this->speakers[a].getScore(index) >= this->speakers[b].getScore(index);
			});
		for (auto num : this->v2) {
			cout << "选手编号：" << num << " 姓名： " << this->speakers[num].getName() << " 得分： " << this->speakers[num].getScore(index) << endl;
		}
	}
	else {
		cout << "---------得奖选手信息如下：-----------" << endl;
		for (auto num : this->champions) {
			cout << "选手编号：" << num << " 姓名： " << this->speakers[num].getName() << " 得分： " << this->speakers[num].getScore(index) << endl;
		}
	}
	cout << endl;

	system("pause");
	system("cls");
}

void SpeechManager::saveRecord() {
	fstream iofs;
	// 写文件并且每次打开不清空
	iofs.open("speech.csv", ios::out | ios::app);
	for (int i = 0; i < this->champions.size(); i++) {
		iofs << this->champions[i] << ","
			<< fixed << setprecision(2) << speakers[this->champions[i]].getScore(index) << ",";
	}
	iofs << endl;
	iofs.close();
	cout << "记录已经保存" << endl;
	this->isEmpty = false;
}

void SpeechManager::loadRecord() {
	fstream iofs;
	iofs.open("speech.csv", ios::in);

	if (!iofs.is_open()) {
		this->isEmpty = true;
		cout << "文件不存在！" << endl;
		iofs.close();
		return;
	}
	if (iofs.peek() == fstream::traits_type::eof()) {
		cout << "记录为空！" << endl;
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
		cout << "没有往届比赛信息！" << endl;
	}
	for (int i = 0; i < this->record.size(); i++)
	{
		cout << "第" << i + 1 << "届 " <<
			"冠军编号：" << this->record[i][0] << " 得分：" << this->record[i][1] << " "
			"亚军编号：" << this->record[i][2] << " 得分：" << this->record[i][3] << " "
			"季军编号：" << this->record[i][4] << " 得分：" << this->record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int choice = 0;
	cin >> choice;

	if (choice == 1) {
		/*ofstream ofs;
		ofs.open("speech.csv", ios::trunc);*/

		fstream iofs;
		iofs.open("speech.csv", ios::trunc);

		iofs.close();

		//获取往届记录
		this->record.clear();
		this->isEmpty = true;

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {

}