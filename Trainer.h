/******************************************************************************
Author: Tucker Neikirk
Date: August 29, 2025
Purpose: Declare the Trainer type, which manages a trainer's information and
         Pokémon data. Includes function prototypes for adding, copying, and
         displaying trainer details.
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
		// constructors
		Trainer();
		Trainer(const string userName, const string starter);
		Trainer(const Trainer& other);

		// destructor
		~Trainer();

		// getters
		string getName() const;
		string getPokemon(const int index) const;
		int getNumPokemon() const;
		int getItemAmount(const int index) const;

		// setters
		void setName(const string userName);

		// other methods
		void printStats() const;
		bool hasPokemonSpace() const;
		void addPokemon(const string pokemonName);
		bool addItem(const int index);
		void useItem(const int index);
		void removePokemon(const int index);
		void writeFile(const string filename);

		// member variables - indices of each item
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
