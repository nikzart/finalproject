#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    char a;

    // creating move obj based on characters in commandString
    if (commandString == "") {
        isPass = true;
        isPickup = false;
        isSave = false;
        isQuit = false;
    }
    else if ((commandString == "s") || (commandString == "S")) {
        isPass = false;
        isPickup = false;
        isSave = true;
        isQuit = false;
    }
    else if ((commandString == "q") || (commandString == "Q")) {
        isPass = false;
        isPickup = false;
        isSave = false;
        isQuit = true;
    }
    else {
        // lets string obj to be treated as a stream
        stringstream ss(commandString);
        ss >> a >> elevatorId >> a;
        if (a == 'f') {
            isPass = false;
            isPickup = false;
            isSave = false;
            isQuit = false;
            ss >> targetFloor;
        }
        else if (a == 'p') {
            isPass = false;
            isPickup = true;
            isSave = false;
            isQuit = false;
        }
    }

}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    bool validityCheck = false;
    // valid moves
    if ((isPass == true) || (isQuit == true) || (isSave == true)) {
        validityCheck = true;
    }
    // when elevator is not servicing request
    else if ((elevatorId < NUM_ELEVATORS) && (elevatorId >= 0)
        && (!elevators[elevatorId].isServicing())) {
        if (isPickup == true) {
            validityCheck = true;
        }
        // for servicing moves
        else if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) 
            && (targetFloor != elevators[elevatorId].getCurrentFloor())) {
            validityCheck = true;
        }
    }
    return validityCheck;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    
    Move number;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    const int constantASCII = 48;

        for (int i = 0; i < pickupList.length(); i++) {
            peopleToPickup[i] = (int)pickupList.at(i) - constantASCII;
            numPeopleToPickup++;
            totalSatisfaction = totalSatisfaction + 
                (MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel());
        }

        int maximumFloor = 0;

        for (int i = 0; i < pickupList.length(); i++) {
            if ((abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor()
                - currentFloor)) > maximumFloor) {
                maximumFloor = abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor);
                targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
            }
        }

}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
