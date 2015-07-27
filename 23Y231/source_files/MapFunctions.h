#ifndef MAP_FUNCTIONS_H
#define MAP_FUNCTIONS_H

#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Globals.h"
#include "MapPosition.h"
#include "RandomNumbers.h"

using namespace std;

void initializeMap(MapPosition[XMAP][YMAP]);
void printMap(MapPosition[XMAP][YMAP]);
void printMapStats(MapPosition[XMAP][YMAP]);
void printPlanetPosition(MapPosition[XMAP][YMAP]);
void editMapPosition(MapPosition[XMAP][YMAP]);

#endif
