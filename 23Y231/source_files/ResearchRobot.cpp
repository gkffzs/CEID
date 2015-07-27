#include "Vehicle.h"
#include "ResearchRobot.h"

ResearchRobot::ResearchRobot(): Vehicle(3,false,0.5){
    Vehicle::setName((char*) "|A|");
    number_of_flags = 0;
}

ResearchRobot::ResearchRobot(int s, bool b, float a): Vehicle(s, b, a){
    Vehicle::setName((char*) "|A|");
    number_of_flags = 0;
}

ResearchRobot::~ResearchRobot(){}

void ResearchRobot::setNumberOfFlags(int nof){number_of_flags = nof;}
int ResearchRobot::getNumberOfFlags() const {return number_of_flags;}

/* Enhanced print function. */
void ResearchRobot::printVehicle(){
    Vehicle::printVehicle();
    cout << " >>> --- Flags set: " << number_of_flags << endl;
}

/* doTask() for ResearchRobot. */
void ResearchRobot::doTask(MapPosition m[XMAP][YMAP],vector<Vehicle*> rf){
    if(getBroken() == false){ /* Checking if the robot is broken. */
        float current_danger = m[x][y].getDanger();
        bool is_flag_set = m[x][y].getFlag();
        /* If current position is dangerous and has no flag yet, the robot places one. */
        if (current_danger > 0.7 && is_flag_set == false) {
            m[x][y].setFlag(true);
            m[x][y].setDisplayName((char*) " x ");
            setNumberOfFlags(getNumberOfFlags()+1);
            cout << " >>> " << getName() << "(#" << getID() << ") just flagged position (" << x << "," << y << ") as dangerous." << endl;
        }
    } else {
        cout << " >>> " << getName() << "(#" << getID() << ") at (" << x << "," << y << ") cannot perform any tasks due to breakdown." << endl;
    }
}

