#ifndef PLAYERS_H
#define PLAYERS_H
#include <iostream>
#include <vector>
#include <string>

class Player 
{
    private:
        std::string hometown;
        int salary;



    public:
       Player(std::string first_name, std::string last_name, int jerseyNumber, std::string team, std::string position, int overall);
       std::string first_name;
       std::string last_name;
       int jerseyNumber;
       std::string team;
       std::string position;
       std::string getHome();
       void setHome(std::string hometown);
       void setSalary(int salary);
       int getSalary();
       int pointsScored;
       int assists;
       int rebounds;
       int overall;
       double avgPoints = 0;
       double totalPoints;

     
       
        
};
#endif