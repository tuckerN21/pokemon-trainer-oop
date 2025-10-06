/******************************************************************************
Author: Tucker Neikirk
Date: November 12, 2024
Purpose: Declare the Trainer class and related constants. Defines the interface
         for managing a trainer's name, Pokémon, and items.
*******************************************************************************/

#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

class Trainer
{
	public:
		// Constructors
		Trainer();
		Trainer(const string userName, const string starter);
		Trainer(const Trainer& other);

		// Destructor
		~Trainer();

		// Getters
		string getName() const;
		string getPokemon(const int index) const;
		int getNumPokemon() const;
		int getItemAmount(const int index) const;

		// Setters
		void setName(const string userName);

		// Other methods
		void printStats() const;
		bool hasPokemonSpace() const;
		void addPokemon(const string pokemonName);
		bool addItem(const int index);
		void useItem(const int index);
		void removePokemon(const int index);
		void writeFile(const string filename);

		// Member variables - indices of each item
		static const int POKE_BALL = 0;
		static const int ULTRA_BALL = 1;
		static const int REVIVE = 2;

		static const int INVENTORY_MAX = 3;
		
	private:
		static const int POKEMON_MAX = 5;
		static const int ITEM_MAX = 5;

		string name;
		int numPokemon;
		string pokemon[POKEMON_MAX];
		int inventory[INVENTORY_MAX];
};
