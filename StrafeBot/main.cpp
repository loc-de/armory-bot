#include <iostream>
#include "memory.h"
#include "controller.h"
#include "constants.h"
#include <thread>
#include <chrono>
using namespace std;

const string Data::graph_path = "graph.txt";

void test() {

}

int main() {

	//test();
	//return 0;

	this_thread::sleep_for(chrono::milliseconds(5000));

	Goal goal(Point(-360, 855, -85, vars::GOAL_ID), -90);
	Controller controller(goal);

	//controller.testMem();
	//return 0;

	thread rot_thread(&Controller::controlRot, &controller);
	controller.run();

	rot_thread.join();

	return 0;
}