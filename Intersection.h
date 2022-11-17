#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include "Trafficlight.h"

#define MAXLIGHTS 12 //The max possible amount of lights in an intersection
#define CURRENTLIGHTS 4 //The amount of trafficlights used in the current simulation
#define REFRESHTIME 86400 //The time interval that the simulation updates the green light times (24hrs = 86400s)
using namespace std;


class Intersection {
private: //Private variable declaration
	double Totalflow = 0;  //The total flow rate of cars in the intersection
	double Cycle_length = 0; //The total amount of time a loop through the intersection takes
	double Q[MAXLIGHTS]; //The flow rate of each traffic light
	int NumOfTrafficlights; //Variable to keep track of the number of traffic lights
	int currentlights= CURRENTLIGHTS +1;
	Trafficlight lightarray[MAXLIGHTS]; //Array of Trafficlight objects
public:
	Intersection() { //Default constuctor for the Intersection class
		NumOfTrafficlights = 0;
		Q[MAXLIGHTS - 1] = { 0 };
		Cycle_length = 0;
		lightarray[MAXLIGHTS - 1] = { 0 };
	}
	void printIntersectionInfo() {
		cout <<"Number of traffic lights: "<< NumOfTrafficlights << endl;
		cout <<"Cycle length: "<<Cycle_length << endl;
		cout << "Total flow: " << Totalflow << endl;
	}
	void AddLight(int i) { //Used too add a Trafficlight object to the lightarray array
		lightarray[i] = Trafficlight(i);
		NumOfTrafficlights++;
	}
	void DropLight(int ID) { //Used too remove a Trafficlight object to the lightarray array
		
		for (int j = ID; j < MAXLIGHTS;j++)
		{
			lightarray[j] = lightarray[j + 1];
		}
		NumOfTrafficlights--;	
		currentlights--;
	}
	int getcurrentlights() { //Used to access currentlights
		return currentlights;
	}
	int getNumOfTrafficLights() {	//Used to access NumOfTrafficLights
		return NumOfTrafficlights;
	}
	void run() { //This function simulates one loop of the trafficlight intersection
		cout << "Calculating green light timings..." << endl;
		cout << endl;
		updateTiming(); //Initializes the green time in each traffic light object

		for (int l = 1;l < getcurrentlights();l++) { //This loop prints the information of all the trafficlights
			getlightarray(l).printLightInfo();
		}
		time_t start = time(NULL); //infinite loop to simulate a traffic intersection
		for (;;) {
			for (int i = 1;i < currentlights;i++) { //This for loop is for displaying the light state aas well as waiting the amount of time

				if (getlightarray(i).getstate() > 0) {
					lightarray[i].setgreen();
				}
				for (int j = 1;j < currentlights;j++) {
					lightarray[j].DisplayLightState(j);
				}
				cout << endl;
				cout << endl;
				lightarray[i].wait();
				if (getlightarray(i).getstate() > 0) {
					lightarray[i].setyellow();
				}
				for (int k = 1;k < currentlights;k++) {
					lightarray[k].DisplayLightState(k);
				}
				lightarray[i].wait();
				if (getlightarray(i).getstate() > 0) {
					lightarray[i].setred();
				}
				cout << endl;
				cout << endl;
			}
			time_t end = time(NULL); //Keep track of the time the simulation starts
			double elapsed_time = difftime(end, start);
			if (elapsed_time >= REFRESHTIME) { //if the time elapsed is more than 86400 which is 24 hrs in seconds then refresh the flow rates/green light times
				cout << "Updating timings..." << endl;
				cout << endl;
				updateTiming(); //Refreshes the green times
				for (int m = 1;m < getcurrentlights();m++) { //This loop prints the information of all the trafficlights
					getlightarray(m).printLightInfo();
				}
				start = time(NULL); //resets the start time so the time interval resets
			}
		}
	}
	Trafficlight getlightarray(int i) { //Used to get access to the private lightarray object
		return lightarray[i];
	}
	void setlightarraystateoff(int i) {
		lightarray[i].setoff();
	}
	void readTrafficData() { //Used to get data from a file into the variables of the Intersection object
		ifstream infile;
		infile.open("in.txt", ios::in);
		if (infile.fail()) //Error message if file fails to open
		{
			cerr << "File could not be opened" << endl;
			exit(1);
		}
		infile >> Cycle_length; //Inputting the Data into their respective variables
		for (int i = 1;i < currentlights;i++) {
			infile >> Q[i];
			Totalflow += Q[i];
		}
	}
	void updateTiming() { //Used to calculate the green light time from the provided data in the file
		readTrafficData();
		double time;
		for (int i = 1;i < currentlights;i++) {
			if (getlightarray(i).getstate() == 0) {
				lightarray[i].setgreentime(0);
			}
			else {
				time = (Q[i] / Totalflow) * Cycle_length;
				lightarray[i].setgreentime(time);
			}
		}
		Totalflow = 0;
	}
};