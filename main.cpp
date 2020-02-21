
#include "pch.h"

using namespace std;

void dispx(std::vector<int>& a)
{

	for (int i = 0; i < a.size(); i++)
	{
		cout << a.at(i) << " ";
	}
	cout << endl;
}

int main()
{
	double timex;
	char menu;
	Timer timer;
	int wynik, wynik2, wynik3, tmp;

	double czas, brute, bound, dynamic;

	Graph* graph;
	graph = new Graph("rbg403.atsp");

	//Heuristics::GA(graph);
	
	
	string linia;
	ifstream nazwy("filenames3.txt");

	if (nazwy.is_open())
	{

		while ( getline (nazwy,linia) )
		{
			graph = new Graph(linia);

						 cout << graph->getName() <<"; ";
						 // cout << endl << "Genetic algorithm, kalkuluje koszt. " << endl;
						  //timer.startCounter();
						  wynik = Heuristics::GA(graph);
						  //cout << "Wynik to: " << wynik << endl;
						  cout <<((double)(wynik - graph->getOptimum()) / graph->getOptimum() * 100) << "; "<<endl;
						  //cout <<(double) (timer.getCounter()) << "; " << endl;
						 //cout<<endl;
		}
		nazwy.close();
	}
	
	
	_getch();
	

	/*
		while (1)
		{
			
			system("cls");
			
			cout << "Aktualny graf: " << graph->getName() <<endl<<"Wielkosc: "<<graph->getSize()<<" Optimum: "<<graph->getOptimum()<<endl<<endl;
			cout << "Wyswietl graf        [1]" << endl;
			cout << "Policz koszt sciezki [2]" << endl;
			cout << "Wczytaj nowy graf    [3]" << endl;
			cout << "Generuj losowy graf  [4]" << endl;
			cout << "------------------------" << endl;
			cout << "Algorytm NN          [5]" << endl;
			cout << "Tabu search          [6]" << endl;
			cout << "SA algorithm         [7]" << endl;
			cout << "Dynamic programming  [8]" << endl;
			cout << "Genetic              [9]" << endl;

			menu = _getch();

			switch (menu)
			{
				case '1': graph->display(); 
						  _getch(); 
						  break;
				case '2': cout <<endl<< "Koszt podanej sciezki to: " << graph->calculateCost() << endl << endl;
					      _getch();
						  break;
				case '5': cout <<endl<< "Nearest neighbour, kalkuluje koszt. " << endl;
						  timer.startCounter();
						  wynik = Algorithms::NN(graph);
						  cout << "Wynik to: " << wynik << endl;
						  cout << "Blad wyniku: " << ((double)(wynik - graph->getOptimum()) / graph->getOptimum() * 100 )<< "% " << endl;
						  cout << "Czas: " << timer.getCounter() << "s" << endl;
						  _getch();
						  break;
				case '3': 
					
						try
						{
							delete graph; 
							graph = new Graph();
						}
						catch (int e)
						{
							_getch();
							graph = new Graph("m6.atsp");
						}
						
						  break;
				case '6': cout << endl << "Tabu search, kalkuluje koszt. " << endl;
						  timer.startCounter();
						  wynik = Heuristics::tabu(graph);
						  cout << "Wynik to: " << wynik << endl;
						  cout << "Blad wyniku: " << ((double)(wynik - graph->getOptimum()) / graph->getOptimum() * 100) << "% " << endl;
						  cout << "Czas: " << timer.getCounter() << "s" << endl;
						  _getch();
						  break;
				case '7': cout << endl << "SA, kalkuluje koszt. " << endl;
						  timer.startCounter();
						  wynik = Heuristics::SA(graph);
						  cout << "Wynik to: " << wynik << endl;
						  cout << "Blad wyniku: " << ((double)(wynik - graph->getOptimum()) / graph->getOptimum() * 100) << "% " << endl;
						  cout << "Czas: " << timer.getCounter() << "s" << endl;
						  _getch();
						  break;
				case '8': cout << endl << "Dynamic programming, kalkuluje koszt. " << endl;
						  timer.startCounter();
						  wynik = Algorithms::DP(graph);
						  cout << "Wynik to: " << wynik << endl;
						  cout << "Blad wyniku: " << ((double)(wynik - graph->getOptimum()) / graph->getOptimum() * 100) << "% " << endl;
						  cout << "Czas: " << timer.getCounter() << "s" << endl;
						  _getch();
					break;

				case '4':
					cout<< endl<< "Generowanie losowej instancji. " << endl;
					cout << "Podaj rozmiar: ";
					cin >> tmp;
					delete graph; graph = new Graph(tmp);
					break;		  
				case '9':

						  cout << endl << "Genetic algorithm, kalkuluje koszt. " << endl;
						  timer.startCounter();
						  wynik = Heuristics::GA(graph);
						  cout << "Wynik to: " << wynik << endl;
						  cout << "Blad wyniku: " << ((double)(wynik - graph->getOptimum()) / graph->getOptimum() * 100) << "% " << endl;
						  cout << "Czas: " <<(double) (timer.getCounter()/60) << " min" << endl;
						  _getch();
						
						


						break;
				default: break;
			}
			
		}
		
	
	
	*/

}

