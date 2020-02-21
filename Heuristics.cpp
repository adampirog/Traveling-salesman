#include "pch.h"
using namespace std;

void disp(std::vector<int>& a)
{

	for (int i = 0; i < a.size(); i++)
	{
		cout << a.at(i) << " ";
	}
	cout << endl;
}

void Heuristics::display(std::vector<candidate>& a)
{

	for (int i = 0; i < a.size(); i++)
	{
		cout << a.at(i).a << " " << a.at(i).b << " " << a.at(i).c << endl;
	}
	cout << endl;
}

void Heuristics::display(std::deque<candidate>& a)
{

	for (int i = 0; i < a.size(); i++)
	{
		cout << a.at(i).a << " " << a.at(i).b << " " << a.at(i).c << endl;
	}
	cout << endl;
}

int Heuristics::SA(Graph* graph)
{
	//result przechowuje najmniejszy znaleziony koszt, route przechowuje trase
	int  current = 0, tmpResult = 0, result = 0, previousResult = 0, minCost = INT_MAX, minIndex = 0, i = 0, j = 0, n = graph->size;

	vector<int> route;
	std::vector<int> tmpRoute;

	//dlugosc schodka
	int stepLength = (pow(n, 2) / 2), stagnation = 0,stagnationLimit =(pow(n, 2) / 4) ;
	double cooling = 0.97;
	bool noswap = false;

	//Gorne ograniczenie - algorytm najbizszego sasaida
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (graph->costs[i][j] < minCost)
				if (i != j)
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

	result = result + graph->costs[current][route.at(0)];
	tmpRoute = route;
	tmpResult = result;
	//Koniec najblizszego sasiada


	double temp = 20000, mintemp = 1;
	//kandydaci do zamiany
	int a, b, delta;

	std::default_random_engine generator;
	std::uniform_real_distribution<double> tempDistrib(0.0, 1.0);
	std::uniform_int_distribution<int> indexDistrib(0, n - 1);


	//Glowna petla algorytmu
	while (temp > mintemp)
	{
		//zatrzymanie stalej temperatury na schodku
		for (int i = 0; i < stepLength; i++)
		{
			//indexy do zamiany
			a = indexDistrib(generator);
			b = indexDistrib(generator);


			previousResult = tmpResult;

			std::swap(tmpRoute[a], tmpRoute[b]);
			tmpResult = graph->calculateHamiltonsCost(tmpRoute);
			delta = tmpResult - previousResult;

			std::swap(tmpRoute[a], tmpRoute[b]);
			tmpResult = graph->calculateHamiltonsCost(tmpRoute);


			
			//poprawa rozwiazania
			if ((delta <= 0))
			{
				//cout << "Poprawa" << endl;
				std::swap(tmpRoute[a], tmpRoute[b]);
				tmpResult = graph->calculateHamiltonsCost(tmpRoute);
				stagnation = 0;
				
			}
			//spelnione prawdopodobienstwo
			else if ((exp((-delta) / temp) > tempDistrib(generator)))
			{
				//cout << "Wchodze w pogorszenie" << endl;
				std::swap(tmpRoute[a], tmpRoute[b]);
				tmpResult = graph->calculateHamiltonsCost(tmpRoute);
				stagnation = 0;
			}
			else
			{
				stagnation++;

				if (stagnation >= stagnationLimit)
				{
					//cout << "Stagnacja" << endl;
					srand(time(NULL));

					for (int i = n - 1; i > 0; i--)
					{
						int x = rand() % (i + 1);
						std::swap(tmpRoute[i], tmpRoute[x]);
					}
					stagnation = 0;

					tmpResult = graph->calculateHamiltonsCost(tmpRoute);

				}
					
			}

			//aktualizacja najlepszego wyniku
			if (tmpResult < result)
			{
				result = tmpResult;
				route = tmpRoute;
				//cout << "Wynik" << result << endl;
				//cout << "Blad wyniku: " << ((double)(result - graph->getOptimum()) / graph->getOptimum() * 100 )<< "% " << endl;
			}
		}


		//ochlodzenie
		temp *= cooling;

	}
	//disp(route);
	return result;

}

