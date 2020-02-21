#pragma once

using namespace std;

class Graph
{
public:
	Graph();
	Graph(int n);
	Graph(string fileName);
	~Graph();

	//Gettery wyswietlaja podstawowe informacje o grafie
	int getSize();
	string getName();
	int getOptimum();

	//Wyswietla macierz grafu
	void display();

	//Funkcja oblicza koszt drogi
	int calculateCost();

	int calculateHamiltonsCost(int tab[]);
	int calculateHamiltonsCost(std::vector<int>& route);


private:
	vector<vector<int>> costs;
	int optimum = 0;
	int size = 0;
	std::string name;


	friend class Algorithms;
	friend class Heuristics;
};

