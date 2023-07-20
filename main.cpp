#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <ctime>
#include "Header.h"
using namespace std;

mt19937 random_mt;
int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void setText(sf::Text& text, float x, float y) {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
	textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(x, y));
	}



int main()
{
	time_t current_time = time(NULL);
	random_mt.seed(current_time);
	//textures
	sf::Texture hidden;
	hidden.loadFromFile("files/images/tile_hidden.png");
	sf::Texture happy;
	happy.loadFromFile("files/images/face_happy.png");
	sf::Texture debug;
	debug.loadFromFile("files/images/debug.png");
	sf::Texture lose;
	lose.loadFromFile("files/images/face_lose.png");
	sf::Texture win;
	win.loadFromFile("files/images/face_win.png");
	sf::Texture flag;
	flag.loadFromFile("files/images/flag.png");
	sf::Texture leaderboard;
	leaderboard.loadFromFile("files/images/leaderboard.png");
	sf::Texture mine;
	mine.loadFromFile("files/images/mine.png");
	sf::Texture num1;
	num1.loadFromFile("files/images/number_1.png");
	sf::Texture num2;
	num2.loadFromFile("files/images/number_2.png");
	sf::Texture num3;
	num3.loadFromFile("files/images/number_3.png");
	sf::Texture num4;
	num4.loadFromFile("files/images/number_4.png");
	sf::Texture num5;
	num5.loadFromFile("files/images/number_5.png");
	sf::Texture num6;
	num6.loadFromFile("files/images/number_6.png");
	sf::Texture num7;
	num7.loadFromFile("files/images/number_7.png");
	sf::Texture num8;
	num8.loadFromFile("files/images/number_8.png");
	sf::Texture pause;
	pause.loadFromFile("files/images/pause.png");
	sf::Texture play;
	play.loadFromFile("files/images/play.png");
	sf::Texture revealed;
	revealed.loadFromFile("files/images/tile_revealed.png");
	sf::Texture digits0;
	digits0.loadFromFile("files/images/digits.png", sf::IntRect(0, 0, 21, 32));
	sf::Texture digits1;
	digits1.loadFromFile("files/images/digits.png", sf::IntRect(21, 0, 21, 32));
	sf::Texture digits2;
	digits2.loadFromFile("files/images/digits.png", sf::IntRect(42, 0, 21, 32));
	sf::Texture digits3;
	digits3.loadFromFile("files/images/digits.png", sf::IntRect(63, 0, 21, 32));
	sf::Texture digits4;
	digits4.loadFromFile("files/images/digits.png", sf::IntRect(84, 0, 21, 32));
	sf::Texture digits5;
	digits5.loadFromFile("files/images/digits.png", sf::IntRect(105, 0, 21, 32));
	sf::Texture digits6;
	digits6.loadFromFile("files/images/digits.png", sf::IntRect(126, 0, 21, 32));
	sf::Texture digits7;
	digits7.loadFromFile("files/images/digits.png", sf::IntRect(147, 0, 21, 32));
	sf::Texture digits8;
	digits8.loadFromFile("files/images/digits.png", sf::IntRect(168, 0, 21, 32));
	sf::Texture digits9;
	digits9.loadFromFile("files/images/digits.png", sf::IntRect(189, 0, 21, 32));
	sf::Texture digitsneg;
	digitsneg.loadFromFile("files/images/digits.png", sf::IntRect(210, 0, 21, 32));
	vector<Tiles> tiles;
	bool open = false;
	bool firsttime = true;
	bool minesneg = false;
	bool gamecont = true;
	bool debugb = false;
	bool gamepaused = false;
	bool gamewin = false;
	float width = 800;
	float height = 600;
	int correct = 0;
	sf::RenderWindow welcomewindow(sf::VideoMode(width, height), "Welcome Window");
	sf::Text welcometext;
	sf::Text inputtext;
	sf::Text userinput;
	string input = "";
	string name = "";
	sf::Font Font;
	Font.loadFromFile("files/font.ttf");
	welcometext.setFont(Font);
	welcometext.setString("WELCOME TO MINESWEEPER!");
	welcometext.setCharacterSize(24);
	welcometext.setFillColor(sf::Color::White);
	welcometext.setStyle(sf::Text::Underlined | sf::Text::Bold);
	setText(welcometext, (width / 2.0f), (height / 2.0f) - 150);
	inputtext.setFont(Font);
	inputtext.setString("Enter your name:");
	inputtext.setCharacterSize(20);
	inputtext.setFillColor(sf::Color::White);
	inputtext.setStyle(sf::Text::Bold);
	setText(inputtext, (width / 2.0f), (height / 2.0f) - 75);
	userinput.setFont(Font);
	userinput.setString("|");
	userinput.setCharacterSize(18);
	userinput.setFillColor(sf::Color::Yellow);
	userinput.setStyle(sf::Text::Bold);
	setText(userinput, (width / 2.0f), (height / 2.0f) - 45);
	
	//welcome window
	while (welcomewindow.isOpen())
	{
		sf::Event event;
		while (welcomewindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				welcomewindow.close();
			}
			else if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == '\b') {
					input.erase(input.size() - 1, 1);
					userinput.setString(input + "|");
					setText(userinput, (width / 2.0f), (height / 2.0f) - 45);
				}
				else if (event.text.unicode < 128) {
					char newchar = event.text.unicode;
					if (isalpha(newchar) && input.size() < 10) {
						string s(1, newchar);
						input.append(s);
						userinput.setString(input + "|");
						setText(userinput, (width / 2.0f), (height / 2.0f) - 45);
					}
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				welcomewindow.close();
				open = true;
			}
		}
		welcomewindow.clear(sf::Color::Blue);
		welcomewindow.draw(welcometext);
		welcomewindow.draw(inputtext);
		welcomewindow.draw(userinput);
		welcomewindow.display();
	}

	//name
	for (int i = 0; i < input.size(); i++) {
		if (i == 0) {
			char newchar = (toupper(input.at(i)));
			string s(1, newchar);
			name.append(s);
		}
		else {
			char newchar = (tolower(input.at(i)));
			string s(1, newchar);
			name.append(s);
		}
	}
	userinput.setString(name);

	//read file
	ifstream file("files/board_config.cfg");
	if (!file.is_open()) {
		cout << "file not open";
	}
	int cols;
	int rows;
	int mines;
	file >> cols;
	file >> rows;
	file >> mines;
	file.close();
	int minesnum = mines;
	int gwidth = cols * 32;
	int gheight = (rows * 32) + 100;
	cout << "rows: " << rows << endl << "cols" << cols << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//cout << i << " " << j << endl;
			Tiles testtile("hidden", j, i);
			//cout << testtile.row << " " << testtile.col << endl;
			tiles.push_back(testtile);
		}
	}

	//leaderboard text
	sf::Text leaderboardt;
	leaderboardt.setFont(Font);
	leaderboardt.setString("LEADERBOARD");
	leaderboardt.setCharacterSize(20);
	leaderboardt.setFillColor(sf::Color::White);
	leaderboardt.setStyle(sf::Text::Underlined | sf::Text::Bold);
	setText(leaderboardt, (gwidth / 2) / 2.0f, (((gheight / 2) / 2.0f) - 120));

	//sprites
	sf::Sprite gamestatus;
	gamestatus.setTexture(happy);
	gamestatus.setPosition(sf::Vector2f((cols / 2.0) * 32 - 32, 32 * (rows + .5f)));
	sf::Sprite debugbutton;
	debugbutton.setTexture(debug);
	debugbutton.setPosition(sf::Vector2f((cols * 32) - 304, 32 * (rows + .5f)));
	sf::Sprite pauseplay;
	pauseplay.setTexture(pause);
	pauseplay.setPosition(sf::Vector2f((cols * 32) - 240, 32 * (rows + .5f)));
	sf::Sprite leaderbutton;
	leaderbutton.setTexture(leaderboard);
	leaderbutton.setPosition(sf::Vector2f((cols * 32) - 176, 32 * (rows + .5f)));
	sf::Sprite neg;
	neg.setTexture(digits0);
	neg.setPosition(sf::Vector2f(12, 32 * (rows + .5f) + 16));
	sf::Sprite tenscounter;
	tenscounter.setTexture(digits0);
	tenscounter.setPosition(sf::Vector2f(33, 32 * (rows + .5f) + 16));
	sf::Sprite onescounter;
	onescounter.setTexture(digits0);
	onescounter.setPosition(sf::Vector2f(54, 32 * (rows + .5f) + 16));
	sf::Sprite minutestens;
	minutestens.setTexture(digits0);
	minutestens.setPosition(sf::Vector2f((cols * 32) - 97, 32 * (rows + .5f) + 16));
	sf::Sprite minutesones;
	minutesones.setTexture(digits0);
	minutesones.setPosition(sf::Vector2f((cols * 32) - 76, 32 * (rows + .5f) + 16));
	sf::Sprite secondstens;
	secondstens.setTexture(digits0);
	secondstens.setPosition(sf::Vector2f((cols * 32) - 54, 32 * (rows + .5f) + 16));
	sf::Sprite secondsones;
	secondsones.setTexture(digits0);
	secondsones.setPosition(sf::Vector2f((cols * 32) - 33, 32 * (rows + .5f) + 16));

	//set mines
	for (int i = 0; i < mines;) {
		int num = Random(0, (rows * cols) - 1);
		if ((tiles.at(num)).name != "mine") {
			tiles.at(num).name = "mine";
			i++;
		}
	}

	//set adjacent tiles
	for (int i = 0; i < tiles.size(); i++) {
		int currow = tiles.at(i).row;
		int curcol = tiles.at(i).col;
		if (currow == 0) {
			if (curcol == 0) {
				tiles.at(i).setadjacent(tiles.at(i + 1));
				tiles.at(i).setadjacent(tiles.at(i + cols));
				tiles.at(i).setadjacent(tiles.at(i + cols + 1));
			}
			else if (curcol == (cols - 1)) {
				tiles.at(i).setadjacent(tiles.at(i - 1));
				tiles.at(i).setadjacent(tiles.at(i + cols));
				tiles.at(i).setadjacent(tiles.at(i + cols - 1));
			}
			else {
				tiles.at(i).setadjacent(tiles.at(i - 1));
				tiles.at(i).setadjacent(tiles.at(i + 1));
				tiles.at(i).setadjacent(tiles.at(i + cols - 1));
				tiles.at(i).setadjacent(tiles.at(i + cols));
				tiles.at(i).setadjacent(tiles.at(i + cols + 1));
			}
		}
		else if (curcol == 0) {
			if (currow == (rows - 1)) {
				tiles.at(i).setadjacent(tiles.at(i - cols));
				tiles.at(i).setadjacent(tiles.at(i - cols + 1));
				tiles.at(i).setadjacent(tiles.at(i + 1));
			}
			else {
				(tiles.at(i)).setadjacent(tiles.at(i - cols));
				tiles.at(i).setadjacent(tiles.at(i - cols + 1));
				tiles.at(i).setadjacent(tiles.at(i + 1));
				tiles.at(i).setadjacent(tiles.at(i + cols));
				tiles.at(i).setadjacent(tiles.at(i + cols + 1));
			}
		}
		else if (currow == (rows - 1)) {
			if (curcol == (cols - 1)) {
				tiles.at(i).setadjacent(tiles.at(i - cols - 1));
				tiles.at(i).setadjacent(tiles.at(i - cols));
				tiles.at(i).setadjacent(tiles.at(i - 1));
			}
			else {
				tiles.at(i).setadjacent(tiles.at(i - cols - 1));
				tiles.at(i).setadjacent(tiles.at(i - cols));
				tiles.at(i).setadjacent(tiles.at(i - cols + 1));
				tiles.at(i).setadjacent(tiles.at(i - 1));
				tiles.at(i).setadjacent(tiles.at(i + 1));
			}
		}
		else if (curcol == (cols - 1)) {
			tiles.at(i).setadjacent(tiles.at(i - cols - 1));
			tiles.at(i).setadjacent(tiles.at(i - cols));
			tiles.at(i).setadjacent(tiles.at(i - 1));
			tiles.at(i).setadjacent(tiles.at(i + cols));
			tiles.at(i).setadjacent(tiles.at(i + cols - 1));
		}
		else {
			tiles.at(i).setadjacent(tiles.at(i - cols - 1));
			tiles.at(i).setadjacent(tiles.at(i - cols));
			tiles.at(i).setadjacent(tiles.at(i - cols + 1));
			tiles.at(i).setadjacent(tiles.at(i - 1));
			tiles.at(i).setadjacent(tiles.at(i + 1));
			tiles.at(i).setadjacent(tiles.at(i + cols - 1));
			tiles.at(i).setadjacent(tiles.at(i + cols));
			tiles.at(i).setadjacent(tiles.at(i + cols + 1));
		}
	}

	//check for adjacent mines
	for (int i = 0; i < tiles.size(); i++) {
		tiles.at(i).checkformines();
	}

	bool openleader = false;

	//game window

	if (open) {
		sf::RenderWindow gamewindow(sf::VideoMode(gwidth, gheight), "Game Window");
		//timer start
		auto start = chrono::steady_clock::now();
		while (gamewindow.isOpen()) {
			sf::Event event;
			//events
			while (gamewindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gamewindow.close();
				}
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						int x = event.mouseButton.x;
						int y = event.mouseButton.y;
						int clickedrow = y / 32;
						int clickedcol = x / 32;
						for (int i = 0; i < tiles.size(); i++) {
							if (tiles.at(i).row == clickedrow && tiles.at(i).col == clickedcol && tiles.at(i).rightclicked == false && gamecont && (gamepaused == false)) {
								tiles.at(i).clicked = true;
							}
						}
						if ((((((cols / 2.0) * 32) - 32) < x) && (((cols / 2.0) * 32) + 32) > x) && (((32 * (rows + .5f)) < y) && (((32 * (rows + .5f) + 64) > y)))) {
							//game status button
							cout << "status button";
							gamewin = false;
							for (int i = 0; i < tiles.size(); i++) {
								tiles.at(i).clicked = false;
								tiles.at(i).rightclicked = false;
								tiles.at(i).name = "hidden";
								tiles.at(i).admines = 0;
								tiles.at(i).adjacent.clear();
							}
							mines = minesnum;

							//set mines
							for (int i = 0; i < mines;) {
								int num = Random(0, (rows * cols) - 1);
								if ((tiles.at(num)).name != "mine") {
									tiles.at(num).name = "mine";
									i++;
								}
							}

							//set adjacent tiles
							for (int i = 0; i < tiles.size(); i++) {
								int currow = tiles.at(i).row;
								int curcol = tiles.at(i).col;
								if (currow == 0) {
									if (curcol == 0) {
										tiles.at(i).setadjacent(tiles.at(i + 1));
										tiles.at(i).setadjacent(tiles.at(i + cols));
										tiles.at(i).setadjacent(tiles.at(i + cols + 1));
									}
									else if (curcol == (cols - 1)) {
										tiles.at(i).setadjacent(tiles.at(i - 1));
										tiles.at(i).setadjacent(tiles.at(i + cols));
										tiles.at(i).setadjacent(tiles.at(i + cols - 1));
									}
									else {
										tiles.at(i).setadjacent(tiles.at(i - 1));
										tiles.at(i).setadjacent(tiles.at(i + 1));
										tiles.at(i).setadjacent(tiles.at(i + cols - 1));
										tiles.at(i).setadjacent(tiles.at(i + cols));
										tiles.at(i).setadjacent(tiles.at(i + cols + 1));
									}
								}
								else if (curcol == 0) {
									if (currow == (rows - 1)) {
										tiles.at(i).setadjacent(tiles.at(i - cols));
										tiles.at(i).setadjacent(tiles.at(i - cols + 1));
										tiles.at(i).setadjacent(tiles.at(i + 1));
									}
									else {
										(tiles.at(i)).setadjacent(tiles.at(i - cols));
										tiles.at(i).setadjacent(tiles.at(i - cols + 1));
										tiles.at(i).setadjacent(tiles.at(i + 1));
										tiles.at(i).setadjacent(tiles.at(i + cols));
										tiles.at(i).setadjacent(tiles.at(i + cols + 1));
									}
								}
								else if (currow == (rows - 1)) {
									if (curcol == (cols - 1)) {
										tiles.at(i).setadjacent(tiles.at(i - cols - 1));
										tiles.at(i).setadjacent(tiles.at(i - cols));
										tiles.at(i).setadjacent(tiles.at(i - 1));
									}
									else {
										tiles.at(i).setadjacent(tiles.at(i - cols - 1));
										tiles.at(i).setadjacent(tiles.at(i - cols));
										tiles.at(i).setadjacent(tiles.at(i - cols + 1));
										tiles.at(i).setadjacent(tiles.at(i - 1));
										tiles.at(i).setadjacent(tiles.at(i + 1));
									}
								}
								else if (curcol == (cols - 1)) {
									tiles.at(i).setadjacent(tiles.at(i - cols - 1));
									tiles.at(i).setadjacent(tiles.at(i - cols));
									tiles.at(i).setadjacent(tiles.at(i - 1));
									tiles.at(i).setadjacent(tiles.at(i + cols));
									tiles.at(i).setadjacent(tiles.at(i + cols - 1));
								}
								else {
									tiles.at(i).setadjacent(tiles.at(i - cols - 1));
									tiles.at(i).setadjacent(tiles.at(i - cols));
									tiles.at(i).setadjacent(tiles.at(i - cols + 1));
									tiles.at(i).setadjacent(tiles.at(i - 1));
									tiles.at(i).setadjacent(tiles.at(i + 1));
									tiles.at(i).setadjacent(tiles.at(i + cols - 1));
									tiles.at(i).setadjacent(tiles.at(i + cols));
									tiles.at(i).setadjacent(tiles.at(i + cols + 1));
								}
							}

							//check for adjacent mines
							for (int i = 0; i < tiles.size(); i++) {
								tiles.at(i).checkformines();
							}

							gamestatus.setTexture(happy);
							gamecont = true;
							start = chrono::steady_clock::now();
						}
						else if (((((cols * 32) - 304) < x) && ((cols * 32) - 240) > x) && (((32 * (rows + .5f)) < y) && (((32 * (rows + .5f) + 64) > y)))) {
							//debug button
							cout << "debug button";
							if (debugb == false && !gamewin && gamecont) {
								debugb = true;
								for (int i = 0; i < tiles.size(); i++) {
									if (tiles.at(i).name == "mine") {
										tiles.at(i).clicked = true;

									}
								}
							}
							else if (debugb == true && !gamewin && gamecont) {
								debugb = false;
								for (int i = 0; i < tiles.size(); i++) {
									if (tiles.at(i).name == "mine") {
										tiles.at(i).clicked = false;
									}
								}
							}
						}
						else if (((((cols * 32) - 240) < x) && ((cols * 32) - 176) > x) && (((32 * (rows + .5f)) < y) && (((32 * (rows + .5f) + 64) > y)))) {
							//pause button
							cout << "pause button";
							if (gamepaused == false && gamecont) {
								pauseplay.setTexture(play);
								gamepaused = true;
								for (int i = 0; i < tiles.size(); i++) {
									sf::Sprite testsprite;
									testsprite.setTexture(revealed);
									testsprite.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
									gamewindow.draw(testsprite);
								}
							}
							else if (gamepaused == true) {
								pauseplay.setTexture(pause);
								gamepaused = false;
							}
						}
						else if (((((cols * 32) - 176) < x) && ((cols * 32) - 112) > x) && (((32 * (rows + .5f)) < y) && (((32 * (rows + .5f) + 64) > y)))) {
							//leaderboard button
							cout << "leaderboard";
							openleader = true;
							gamepaused = true;
							for (int i = 0; i < tiles.size(); i++) {
								sf::Sprite testsprite;
								testsprite.setTexture(revealed);
								testsprite.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
								gamewindow.draw(testsprite);
								
							}
							gamewindow.display();
						}
					}
					else if (event.mouseButton.button == sf::Mouse::Right) {
						int x = event.mouseButton.x;
						int y = event.mouseButton.y;
						int clickedrow = y / 32;
						int clickedcol = x / 32;
						for (int i = 0; i < tiles.size(); i++) {
							if (tiles.at(i).row == clickedrow && tiles.at(i).col == clickedcol && gamecont && gamepaused == false) {
								if (tiles.at(i).rightclicked == true) {
									tiles.at(i).rightclicked = false;
									mines += 1;
								}
								else if (tiles.at(i).rightclicked == false) {
									tiles.at(i).rightclicked = true;
									mines -= 1;
								}
							}
						}
					}
				}
			}
			gamewindow.clear(sf::Color::White);

			//set tiles
			for (int i = 0; i < tiles.size(); i++) {
				sf::Sprite testsprite;
				if (gamepaused == true) {
					testsprite.setTexture(revealed);
					testsprite.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
					gamewindow.draw(testsprite);
				}
				else if (tiles.at(i).clicked == false && tiles.at(i).rightclicked == false) {
					testsprite.setTexture(hidden);
					testsprite.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
					gamewindow.draw(testsprite);
				}
				else if (tiles.at(i).clicked == true) {
					if (tiles.at(i).name == "mine") {
						for (int j = 0; j < tiles.size(); j++) {
							if (tiles.at(j).name == "mine") {
								if (debugb == true) {
									sf::Sprite overlay;
									testsprite.setTexture(revealed);
									overlay.setTexture(mine);
									testsprite.setPosition(sf::Vector2f((tiles.at(j)).col * 32.f, (tiles.at(j)).row * 32.f));
									gamewindow.draw(testsprite);
									overlay.setPosition(sf::Vector2f((tiles.at(j)).col * 32.f, (tiles.at(j)).row * 32.f));
									gamewindow.draw(overlay);
								}
								else {
									tiles.at(j).clicked = true;
									gamecont = false;
									gamestatus.setTexture(lose);
									gamewindow.draw(gamestatus);
									sf::Sprite overlay;
									testsprite.setTexture(revealed);
									overlay.setTexture(mine);
									testsprite.setPosition(sf::Vector2f((tiles.at(j)).col * 32.f, (tiles.at(j)).row * 32.f));
									gamewindow.draw(testsprite);
									overlay.setPosition(sf::Vector2f((tiles.at(j)).col * 32.f, (tiles.at(j)).row * 32.f));
									gamewindow.draw(overlay);
								}
							}
						}
					}
					else {
						testsprite.setTexture(revealed);
						sf::Sprite overlay;
						if (tiles.at(i).admines == 1) {
							overlay.setTexture(num1);
						}
						else if (tiles.at(i).admines == 2) {
							overlay.setTexture(num2);
						}
						else if (tiles.at(i).admines == 3) {
							overlay.setTexture(num3);
						}
						else if (tiles.at(i).admines == 4) {
							overlay.setTexture(num4);
						}
						else if (tiles.at(i).admines == 5) {
							overlay.setTexture(num5);
						}
						else if (tiles.at(i).admines == 6) {
							overlay.setTexture(num6);
						}
						else if (tiles.at(i).admines == 7) {
							overlay.setTexture(num7);
						}
						else if (tiles.at(i).admines == 8) {
							overlay.setTexture(num8);
						}
						else {
							for (int j = 0; j < tiles.at(i).adjacent.size(); j++) {
								if (tiles.at(i).adjacent.at(j)->rightclicked == false) {
									tiles.at(i).adjacent.at(j)->clicked = true;
								}
							}
						}
						testsprite.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
						gamewindow.draw(testsprite);
						overlay.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
						gamewindow.draw(overlay);
					}
				}
				else if (tiles.at(i).rightclicked == true) {
					testsprite.setTexture(hidden);
					sf::Sprite overlay;
					overlay.setTexture(flag);
					testsprite.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
					gamewindow.draw(testsprite);
					overlay.setPosition(sf::Vector2f((tiles.at(i)).col * 32.f, (tiles.at(i)).row * 32.f));
					gamewindow.draw(overlay);
				}
			}


			//check if game is won
			if (mines == 0 && gamewin == false) {
				for (int i = 0; i < tiles.size(); i++) {
					if (tiles.at(i).clicked == true || tiles.at(i).name == "mine") {
						correct += 1;
					}
				}
				if (correct == tiles.size()) {
					gamecont = false;
					gamestatus.setTexture(win);
					openleader = true;
					gamewin = true;
				}
				else {
					correct = 0;
				}
			}

			//counter
			if (mines < 0) {
				neg.setTexture(digitsneg);
				minesneg = true;
				mines *= -1;
			}
			else if (mines >= 0) {
				neg.setTexture(digits0);
				minesneg = false;
			}
			int tens = (mines / 10) % 10;
			int ones = mines % 10;
			if (tens == 0) {
				tenscounter.setTexture(digits0);
			}
			else if (tens == 1) {
				tenscounter.setTexture(digits1);
			}
			else if (tens == 2) {
				tenscounter.setTexture(digits2);
			}
			else if (tens == 3) {
				tenscounter.setTexture(digits3);
			}
			else if (tens == 4) {
				tenscounter.setTexture(digits4);
			}
			else if (tens == 5) {
				tenscounter.setTexture(digits5);
			}
			else if (tens == 6) {
				tenscounter.setTexture(digits6);
			}
			else if (tens == 7) {
				tenscounter.setTexture(digits7);
			}
			else if (tens == 8) {
				tenscounter.setTexture(digits8);
			}
			else if (tens == 9) {
				tenscounter.setTexture(digits9);
			}
			if (ones == 0) {
				onescounter.setTexture(digits0);
			}
			else if (ones == 1) {
				onescounter.setTexture(digits1);
			}
			else if (ones == 2) {
				onescounter.setTexture(digits2);
			}
			else if (ones == 3) {
				onescounter.setTexture(digits3);
			}
			else if (ones == 4) {
				onescounter.setTexture(digits4);
			}
			else if (ones == 5) {
				onescounter.setTexture(digits5);
			}
			else if (ones == 6) {
				onescounter.setTexture(digits6);
			}
			else if (ones == 7) {
				onescounter.setTexture(digits7);
			}
			else if (ones == 8) {
				onescounter.setTexture(digits8);
			}
			else if (ones == 9) {
				onescounter.setTexture(digits9);
			}
			if (minesneg == true) {
				mines *= -1;
			}

			//timer
			if (gamecont && gamepaused == false) {
				auto current = chrono::steady_clock::now();
				int elapsed = (chrono::duration_cast<chrono::seconds>(current - start)).count();
				int tensm = (elapsed / 600);
				elapsed -= (tensm * 600);
				int onesm = (elapsed / 60);
				elapsed -= (onesm * 60);
				int tenss = (elapsed / 10);
				elapsed -= (tenss * 10);
				if (tensm == 0) {
					minutestens.setTexture(digits0);
				}
				else if (tensm == 1) {
					minutestens.setTexture(digits1);
				}
				else if (tensm == 2) {
					minutestens.setTexture(digits2);
				}
				else if (tensm == 3) {
					minutestens.setTexture(digits3);
				}
				else if (tensm == 4) {
					minutestens.setTexture(digits4);
				}
				else if (tensm == 5) {
					minutestens.setTexture(digits5);
				}
				else if (tensm == 6) {
					minutestens.setTexture(digits6);
				}
				else if (tensm == 7) {
					minutestens.setTexture(digits7);
				}
				else if (tensm == 8) {
					minutestens.setTexture(digits8);
				}
				else if (tensm == 9) {
					minutestens.setTexture(digits9);
				}
				if (onesm == 0) {
					minutesones.setTexture(digits0);
				}
				else if (onesm == 1) {
					minutesones.setTexture(digits1);
				}
				else if (onesm == 2) {
					minutesones.setTexture(digits2);
				}
				else if (onesm == 3) {
					minutesones.setTexture(digits3);
				}
				else if (onesm == 4) {
					minutesones.setTexture(digits4);
				}
				else if (onesm == 5) {
					minutesones.setTexture(digits5);
				}
				else if (onesm == 6) {
					minutesones.setTexture(digits6);
				}
				else if (onesm == 7) {
					minutesones.setTexture(digits7);
				}
				else if (onesm == 8) {
					minutesones.setTexture(digits8);
				}
				else if (onesm == 9) {
					minutesones.setTexture(digits9);
				}
				if (tenss == 0) {
					secondstens.setTexture(digits0);
				}
				else if (tenss == 1) {
					secondstens.setTexture(digits1);
				}
				else if (tenss == 2) {
					secondstens.setTexture(digits2);
				}
				else if (tenss == 3) {
					secondstens.setTexture(digits3);
				}
				else if (tenss == 4) {
					secondstens.setTexture(digits4);
				}
				else if (tenss == 5) {
					secondstens.setTexture(digits5);
				}
				if (elapsed == 0) {
					secondsones.setTexture(digits0);
				}
				else if (elapsed == 1) {
					secondsones.setTexture(digits1);
				}
				else if (elapsed == 2) {
					secondsones.setTexture(digits2);
				}
				else if (elapsed == 3) {
					secondsones.setTexture(digits3);
				}
				else if (elapsed == 4) {
					secondsones.setTexture(digits4);
				}
				else if (elapsed == 5) {
					secondsones.setTexture(digits5);
				}
				else if (elapsed == 6) {
					secondsones.setTexture(digits6);
				}
				else if (elapsed == 7) {
					secondsones.setTexture(digits7);
				}
				else if (elapsed == 8) {
					secondsones.setTexture(digits8);
				}
				else if (elapsed == 9) {
					secondsones.setTexture(digits9);
				}
			}


			//draw 
			gamewindow.draw(gamestatus);
			gamewindow.draw(pauseplay);
			gamewindow.draw(leaderbutton);
			gamewindow.draw(debugbutton);
			gamewindow.draw(neg);
			gamewindow.draw(tenscounter);
			gamewindow.draw(onescounter);
			gamewindow.draw(minutestens);
			gamewindow.draw(minutesones);
			gamewindow.draw(secondstens);
			gamewindow.draw(secondsones);
			gamewindow.display();


			if (openleader) {
				ifstream file2("files/leaderboard.txt");
				if (!file2.is_open()) {
					cout << "file not open";
				}
				string time1;
				getline(file2, time1, ',');
				int time1s = (time1[0] * 600) + (time1[1] * 60) + (time1[3] * 10) + time1[4];
				string name1;
				getline(file2, name1);
				string time2;
				getline(file2, time2, ',');
				int time2s = (time2[0] * 600) + (time2[1] * 60) + (time2[3] * 10) + time2[4];
				string name2;
				getline(file2, name2);
				string time3;
				getline(file2, time3, ',');
				int time3s = (time3[0] * 600) + (time3[1] * 60) + (time3[3] * 10) + time3[4];
				string name3;
				getline(file2, name3);
				string time4;
				getline(file2, time4, ',');
				int time4s = (time4[0] * 600) + (time4[1] * 60) + (time4[3] * 10) + time4[4];
				string name4;
				getline(file2, name4);
				string time5;
				getline(file2, time5, ',');
				int time5s = (time5[0] * 600) + (time5[1] * 60) + (time5[3] * 10) + time5[4];
				string name5;
				getline(file2, name5);
				file2.close();
				if (gamewin) {
					auto current = chrono::steady_clock::now();
					int elapsed = (chrono::duration_cast<chrono::seconds>(current - start)).count();
					int elapsed1 = elapsed;
					int tensm = (elapsed / 600);
					elapsed -= (tensm * 600);
					int onesm = (elapsed / 60);
					elapsed -= (onesm * 60);
					int tenss = (elapsed / 10);
					elapsed -= (tenss * 10);
					string usertime = to_string(tensm) + to_string(onesm) + ":" + to_string(tenss) + to_string(elapsed) + "*";
					if (elapsed < time1s) {
						time5 = time4;
						time4 = time3;
						time3 = time2;
						time2 = time1;
						time1 = usertime;
						name5 = name4;
						name4 = name3;
						name3 = name2;
						name2 = name1;
						name1 = name;
					}
					else if (elapsed < time2s) {
						time5 = time4;
						time4 = time3;
						time3 = time2;
						time2 = usertime;
						name5 = name4;
						name4 = name3;
						name3 = name2;
						name2 = name;
					}
					else if (elapsed < time3s) {
						time5 = time4;
						time4 = time3;
						time3 = usertime;
						name5 = name4;
						name4 = name3;
						name3 = name;
					}
					else if (elapsed < time4s) {
						time5 = time4;
						time4 = usertime;
						name5 = name4;
						name4 = name;
					}
					else if (elapsed < time5s) {
						time5 = usertime;
						name5 = name;
					}
				}
				sf::RenderWindow leaderwindow(sf::VideoMode(gwidth / 2, (gheight / 2) + 50), "Leaderboard Window");
				while (leaderwindow.isOpen()) {
					sf::Event event2;
					//events
					while (leaderwindow.pollEvent(event2)) {
						if (event2.type == sf::Event::Closed) {
							leaderwindow.close();
							gamepaused = false;
							openleader = false;
						}
					}
					sf::Text leaderboardt1;
					leaderboardt1.setFont(Font);
					leaderboardt1.setString("1.\t" + time1 + '\t' + name1 + "\n\n" + "2." + '\t' + time2 + '\t' + name2 + "\n\n" + "3." + '\t' + time3 + '\t' + name3 + "\n\n" + "4." + '\t' + time4 + '\t' + name4 + "\n\n" + "5." + '\t' + time5 + '\t' + name5);
					leaderboardt1.setCharacterSize(18);
					leaderboardt1.setStyle(sf::Text::Bold);
					setText(leaderboardt1, (gwidth / 2) / 2.0f, (((gheight / 2) / 2.0f) + 20));
					leaderwindow.clear(sf::Color::Blue);
					leaderwindow.draw(leaderboardt);
					leaderwindow.draw(leaderboardt1);
					leaderwindow.display();
				}
			}
		}

	}

	return 0;
}