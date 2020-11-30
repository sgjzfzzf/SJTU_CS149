#include<iostream>
#include<queue>
using namespace std;

class Vehicle {
private:
	int arrivingTime;
public:
	Vehicle(int);
	int waitingTime(int);
};

Vehicle::Vehicle(int at) :arrivingTime(at) {}

int Vehicle::waitingTime(int currentTime) {
	return currentTime - arrivingTime;
}

class TimeSimulator {
private:
	int carArrivingTime;
	int truckArrivingTime;
	int simulateTotalTime;
	int carsNum;
	int trucksNum;
	const int shipArrivingTime = 10;
public:
	TimeSimulator(int, int, int);
	void averageWaitingTime(double&, double&);
};

TimeSimulator::TimeSimulator(int cAT, int tAT, int sTT) :carArrivingTime(cAT), truckArrivingTime(tAT), simulateTotalTime(sTT) {
	carsNum = trucksNum = 0;
}

void TimeSimulator::averageWaitingTime(double& carWaitingAverageTime, double& truckWaitingAverageTime) {
	queue<Vehicle> carQueue, truckQueue;
	int carWaitingTotalTime = 0, truckWaitingTotalTime = 0, currentTime;
	for (currentTime = 0; currentTime <= simulateTotalTime; ++currentTime) {
		if (currentTime % carArrivingTime == 0) {
			carQueue.push(Vehicle(currentTime));
			++carsNum;
		}
		if (currentTime % truckArrivingTime == 0) {
			truckQueue.push(Vehicle(currentTime));
			++trucksNum;
		}
		if (currentTime % shipArrivingTime == 0) {
			for (int i = 0; i < 10; ++i) {
				if (i < 8 && !carQueue.empty()) {
					carWaitingTotalTime += carQueue.front().waitingTime(currentTime);
					carQueue.pop();
				}
				else if (!truckQueue.empty()) {
					truckWaitingTotalTime += truckQueue.front().waitingTime(currentTime);
					truckQueue.pop();
				}
			}
		}
	}
	//清出两队列中剩下车辆，并将它们已等待的时间添加到总时长中去
	while (!carQueue.empty()) {
		carWaitingTotalTime += carQueue.front().waitingTime(currentTime);
		carQueue.pop();
	}
	while (!truckQueue.empty()) {
		truckWaitingTotalTime += truckQueue.front().waitingTime(currentTime);
		truckQueue.pop();
	}
	carWaitingAverageTime = static_cast<double>(carWaitingTotalTime) / carsNum, truckWaitingAverageTime = static_cast<double>(truckWaitingTotalTime) / trucksNum;
}

int main() {
	int totalTime, carArrivingTime, truckArrivingTime;
	double carAverageWaitingTime, truckAverageWaitingTime;
	cout << "请输入希望模拟的时长:"; cin >> totalTime;
	cout << "请输入希望模拟的客车平均到达间隔时长:"; cin >> carArrivingTime;
	cout << "请输入希望模拟的卡车平均到达间隔时长:"; cin >> truckArrivingTime;
	TimeSimulator simulator(carArrivingTime, truckArrivingTime, totalTime);
	simulator.averageWaitingTime(carAverageWaitingTime, truckAverageWaitingTime);
	cout << "汽车等待平均时长:" << carAverageWaitingTime << ",卡车平均等待时长:" << truckAverageWaitingTime << endl;
	return 0;
}