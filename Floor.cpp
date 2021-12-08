#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int total = 0;
    int explodedPeople[MAX_PEOPLE_PER_FLOOR]; 
    for (int i = 0; i < numPeople; i++) {
        if (people[i].tick(currentTime)) {
            explodedPeople[total] = i;
            total++;
        }
        
    }
    removePeople(explodedPeople, total);
    return total;

    //returning 0 to prevent compilation error
    return 0;
}

void Floor::addPerson(Person p, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = p;
        numPeople += 1;
    }
    if (request > 0){
        hasUpRequest = true;
    }
    if (request < 0){
        hasDownRequest = true;
    }
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {

    Person personas[MAX_PEOPLE_PER_FLOOR];
    int pplCounter = 0;

    for (int i = 0; i < numPeople; i++) {
        bool savePerson = true;
        for (int j = 0; j < numPeopleToRemove; j++) {
            if (i == indicesToRemove[j]) {
                savePerson = false;
            }
        }
            if (savePerson) {
                personas[pplCounter] = people[i];
                pplCounter += 1;
            }
       
    }

    numPeople = pplCounter;

    for (int y = 0; y < numPeople; y++) {
        people[y] = personas[y];
    }

    resetRequests();
}

void Floor::resetRequests() {
    hasDownRequest = false;
    hasUpRequest = false;
    int countUp = 0;
    int countDown = 0;
    for (int i = 0; i < numPeople; i++) {
        int x = people[i].getTargetFloor();
        int y = people[i].getCurrentFloor();
        if (x > y){
            countUp ++;
        }
        if (y > x) {
            countDown ++;
        }
    }
    if (countUp > 0) {
        hasUpRequest = true;
    }
    if (countDown > 0) {
        hasDownRequest = true;
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
