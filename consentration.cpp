// Concentration (macthing card) game (Donovan Jones-Myers & Malone Hemsley)
/*
int main()       // Program start
{
1.DO   				 // (Do while to repeat game)
	2.intialize_board (board, 4)
	3.Show_board (board, 4)
	4.make_cards (card, 4)
	5.shuffle_deck (card_content, 4)
	6.SET points_left = 26

	7.PRINT "Enter the number of players (2-4): "
	8.GET num_players
	9.SET player_score[num_players] = {0}
	10.SET GameOver = false
	11.DO         		   //Do while to repeat game play until all of the cards are gone.
		12.SET player = 1
		13.While (player <= num_players && !(GameOver))
			14.SET player_score[player -1] = player_score[player -1] + player_turn (player, board, card, 4) //points added
			15.display_scores (player_score, num_players)
			16.SET points_left = points_left - player_score[player -1] // take from remaining points
			17.IF (points_left == 0)       // check if cards are all matched
				18.SET GameOver = true
			19.SET player = player + 1
		20.END WHILE
	21.WHILE (!(GameOver) )

	22.display_scores (player_score, num_players)  //Display scores
	23.Winner (player_score, num_players) // display the winner(s)

	24.PRINT "Would you like to play again?(y/n) "
	25.GET answer
	26.WHILE (answer == y)

	27.STOP
}
*/

#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

struct Card
{
	string rank;
	char suit;
};
const int SIZE = 52;

// prototype function
void make_cards(Card [], int);
void card_swap(Card&, Card& );
void shuffle_deck(Card [], int);
void Show_board(const string [], int);
void intialize_board(string [], int);
int player_turn(int, string [], const Card [], int, int);
void display_scores(const vector<int>&, int);
void Winner(const vector<int>&, int);

