#ifndef TEAMS_H
#define TEAMS_H

#include <iostream>
#include <string>
#include <vector>
#include "players.h"

class Team
{
    private: 
        std::string location;
        unsigned int salaryCap;
        

    public:
        int totalGames;
        int wins = 0;
        int losses= 0;
        int score;
        std::vector<Player*> teamPlayers;
        Team(std::string location,std::string teamName);
        std::string teamName;
        void setLocation(std::string location);
        std::string getLocation();
        void addPlayer(std::string first_name, std::string last_name, int jerseyNumber, std::string team, std::string position, int overall);
        
};
#endif