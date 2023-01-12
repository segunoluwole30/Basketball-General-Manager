#include "NBA.h"
#include <fstream>
#include <sstream>

using std::cout, std::endl;

int NBA::getPlayerCount()
{
    return player_count;
}
int NBA::getTeamCount()
{
    return team_count;
}
//add team to league
void NBA::addTeam(std::string location, std::string teamName)
{
    Team* new_team = new Team(location, teamName);
    teams.push_back(new_team);
    team_count++;
    std::cout << new_team->teamName << " was added." << std::endl;
}

void NBA::addPlayer(std::string first_name, std::string last_name, int jerseyNumber, std::string team, std::string position, int overall)
{
    Player* new_player = new Player(first_name, last_name, jerseyNumber, team, position,  overall);
    players.push_back(new_player);
    player_count++;
    std::cout << new_player->first_name + " " + new_player->last_name << " was added to the "  << team << std::endl;
}

NBA::NBA() 
{
    //creates empty vectors for players and teams
}
  
//destrcutor for league
NBA::~NBA()
  {
    for (int i = 0; i < teams.size();i++)
    {
        delete teams.at(i);
        team_count--;
    }
     for (int i = 0; i < players.size();i++)
    {
        delete players.at(i);
        player_count--;
    }
  }

  //access teams
  std::vector<Team*> NBA::getTeams()
  {
    return teams;
  }

  Team* NBA::findTeam(std::string team)
{
    for (int i = 0; i < getTeams().size();i++)
    {
        if (getTeams().at(i)->teamName == team)
        {
            return getTeams().at(i);
        }
    }
}

  std::vector<Player*> NBA::getPlayers()
  {
    return players;
  }

  int NBA::player_count = 0;
  int NBA::team_count = 0;

  void NBA::loadTeamsFromFile(std::string filename)
  {
        std::string location;
        std::string name;
        std::string team;


        std::ifstream file;
        file.open(filename);

        while (std::getline(file, team)) //load teams from file
        {
            
            std::istringstream in_string(team);
            in_string >> location;
            in_string >> name;
            addTeam(location, name);
        }

  }

  void NBA::loadPlayersFromFile(std::string filename)
  {
    std::string firstName;
    std::string lastName;
    int number;
    std::string team;
    std::string line;
    std::string position;
    int overall;


    std::ifstream file;
    file.open(filename);

    while (getline(file, line))
    {
        if (line.at(0) == 'q')
        {
            cout << "End of File" << endl;
            break;
        }
        std::istringstream inSS(line);
        inSS >> firstName;
        inSS >> lastName;
        inSS >> number;
        inSS >> team;
        inSS >> position;
        inSS >> overall;

    
        
            for (int i = 0; i < getTeams().size();i++) // loops through nba vector of teams
            {
                if (team == getTeams().at(i)->teamName) // if player's team exists
                {
                    try
                    {
                        if (getTeams().at(i)->teamPlayers.size() > 0) //checks if team size is greater than one in order for player comparison
                        {
                            for (int k = 0; k < getTeams().at(i)->teamPlayers.size();k++) //loops through current team's player vector
                            {
                                if (getTeams().at(i)->teamPlayers.at(k)->first_name == firstName && getTeams().at(i)->teamPlayers.at(k)->last_name == lastName) //checks if player already exists
                                {
                                    
                                    throw std::invalid_argument("Player is already on team");
                                    //break;
                                    
                                }
                                if (getTeams().at(i)->teamPlayers.at(k)->jerseyNumber == number)
                                {
                                    // cout << number << " is already taken" << endl;
                                    // break;
                                    throw std::invalid_argument("This jersey number is already taken");
                                }
                            }
                    
                        }
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        break;    
                    }
                addPlayer(firstName, lastName, number, team, position, overall); //add player to NBA
                getTeams().at(i)->addPlayer(firstName, lastName, number, team, position, overall); //add player to team
                
            }
            else
            {
                continue;
            }
            }
            continue;       
    }
    file.close();
  }

  void NBA::simSeason(Team* team1)
  {
    Team* team2;
    int totalGames = 0;
   
    while(totalGames < 82)
    {
        team2 = getTeams().at(rand() % getTeams().size());
        if (team2->teamName != team1->teamName)
        {
            playGame(team1, team2);
            if (team1->score > team2->score)
            {
                team1->wins++;
                team2->losses++;
            }
            else if (team2->score > team1->score)
            {
                team1->losses++;
                team2->wins++;
            }
            else //tie after regulation
            {
                while (team1->score == team2->score)
                {
                    playGame(team1,team2); //overtime
                    if (team1->score > team2->score)
                    {
                        team1->wins++;
                        team2->losses++;
                    }
                    else if (team2->score > team1->score)
                    {
                        team1->losses++;
                        team2->wins++;
                    }
                }
                
            }
            totalGames++;
            team1->score = 0; //reset each team's score to zero after each game
            team2->score = 0; //^^^  
        }
        else 
        {
            continue;
        }
        
    }

    for (int i = 0; i < team1->teamPlayers.size();i++) //average points = player's total points divided by num of games played
        {
            team1->teamPlayers.at(i)->avgPoints += (team1->teamPlayers.at(i)->totalPoints)/(totalGames);
        }
    
    
    
    std::cout << team1->wins << std::endl;
    std::cout << team1->losses << std::endl;
  }

