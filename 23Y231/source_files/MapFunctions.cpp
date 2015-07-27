#include "MapFunctions.h"

/* Map's initializing function. */
void initializeMap(MapPosition m[XMAP][YMAP]){
    /* Main loop of initialization, it sets all variables' values. */
    for(int i = 0; i < XMAP; i++){
        for(int j = 0; j < YMAP; j++){
            m[i][j].setX(i);
            m[i][j].setY(j);
            m[i][j].setPalladium(getIntRandomNumber(25,200));
            m[i][j].setIridium(getIntRandomNumber(25,200));
            m[i][j].setPlatinum(getIntRandomNumber(25,200));
            m[i][j].setDanger(getFloatRandomNumber(1,10));
            m[i][j].setFlag(false);
            m[i][j].setTaken(false);
        }
    }
    cout << " >>> PLANET INITIALIZATION ------------------------------------------" << endl;
    cout << " >>> --| Planet (" << XMAP << "x" << YMAP <<") initialized successfully." << endl;

    /* Specifying base as a special MapPosition. */
    int b_x = getIntRandomNumber(0,XMAP-1);
    int b_y = getIntRandomNumber(0,YMAP-1);
    m[b_x][b_y].setDisplayName((char*) "###");
    m[b_x][b_y].setPalladium(0);
    m[b_x][b_y].setIridium(0);
    m[b_x][b_y].setPlatinum(0);
    m[b_x][b_y].setDanger(0);
    m[b_x][b_y].setFlag(false);
    m[b_x][b_y].setTaken(true);
    cout << " >>> --| Base (represented as " << m[b_x][b_y].getDisplayName() << ") is currently located at (" << b_x << ","<< b_y << ")." << endl;
}

/* Printing map on terminal. */
void printMap(MapPosition m[XMAP][YMAP]){
    cout << "---------------------------------------------------------------------" << endl;
    cout << "     ";
    /* Loop for printing numbers on the upper side of the map. */
    for(int j = 0; j < YMAP; j++){
        if(j < 10){
            cout << " " << j << "  ";
        }else{
            cout << " " << j << " ";
        }
    }
    cout << endl;
    cout << "    -----------------------------------------------------------------" << endl;
    for(int i = 0; i < XMAP; i++){ /* Printing map by rows. */
        /* If-block for printing numbers on the left side of the map. */
        if(i < 10){
            cout << "  " << i << "| ";
        }else{
            cout << " " << i << "| ";
        }

        /* Loop for printing every position in current row. */
        for(int j = 0; j < YMAP; j++){
            cout << m[i][j].getDisplayName() << " ";
            if((j+1) % YMAP == 0) cout << endl;
        }
    }
    cout << "---------------------------------------------------------------------" << endl;
}

/* Statistics printing function. */
void printMapStats(MapPosition m[XMAP][YMAP]){
    int total_pal = 0;
    int total_iri = 0;
    int total_pla = 0;
    float total_danger = 0;
    char* base_symbol = (char*) "###";

    /* Loop for calculating what we want to display. */
    for(int i=0; i<XMAP; i++){
        for(int j=0; j<YMAP; j++){
            if(strcmp(m[i][j].getDisplayName(),base_symbol) != 0){
                total_pal = total_pal + m[i][j].getPalladium();
                total_iri = total_iri + m[i][j].getIridium();
                total_pla = total_pla + m[i][j].getPlatinum();
                total_danger = total_danger + m[i][j].getDanger();
            }
        }
    }
    cout << " >>> ----------------------------------------------------------------" << endl;
    cout << " >>> PLANET STATISTICS ----------------------------------------------" << endl;
    cout << " >>> --| Number of positions: " << XMAP*YMAP-1 << endl;
    cout << " >>> --| Available palladium: " << total_pal << endl;
    cout << " >>> --| Available iridium: " << total_iri << endl;
    cout << " >>> --| Available platinum: " << total_pla << endl;
    cout << " >>> --| Medium danger: " << setprecision(4) << (total_danger*100)/(XMAP*YMAP-1) << "%" << endl;
}

/* Function that prints the data of a position. */
void printPlanetPosition(MapPosition m[XMAP][YMAP]){
    int n_x, n_y;
    cout << " >>> Please enter the position that you want to print:" << endl;
    cout << " >>> --- x: "; cin >> n_x;
    cout << " >>> --- y: "; cin >> n_y;
    m[n_x][n_y].printMapPosition();
}

/* Function that edits a position on the map. */
void editMapPosition(MapPosition m[XMAP][YMAP]){
    int n_x, n_y;
    int n_pal, n_iri, n_pla;
    float n_danger;
    cout << " >>> Please enter the position that you want to edit:" << endl;
    cout << " >>> --- x: "; cin >> n_x;
    cout << " >>> --- y: "; cin >> n_y;
    m[n_x][n_y].printMapPosition();
    cout << " >>> Enter new values for the position:" <<  endl;
    cout << " >>> --- Palladium: "; cin >> n_pal;
    m[n_x][n_y].setPalladium(n_pal);
    cout << " >>> --- Iridium: "; cin >> n_iri;
    m[n_x][n_y].setIridium(n_iri);
    cout << " >>> --- Platinum: "; cin >> n_pla;
    m[n_x][n_y].setPlatinum(n_pla);
    cout << " >>> --- Danger: "; cin >> n_danger;
    m[n_x][n_y].setDanger(n_danger);
    cout << " >>> (" << n_x << "," << n_y << ")'s data changed successfully!" << endl;
    m[n_x][n_y].printMapPosition();
}
