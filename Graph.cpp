#include "pch.h"
#include "Graph.h"

using namespace std;

Graph::Graph()
{
	int tmp;
	string fileName;
	cout << endl << "Wczytywanie nowego grafu" << endl;
	cout << "Podaj nazwe instancji:" << endl;
	cin >> fileName;
	fileName = "instancje/" + fileName;
	ifstream graphFile;
	graphFile.open(fileName);

	if (graphFile.is_open())
	{
		getline(graphFile, name);

		//Pobranie ilosci miast
		graphFile >> size;


		//Pobieranie wag sciezek
		for (int i = 0; i < size ; i++)
		{
			vector<int> row;
			for (int i = 0; i < size; i++)
			{
				graphFile >> tmp;
				row.push_back(tmp);
			}

			costs.push_back(row);
		}

		//Pobieranie optimum
		graphFile >> optimum;

	}
	else
	{
		cout << "Blad otwarcia pliku" << endl;
		throw -1;
	}
	

	graphFile.close();
}

Graph::Graph(int n)
{
	name = "Random";
	size = n;
	optimum = 0;


		for (int i = 0; i < n; i++)
		{
			vector<int> row;
			for (int j = 0; j < n; j++)
			{

				if (i == j)
					row.push_back(-1);
				else
					row.push_back(rand() % 100 + 1);
			}
			costs.push_back(row);
		}
}
Graph::Graph(string fileName)
{
	int tmp;
	fileName = "instancje/" + fileName;
	ifstream graphFile;
	graphFile.open(fileName);

	if (graphFile.is_open())
	{
		getline(graphFile, name);

		//Pobranie ilosci miast
		graphFile >> size;


		//Pobieranie wag sciezek
		for (int i = 0; i < size; i++)
		{
			vector<int> row;
			for (int i = 0; i < size; i++)
			{
				graphFile >> tmp;
				row.push_back(tmp);
			}

			costs.push_back(row);
		}

		//Pobieranie optimum
		graphFile >> optimum;


	}
	else
	{
		cout << "Blad otwarcia pliku" << endl;
	}


	graphFile.close();
}

void Graph::display()
{
	cout << endl;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout <<setw(4) << costs[i][j] << " ";
		}
		cout << endl;
	}
}

int Graph::calculateCost()
{
	vector<int> route;
	string buffer;
	int buffer2, result=0;
	cout << endl << "Podaj trase do obliczenia kosztu" << endl;

	//Podwojny bufor ze string na int aby wprowadzanie i wyjscie odbywalo sie plynnie
	while(1)
	{
		cin >> buffer;
		try 
		{
			buffer2 = stoi(buffer);
		}
		catch (invalid_argument& e)
		{
			break;
		}
		
		if(buffer2>=0 && buffer2<size)
			route.push_back(buffer2);
	} 


	//Wyswietlenie sciezki
	cout << "Podana sciezka: ";
	for (int i = 0; i < route.size(); i++)
	{
		cout << route.at(i) << " ";
	}
	cout << endl;


	for (int i = 0; i < route.size()-1; i++)
	{
		if(costs[route[i]][route[i + 1]] > 0)
			result = result + costs[route[i]][route[i + 1]];
	}

	

	return result;
}

int Graph::calculateHamiltonsCost(int route[])
{
	int  tmp=0, i=0;
	int result = costs[route[size - 1]][route[0]];
	
	for (i = 0; i < size - 1; i++)
	{
		tmp = costs[route[i]][route[i + 1]];
		if (tmp > 0)
			result += tmp;
	}


	return result;
}

int Graph::calculateHamiltonsCost(std::vector<int>& route)
{
	int  tmp = 0, i = 0;
	int result = costs[route[size - 1]][route[0]];

	for (i = 0; i < size - 1; i++)
	{
		tmp = costs[route[i]][route[i + 1]];
		if (tmp > 0)
			result += tmp;
	}


	return result;
}

string Graph::getName()
{
	return name;
}

int Graph::getSize()
{
	return size;
}

int Graph::getOptimum()
{
	return optimum;
}

Graph::~Graph()
{
	costs.clear();
}