int Heuristics::tabu(Graph* graph)
{
	//result przechowuje najmniejszy znaleziony koszt, route przechowuje trase
	int  current = 0, tmpResult = 0,result = 0, previousResult=0, minCost = INT_MAX, minIndex = 0, i = 0, j = 0, n = graph->size;


	bool allTabu = false;

	//licznik braku porpaw, licznik przepelnienia tabu
	int stagnation = 0, allTabuCounter = 0;

	int stagnationLimit = 500, allTabuLimit = (n/2), iterationLimit = 10000, timeLimit = 60, penalty = 15;

	Timer timer;
	vector<int> route;
	vector<int> tmpRoute;

	unsigned long long int mainLoop = 0;


	//Gorne ograniczenie - algorytm najbizszego sasaida
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (graph->costs[i][j] < minCost)
				if (i != j)
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

	result = result + graph->costs[current][route.at(0)];
	tmpRoute = route;
	tmpResult = result;
	//Koniec najblizszego sasiada
	
	
	//inicjalizacja listy kandydatow
	deque<candidate> candidates;
	int candidateBound = refreshCandidates(graph, tmpRoute,tmpResult, candidates);

	//inicjalizacja listy tabu 
	vector<candidate> tabu; 
	vector<candidate>::iterator tabuIterator;
	candidate bestCandidate;

    //cout << "Start: " << endl;
	//disp(tmpRoute);
	//cout << tmpResult << endl;


	//ograniczenie czasowe
	timer.startCounter();

	for (mainLoop = 0; mainLoop < iterationLimit; mainLoop++)
	{


		//cout << "ITERACJA: " << mainLoop << endl;


		//zapisanie poprzedniego wyniku iteracji w ramach potrzeby badania stagnacji
		previousResult = tmpResult;
		
		//sprawdz czy lista kandydatow nie jest pusta 
		if (candidates.size() == 0)
		{
			//cout << "Lista kandydatow pusta" << endl;
			int candidateBound = refreshCandidates(graph, tmpRoute, tmpResult, candidates);
		}
		else
		{
			//cout << "Odswiezam koszt kandydatow" << endl;
			refreshCandidatesCosts(graph, tmpRoute, tmpResult, candidates);

			//sprawdz czy lista kandydatow nie jest przeterminowana
			if (candidates.front().c > candidateBound)
			{
				//cout << "Lista kandydatow przeterminowana" << endl;
				int candidateBound = refreshCandidates(graph, tmpRoute, tmpResult, candidates);
			}
		}
		
		//cout << "Lista kandydatow: " << endl;
		//Heuristics::display(candidates);
		//cout << "Lista tabu: " << endl;
		//Heuristics::display(tabu);

		//pobierz kadydata
		bestCandidate = candidates.front();
		tabuIterator = std::find(tabu.begin(), tabu.end(), bestCandidate);


		//jesli kandydata nie ma na liscie tabu
		if (tabuIterator == tabu.end())
		{
			//cout << "Najlepszy kandydat NIE na tabu" << endl;

			//usun go z listy kandydatow
			candidates.pop_front();

			//wykonaj ruch, akutalizuj zapamietane rezultaty
			std::swap(tmpRoute.at(bestCandidate.a), tmpRoute.at(bestCandidate.b));
			tmpResult += bestCandidate.c;


			//dodaj ruch do listy tabu
			bestCandidate.c = penalty;
			tabu.push_back(bestCandidate);


			
				


			
		}
		//jesli kandydat jest na liscie tabu
		else
		{
			//cout << "Najlepszy kandydat na tabu" << endl;

			//jesli jest to globalnie najlepsze rozwiazanie - zignoruj tabu
			if (tmpResult + bestCandidate.c < result) 
			{

				//cout << "Globalna poprawa" << endl;
				//usun go z listy kandydatow
				candidates.pop_front();

				//wykonaj ruch, akutalizuj zapamietane rezultaty
				std::swap(tmpRoute.at(bestCandidate.a), tmpRoute.at(bestCandidate.b));
				tmpResult += bestCandidate.c;


				//aktualizuj wpis na liscie tabu
				(*tabuIterator).c = penalty;



			}


			//SPRAWDZENIE POZOSTALYCH KANDYDATOW
			for (i = 1; i < candidates.size(); i++)
			{
				bestCandidate = candidates.at(i);
				tabuIterator = std::find(tabu.begin(), tabu.end(), bestCandidate);

				//jesli nowego kandtdata nie ma na liscie tabu
				if (tabuIterator == tabu.end())
				{
					//cout << i << " kandydat NIE na tabu" << endl;
					//usun go z listy kandydatow
					std::swap(candidates.at(0), candidates.at(i));
					candidates.pop_front();

					//wykonaj ruch, akutalizuj zapamietane rezultaty
					std::swap(tmpRoute.at(bestCandidate.a), tmpRoute.at(bestCandidate.b));
					tmpResult += bestCandidate.c;


					//dodaj ruch do listy tabu
					bestCandidate.c = penalty;
					tabu.push_back(bestCandidate);


					//aktualizuj najlepsza znaleziona trase


					//przerwij przeszukiwanie pozostalych kandydatow
					allTabu = false;
					break;
				}
				else
				{
					//nowy kandydat tez jest na liscie tabu
					allTabu = true;
				}
				
			}

			if (allTabu == true)
			{
				
				//WSZYSCY KANDYDACI SA NA LISCIE TABU - odsiwez liste tabu 
				//cout << "Wszyscy tabu" << endl;

				if (allTabuCounter >= allTabuLimit)
				{
					//cout << "Kolejne przepelnienia tabu" << endl;
					//gdy taby jest pelne wiele razy pod rzad zlam tabu - usun wszystkie wpisy ponizej polowy kadencji

					for (tabuIterator = tabu.begin(); tabuIterator != tabu.end(); tabuIterator++)
					{
					
						if ((*tabuIterator).c < (penalty/2))
						{
							tabu.erase(tabuIterator--);
						}
					}
					mainLoop--;
				}
				else
				{
					int candidateBound = refreshCandidates(graph, tmpRoute, tmpResult, candidates);
					mainLoop--;
				}

			}
			else
			{
				allTabuCounter = 0;
			}
				
			
			
		}


		//aktualizacja kadencji tabu
		for (tabuIterator = tabu.begin(); tabuIterator != tabu.end(); tabuIterator++)
		{
			(*tabuIterator).c--;
			if ((*tabuIterator).c <= 0)
			{
				tabu.erase(tabuIterator--);
			}
		}


		if (tmpResult >= previousResult)
			stagnation++;

		if (stagnation >= stagnationLimit)
		{
			//cout << "Stagnacja, mieszam sciezke " << endl;

			srand(time(NULL));

			for (int i = n - 1; i > 0; i--)
			{
				int x = rand() % (i + 1);
				std::swap(tmpRoute[i], tmpRoute[x]);
			}
			stagnation = 0;

			tmpResult = graph->calculateHamiltonsCost(tmpRoute);
		}

		//aktualizuj najlepsza znaleziona trase

		if (tmpResult < result)
		{
			result = tmpResult;
			route = tmpRoute;

			//cout << "Wynik" << result << endl;
			//cout << "Blad wyniku: " << ((double)(result - graph->getOptimum()) / graph->getOptimum() * 100) << "% " << endl;
		}

		if (timer.getCounter() >= timeLimit)
		{
			//cout << "Czas: " << timer.getCounter() << endl;
			disp(route);
			return result;
		}

		//cout << "Po  iteracji: " << mainLoop << endl;
		//disp(tmpRoute);
		//cout << tmpResult << endl;

	}

	disp(route);
	return result;
}




