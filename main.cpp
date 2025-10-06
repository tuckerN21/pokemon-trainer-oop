/******************************************************************************
Author: Tucker Neikirk
Date: November 12, 2024
Purpose: Run the Pokémon Trainer program. Handles wild encounters, item
         collection, battles, catching Pokémon, and saving the final results.
*******************************************************************************/

#include "Trainer.h"

// Wild Pokemon (read in from a file) list size
const int WILD_POKEMON_LIST_SIZE = 25;

// Error checking for input of y or n
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


// Generate both a wild Pokemon and an item
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
		// Generate an encounter to get the random item and the wild Pokemon
		generateEncounter(pokemonList, wildPokemon, item);
		
		// Fulfill item encounter
        cout << "You found a(n) " << item << ". Do you want to keep it? (y/n)" << endl; // Ask user if they want to keep the item
        
        // If-else statements to check index of the item that the trainer has found
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
        
        if (input == 'y') // If user says yes
        {
            if (player.addItem(itemIndex) == true) // Add item if they have room
            {
                cout << "Successfully added " << item << " to your inventory!" << endl;
            }
            else // Otherwise, let them know they don't have room
            {
                cout << "You don't have enough room for that type of item." << endl;
            }
        }
        else if (input == 'n') // If user says no
        {
            cout << "You put the " << item << " back." << endl;
        }

		// Print stats
		player.printStats();
		
		// Generate steps
		int numSteps = rand() % 10 + 1;
		for (int i = 1; i <= numSteps; i++)
		{ 
			if(numSteps == 1)
				cout << "You've taken 1 step.\n";
			else
				cout << "You've taken " << i << " steps." << endl;
		}

		// Fulfill Pokemon encounter
		cout << "You've encountered a(n) " << wildPokemon << "!" << endl; //  User encounters wild pokemon
		cout << "Do you want to fight it?" << endl; // Ask user if they want to fight the wild pokemon
		
		input = charInputCheck(); // Error check user's input
		
		if (input == 'y') // If user wants to fight
        {
            
            // Display the pokemon in user's trainer class and have them pick one
            cout << "Which Pokemon do you want to use?" << endl;
            for (int i = 0; i < player.getNumPokemon(); i++)
            {
                cout << i + 1 << ") " << player.getPokemon(i) << endl;
            }
            
            do { // Do-while loop for error checking user input
                cout << ">> ";
                cin >> choice;
                if (choice < 1 || choice > player.getNumPokemon())
                {
                    cout << "Please enter a valid number." << endl;
                }
            } while (choice < 1 || choice > player.getNumPokemon());
            
            int win = rand() % 2; // Generate random number for results of battle
            
            if (win == 0) // User loses
            {
                // User's pokemon faints and the wild one runs away
                cout << "Oh no! " << player.getPokemon(choice - 1) << " fainted and the " << wildPokemon << " escaped! "; 
                
                // Check if user has revives
                if (player.getItemAmount(Trainer::REVIVE) == 0) // If user doesn't have revives
                {
                    // Let user know they're out of revives and remove chosen pokemon from inventory
                    cout << endl << "Looks like you're out of revives. " << player.getPokemon(choice - 1) << " was transferred to Professor Oak." << endl;
                    player.removePokemon(choice - 1);
                }
                else if (player.getItemAmount(Trainer::REVIVE) != 0) // If user does have revives
                {
                    // Ask user if they want to use a revive
                    cout << "Use a Revive? (y/n)" << endl; 
                    input = charInputCheck();
                    
                    // If-else statements for user input
                    if (input == 'y') // if user says yes
                    {
                        // Use function to update inventory and display that pokemon was healed
                        player.useItem(Trainer::REVIVE); 
                        cout << player.getPokemon(choice - 1) << " was healed. " << player.getItemAmount(Trainer::REVIVE) << " revive(s) remaining." << endl; 
                    }
                    else if (input == 'n') // If user says no
                    {
                        // Remove pokemon from inventory using function
                        cout << player.getPokemon(choice - 1) << " was transferred to Professor Oak." << endl;
                        player.removePokemon(choice - 1);
                    }
                }
                
            }
            else if (win == 1) // User wins
            {
                // Give user the option of catching the wild pokemon
                cout << "You and " << player.getPokemon(choice - 1) << " won! Do you want to catch the " << wildPokemon << "?" << endl;
                input = charInputCheck();
                
                if (input == 'y') // If user says yes
                {
                    // Check if user's inventory is maxed out
                    if (player.hasPokemonSpace() == true) // If user has inventory space
                    {
                        // Make sure user has poke balls or ultra balls on hand
                        if (player.getItemAmount(Trainer::POKE_BALL) > 0 || player.getItemAmount(Trainer::ULTRA_BALL) > 0) // If user has poke balls or ultra balls
                        {
                            // Let user choose what they want to use
                            cout << "What ball do you want to use?" << endl;
                            if (player.getItemAmount(Trainer::POKE_BALL) > 0)
                            {
                                cout << "1) Poke Ball (" << player.getItemAmount(Trainer::POKE_BALL) << " remaining)" << endl;
                            }
                            if (player.getItemAmount(Trainer::ULTRA_BALL) > 0)
                            {
                                cout << "2) Ultra Ball (" << player.getItemAmount(Trainer::ULTRA_BALL) << " remaining)" << endl;
                            }
                            
                            do { // Do-while loop to error check user input
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
                            
                            // User has 100% chance of catching the wild pokemon
                            cout << "You caught " << wildPokemon << "!" << endl;
                            player.useItem(choice - 1); // Update item inventory using function
                            player.addPokemon(wildPokemon); // Update pokemon inventory using function

                        } 
                        else // If user doesn't have poke balls or ultra balls
                        {
                            cout << "You don't have any balls to catch the wild Pokémon." << endl; // Display a message
                        }
                    }
                    else if (player.hasPokemonSpace() == false) // If user does not have inventory space
                    {
                        cout << "Looks like you don't have enough space in your inventory." << endl; // Display a message letting user know they have no space
                    }
                }
                else if (input == 'n') // Otherwise, leave wild pokemon and let user continue
                {
                    cout << "You leave the wild " << wildPokemon << " and continue on your way." << endl;
                }
            }
        }
        else if (input == 'n') // If user does not want to fight
        {
            cout << "You chose to run away." << endl; // Have user run away
        }

		// Check if user can still play, and then if they want to still play
		// If the user has no pokemon, they can't keep playing
		if (player.getNumPokemon() == 0) // If user has no pokemon left
		{
		    // Display message and set stillPlaying to false
		    cout << "Looks like you have no Pokémon remaining." << endl;
		    stillPlaying = false;
		}
		
		// Else, see if the user wants to keep playing
		else // If user has pokemon left
		{
			cout << "Do you want to keep playing?" << endl; // Ask user if they want to keep playing
			input = charInputCheck();

			if (input == 'n') // If user says no
				stillPlaying = false; // Set stillPlaying to false
		}
		
	}
	// Create a unique filename with number of seconds passed since Jan 1, 1970 so multiple runs of the program will save to different files
	string outputFilename = "player-";
	outputFilename.append(std::to_string(time(0)));
	outputFilename.append(".txt");

	//Save to file
	player.writeFile(outputFilename);
	
	cout << "Your player information has been saved to " << outputFilename << ". Until next time!\n";
	return 0;
}
