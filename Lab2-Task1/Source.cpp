#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <time.h>

using namespace std;

class bballPlayer {
	private:
		string name;
		int shotsTaken;
		int shotsMade;
		int passesAttempted;
		int passesMade;

	public:
		bballPlayer(string, int, int, int, int);
		void setName(string);
		void setShotsTaken(int);
		void setShotsMade(int);
		void setPassesAttempted(int);
		void setPassesMade(int);

		string getName() const {
			return name;
		}
		int getShotsTaken() const {
			return shotsTaken;
		}
		int getShotsMade() {
			return shotsMade;
		}
		int getPassesAttempted() const {
			return passesAttempted;
		}
		int getPassesMade() const {
			return passesMade;
		}

		bool PassBall();
		int TakeShot(int);
		void ShowStats();
};

bballPlayer::bballPlayer(string n, int sm, int st, int pm, int pa) {
	name = n;
	shotsMade = sm;
	shotsTaken = st;
	passesMade = pm;
	passesAttempted = pa;
}

void bballPlayer::setName(string n) {
	name = n;
}

void bballPlayer::setShotsMade(int sm) {
	shotsMade = sm;
}

void bballPlayer::setShotsTaken(int st) {
	shotsTaken = st;
}

void bballPlayer::setPassesMade(int pm) {
	passesMade = pm;
}

void bballPlayer::setPassesAttempted(int pt) {
	passesAttempted = pt;
}

bool bballPlayer::PassBall() {
	int randNum = rand() % 100 + 1;
	passesAttempted++;
	double passPercent = static_cast<double>(passesMade) / passesAttempted;
	
	if (randNum > passPercent) {
		return false; // Turnover
	}
	else {
		passesMade++;
		return true; // Pass completed
	}
}

int bballPlayer::TakeShot(int shotType) {
	int randNum;
	int pointsScored = 0;
	shotsTaken++;
	double shootingPercent = static_cast<double>(shotsMade) / shotsTaken;

	if (shotType == 1) {
		randNum = rand() % 80 + 1;
		if (randNum > shootingPercent) {
			shotsMade++;
			pointsScored = shotType;
		}
	}
	else if (shotType == 2) {
		randNum = rand() % 100 + 1;
		if (randNum > shootingPercent) {
			shotsMade++;
			pointsScored = shotType;
		}
	}
	else if (shotType == 3) {
		randNum = rand() % 120 + 1;
		if (randNum > shootingPercent) {
			shotsMade++;
			pointsScored = shotType;
		}
	}
	else {
		std::cout << "Invalid input";
		exit(EXIT_FAILURE);
	}

	return pointsScored;
}

void bballPlayer::ShowStats() {
	std::cout << "Stats - ";
	std::cout << "Shots Made:" << shotsMade << " ";
	std::cout << "Shots Taken:" << shotsTaken << " ";
	std::cout << "Passes Made:" << passesMade << " ";
	std::cout << "Passes Attempted:" << passesAttempted << endl;
}

int team1ChoosePlayer() {	// Chooses random player on team 1
	int nextPossession = rand() % 5 + 0;
	for (int i = 0; i < 5; ++i) {
		if (nextPossession == i) {
			return i;
		}
	}
}

void Menu() {
	std::cout << "Choose an option: " << endl;
	std::cout << "\tEnter 1 to shoot: " << endl;
	std::cout << "\tEnter 2 to pass: " << endl;
	std::cout << "\tEnter 3 to show Scoreboard: " << endl;
	std::cout << "\tEnter 4 to show Stats: " << endl;
	std::cout << "Input: ";
}

void ShowScoreBoard(int possessions, int playerScore, int cpuScore) {
	std::cout << "Player:" << playerScore << " - CPU:" << cpuScore << " Possessions:" << possessions << endl;
	std::cout << endl;
}

