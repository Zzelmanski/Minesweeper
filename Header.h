#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;
#pragma once

class Tiles {
public: 
	bool clicked;
	bool rightclicked;
	string name;
	int row;
	int col;
	vector<Tiles*> adjacent;
	int admines;
	Tiles();
	Tiles(string _name, int _row, int _col);
	void setadjacent(Tiles &add);
	void checkformines();
};
