#ifndef MAP_POSITION_H
#define MAP_POSITION_H

#include <cstring>
#include <iostream>
#include "Globals.h"

using namespace std;

class MapPosition{
public:
    MapPosition(char* =(char* ) " * ", int =0, int =0, int =0,
                float =0, bool =false, bool =false);
    ~MapPosition();

    void setDisplayName(char*);
    void setCurrentVehicleID(int);
    void resetDisplayName();
    void setX(int);
    void setY(int);
    void setPalladium(int);
    void setIridium(int);
    void setPlatinum(int);
    void setDanger(float);
    void setFlag(bool);
    void setTaken(bool);

    char* getDisplayName() const;
    int getCurrentVehicleID() const;
    int getX() const;
    int getY() const;
    int getPalladium() const;
    int getIridium() const;
    int getPlatinum() const;
    float getDanger() const;
    bool getFlag() const;
    bool getTaken() const;

    void printMapPosition() const;

private:
    char* display_name;
    int current_vehicle_id;
    int x;
    int y;
    int palladium;
    int iridium;
    int platinum;
    float danger;
    bool danger_flag;
    bool taken;
};

#endif