int main()       // Program start
{
	Card deck[SIZE];										// variable declarations
	string card_slot[SIZE];									//
	int points_left, num_players, winner, points_earned;	//
	bool GameOver;											//
	char answer;											//

	do  				 // (Do while to repeat game)
	{
		cout << "How many players?(2 - 4) ";
		cin >> num_players;
		while (num_players < 2 || num_players > 4) // input validation
		{
			cout << "Error, invalid input.\n";
			cin >> num_players;
		}
		intialize_board(card_slot, SIZE);   // fucntion call
		Show_board(card_slot, SIZE);   // fucntion call
		make_cards(deck, SIZE);   // fucntion call
		shuffle_deck(deck, SIZE);   // fucntion call
		
		points_left = 26;
		vector<int> player_score(num_players, 0);
		GameOver = false;   // flag
		
		do        		   //Do while to repeat game play until all of the cards are gone.
		{
			for (int player = 1; player <= num_players && !(GameOver); player++)
			{
				points_earned = player_turn(player, card_slot, deck, SIZE, points_left);
				player_score[player - 1] += points_earned; //points added after players turns
				display_scores(player_score, num_players);
				Show_board(card_slot, SIZE);	// Function call and showing the cards flipped back over (hidden)
				points_left -= points_earned; // take from remaining points
				if (points_left == 0)       // check if cards are all matched
					GameOver = true;
			}
		} while (!(GameOver));
		
		display_scores(player_score, num_players);  //Display scores
		Winner(player_score, num_players); // function call displays the winner(s)(if tie occurs)
		
		cout << "Would you like to play again ? (y/n) ";
		cin >> answer;
		while (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N') // input validation
		{
			cout << "Error, invalid input.\n";    // error message
			cin >> answer;
		}
		
	} while (answer == 'y' || answer == 'Y');
	
	return (0);									// STOP
}
// Function make_cards returns nothings and assigns values (A,2-10,J Q,K & C,S,H,D) to the rank and suit to each card. It uses a Card variable array and int variable as parameters
void make_cards (Card deck[], int Size)
{
	for (int i = 0, rank = 1; i < Size; i++, rank++)
	{
		if (rank == 14)  // value loops between 1-13
			rank = 1;

		if (rank == 1)
		{
			deck[i].rank.append("A");
			deck[i].rank.append(" ");
		}
		else if (rank > 1 && rank < 10)
		{
			deck[i].rank = to_string(rank);
			deck[i].rank.append(" ");
		}
		else if (rank == 10)
			deck[i].rank = to_string(rank);
		else if (rank == 11)
		{
			deck[i].rank.append("J");
			deck[i].rank.append(" ");
		}
		else if (rank == 12)
		{
			deck[i].rank.append("Q");
			deck[i].rank.append(" ");
		}
		else if (rank == 13)
		{
			deck[i].rank.append("K");
			deck[i].rank.append(" ");
		}

		if (i < 13)
			deck[i].suit = 'S';
		else if (i < 26)
			deck[i].suit = 'C';
		else if (i < 39)
			deck[i].suit = 'H';
		else if (i < 52)
			deck[i].suit = 'D';
	}
}	 // Go back to main

// Function card_swap returns nothings and swaps the postions/values of two Card variables's using two Card variables as parameters
void card_swap(Card& one, Card& two)
{
	Card temp = one;				// variable for swaping the two values
	one = two;
	two = temp;
}	 // Go back to caller

// Function shuffle_deck returns nothings and swaps a random card with the first card 100 times to shuffle the deck of cards.
// It uses a Card variable array and int variable as parameters
void shuffle_deck(Card deck[], int Size)
{
	random_device randEngine; // Random number engine name
	uniform_int_distribution<int> randomInt(1, 51); // random numbers 1-51
	for (int i = 0; i < 200; i++)
	{
		int num = randomInt(randEngine);
		card_swap(deck[0], deck[num]);
	}
}	 // Go back to main

// Function intialize_board returns nothings and assigns the string value "[?]" to the "back" of the deck of cards.
// It uses a string variable array and int variable as parameters
void intialize_board(string location[], int SIZE)  // intialize the board
{
	for (int i = 0; i < SIZE; i++)
		location[i] = "[?]";
}	 // Go back to main

// Function Show_board returns nothings and displays the outer grid (1-13 and A-D) and cards with whatever value is in the string array.
// It uses a string variable array and int variable as parameters
void Show_board(const string location[], int SIZE)  // show the board
{
	system("cls");
	
	int num_location = 1;			// variables for outer grid
	char letter_location = 'A';		//

	for (int rows = 0; rows < 2; rows++)							// Top of outer grid
	{																// 1-13
		for (int cols = 0; cols < 13; cols++, num_location++)		//
		{															//
			if (cols == 0)											//
				cout << "  ";										//
			if (rows == 0 && num_location < 10)						//
				cout << "  " << num_location << "  " << "  ";		//
			else if (rows == 0 && num_location >= 10)				//
				cout << "  " << num_location << " " << "  ";		//
			else													//
				cout << " --- " << "  ";							//
		}															//
		cout << endl;												//
	}																//
	
	int index = 0; 
	for (int rows = 0; rows < 16; rows++)
	{ 
		for (int cols = 0; cols < 13; cols++)
		{
			if (rows == 2 && cols == 0 || (rows - 2) % 4 == 0 && cols == 0)			// left of outer grid
				cout << letter_location++ << "|";									// A-D
			else if (rows != 2 && cols == 0 || (rows - 2) % 4 != 0 && cols == 0)	//
				cout << "  ";														//
			
			if (rows == 0 || rows % 4 == 0)								// Game cards
				cout << " ___ " << "  ";								//
			else if (rows == 1 || (rows - 1) % 4 == 0)					//
				cout << "|   |" << "  ";								//
			else if (rows == 2 || (rows - 2) % 4 == 0)					//
				cout << "|" << location[index++] <<  "|" << "  ";		//
			else if (rows == 3 || (rows - 3) % 4 == 0)					//
				cout << "|___|" << "  ";								//
		}
		cout << endl;    // new line
	}
}  // Go back to caller

// Function display_scores returns nothings and displays the scores of each player.
// It uses an int vector and int variable as parameters
void display_scores(const vector<int> &scores, int num_players)
{
	cout << endl;
	for (int rows = 0; rows < 3; rows++)
	{
		for (int player = 1; player <= num_players; player++)
		{
			if (rows == 0)
				cout << "Player " << player;
			else if (rows == 1 && player == 1)
				for (int count = 0; count < (num_players * 8 + (num_players - 1)); count++)
					cout << "-";
			else if (rows == 2)
				cout << left << setw(8) << scores[player - 1];
			if (player != num_players && rows != 1)
				cout << "|";
		}
		cout << endl;
	}
	cout << "(press Enter to continue)\n";
	cin.get();
} // Go back to main

// Function Winner returns nothings and displays the winner(s) of each game. Also a record of of each winner is kept for continued play.
// It uses an int vector and int variable as parameters
void Winner(const vector<int> &scores, int num_players)
{
	vector<int> winners;			// stores which players win one game
	int highest_score;
	static int GamesWon[4];				// keeps win records saved between function calls

	highest_score = scores[0];  // starting with player one
	for (int i = 0; i < num_players; i++)  // finding the the highest score value
	{
		if (scores[i] > highest_score)
		{
			highest_score = scores[i];
		}
	}
	for (int i = 0; i < num_players; i++)  // determining the winner(s) -- accounts for first place ties by recording all players with the "highest_score" value
	{
		if (scores[i] == highest_score)
		{
			winners.push_back(i + 1);
		}
	}
	if (winners.size() == 1) // one winner case
		cout << "Player " << winners[0] << " is the winner!\n";
	else					 // multi-winner case
	{
		cout << "Tie. Players ";
		for (int i = 0; i < winners.size(); i++)
		{
			cout << winners[i] << " ";
			if (i < winners.size() - 1)
				cout << "& ";
		}
		cout << "are the winners!\n";
	}
	// Keeping track of the winners
	for (int i = 0; i < winners.size(); i++)  // counting the winners' score count
	{
		if (winners[i] == 1)
			GamesWon[0] += 1;
		else if (winners[i] == 2)
			GamesWon[1] += 1;
		else if (winners[i] == 3)
			GamesWon[2] += 1;
		else if (winners[i] == 4)
			GamesWon[3] += 1;
	}
	cout << "\nGames Won\n";									// displaying the number of wins based on the number of players
	for (int rows = 0; rows < 3; rows++)
	{
		for (int player = 1; player <= num_players; player++)
		{
			if (rows == 0)
				cout << "Player " << player;
			else if (rows == 1 && player == 1)
				for (int count = 0; count < (num_players * 8 + (num_players - 1)); count++)
					cout << "-";
			else if (rows == 2)
				cout << left << setw(8) << GamesWon[player - 1];
			if (player != num_players && rows != 1)
				cout << "|";
		}
		cout << endl;
	}
}   // Go back to main

// Function Winner returns the accumulated player score (an int) and excutes the gameplay. It asks for the first the second card.
// If a match, then it says and loops. otherwise, the function tells you and stops.
// It uses an int vector and int variable as parameters
int player_turn(int player, string card_position[], const Card deck[], int SIZE, int remainingPoints)
{
	int selection_index, temp_int, accumlated_points = 0;					// Variable declarition
	string user_selection, selection_pt1, selection_pt2, card1, card2;		//
	int card1_index, card2_index;											//
	static int picked_cards[52];											//
	bool matched;				// flag
	do
	{
		matched = false;
		cout << "Player " << player << ", select your first card:(i.e. A1 or D13) ";  // first card selection
		do
		{
			do
			{
				cin >> user_selection;
				selection_pt1 = user_selection[0];						// breakdown input 
				if (user_selection.length() == 2)
				{
					selection_pt2 = user_selection[1];						// breakdown input to convert into an interger to be a array index later
					while (selection_pt2 != "1" && selection_pt2 != "2" && selection_pt2 != "3" && selection_pt2 != "4" && selection_pt2 != "5" && selection_pt2 != "6" && selection_pt2 != "7" && selection_pt2 != "8" && selection_pt2 != "9") // input validation
					{
						cout << "Error, invalid input.\n";
						cin >> user_selection;
						selection_pt2 = user_selection[1];    // restablishing values
						selection_pt1 = user_selection[0];
					}
					temp_int = stoi(selection_pt2);
				}
				else if (user_selection.length() == 3)
				{
					selection_pt2 = user_selection[1];
					selection_pt2.push_back(user_selection[2]);		// breakdown input to convert into an interger to be a array index later
					while (selection_pt2 != "10" && selection_pt2 != "11" && selection_pt2 != "12" && selection_pt2 != "13") // input validation
					{
						cout << "Error, invalid input.\n";
						cin >> user_selection;
						selection_pt2 = user_selection[1];    // restablishing values
						selection_pt2.push_back(user_selection[2]);
						selection_pt1 = user_selection[0];
					}
					temp_int = stoi(selection_pt2);
				}
				else
					cout << "Error, invalid input.\n";    // error message
				if (selection_pt1 != "A" && selection_pt1 != "a" && selection_pt1 != "B" && selection_pt1 != "b" && selection_pt1 != "C" && selection_pt1 != "c" && selection_pt1 != "D" && selection_pt1 != "d")
					cout << "Invalid input\n";			// error meassage
			} while (user_selection.length() != 3 && user_selection.length() != 2 || selection_pt1 != "A" && selection_pt1 != "a" && selection_pt1 != "B" && selection_pt1 != "b" && selection_pt1 != "C" && selection_pt1 != "c" && selection_pt1 != "D" && selection_pt1 != "d"); // input validation

			if (selection_pt1 == "A" || selection_pt1 == "a")				// convert input into an interger to be a array index later
				selection_index = 0;										//
			else if (selection_pt1 == "B" || selection_pt1 == "b")			//
				selection_index = 13;										//
			else if (selection_pt1 == "C" || selection_pt1 == "c")			//
				selection_index = 26;										//
			else if (selection_pt1 == "D" || selection_pt1 == "d")			//
				selection_index = 39;										//
			selection_index += (temp_int - 1);								//
			if (picked_cards[selection_index] != 0)
				cout << "Error, card not availble for selction -- Pick again\n";
		} while (picked_cards[selection_index] != 0);
		card1_index = selection_index;
		picked_cards[card1_index] = 1;

		card1 = deck[selection_index].rank;   // variablie to compare values
		card_position[selection_index] = deck[selection_index].rank;		// variable to show flipped card
		card_position[selection_index].push_back(deck[selection_index].suit);
		Show_board(card_position, SIZE);	// Function call & and showing flipped card
		
		cout << "Player " << player << ", select your second card:(i.e. A1 or D13) ";  // second card selection
		do
		{
			do
			{
				cin >> user_selection;
				selection_pt1 = user_selection[0];						// breakdown input 
				if (user_selection.length() == 2)
				{
					selection_pt2 = user_selection[1];						// breakdown input to convert into an interger to be a array index later (for single didgit numbers)
					while (selection_pt2 != "1" && selection_pt2 != "2" && selection_pt2 != "3" && selection_pt2 != "4" && selection_pt2 != "5" && selection_pt2 != "6" && selection_pt2 != "7" && selection_pt2 != "8" && selection_pt2 != "9") // input validation
					{
						cout << "Error, invalid input.\n";
						cin >> user_selection;
						selection_pt2 = user_selection[1];    // restablishing values
						selection_pt1 = user_selection[0];
					}
					temp_int = stoi(selection_pt2);
				}
				else if (user_selection.length() == 3)
				{
					selection_pt2 = user_selection[1];
					selection_pt2.push_back(user_selection[2]);		// breakdown input to convert into an interger to be a array index later (for double didgit numbers)
					while (selection_pt2 != "10" && selection_pt2 != "11" && selection_pt2 != "12" && selection_pt2 != "13") // input validation
					{
						cout << "Error, invalid input.\n";
						cin >> user_selection;
						selection_pt2 = user_selection[1];    // restablishing values
						selection_pt2.push_back(user_selection[2]);
						selection_pt1 = user_selection[0];
					}
					temp_int = stoi(selection_pt2);
				}
				else
					cout << "Error, invalid input.\n";    // error message
				if (selection_pt1 != "A" && selection_pt1 != "a" && selection_pt1 != "B" && selection_pt1 != "b" && selection_pt1 != "C" && selection_pt1 != "c" && selection_pt1 != "D" && selection_pt1 != "d")
					cout << "Invalid input\n";			// error meassage
			} while (user_selection.length() != 3 && user_selection.length() != 2 || selection_pt1 != "A" && selection_pt1 != "a" && selection_pt1 != "B" && selection_pt1 != "b" && selection_pt1 != "C" && selection_pt1 != "c" && selection_pt1 != "D" && selection_pt1 != "d"); // input validation

			if (selection_pt1 == "A" || selection_pt1 == "a")				// convert input into an interger to be a array index later
				selection_index = 0;										//
			else if (selection_pt1 == "B" || selection_pt1 == "b")			//
				selection_index = 13;										//
			else if (selection_pt1 == "C" || selection_pt1 == "c")			//
				selection_index = 26;										//
			else if (selection_pt1 == "D" || selection_pt1 == "d")			//
				selection_index = 39;										//
			selection_index += (temp_int - 1);								//
			if (picked_cards[selection_index] != 0)
				cout << "Error, card not availble for selction -- Pick again\n";
		} while (picked_cards[selection_index] != 0);
		card2_index = selection_index;
		picked_cards[card2_index] = 1;

		card2 = deck[selection_index].rank;		// variablie to compare values
		card_position[selection_index] = deck[selection_index].rank;		// variable to show flipped card
		card_position[selection_index].push_back(deck[selection_index].suit);
		Show_board(card_position, SIZE);	// Function call and showing flipped card

		if (card1 == card2)			// match option
		{
			remainingPoints--; 

			if (remainingPoints != 0)
				cout << "You got a match! Keep going (press Enter to continue)";
			else
				cout << "You got the last match! (press Enter to continue)";
			cout << endl;
			accumlated_points++;
			matched = true;

			card_position[card1_index] = "   ";
			card_position[card2_index] = "   ";
			cin.ignore();
			cin.get();
			Show_board(card_position, SIZE);	// Function call and showing matched cards taking off the board
		}
		else
		{
			cout << "Not a matched. Better luck next time (press Enter to continue).\n";  // no match option

			card_position[card1_index] = "[?]";
			card_position[card2_index] = "[?]";
			picked_cards[card1_index] = 0;
			picked_cards[card2_index] = 0;
			cin.ignore();
			cin.get();
		}

	} while (remainingPoints != 0 && matched == true);

	return accumlated_points;  // Go back to main
}
