/******************************************************************************
Author: Tucker Neikirk
Date: November 12, 2024
Purpose: Run the Pokémon Trainer program. Handles wild encounters, item
         collection, battles, catching Pokémon, and saving the final results.
*******************************************************************************/

#include "Trainer.h"

//wild Pokemon (read in from a file) list size
const int WILD_POKEMON_LIST_SIZE = 25;

//error checking for input of y or n
char charInputCheck()
{
	char input;
		cout << ">> "; cin >> input;
		while(input != 'y' && input != 'n')
		{
			   cout << "Please enter either 'y' or 'n'.\n>> ";
			   cin >> input;
		}
	return input;
}


//given - generate both a wild Pokemon and an item
void generateEncounter(string pokeList[], string &encounteredPokemon, string &pickedUpItem)
{
	srand(time(NULL));
	int randomNum = rand() % WILD_POKEMON_LIST_SIZE;
	encounteredPokemon = pokeList[randomNum];
	
	randomNum = rand() % Trainer::INVENTORY_MAX;
	switch(randomNum)
	{
		case 0: 
			pickedUpItem = "Poke Ball";
			break;
		case 1: 
			pickedUpItem = "Ultra Ball";
			break;
		case 2: 
			pickedUpItem = "Revive";
			break;
		default: 
			pickedUpItem = "Poke Ball";
	}
}

// -------------------------------------------------
// Name: readFile
// Parameters: an array of available wild Pokémon and a string containing the filename
// Returns: none
// Purpose: read the Pokémon in the file into an array for wild Pokémon encounters
// -------------------------------------------------
void readFile(string pokemonList[], const string fileName)
{
    ifstream infile;
    infile.open(fileName);
    
    if (infile.fail())
    {
        cout << "Error: could not open input file\n";
        return;
    }
    
    for (int i = 0; i < WILD_POKEMON_LIST_SIZE; i++)
    {
        infile >> pokemonList[i];
    }
}

