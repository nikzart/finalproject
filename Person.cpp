#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string input_string) : Person() {
    stringstream ss(input_string);
    // initializing a test char in order to store 
    // non-integers in the string
    char test;
    ss >> turn;
    ss >> test;
    ss >> currentFloor;
    ss >> test;
    ss >> targetFloor;
    ss >> test;
    ss >> angerLevel;

}

bool Person::tick(int currentTime) {
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
          ++angerLevel;
      }
      if (angerLevel < MAX_ANGER) {
          return false;
      }
      else {
          return true;
      }

    //Returning false to prevent compilation error
    return false;
}

void Person::print(ostream &outs) {    
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
