#include "pch.h"

using namespace std;

int Algorithms:: NN(Graph* graph)
{ 
	int  current = 0, result = 0, minCost = INT_MAX, minIndex = 0, i = 0, j = 0, n = graph->size;
	vector<int> route;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (graph->costs[i][j] < minCost)
				if (i!=j)
				{
					minCost = graph->costs[i][j];
					minIndex = i;
				}
		}
	}

	current = minIndex;
	route.push_back(current);


	do
	{
		minCost = INT_MAX;
		for (i = 0; i < graph->size; i++)
		{
			if(graph->costs[current][i]<minCost )
				if(current!=i)
					if (find(route.begin(), route.end(), i) == route.end())
					{
						minCost = graph->costs[current][i];
						minIndex = i;
					}
						
		
		}
		if (current == minIndex)
		{
			cout << "Graf nie jest grafem Hamiltonowskim" << endl;
			return 0;
		}
		current = minIndex;
		route.push_back(current);
		result = result + minCost;
	} while (route.size() < graph->size);
	


	route.push_back(route.at(0));
	result = result + graph->costs[current][route.at(0)];
	cout << "Cykl Hamiltona: ";
	for (int i = 0; i < route.size(); i++)
	{
		cout << route[i]<<" ";
	}
	cout << endl;
	return result;
}

int Algorithms::NN(Graph* graph, std::vector<int>& route)
{
	int  current = 0, result = 0, minCost = INT_MAX, minIndex = 0, i = 0, j = 0, n = graph->size;
	
	for (i = 0; i < route.size() - 1; i++)
	{
		result += graph->costs[route[i]][route[i + 1]];
	}
	current = route.at(route.size()-1);


	do
	{
		minCost = INT_MAX;
		for (i = 0; i < graph->size; i++)
		{
			if (graph->costs[current][i] < minCost)
				if (current != i)
					if (find(route.begin(), route.end(), i) == route.end())
					{
						minCost = graph->costs[current][i];
						minIndex = i;
					}


		}
		if (current == minIndex)
		{
			cout << "Graf nie jest grafem Hamiltonowskim" << endl;
			return 0;
		}
		current = minIndex;
		route.push_back(current);
		result = result + minCost;
	} while (route.size() < graph->size);



	route.push_back(route.at(0));
	result += graph->costs[current][route.at(0)];
	cout << "Cykl Hamiltona: ";
	for (int i = 0; i < route.size(); i++)
	{
		cout << route[i] << " ";
	}
	cout << endl;
	return result;
}

int Algorithms::upperBound(Graph* graph, vector<int>& route)
{
	int  current = 0, result = 0, minCost = INT_MAX, minIndex = 0, i = 0, j = 0, n = graph->size;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (graph->costs[i][j] < minCost)
				if (i!=j)
				{
					minCost = graph->costs[i][j];
					minIndex = i;
				}
		}
	}

	current = minIndex;
	route.push_back(current);


	do
	{
		minCost = INT_MAX;
		for (i = 0; i < graph->size; i++)
		{
			if (graph->costs[current][i] < minCost)
				if (current!=i)
					if (find(route.begin(), route.end(), i) == route.end())
					{
						minCost = graph->costs[current][i];
						minIndex = i;
					}


		}
		if (current == minIndex)
		{
			cout << "Graf nie jest grafem Hamiltonowskim" << endl;
			return 0;
		}
		current = minIndex;
		route.push_back(current);
		result = result + minCost;
	} while (route.size() < graph->size);



	
	result += graph->costs[current][route.at(0)];
	return result;
}



int Algorithms::bruteForceSTL(Graph* graph)
{
	int  result = INT_MAX, i = 0, n = graph->size, partResult = 0;
	int * tab = new int[n];


	//inicjacja tablicy permutacji - podanie pierwszej z nich
	for (i = 0; i < n; i++)
	{
		tab[i] = i;
	}

	do
	{
		partResult = graph->calculateHamiltonsCost(tab);
		//cout << "Wynik czesciowy: " << partResult << endl;

		if (partResult < result)
			result = partResult;
	} while (std::next_permutation(tab, tab + n));


	delete[] tab;


	return result;
}