int Heuristics::refreshCandidates(Graph* graph, std::vector<int>& currentRoute,int currentResult, std::deque<candidate>& candidates)
{
	//DLUGOSC LIST KANDYDATOW
	int maxSize = graph->size;

	int tmpResult, tmpCandidateCost;
	vector<int> tmpRoute;
	int n = graph->size,i,j;
	candidates.clear();
	candidate tmpCandidate;

	tmpRoute = currentRoute;
	tmpResult = currentResult;

	//cout << "Cale sasiedztwo: " << endl;
	
	for (i = 0; i < n; i++)
	{

		for (j = i+1; j < n; j++)
		{	
			
				std::swap(tmpRoute.at(i), tmpRoute.at(j));
				tmpResult = graph->calculateHamiltonsCost(tmpRoute);
				tmpCandidateCost = tmpResult - currentResult;

				//cout << i << " " << j << " " << tmpCandidateCost << endl;

				tmpCandidate.a = i;
				tmpCandidate.b = j;
				tmpCandidate.c = tmpCandidateCost;
				

				if (candidates.size() == 0)
				{
					candidates.push_back(tmpCandidate);
				}
				else if (candidates.back().c > tmpCandidateCost)
				{

					candidates.push_back(tmpCandidate);

					std::sort(candidates.begin(), candidates.end());

					if (candidates.size() > maxSize)
						candidates.pop_back();
				}


				std::swap(tmpRoute.at(i), tmpRoute.at(j));
			
		}
	}


	return candidates.back().c;
}

