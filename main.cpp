#include <iostream>
#include "NBA.h"

int main()
{
    // std::string hometown;
    // Team Grizzlies("Memphis", "Grizzlies");
    // Grizzlies.addPlayer("Ja", "Morant", 12, "Murray State");
    // for (int i = 0; i < Grizzlies.teamPlayers.size();i++)
    // {
    //     Grizzlies.teamPlayers[i]->setHome(hometown);
    //     std::cout << Grizzlies.teamPlayers[i]->first_name << std::endl;
    // }

    // NBA nba;
    // nba.addTeam("Memphis", "Grizzlies");
    // nba.addTeam("Golden State", "Warriors");

    // for (int i = 0; i < nba.getTeams().size();i++)
    // {
    //     std::cout << nba.getTeams()[i]->teamName << std::endl;
    // }

//add player to team
    // nba.getTeams().at(1)->Team::addPlayer("Ja", "Morant", 12, "Murray State");
    
    // for (int i = 0; i < nba.getTeams().at(1)->teamPlayers.size();i++)
    // {
    //     std::cout << nba.getTeams().at(1)->teamPlayers[i]->first_name << std::endl;
    // }



    NBA nba;
    std::cout << "Would you like to create new league?" << std::endl;
    bool makeLeague;
    std::string location;
    std::string name;
    std::cin >> makeLeague;
    if (makeLeague)
    {
        for (int i = 0; i < 2;i++)
        {
            std::cout << "Enter team's location and name" << std::endl;
            std::cin >> location >> name;
            nba.NBA::addTeam(location, name);
            std::cout << nba.getTeams().at(i)->teamName << " were added " << std::endl;
        }
    }
    
    

    return 0;
}