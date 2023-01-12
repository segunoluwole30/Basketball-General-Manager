
#include "teams.h"



//constructor
Team::Team(std::string location,std::string teamName)
{
    setLocation(location);
    this->teamName = teamName;
}
void Team::setLocation(std::string location)
{
    this->location = location;
}
std::string Team::getLocation()
{
    return location;
}
void Team::addPlayer(std::string first_name, std::string last_name, int jerseyNumber, std::string team, std::string position, int overall)
{
        Player* new_player = new Player(first_name, last_name, jerseyNumber, team, position, overall);
         teamPlayers.push_back(new_player);
    
    
}

