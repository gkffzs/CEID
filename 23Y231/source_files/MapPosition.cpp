#include "MapPosition.h"

MapPosition::MapPosition(char* d_n, int pal, int iri, int pla, float dan, bool fla, bool t):
    display_name((char*) d_n), palladium(pal),iridium(iri),platinum(pla),danger(dan),danger_flag(fla),taken(t) {
        current_vehicle_id = 0;
    }
MapPosition::~MapPosition(){}

void MapPosition::setDisplayName(char* d_n){display_name = (char*) d_n;}
void MapPosition::setCurrentVehicleID(int new_c_v_ID){current_vehicle_id = new_c_v_ID;}
void MapPosition::resetDisplayName(){
    if(danger_flag == false){
        display_name = (char*) " * ";
    } else {
        display_name = (char*) " x ";
    }
}
void MapPosition::setX(int new_x){x = new_x;}
void MapPosition::setY(int new_y){y = new_y;}
void MapPosition::setPalladium(int pal){palladium=pal;}
void MapPosition::setIridium(int iri){iridium=iri;}
void MapPosition::setPlatinum(int pla){platinum=pla;}
void MapPosition::setDanger(float dan){danger=dan;}
void MapPosition::setFlag(bool fla){danger_flag=fla;}
void MapPosition::setTaken(bool t){taken=t;}

char* MapPosition::getDisplayName() const {return display_name;}
int MapPosition::getCurrentVehicleID() const {return current_vehicle_id;}
int MapPosition::getX() const {return x;}
int MapPosition::getY() const {return y;}
int MapPosition::getPalladium() const {return palladium;}
int MapPosition::getIridium() const {return iridium;}
int MapPosition::getPlatinum() const {return platinum;}
float MapPosition::getDanger() const {return danger;}
bool MapPosition::getFlag() const {return danger_flag;}
bool MapPosition::getTaken() const {return taken;}

void MapPosition::printMapPosition() const {
    if(strcmp(display_name,"###") != 0){ /* For all positions except the one where the base is. */
           cout << " >>> POSITION (" << x << "," << y << ")";
        if (taken == false){
            cout << " - This position is currently free." << endl;
        } else {
            cout << endl << " >>> There is a " << display_name << " vehicle with ID #" << current_vehicle_id << "." << endl;
        }
        cout << " >>> It is " << (danger*100) << "% dangerous and has ";
        if(danger_flag == false){
            cout << "not been flagged yet." << endl;
        } else {
            cout << "been flagged as such." << endl;
        }
        cout << " >>> Concentration of metals: ";
        cout << " pal(" << palladium <<"), iri(" << iridium << "), pla(" << platinum << ")." << endl;
    } else { /* Printing different things if base is located in the specific position. */
        cout << " >>> BASE (" << x << "," << y << ")" << endl;
        cout << " >>> ~~~ Palladium: " << palladium << "/" << MAXPAL << endl;
        cout << " >>> ~~~ Iridium: " << iridium<< "/" << MAXIRI << endl;
        cout << " >>> ~~~ Platinum: " << platinum << "/" << MAXPLA << endl;
    }
}
