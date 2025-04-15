#include <iostream>
#include "memory.h"
#include "controller.h"
#include "constants.h"
#include <thread>
#include <chrono>
using namespace std;

int main() {
	Goal goal(Point(-445, 855, -85), -90);
	Controller controller(goal);
	//controller.testMem();
	//return 0;
	
	this_thread::sleep_for(chrono::seconds(1));

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