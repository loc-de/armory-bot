#include <iostream>
#include "controller.h"
#include <thread>
#include <chrono>
#include "config.h"
using namespace std;

int main() {
	Config::get().load("config.json");
	Goal goal(Point(-445, 855, -85), -90);
	Controller controller(goal);
	
	string flag;
	cout << "test mem? (y/n): ";
	cin >> flag;
	if (flag == "y") {
		controller.testMem();
		return 0;
	}

	controller.connectToServer();

	string s;
	while (s != "y") {
		cout << "on server? (y/n): ";
		cin >> s;
	}
	controller.activateWindow();
	this_thread::sleep_for(chrono::seconds(3));
	controller.run();

	return 0;
}