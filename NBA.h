#include "players.h"
#include "teams.h"


class NBA
{
    private:
        static int player_count;
        static int team_count;
        std::vector <Player*> players;
        std::vector <Team*> teams;

    public:
        NBA();
        ~NBA();
        int getPlayerCount();
        int getTeamCount();
        void addTeam(std::string location, std::string teamName);
        void addPlayer(std::string first_name, std::string last_name, int jerseyNumber, std::string team, std::string position, int overall);
        std::vector<Team*> getTeams();
        Team* findTeam(std::string team);
        std::vector<Player*> getPlayers();
        void loadTeamsFromFile(std::string filename);
        void loadPlayersFromFile(std::string filename);
        void simSeason(Team* team1); //sim season with user team
        void simSeason(); //sim seeason with all teams as CPU
        void playGame(Team* team1, Team* team2);
        void gameStats(Team* team1, Team* team2);

};