//inicjalizacja algorytmu silowego
int Algorithms::bruteForce(Graph* graph)
{
	int  resultInt = INT_MAX, i = 0, n = graph->size;
	//tablica przechowujaca poszczegolne permutacje
	int * tab = new int[n];
	//tablica przechowujaca wynik (cykl+koszt)
	int * result = new int[n + 1];
	result[n] = INT_MAX;

	//inicjacja tablicy permutacji - podanie pierwszej z nich
	for (i = 0; i < n; i++)
	{
		tab[i] = i;
	}
	

	 bruteForce(graph, tab, n,result);
	 delete[] tab;
	 resultInt = result[n];

	 //wyswietlenie minimalnego cyklu
	 cout <<endl<< "Cykl Hamiltona: " << endl;
	 for (i = 0; i < n; i++)
	 {
		 cout << result[i] << " ";
	 }
	 cout << result[0] << endl;
	 delete[] result;


return resultInt;
}

void swapA(int &x, int&y)
{
	int tmp = x;
	x = y;
	y = tmp;
}


//rekurencyjna czesc algorytmu na bazie algorytmu Heapa
void Algorithms::bruteForce(Graph* graph, int tab[], int n, int result[])
{
	int i = 0, x = graph->size, partResult = 0;
	
	//n- glebokosc rekurencji
	if (n == 1)
	{
		//wyswietlanie kazdej z permutacji
		/*
		for (int i = 0; i < x; i++)
			cout << tab[i] << " ";
		printf("\n");
		*/

		//obliczenie kosztu danej permutacji
		partResult = graph->calculateHamiltonsCost(tab);

		//wynieranie najlepszej sciezki
		if (partResult < result[x])
		{
			for (i = 0; i < x; i++)
			{
				result[i] = tab[i];
			}
			result[x] = partResult;
		}
			

	}

	else
	{
		//wygeneruj perimutacje z niezmienionym n-tym elementem
		bruteForce(graph, tab, n - 1,result);

		for (i = 0; i < n - 1; i++)
		{

			if (n % 2 == 0)
				swapA(tab[i], tab[n - 1]);
			else
				swapA(tab[0], tab[n - 1]);

			bruteForce(graph, tab, n - 1,result);
		}
	}
}


int Algorithms::bound(Graph* graph,const vector<int>& path)
{
	int tmp = 0, bound = 0,i=0, j=0, n = graph->size;
	//okreslenie bound dla korzenia - suma minimalnych wyjsc z wierzcholka
	if (path.size() == 1)
	{	
		for (i = 0; i < n; i++)
		{
			tmp = INT_MAX;
			for (int j = 0; j < n; j++)
			{
				if (tmp > graph->costs[i][j])
					if(i!=j)
						tmp = graph->costs[i][j];
				
			}
			
			bound += tmp;
		}
		
		return bound;
	}

	//dla elementow ktore sa juz w czesciowym rozwiazaniu
	for (i = 0; i < path.size() - 1; i++)
	{
			bound += graph->costs[path[i]][path[i + 1]];
	}


	if (path.size() == n)
	{
		bound += graph->costs[path[n-1]][path[0]];
		return bound;
	}

	//dla elementow, ktorych nie ma jeszcze czesciowym rozwiazaniu znajdujemy krawedzie o min koszcie 
	for ( i = 0; i < n; i++)  
	{
		//pomija elementy ktore sa w czesciowym rozwiazaniu (poza ostatnim odwiedzanym)
		if (find(path.begin(), path.end(), i) != path.end() && i!=path.at(path.size()-1))
			continue;

			
		tmp = INT_MAX;
		for ( j = 0; j < n; j++)
		{
			//pomija 1 kolumne dla ostatniego wezla w rozwiazaniu czesciowym
			if (i == path.at(path.size()-1) && j == path.at(0))
				continue;

			//pomija kolumny ktore sa juz w rozwiazaniu czesciowym (ale sprawdza powrot od 1 elementu)
			else if (find(path.begin(), path.end(), j) != path.end() &&  j != path.at(0))
				continue;
				
			if (tmp > graph->costs[i][j])
				if(i!=j)
					tmp = graph->costs[i][j];

		}
		bound += tmp;

	}

	return bound;
}
int Algorithms::BnB(Graph* graph)
{
	int  i = 0, n = graph->size;
	int bound = INT_MAX, bestFound=INT_MAX, minBound= INT_MAX, minIndex= INT_MAX;
	vector<int> bestPath;

	//w kolejce prioryterowej jest para bound i path
	typedef pair<int, vector<int>> node;
	node tmpNode;

	priority_queue <node, vector<node>, greater<node>> tree;

	
	//inicjalizacja upperBound na podstawie algorytmu nearest neighbour
	bestFound = Algorithms::upperBound(graph, bestPath);


	//inicjalizacja korzenia
	vector<int> path;
	path.push_back(0);
	bound = Algorithms::bound(graph, path);
	tree.push(make_pair(bound, path));

	
	while (!tree.empty())
	{

			tmpNode = tree.top();
			tree.pop();
		

		if (tmpNode.first < bestFound)
		{
			//przeszukuje wszystkich synow wezla
			for (i = 0; i < n; i++)
			{
				if (find(tmpNode.second.begin(), tmpNode.second.end(), i) == tmpNode.second.end())
				{
					vector<int> path2 = tmpNode.second;
					path2.push_back(i);
					int bound2 = Algorithms::bound(graph, path2);

					//jesli mamy juz pelen cykl hamiltona
					if (path2.size() == n)
					{
						//jesli wartosc cyklu jest mniejsza niz najlepsza znaleziona
						if (bound2 < bestFound)
						{
							bestFound = bound2;
							bestPath = path2;
						}
					}

					//jesli wezel jest obiecujacy
					if (bound2 < bestFound)
					{
						try
						{
							tree.push(make_pair(bound2, path2));
						}
						catch (bad_alloc)
						{
							cout << "Koniec pamieci." << " Najlepsze rozwiazanie: " << endl;
							for (i = 0; i < n; i++)
							{
								cout << bestPath.at(i) << " ";
							}
							cout << bestPath.at(0)<< endl;
							return bestFound;

						}

							
					}
				}
			}
		}

		
	}

	cout <<endl<< "Cykl Hamiltona: " << endl;
	for (i = 0; i < bestPath.size(); i++)
	{
		cout << bestPath.at(i) << " ";
	}
	cout << bestPath.at(0)<< endl;
	return bestFound;
	
}

