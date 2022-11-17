#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>


#define YELLOWTIME 6 //The amount of time the yellow light stays on

using namespace std;

class Trafficlight {
private: //Private variable declaration
	int ID, State;
	double greentime;
	
public:
	Trafficlight() { //Default constuctor for the Trafficlight class
		ID = 1;
		State = 1;
		greentime = 0;
	}
	Trafficlight(int id) { //Non-default constuctor for the Trafficlight class
		ID = id;
		State = 1;
		greentime = 0;
	}
	void wait() { //Function used for the time delay in the simulation
		if (State == 3) {
			Sleep(greentime * 1000); //This function pauses the program for a duration of the inputed time in milliseconds, so we mutiply by 1000 for seconds
		}
		else if(State == 2){
			Sleep(YELLOWTIME * 1000);
		}
	}
	int getstate() {
		return State;
	}
	void setgreentime(double time) { //Used to set the green time 
		greentime = time;
	}
	void printLightInfo() { //Prints all the information of a Trafficlight object
		cout << "ID: " << ID << endl;
		if (State != 0) {
			cout << "State: Active" << endl;
		}
		else {
			cout << "State: Inactive" << endl;
		}
		cout << "Green light time: " << greentime << " seconds" << endl;
	}
	void DisplayLightState(int i) { //Used to display the light state in the simulation
		if (State == 1) {
			cout << "T" << i << ": red" << endl;
		}
		else if (State == 2) {
			cout << "T" << i << ": yellow" << endl;
		}
		else if (State == 3) {
			cout << "T" << i << ": green" << endl;
		}
		else if (State == 0) {
			cout << "T" << i << ": Inactive" << endl;
		}
	}
	void setoff() { //Used to set the state to off
		State = 0;
	}
	void setred() { //Used to set the state to red
		State = 1;
	}
	void setyellow() { //Used to set the state to yellow
		State = 2;
	}
	void setgreen() { //Used to set the state to green
		State = 3;
	}

};