void NBA::simSeason()
{
    
        for (int i = 0; i < getTeams().size()-1;i++)
            {
                while (getTeams().at(i)->totalGames < 82)
                {
                    Team* team2;
                    team2= getTeams().at(rand() % getTeams().size());
                    if (team2 != getTeams().at(i) && team2->totalGames < 82)
                    {
                        playGame(getTeams().at(i), team2);
                        if (getTeams().at(i)->score > team2->score)
                        {
                            getTeams().at(i)->wins++;
                            team2->losses++;
                        }
                        else if (team2->score > getTeams().at(i)->score)
                        {
                            getTeams().at(i)->losses++;
                            team2->wins++;
                        }
                        else //tie after regulation
                        {
                            while (getTeams().at(i)->score == team2->score)
                            {
                                playGame(getTeams().at(i),team2); //overtime
                                if (getTeams().at(i)->score > team2->score)
                                {
                                    getTeams().at(i)->wins++;
                                    team2->losses++;
                                }
                                else if (team2->score > getTeams().at(i)->score)
                                {
                                    getTeams().at(i)->losses++;
                                    team2->wins++;
                                }
                            }
                    
                        }
                       
                    // cout <<  getTeams().at(i)->totalGames << endl;
                    // cout <<  team2->totalGames << endl;    
                    getTeams().at(i)->totalGames++;
                    team2->totalGames++;
                    getTeams().at(i)->score = 0; //reset each team's score to zero after each game
                    team2->score = 0; //^^^ 
                       
                         
                    }
                    else 
                    {
                        continue;
                    }
                }
                for (int j = 0; j < getTeams().at(i)->teamPlayers.size();j++) //average points = player's total points divided by num of games played
                {
                    getTeams().at(i)->teamPlayers.at(j)->avgPoints += (getTeams().at(i)->teamPlayers.at(j)->totalPoints)/(getTeams().at(i)->totalGames);
                }

                if (getTeams().at((getTeams().size())-1)->totalGames > 70) //check if last team in nba has played more than 70 games
                    {
                        break;
                    }
            }
            /*Find highest scorer*/
            double highAvg = 0;
            std::string player;
            for (int j = 0; j < getTeams().size(); j++)
            {
                for (int i = 0; i < getTeams().at(j)->teamPlayers.size();i++)
                {
                    if (getTeams().at(j)->teamPlayers.at(i)->avgPoints > highAvg)
                    {
                        highAvg = getTeams().at(j)->teamPlayers.at(i)->avgPoints;
                        player = getTeams().at(j)->teamPlayers.at(i)->first_name;
                        
                    }
                }    
            }
            cout << player << " " << highAvg << endl;

            /*Show Standings*/
            for (int i = 0; i < getTeams().size();i++)
            {
                cout << getTeams().at(i)->teamName << " Wins:  " << getTeams().at(i)->wins << " Losses: " << getTeams().at(i)->losses << endl;
            }
            
    //}

    
    }
                

  void NBA::playGame(Team* team1, Team* team2)
  {
    //alwasy call srand() at beginning of main function
    std::cout << team1->teamName << " VS " << team2->teamName << std::endl;
    
    /* loop through players on team and give them random stat totals*/
    /*TEAM 1 STATS*/
    for (int i = 0; i < team1->teamPlayers.size();i++)
    {
        if (team1->teamPlayers.at(i)->overall > 90) //if overall is greater than or equal to 90
        {
            if (team1->teamPlayers.at(i)->position == "PG")                                                       /*rebounds and assists for each position*/
            {
                team1->teamPlayers.at(i)->rebounds = rand() % 12;
                team1->teamPlayers.at(i)->assists = 5 + (rand() % 10);
            }
            else if (team1->teamPlayers.at(i)->position == "SG")
            {
                team1->teamPlayers.at(i)->rebounds = rand() % 5;
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team1->teamPlayers.at(i)->position == "SF")
            {
                team1->teamPlayers.at(i)->rebounds = 5+ (rand() % 5);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 10);
            }
            else if (team1->teamPlayers.at(i)->position == "PF")
            {
                team1->teamPlayers.at(i)->rebounds = 8 + (rand() % 5);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team1->teamPlayers.at(i)->position == "C")
            {
                team1->teamPlayers.at(i)->rebounds = 10 + (rand() % 9);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 6);
            }

            team1->teamPlayers.at(i)->pointsScored = 20 + (rand() % 21);
            
        }
        else if(team1->teamPlayers.at(i)->overall >80 && team1->teamPlayers.at(i)->overall <= 90)
        {
            if (team1->teamPlayers.at(i)->position == "PG")                                                       /*rebounds and assists for each position*/
            {
                team1->teamPlayers.at(i)->rebounds = rand() % 12;
                team1->teamPlayers.at(i)->assists = 5 + (rand() % 10);
            }
            else if (team1->teamPlayers.at(i)->position == "SG")
            {
                team1->teamPlayers.at(i)->rebounds = rand() % 5;
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team1->teamPlayers.at(i)->position == "SF")
            {
                team1->teamPlayers.at(i)->rebounds = 5+ (rand() % 5);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 10);
            }
            else if (team1->teamPlayers.at(i)->position == "PF")
            {
                team1->teamPlayers.at(i)->rebounds = 8 + (rand() % 5);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team1->teamPlayers.at(i)->position == "C")
            {
                team1->teamPlayers.at(i)->rebounds = 10 + (rand() % 9);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 6);
            }

            team1->teamPlayers.at(i)->pointsScored =  15 + (rand() % 11);
        }
        else
        {
            if (team1->teamPlayers.at(i)->position == "PG")                                                       /*rebounds and assists for each position*/
            {
                team1->teamPlayers.at(i)->rebounds = rand() % 12;
                team1->teamPlayers.at(i)->assists = 5 + (rand() % 10);
            }
            else if (team1->teamPlayers.at(i)->position == "SG")
            {
                team1->teamPlayers.at(i)->rebounds = rand() % 5;
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team1->teamPlayers.at(i)->position == "SF")
            {
                team1->teamPlayers.at(i)->rebounds = 5+ (rand() % 5);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 10);
            }
            else if (team1->teamPlayers.at(i)->position == "PF")
            {
                team1->teamPlayers.at(i)->rebounds = 8 + (rand() % 5);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team1->teamPlayers.at(i)->position == "C")
            {
                team1->teamPlayers.at(i)->rebounds = 10 + (rand() % 9);
                team1->teamPlayers.at(i)->assists = 0 + (rand() % 6);
            }

            team1->teamPlayers.at(i)->pointsScored =  10 + (rand() % 11);
        }
        
        team1->score += team1->teamPlayers.at(i)->pointsScored;
    }
    std::cout << team1->teamName << " scored " << team1->score << " points " << endl << endl;
    
    /*TEAM 2 STATS*/
    for (int i = 0; i < team2->teamPlayers.size();i++)
    {
        if (team2->teamPlayers.at(i)->overall > 90) //if overall is greater than 90
        {
            if (team2->teamPlayers.at(i)->position == "PG")                                                       /*rebounds and assists for each position*/
            {
                team2->teamPlayers.at(i)->rebounds = rand() % 12;
                team2->teamPlayers.at(i)->assists = 5 + (rand() % 10);
            }
            else if (team2->teamPlayers.at(i)->position == "SG")
            {
                team2->teamPlayers.at(i)->rebounds = rand() % 5;
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team2->teamPlayers.at(i)->position == "SF")
            {
                team2->teamPlayers.at(i)->rebounds = 5+ (rand() % 5);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 10);
            }
            else if (team2->teamPlayers.at(i)->position == "PF")
            {
                team2->teamPlayers.at(i)->rebounds = 8 + (rand() % 5);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team2->teamPlayers.at(i)->position == "C")
            {
                team2->teamPlayers.at(i)->rebounds = 10 + (rand() % 9);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 6);
            }

            team2->teamPlayers.at(i)->pointsScored = 25 + (rand() % 21);
        }
        else if(team2->teamPlayers.at(i)->overall >=80 && team2->teamPlayers.at(i)->overall <= 90)
        {
            if (team2->teamPlayers.at(i)->position == "PG")                                                       /*rebounds and assists for each position*/
            {
                team2->teamPlayers.at(i)->rebounds = rand() % 12;
                team2->teamPlayers.at(i)->assists = 5 + (rand() % 10);
            }
            else if (team2->teamPlayers.at(i)->position == "SG")
            {
                team2->teamPlayers.at(i)->rebounds = rand() % 5;
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team2->teamPlayers.at(i)->position == "SF")
            {
                team2->teamPlayers.at(i)->rebounds = 5+ (rand() % 5);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 10);
            }
            else if (team2->teamPlayers.at(i)->position == "PF")
            {
                team2->teamPlayers.at(i)->rebounds = 8 + (rand() % 5);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team2->teamPlayers.at(i)->position == "C")
            {
                team2->teamPlayers.at(i)->rebounds = 10 + (rand() % 9);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 6);
            }
            team2->teamPlayers.at(i)->pointsScored =  15 + (rand() % 11);
        }
        else
        {
            if (team2->teamPlayers.at(i)->position == "PG")                                                       /*rebounds and assists for each position*/
            {
                team2->teamPlayers.at(i)->rebounds = rand() % 12;
                team2->teamPlayers.at(i)->assists = 5 + (rand() % 10);
            }
            else if (team2->teamPlayers.at(i)->position == "SG")
            {
                team2->teamPlayers.at(i)->rebounds = rand() % 5;
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team2->teamPlayers.at(i)->position == "SF")
            {
                team2->teamPlayers.at(i)->rebounds = 5+ (rand() % 5);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 10);
            }
            else if (team2->teamPlayers.at(i)->position == "PF")
            {
                team2->teamPlayers.at(i)->rebounds = 8 + (rand() % 5);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 3);
            }
            else if (team2->teamPlayers.at(i)->position == "C")
            {
                team2->teamPlayers.at(i)->rebounds = 10 + (rand() % 9);
                team2->teamPlayers.at(i)->assists = 0 + (rand() % 6);
            }
            team2->teamPlayers.at(i)->pointsScored =  10 + (rand() % 11);
        }
        // cout << team2->teamPlayers.at(i)->first_name << " scored " << team2->teamPlayers.at(i)->pointsScored << " points" << endl;
        team2->score += team2->teamPlayers.at(i)->pointsScored;
    }
    std::cout << team2->teamName << " scored " << team2->score << " points " << endl << endl;


    

      if (team1->score > team2->score)
    {
        cout << team1->teamName + " Win " << endl;
    }
    else if (team2->score > team1->score)
    {
        cout << team2->teamName + " Win " << endl;
    }
    cout << endl;

    gameStats(team1, team2);
    
    for (int i = 0; i < team1->teamPlayers.size();i++) //add players points scored to total points
    {
        team1->teamPlayers.at(i)->totalPoints += team1->teamPlayers.at(i)->pointsScored;
    }

    //reset each player's points to zero after each game
    for (int i = 0; i < team1->teamPlayers.size();i++) 
    {
        team1->teamPlayers.at(i)->pointsScored = 0;
            
    }
    for (int i = 0; i < team2->teamPlayers.size();i++)//reset each player's points to zero after each game
    {
        team2->teamPlayers.at(i)->pointsScored = 0;

    }  
    
    
  }

  void NBA::gameStats(Team* team1, Team* team2)
  /*shows box score*/
  {
    cout << team1->teamName + " Box Score" << endl;
    cout << "------------" << endl;
    cout << "\t \t \tPoints" << " \t\t" << "Assists" <<"\t\tRebounds"  <<endl;
    for (int i = 0; i < team1->teamPlayers.size();i++)
    {
        cout <<  team1->teamPlayers.at(i)->first_name[0] << ". " << team1->teamPlayers.at(i)->last_name << "\t \t " << team1->teamPlayers.at(i)->pointsScored << " \t \t " << team1->teamPlayers.at(i)->assists << "\t\t" << team1->teamPlayers.at(i)->rebounds << endl;
    }
    cout << "\n\n\n\n\n";
    cout << team2->teamName + " Box Score" << endl;
    cout << "------------" << endl;
    cout << "\t \t \tPoints" << " \t\t" << "Assists" <<"\t\tRebounds"  <<endl;
    for (int i = 0; i < team2->teamPlayers.size();i++)
    {
        cout <<  team2->teamPlayers.at(i)->first_name[0] << ". " << team2->teamPlayers.at(i)->last_name << "\t \t " << team2->teamPlayers.at(i)->pointsScored << "\t \t " << team2->teamPlayers.at(i)->assists << "\t\t" << team2->teamPlayers.at(i)->rebounds << endl;
    }
    cout << "\n";
  }

  