#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Header.h"
using namespace std;

Tiles::Tiles() {
	name = "none";
	row = 0;
	col = 0;
	admines = 0;
	clicked = false;
	rightclicked = false;
}

Tiles::Tiles(string _name, int _col, int _row) {
	name = _name;
	col = _col;
	row = _row;
	admines = 0;
	clicked = false;
	rightclicked = false;
	vector<Tiles*> adjacent;
}

void Tiles::setadjacent(Tiles &add) {
	Tiles* pntr = &add;
	this->adjacent.push_back(pntr);
}

void Tiles::checkformines() {
	//cout << "checking for mines" << endl;
	for (int i = 0; i < this->adjacent.size(); i++) {
		Tiles* currptr = this->adjacent.at(i);
		if (currptr->name == "mine") {
			this->admines += 1;
		}
	}
}

