#include "players.h"

//constructor
Player::Player(std::string first_name, std::string last_name, int jerseyNumber, std::string team,std::string position, int overall)
{
    this->first_name = first_name;
    this->last_name = last_name;
    this->jerseyNumber = jerseyNumber;
    this->team = team;
    this->position = position;
    this->overall = overall;
}

std::string Player::getHome()
{
    return hometown;
}
void Player::setHome(std::string hometown)
{
    this->hometown = hometown;
}
void Player::setSalary(int salary)
{
    this->salary = salary;
}
int Player::getSalary()
{
    return salary;
}