int main() 
{
	string wildPokemon = "";
	string item = "";
	bool stillPlaying = true;
	char input = 'a';
	int choice = 0;
	int itemIndex = 0;
	string currPokemon = "";
	string pokemonList[WILD_POKEMON_LIST_SIZE];

	//uncomment each of the tests as you finish writing the code in Trainer.cpp
	cout << "Testing readFile()...\n" << endl;
	readFile(pokemonList, "PokemonList.txt");

	cout << "Testing default constructor..." << endl;
	Trainer player;
	player.printStats();

	cout << "Testing parameterized constructor..." << endl;
	Trainer misty("Misty", "Psyduck");
	misty.printStats();

	cout << "Testing copy constructor..." << endl;
	Trainer misty2(misty);
	misty2.printStats();

	cout << "Testing setName()..." << endl;
	player.setName("Ash");
	player.printStats();

	cout << "Testing addPokemon()..." << endl;
	player.addPokemon("Pikachu");
	player.printStats();

	cout << "Testing addItem()..." << endl;
	player.addItem(Trainer::POKE_BALL);
	player.addItem(Trainer::ULTRA_BALL);
	player.addItem(Trainer::REVIVE);
	player.printStats();

	cout << "Testing generateEncounter()..." << endl;
	generateEncounter(pokemonList, wildPokemon, item);
	cout << "wildPokemon: " << wildPokemon << endl;
	cout << "item: " << item << endl;
	cout << endl;

	cout << "Testing generateEncounter()..." << endl;
	generateEncounter(pokemonList, wildPokemon, item);
	cout << "wildPokemon: " << wildPokemon << endl;
	cout << "item: " << item << endl;
	cout << endl;

	cout << "Game loop starting..." << endl;
	
	while(stillPlaying)
	{
		//generate an encounter to get the random item and the wild Pokemon
		generateEncounter(pokemonList, wildPokemon, item);
		
		//fulfill item encounter
        cout << "You found a(n) " << item << ". Do you want to keep it? (y/n)" << endl; // ask user if they want to keep the item
        
        // if-else statements to check index of the item that the trainer has found
		if (item == "Poke Ball") {
            itemIndex = Trainer::POKE_BALL;
        } 
        else if (item == "Ultra Ball") {
            itemIndex = Trainer::ULTRA_BALL;
        } 
        else if (item == "Revive") {
            itemIndex = Trainer::REVIVE;
        }
        
        input = charInputCheck();
        
        if (input == 'y') // if user says yes
        {
            if (player.addItem(itemIndex) == true) // add item if they have room
            {
                cout << "Successfully added " << item << " to your inventory!" << endl;
            }
            else // otherwise, let them know they don't have room
            {
                cout << "You don't have enough room for that type of item." << endl;
            }
        }
        else if (input == 'n') // if user says no
        {
            cout << "You put the " << item << " back." << endl;
        }

		//print stats
		player.printStats();
		
		//generate steps
		int numSteps = rand() % 10 + 1;
		for (int i = 1; i <= numSteps; i++)
		{ 
			if(numSteps == 1)
				cout << "You've taken 1 step.\n";
			else
				cout << "You've taken " << i << " steps." << endl;
		}

		//fulfill Pokemon encounter
		cout << "You've encountered a(n) " << wildPokemon << "!" << endl; // user encounters wild pokemon
		cout << "Do you want to fight it?" << endl; // ask user if they want to fight the wild pokemon
		
		input = charInputCheck(); // error check user's input
		
		if (input == 'y') // if user wants to fight
        {
            
            // display the pokemon in user's trainer class and have them pick one
            cout << "Which Pokemon do you want to use?" << endl;
            for (int i = 0; i < player.getNumPokemon(); i++)
            {
                cout << i + 1 << ") " << player.getPokemon(i) << endl;
            }
            
            do { // do-while loop for error checking user input
                cout << ">> ";
                cin >> choice;
                if (choice < 1 || choice > player.getNumPokemon())
                {
                    cout << "Please enter a valid number." << endl;
                }
            } while (choice < 1 || choice > player.getNumPokemon());
            
            int win = rand() % 2; // generate random number for results of battle
            
            if (win == 0) // user loses
            {
                // user's pokemon faints and the wild one runs away
                cout << "Oh no! " << player.getPokemon(choice - 1) << " fainted and the " << wildPokemon << " escaped! "; 
                
                // check if user has revives
                if (player.getItemAmount(Trainer::REVIVE) == 0) // if user doesn't have revives
                {
                    // let user know they're out of revives and remove chosen pokemon from inventory
                    cout << endl << "Looks like you're out of revives. " << player.getPokemon(choice - 1) << " was transferred to Professor Oak." << endl;
                    player.removePokemon(choice - 1);
                }
                else if (player.getItemAmount(Trainer::REVIVE) != 0) // if user does have revives
                {
                    // ask user if they want to use a revive
                    cout << "Use a Revive? (y/n)" << endl; 
                    input = charInputCheck();
                    
                    // if-else statements for user input
                    if (input == 'y') // if user says yes
                    {
                        // use function to update inventory and display that pokemon was healed
                        player.useItem(Trainer::REVIVE); 
                        cout << player.getPokemon(choice - 1) << " was healed. " << player.getItemAmount(Trainer::REVIVE) << " revive(s) remaining." << endl; 
                    }
                    else if (input == 'n') // if user says no
                    {
                        // remove pokemon from inventory using function
                        cout << player.getPokemon(choice - 1) << " was transferred to Professor Oak." << endl;
                        player.removePokemon(choice - 1);
                    }
                }
                
            }
            else if (win == 1) // user wins
            {
                // give user the option of catching the wild pokemon
                cout << "You and " << player.getPokemon(choice - 1) << " won! Do you want to catch the " << wildPokemon << "?" << endl;
                input = charInputCheck();
                
                if (input == 'y') // if user says yes
                {
                    // check if user's inventory is maxed out
                    if (player.hasPokemonSpace() == true) // if user has inventory space
                    {
                        // make sure user has poke balls or ultra balls on hand
                        if (player.getItemAmount(Trainer::POKE_BALL) > 0 || player.getItemAmount(Trainer::ULTRA_BALL) > 0) // if user has poke balls or ultra balls
                        {
                            // let user choose what they want to use
                            cout << "What ball do you want to use?" << endl;
                            if (player.getItemAmount(Trainer::POKE_BALL) > 0)
                            {
                                cout << "1) Poke Ball (" << player.getItemAmount(Trainer::POKE_BALL) << " remaining)" << endl;
                            }
                            if (player.getItemAmount(Trainer::ULTRA_BALL) > 0)
                            {
                                cout << "2) Ultra Ball (" << player.getItemAmount(Trainer::ULTRA_BALL) << " remaining)" << endl;
                            }
                            
                            do { // do-while loop to error check user input
                                cout << ">> ";
                                cin >> choice;
                                if ((choice == 1 && player.getItemAmount(Trainer::POKE_BALL) == 0) || (choice == 2 && player.getItemAmount(Trainer::ULTRA_BALL) == 0)) 
                                {
                                    cout << "Invalid choice. Please select a valid number." << endl;
                                    choice = 0; 
                                }
                                else if (choice != 1 && choice != 2) 
                                {
                                    cout << "Invalid choice. Please select a valid number." << endl;
                                    choice = 0;
                                }
                            } while (choice != 1 && choice != 2);
                            
                            // user has 100% chance of catching the wild pokemon
                            cout << "You caught " << wildPokemon << "!" << endl;
                            player.useItem(choice - 1); // update item inventory using function
                            player.addPokemon(wildPokemon); // update pokemon inventory using function

                        } 
                        else // if user doesn't have poke balls or ultra balls
                        {
                            cout << "You don't have any balls to catch the wild Pokémon." << endl; // display a message
                        }
                    }
                    else if (player.hasPokemonSpace() == false) // if user does not have inventory space
                    {
                        cout << "Looks like you don't have enough space in your inventory." << endl; // display a message letting user know they have no space
                    }
                }
                else if (input == 'n') // otherwise, leave wild pokemon and let user continue
                {
                    cout << "You leave the wild " << wildPokemon << " and continue on your way." << endl;
                }
            }
        }
        else if (input == 'n') // if user does not want to fight
        {
            cout << "You chose to run away." << endl; // have user run away
        }

		//check if user can still play, and then if they want to still play
		// if the user has no pokemon, they can't keep playing
		if (player.getNumPokemon() == 0) // if user has no pokemon left
		{
		    // display message and set stillPlaying to false
		    cout << "Looks like you have no Pokémon remaining." << endl;
		    stillPlaying = false;
		}
		
		//else, see if the user wants to keep playing
		else // if user has pokemon left
		{
			//note that these 4 lines will likely be inside of an if/else block that is detailed 
			//at the end of "2. Description" in the homework
			cout << "Do you want to keep playing?" << endl; // ask user if they want to keep playing
			input = charInputCheck();

			if (input == 'n') // if user says no
				stillPlaying = false; // set stillPlaying to false
		}
		
	}
	//create a unique filename with number of seconds passed since Jan 1, 1970 so multiple
	//runs of the program will save to different files
	string outputFilename = "player-";
	outputFilename.append(std::to_string(time(0)));
	outputFilename.append(".txt");

	//save to file
	player.writeFile(outputFilename);
	
	cout << "Your player information has been saved to " << outputFilename << ". Until next time!\n";
	return 0;
}
