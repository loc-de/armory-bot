#include <iostream>
#include "memory.h"
#include "controller.h"
#include "constants.h"
#include <thread>
#include <chrono>
#include <Windows.h>
#include <thread>
using namespace std;

const string Data::graph_path = "graph.txt";

void test() {
	Sleep(5000);
	Mouse m;
	m.smoothMove(int(90 / 0.055), 0);
}

int main() {

	//test();
	//return 0;

	Sleep(7000);

	Goal goal(Point(-360, 855, -85, vars::GOAL_ID), -90);
	Controller controller(goal);

	//controller.testMem();
	//return 0;

	thread rot_thread(&Controller::controlRot, &controller);
	controller.run();
	//Sleep(10000);

	rot_thread.join();

	return 0;
}