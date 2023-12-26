#ifndef PROJ2_AED_MENU_H
#define PROJ2_AED_MENU_H

class Menu{
public:
    void mainMenuView();
    void statisticsMenuView();
    void bestFlightsMenuView();

    int runMainMenu();
    int runStatisticsMenu();
    int runBestFlightsMenu();

    void waitForInput() const;

};

#endif //PROJ2_AED_MENU_H