int main() {

	srand(time(NULL));	// Used so we don't get similiar random variables everytime we compile

	bballPlayer team1[] = {	// Initializes player values
		bballPlayer("P1", 8, 10, 5, 7),
		bballPlayer("P2", 6, 8, 1, 7),
		bballPlayer("P3", 1, 3, 2, 7),
		bballPlayer("P4", 2, 4, 8, 9),
		bballPlayer("P5", 4, 8, 5, 6)
	};

	int nextPossession;
	int shotProbability;
	int typeShot;
	int cpuShotType;
	int totalPossessions = 40;
	int Player = 0, CPU = 0;
	int currentPlayer = 0;
	bool team1HasBall = true;	// User team has first possession
	bool findRandPlayer = true;
	int input;

	while (totalPossessions > 0) {
		while (team1HasBall) {
			if (findRandPlayer) {	// If we need to find a random player on the team
				currentPlayer = team1ChoosePlayer();
			}
			std::cout << team1[currentPlayer].getName() << " has the ball\t" << endl;
			team1[currentPlayer].ShowStats();
			Menu();
			cin >> input;
			std::cout << endl;
			if (input == 1) {	// Team 1 shoots the ball
				std::cout << "Number of points(1, 2, or 3): ";
				cin >> typeShot;
				std::cout << team1[currentPlayer].getName() << " shoots a " << typeShot << endl;
				if (team1[currentPlayer].TakeShot(typeShot) == 0) {	// If the shot is missed
					std::cout << team1[currentPlayer].getName() << " misses" << endl;
					nextPossession = rand() % 10 + 1;	// Finds who gets the rebound
					if (nextPossession % 2 == 0) {		// Team 1 keeps ball
						currentPlayer = team1ChoosePlayer();	// Find random player on the team
						std::cout << team1[currentPlayer].getName() << " got the rebound" << endl;
						std::cout << endl;
						team1HasBall = true;
						break;
					}
					else {	// Team 1 loses ball
						std::cout << "Turnover" << endl;
						std::cout << endl;
						totalPossessions--;
						team1HasBall = false;
						break;
					}
				}
				else {
					Player += typeShot;	// Team 1 scores
					std::cout << team1[currentPlayer].getName() << " makes a " << typeShot << endl;
					std::cout << endl;
					totalPossessions--;
					team1HasBall = false;
					break;
				}
			}
			else if (input == 2) {	// Team 1 Passes
				string passToPlayer;
				int newPlayer = 0;
				cout << "Possible players to pass to: ";
				for (int i = 0; i < 5; ++i) {	// Lists possible players to pass to
					if (team1[i].getName() != team1[currentPlayer].getName()) {
						cout << team1[i].getName() << ", ";
					}
				}
				std::cout << endl;
				std::cout << "Name of player to pass to: " << endl;
				std::cin >> passToPlayer;
				if (passToPlayer == team1[currentPlayer].getName()) {	// Returns error if name is equal to player with the ball
					std::cout << "Invalid input";
					exit(EXIT_FAILURE);
				}
				for (int i = 0; i < 5; ++i) {	// Finds player on team to pass to
					if (team1[i].getName() == passToPlayer) {
						team1[i].PassBall();
						newPlayer = i;
						break;
					}
					if (i == 4) {	// Player has not been found on the team
						std::cout << "Invalid input";
						exit(EXIT_FAILURE);
					}
				}

				if (team1[currentPlayer].PassBall()) {	// If team 1 completes pass
					std::cout << team1[currentPlayer].getName() << " passes the ball to " << team1[newPlayer].getName() << endl;
					std::cout << endl;
					currentPlayer = newPlayer;
					findRandPlayer = false;
					team1HasBall = true;
					break;
				}
				else {	// Pass is not completed
					std::cout << "Turnover" << endl;
					std::cout << endl;
					team1HasBall = false;
					totalPossessions--;
					break;
				}
			}
			else if (input == 3) {	// Shows scoreboard
				ShowScoreBoard(totalPossessions, Player, CPU);
				findRandPlayer = false;
				team1HasBall = true;
				break;
			}
			else if (input == 4) {	// Shows stats for player with ball
				for (int i = 0; i < 5; ++i) {
					std::cout << team1[i].getName() << ": ";
					team1[i].ShowStats();
				}
				std::cout << endl;
				findRandPlayer = false;
				team1HasBall = true;
				break;
			}
			else {	// If the input is invalid
				std::cout << "Invalid input";
				exit(EXIT_FAILURE);
			}
		}
		while (!team1HasBall) {

			shotProbability = rand() % 10 + 1;	// 60% chance of making shot
			cpuShotType = rand() % 3 + 1;	// Shoots either a 1, 2, or 3
			std::cout << "CPU shoots a " << cpuShotType << endl;
			if (shotProbability > 6) {
				std::cout << "CPU misses" << endl;
				nextPossession = rand() % 10 + 1;	// Finds who gets the rebound
				if (nextPossession % 2 == 0) {	// Team 1 keeps ball
					currentPlayer = team1ChoosePlayer();	// Find random player on the team
					std::cout << "CPU got the rebound" << endl;
					std::cout << endl;
					team1HasBall = false;
					break;
				}
				else {	// Team 1 loses ball
					std::cout << "Turnover" << endl;
					std::cout << endl;
					totalPossessions--;
					team1HasBall = true;
					findRandPlayer = true;
					break;
				}
			}
			else {	// CPU makes the shot
				std::cout << "CPU makes a " << cpuShotType << endl;
				std::cout << endl;
				CPU += cpuShotType;
				totalPossessions--;
				team1HasBall = true;
				findRandPlayer = true;
			}
		}
	}
	ShowScoreBoard(totalPossessions, Player, CPU);	// Shows final score

	if (CPU > Player) {
		std::cout << "CPU Wins!" << endl;
	}
	else if (Player > CPU) {
		std::cout << "Player Wins!" << endl;
	}
	return 0;
}