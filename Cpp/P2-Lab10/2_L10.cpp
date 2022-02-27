#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <ctime>


enum State {
	D,
	W,
	Z
};

class Process
{
public:
	int id;
	int stepsToComplete;
	State state;

	Process(int id, int stepsToComplete);
	void solve();
};

Process::Process(int id, int stepsToComplete)
{
	this->id = id;
	this->state = W;
	this->stepsToComplete = stepsToComplete;
}

void Process::solve() {
	state = D;
	if (this->state == D) {
		stepsToComplete--;
		if (stepsToComplete <= 0) this->state = Z;
		else state = W;
	}
}


class History
{
public:
	int rounds=0;
	std::string cycles;
	std::vector<std::string> summary;
};



class Manager
{
public:
	int lastProcessId;
	std::vector<Process> list;
	std::queue<Process> q;
	History history;

	Manager(int processes);
};

Manager::Manager(int processes)
{
	for (int i = 1; i < processes + 1; i++) {
		Process p = *new Process(i, rand() % 20 + 1);
		list.push_back(p);
		q.push(p);
	}


	int counter = 0;
	while (!q.empty()) {
		Process p = q.front();

		p.solve();

		if (p.state != Z) {
			q.pop();
			q.push(p);
		}
		else q.pop();

		for (auto process : list) {
			if (p.id == process.id) {
				history.cycles.push_back('D');
			}
			else {
				switch (process.state)
				{
				case W:
					history.cycles.push_back('W');
					break;
				case Z:
					history.cycles.push_back('Z');
					break;
				default:
					break;
				}

			}
		}


		counter++;
		if (counter == processes + 1) {
			history.rounds++;
			std::cout << history.rounds <<": " << history.cycles << std::endl;
			history.cycles.clear();
			counter = 0;
		}
	}
}


int main()
{
	srand(time(NULL));
	Manager p(5);
}

