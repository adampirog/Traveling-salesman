#pragma once
#include<vector>
class Graph;

static class Algorithms
{
public:

	//Algorytm najblizszego sasiada
	static int NN(Graph* graph);

	static int bruteForce(Graph* graph);

	static int bruteForceSTL(Graph* graph);

	static int BnB(Graph* graph);

	static int DP(Graph* graph);
	

private:

	//metody dodatkowe dla Brute Force
	static void bruteForce(Graph* graph, int tab[], int n, int result[]);


	//metody dodatkowe dla Branch and Bound
	static int bound(Graph* grph, const std::vector<int>& path);
	static int NN(Graph* graph, std::vector<int>& bestPath);	//algorytm ktory kontynuje zachlannie dana sciezke
	static int upperBound(Graph* graph, std::vector<int>& bestPath);

	//metody dodatkowe dla Dynamic Programming
	static int DP(Graph* graph, int lvl, int visited, int **D);
};

