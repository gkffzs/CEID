#include "Vehicle.h"

int newVehicleID(){static int aID = 0; return ++aID;}

Vehicle::Vehicle(): id(newVehicleID()){
    name = (char*) "|V|";
    speed = 1;
    approach_capability = 0.5;
    broken = false;
    moves_made = 0;
    broken_times = 0;
    rounds_broken = 0;
}

Vehicle::Vehicle(int s, bool b, float a):
    speed(s), broken(b), approach_capability(a), id(newVehicleID()){
    name = (char*) "|V|";
    moves_made = 0;
    broken_times = 0;
    rounds_broken = 0;
}

Vehicle::Vehicle(char* n, int s, bool b, float a):
    name(n), speed(s), broken(b), approach_capability(a), id(newVehicleID()){
    moves_made = 0;
    broken_times = 0;
    rounds_broken = 0;
}

Vehicle::~Vehicle(){}

void Vehicle::setName(char* n){name = n;}
void Vehicle::setSpeed(int s){speed = s;}
void Vehicle::setBroken(bool b){broken = b;}
void Vehicle::setApproachCapability(float a){approach_capability = a;}
void Vehicle::setMovesMade(int mm){moves_made = mm;}
void Vehicle::setBrokenTimes(int bt){broken_times = bt;}
void Vehicle::setRoundsBroken(int rb){rounds_broken = rb;}

void Vehicle::setXY(int new_x, int new_y){x = new_x; y = new_y;}

int Vehicle::getID() const {return id;}
char* Vehicle::getName() const {return name;}
int Vehicle::getSpeed() const {return speed;}
bool Vehicle::getBroken() const {return broken;}
float Vehicle::getApproachCapability() const {return approach_capability;}
int Vehicle::getMovesMade() const {return moves_made;}
int Vehicle::getBrokenTimes() const {return broken_times;}
int Vehicle::getRoundsBroken() const {return rounds_broken;}

void Vehicle::printVehicle(){
    cout << " >>> " << name << " @ (" << x << "," << y << ")" << endl;
    cout << " >>> --- VehicleID: " << id << endl;
    cout << " >>> --- Speed: " << speed << endl;
    cout << " >>> --- Broken: " << broken << endl;
    cout << " >>> --- Approach Capability: " << approach_capability << endl;
    cout << " >>> --- Total Moves: " << moves_made << endl;
    cout << " >>> --- Total breakdowns: " << broken_times << endl;
}

void Vehicle::moveVehicle(MapPosition m[XMAP][YMAP]){
    int v_x = x;
    int v_y = y;
    bool success = false;
    float broken_probability = 0;
    int random_move;
    int counter = 0;

    if(getBroken() == false){ /* Checking if the vehicle is broken. */
        while (success == false){ /* Loop for finding randomly an appropriate position to move. */
            random_move = rand()%4; /* Random move. */
            if (random_move == 0 && x-1 > -1 && x-1 < XMAP && m[x-1][y].getTaken() == false && m[x-1][y].getFlag() == false){
                v_x--; success = true; /* Moving up. */
            } else if (random_move == 1 && x+1 > -1 && x+1 < XMAP && m[x+1][y].getTaken() == false && m[x+1][y].getFlag() == false){
                v_x++; success = true; /* Moving down. */
            } else if (random_move == 2 && y-1 > -1 && y-1 < YMAP && m[x][y-1].getTaken() == false && m[x][y-1].getFlag() == false){
                v_y--; success = true; /* Moving left. */
            } else if (random_move == 3 && y+1 > -1 && y+1 < YMAP && m[x][y+1].getTaken() == false && m[x][y+1].getFlag() == false){
                v_y++; success = true; /* Moving right. */
            }

            /* If no appropriate position can be found within 12 iterations, searching stops. */
            if (counter < 12){
                counter++;
            } else {
                break;
            }
        }

        if (success){ /* if a position is found, the vehicle moves there. */
            m[x][y].resetDisplayName();
            m[x][y].setCurrentVehicleID(0);
            m[x][y].setTaken(false);

            m[v_x][v_y].setDisplayName(getName());
            m[v_x][v_y].setCurrentVehicleID(getID());
            m[v_x][v_y].setTaken(true);

            cout <<" >>> " << name << "(#" << id << ") moved from (" << x << "," << y << ") to (";
            setXY(v_x,v_y); cout <<  x << "," << y << ")." << endl;

            /* Increasing moves' counter. */
            setMovesMade(getMovesMade()+1);

            /* Calculating the probability of a breakdown due to moving to the new position. */
            broken_probability = m[x][y].getDanger()*(1-getApproachCapability());
            if (broken_probability > 0.6){
                setBroken(true);
                setBrokenTimes(getBrokenTimes()+1);
                cout << " >>> *** BREAKDOWN: " << name << "(#" << id << ") broke when it moved to (" << x << "," << y <<")." << endl;
            }
        } else { /* In case of failure in finding an appropriate position to move to. */
            cout << " >>> " << name << "(#" << id << ") failed to move from (" << x << "," << y <<")." << endl;
        }
    } else { /* In case the vehicle is broken. */
        cout << " >>> " << name << "(#" << id << ") at (" << x << "," << y <<") is broken and cannot move." << endl;
        setRoundsBroken(getRoundsBroken()+1);
    }
}

/* Simple doTask() function that shall not be used. */
void Vehicle::doTask(MapPosition m[XMAP][YMAP],vector<Vehicle*> rf){
    cout << " >>> " << name << "(#" << id << ") at (" << x << "," << y << ") has nothing specific to do." << endl;
}