int Algorithms::DP(Graph* graph)
{
	int i = 0, j = 0, n = graph->size;

	vector<int> path;
	int result  = INT_MAX;
	int ** D = new int*[n];
	try {
		for (int i = 0; i < n; i++)
			D[i] = new int[(1 << n) - 1];
	}
	catch (bad_alloc)
	{
		cout << "Koniec pamieci. " << endl;
		return 0;
	}
	

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < (1 << n) - 1; j++) 
			D[i][j] = INT_MAX;
	//n*2^n - zlozonosc pamieciowa


	result = Algorithms::DP(graph,0, 1,D);//lvl=0; visited=1(000..0001)->ostatni
	cout << endl;

	//trasa
	path.push_back(0);
	int visited = 1;
	int lastId = 0;
	int opt = result;

	while (path.size() < n - 1)
	{
		for (i = 0; i < n; i++)
		{
			//sprzawdz czy juz nie odwiedzone
			if ((1 << i) & visited) 
				continue;

			if (D[i][(1 << i) | visited] + graph->costs[lastId][i] == opt)
			{
				visited = visited | (1 << i);
				lastId = i;
				opt = D[i][(1 << i) | visited];
				path.push_back(i);
				break;
			}
		}
	}
	for (i = 1; i < n; i++)
	{
		//ostatni z trasy
		if (((1 << i) & visited) == 0)
		{
			path.push_back(i);
			break;
		}
	}

	//wyswietlenie calej trasy
	cout << "Cykl Hamiltona: " << endl;
	for (i = 0; i < path.size(); i++) 
		cout << path[i] << " ";

	cout << path.at(0) << endl;

	return result;
}

int Algorithms::DP(Graph* graph, int lvl, int visited, int **D)
{
	int i = 0, j = 0, n = graph->size;

	//droga powrotna do 0 gdy wszystkie odwiedzone
	if (visited == ((1 << n) - 1)) 
		return graph->costs[lvl][0]; 

	//wierzcholek odwiedzony wczesniej
	if (D[lvl][visited] < INT_MAX) 
		return D[lvl][visited]; 

	for (int i = 0; i < n; i++)
	{
		//je¿li odwiedzone lub droga do samego siebie pomin
		bool alredyVisited = (visited & (1 << i));

		if (i == lvl || alredyVisited) 
			continue;

		int d = DP(graph,i, (visited | (1 << i)),D);

		//poszukiwanie minimum
		if (graph->costs[lvl][i] + d < D[lvl][visited])
		{
			D[lvl][visited] = graph->costs[lvl][i] + d;
		}

	}
	return D[lvl][visited];
}