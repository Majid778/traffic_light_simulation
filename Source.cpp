#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include "Intersection.h"



using namespace std;

int main() {
	Intersection I1;
	for (int i = 1;i < MAXLIGHTS;i++) { //For loop to declare all the objects.
		I1.AddLight(i);
	}
	I1.run();
	return 0;
}