int Heuristics::refreshCandidatesCosts(Graph* graph, std::vector<int>& currentRoute, int currentResult, std::deque<candidate>& candidates)
{
	vector<int> tmpRoute = currentRoute;
	int tmpResult;

	for (int i = 0; i < candidates.size(); i++)
	{
		std::swap(tmpRoute.at(candidates.at(i).a), tmpRoute.at(candidates.at(i).b));

		tmpResult = graph->calculateHamiltonsCost(tmpRoute);
		candidates.at(i).c = tmpResult - currentResult;

		std::swap(tmpRoute.at(candidates.at(i).a), tmpRoute.at(candidates.at(i).b));
	}

	std::sort(candidates.begin(), candidates.end());
}


int Heuristics::NN(Graph* graph, int startVertex, std::vector<int>& route)
{
	

	int minCost = INT_MAX, minIndex;
	int current, result=0;

	route.clear();
	current = startVertex;
	route.push_back(current);

	do
	{
		minCost = INT_MAX;
		for (int i = 0; i < graph->size; i++)
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

	result = result + graph->costs[current][route.at(0)];
	return result;
}

void Heuristics::mutate(std::vector<int>& route)
{

	double percentageChance = 0.1;

	//operator mutacji typu swap

	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> levelDist(1,4);
	std::uniform_int_distribution<int> indexDist(0,route.size()-1);
	std::uniform_real_distribution<double> chanceDist(0.0,100.0);

	int index, index2;

	//test probabilistyczny 

	double chance = chanceDist(generator);


	if (chance >= (percentageChance))
	{
		return;
	}
	//cout << "Mutuje" << endl;

	//ile razy bedzie realizowana operacja swap
	int level = levelDist(generator);
	

	for (int i = 0; i < level; i++)
	{
		index = indexDist(generator);
		do
		{
			index2 = indexDist(generator);

		}while (index == index2);


		swap(route[index], route[index2]);
	}

	

}

void Heuristics::cross(std::vector<int>& parent1, std::vector<int>& parent2, std::vector<int>& child1, std::vector<int>& child2)
{

	//krzyzowanie typu OX

	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> indexDist(1,parent1.size()-2);

	//indeksy czesci wspolnej 
	int index, index2;

	
	index = indexDist(generator);
	do
	{
		index2 = indexDist(generator);

	}while (index == index2);

	if (index > index2)
		swap(index, index2);
	

	//cout << index << " " << index2;
	//cout << endl;
	
	for (int i = index; i < index2+1 ; i++)
	{
		
		child1[i] = parent1[i];
	}
	

	int parentIndex = index2 + 1;
	bool next = false;
	//za czescia wspolna dziecka
	for (int i = index2+1; i < child1.size(); i++)
	{
		do
		{
			if (find(child1.begin(), child1.end(), parent2[parentIndex]) == child1.end())
			{
				child1[i] = parent2[parentIndex];
				next = true;
			}
		
			parentIndex++;
			if (parentIndex == parent2.size())
				parentIndex = 0;
		} while (next == false);
		
		next = false;
		

	}
	
	next = false;
	//przed czescia wspolna dziecka
	for (int i = 0; i < index ; i++)
	{
		
		do
		{
			if (find(child1.begin(), child1.end(), parent2[parentIndex]) == child1.end())
			{
				child1[i] = parent2[parentIndex];
				next = true;
			}
		
			parentIndex++;
			if (parentIndex == parent2.size())
				parentIndex = 0;
		} while (next == false);
		
		next = false;
	}

	//WYTWARZANIE DRUGIEGO POTOMKA


	for (int i = index; i < index2+1 ; i++)
	{
		
		child2[i] = parent2[i];
	}
	

	parentIndex = index2 + 1;
	next = false;
	//za czescia wspolna dziecka
	for (int i = index2+1; i < child2.size(); i++)
	{
		do
		{
			if (find(child2.begin(), child2.end(), parent1[parentIndex]) == child2.end())
			{
				child2[i] = parent1[parentIndex];
				next = true;
			}
		
			parentIndex++;
			if (parentIndex == parent1.size())
				parentIndex = 0;
		} while (next == false);
		
		next = false;
		

	}
	
	next = false;
	//przed czescia wspolna dziecka
	for (int i = 0; i < index ; i++)
	{
		
		do
		{
			if (find(child2.begin(), child2.end(), parent1[parentIndex]) == child2.end())
			{
				child2[i] = parent1[parentIndex];
				next = true;
			}
		
			parentIndex++;
			if (parentIndex == parent1.size())
				parentIndex = 0;
		} while (next == false);
		
		next = false;
	}
}


int Heuristics::localSearch(Graph* graph, std::vector<int>& route)
{

	int i, j, n = route.size(), result = INT_MAX, tmpResult=INT_MAX;
	vector<int> tmpRoute = route;
	//cout << "Cale sasiedztwo: " << endl;
	
	for ( i = 0; i < n; i++)
	{

		for ( j = i + 1; j < n; j++)
		{
			std::swap(tmpRoute.at(i), tmpRoute.at(j));
			tmpResult = graph->calculateHamiltonsCost(tmpRoute);

			if (tmpResult < result)
			{
				result = tmpResult;
				route = tmpRoute;
			}

			std::swap(tmpRoute.at(i), tmpRoute.at(j));
		}
	}

	return result;
}

int Heuristics::GA(Graph* graph)
{
	
	typedef pair<int, vector<int>> gene;
	
	vector<gene> population;
	 
	Timer timer;

	int n=graph->getSize(), bestCost=INT_MAX,index;

	double czas=3;
	//cout << "Czas w minutach: ";
	//cin >> czas;
	double timeLimit = czas * 60;
	int populationSize = 100,  tournamentSize = 25 ;
	
	unsigned int iterations = 5000;

	vector<int> bestPath, tournament;

	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> randomIndex(0,populationSize-1);
	srand(time(0));


	//inicjalizacja populacji
	if (n >= populationSize)
	{
		for (int i = 0; i < populationSize; i++)
		{
			vector<int> path;
			int cost = NN(graph, i, path);
			
			if (cost < bestCost)
			{
				bestCost = cost;
				bestPath = path;	
			}

			gene specimen(cost, path);
			population.push_back(specimen);
		}

	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			vector<int> path;
			int cost = NN(graph, i, path);
			
			if (cost < bestCost)
			{
				bestCost = cost;
				bestPath = path;	
			}

			gene specimen(cost, path);
			population.push_back(specimen);
		}

		for (int i = n; i < populationSize; i++)
		{
			vector<int> path;

			//losowa sciezka
			for (int j = 0; j < n; j++)
			{
				path.push_back(j);
			}

			random_shuffle(path.begin(), path.end());
			int cost = graph->calculateHamiltonsCost(path);

		
			if (cost < bestCost)
			{
				bestCost = cost;
				bestPath = path;
			}

			gene specimen(cost, path);
			population.push_back(specimen);
		}
	}
	


	
	//GLOWNA PETLA
	timer.startCounter();
	for (int mainLoop = 0; mainLoop < iterations; mainLoop++)
	{
		


		//wybor indeksów do turnieju
		tournament.clear();
		for (int i = 0; i < tournamentSize; i++)
		{
			do
			{
				index = randomIndex(generator);
			} while (find(tournament.begin(), tournament.end(), index) != tournament.end());

			tournament.push_back(index);

		}

		int winner1=INT_MAX, winner2=INT_MAX, winner1Value=INT_MAX, winner2Value=INT_MAX; 

		for (int i = 0; i < tournamentSize; i++)
		{
			if (population[tournament[i]].first< winner1Value)
			{

				winner2Value = winner1Value;
				winner1Value = population[tournament[i]].first;

				winner2 = winner1;
				winner1 = tournament[i];
			}
			else if (population[tournament[i]].first < winner2Value && tournament[i]!=winner1)
			{
				winner2 = tournament[i];
				winner2Value = population[tournament[i]].first;
			}
		}

		

		//krzyzowanie
		vector<int> childPath1(n, n+1), childPath2(n, n+1);
		int childCost1, childCost2;
		cross(population[winner1].second, population[winner2].second, childPath1, childPath2);

		//mutacja
		mutate(childPath1);
		mutate(childPath2);

		//BEZ LOCAL SEARCH
		//childCost1 = graph->calculateHamiltonsCost(childPath1);
		//childCost2 = graph->calculateHamiltonsCost(childPath2);

		//SEKCJA LOCAL SEARCH
		childCost1 = Heuristics::localSearch(graph, childPath1);
		childCost2 = Heuristics::localSearch(graph, childPath2);


		gene child1(childCost1, childPath1), child2(childCost2, childPath2);

		//uaktualnienie najlepszego wyniku
		if (child1.first < bestCost)
		{
				bestCost = child1.first;
				bestPath = child1.second;
		}

		if (child2.first < bestCost)
		{
				bestCost = child2.first;
				bestPath = child2.second;
		}

		population[randomIndex(generator)] = child1;
		population[randomIndex(generator)] = child2;

		if (timer.getCounter() > timeLimit)
		{
			//disp(bestPath);
			//cout << "Iteracje " << mainLoop << endl;
			return bestCost;
			
		}
		
	}

	//disp(bestPath);

	return bestCost;

}

