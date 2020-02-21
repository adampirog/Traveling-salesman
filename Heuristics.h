#pragma once
#include<vector>
class Graph;

static class Heuristics
{
public:
	

	static int tabu(Graph* graph);

	static int SA(Graph* graph);

	static int GA(Graph* graph);

private:

	//para do zamiany oraz zmiana w koszcie sciezki
	//na liscie tabu uzywana jako para do zamiany i dlugosc kadencji
	struct candidate
	{
		int a, b, c;

		bool operator < (const candidate &y)
		{
			return (c < y.c);
		}

		bool operator > (const candidate &y)
		{
			return (c > y.c);
		}

		bool operator == (const candidate &y)
		{
			return ((a == y.b && b == y.a)||(a == y.a && b == y.b));
		}
	};


	//funkcja odswieza liste kandydatow - zwraca granice w postaci najgorszego kandydata
	static int refreshCandidates(Graph* graph, std::vector<int>& tmpRoute,int tmpCost, std::deque<candidate>& candidates);
	static int refreshCandidatesCosts(Graph* graph, std::vector<int>& tmpRoute, int tmpCost, std::deque<candidate>& candidates); \



	//metody pomocnicze dla algorytmu genetycznego
	static void cross(std::vector<int>& parent1, std::vector<int>& parent2, std::vector<int>& child1, std::vector<int>& child2);
	static void mutate(std::vector<int>& route);
	static int localSearch(Graph* graph, std::vector<int>& route);
	static int NN(Graph* graph, int startVertex, std::vector<int>& route);
		
	//pominejsze metody pomocnicze	
	static void display(std::vector<candidate>& a);
	static void display(std::deque<candidate>& a);
	

};

