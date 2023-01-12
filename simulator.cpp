#include "NBA.h"
using std::cout, std::endl;

void printMenu()
{
    cout << "Welcome to BestGM" << endl;
    cout << "The options are: " << endl;
    cout << "1. Play game" << endl;
    cout << "2. Simulate season with user team" << endl;
    cout << "3. Simulate season with CPU" << endl;
}




int main()
{
    srand(time(0)); //generate random number
    NBA nba;
    std::string filename1;
    std::string filename2;
    std::cout << "Please input file with teams?" << std::endl;
    std::cin >>  filename1;
    std::cout << "Please input file with players?" << std::endl;
    std::cin >>  filename2;
    nba.loadTeamsFromFile(filename1);
    nba.loadPlayersFromFile(filename2);
    printMenu();
    int choice;
    std::cin >> choice;
    switch(choice)
    {
        case 1:
            {
                std::cout << "Choose your team" << endl;
                std::string team;
                std::cin >> team;
                Team* user_team = nba.findTeam(team);
                std::cout << "Choose opponent" << endl;
                std::string other_team;
                std::cin >> other_team;
                Team* opponent = nba.findTeam(other_team);
                nba.playGame(user_team, opponent);
                break;
            }
        case 2:
            {
                std::cout << "Choose your team" << endl;
                std::string team;
                std::cin >> team;
                Team* user_team = nba.findTeam(team);
                nba.simSeason(user_team);
                //cout << user_team->teamPlayers.at(1)->avgPoints << endl;
                break;
            }
        case 3:
            {
                nba.simSeason();
                break;
            }
    }
    
    // nba.simSeason(nba.getTeams().at(0));


    
    
    return 0;
}