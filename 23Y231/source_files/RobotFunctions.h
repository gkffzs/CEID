#ifndef ROBOT_FUNCTIONS_H
#define ROBOT_FUNCTIONS_H

#include <vector>
#include "Globals.h"
#include "Vehicle.h"
#include "RescueRobot.h"
#include "AnalysisRobot.h"
#include "ResearchRobot.h"
#include "RandomNumbers.h"

vector <Vehicle*> createRobotFleet(MapPosition[XMAP][YMAP]);
void moveRobotFleet(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
void operateRobotFleet(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
void printRobotFleet(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
void printRobotStats(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
void printRobotData(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
vector <Vehicle*> addRobotToFleet(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
void causeOrFixBreakdown(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
int checkMapStatus(vector <Vehicle*>, MapPosition[XMAP][YMAP]);
vector <Vehicle*> seekAndDestroyBrokens(vector <Vehicle*>, MapPosition[XMAP][YMAP]);

#endif
