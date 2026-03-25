#include<iostream>
#include<Windows.h>
#include<fstream>
#include<conio.h>
#include<chrono>

#include"Graph.h"

using namespace std;
using namespace chrono;

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char key1, key2;
	bool flag1 = true, flag2 = true;
	int start, finish, index;

	// переменные необходимые, чтобы засекать время
	steady_clock::time_point begin, end;
	microseconds duration;

	ifstream file;

	Graph grph;

	// пользовательский интерфейс
	cout << "\t\t\t< Добро пожаловать! >" << endl;
	do {
		cout << endl << "---------------------------------->| Главное меню |<---------------------------------" << endl << endl;
		cout << "1 режим - заполнить граф из файла и выбрать способ нахождения пути;" << endl
			<< "2 режим - сформировать граф из данных пользователя и выбрать способ нахождения пути." << endl
			<< "Любая другая клавиша для завершения работы программы." << endl;
		cout << endl << "-------------------------------------------------------------------------------------" << endl;
		key1 = _getch();

		switch (key1) {
		// 1 режим - работа с графом из файла
		case '1':
			file.open("input.txt");
			file >> grph;

			cout << "Граф:" << endl << grph << endl;
			cout << "\tВыберите способ нахождения пути:"<< endl
				<< "\t1 - Алгоритм поиска в глубину;" << endl
				<< "\t2 - Алгоритм поиска в ширину;" << endl
				<< "\tЛюбая другая клавиша для выхода в главное меню." << endl;
			
			key2 = _getch();

			if (key2 == '1' || key2 == '2') {
				cout << "Введите стартовую вершину и конечную соответственно: ";
				cin >> start >> finish;
			}

			// нахождение пути выбраным способом
			switch (key2) {
			case '1':
				cout << endl << "Путь найденый алгоритмом поиска в глубину:" << endl;
				begin = high_resolution_clock::now();
				grph.DFS(start, finish);
				end = high_resolution_clock::now();
				duration = duration_cast<microseconds>(end - begin); // расчет времени нахождения пути

				grph.wayOut();
				cout << "Время: " << duration.count() << " мкс.";
				break;

			case '2':
				cout << endl << "Путь найденый алгоритмом поиска в ширину:" << endl;
				begin = high_resolution_clock::now();
				grph.BFS(start, finish);
				end = high_resolution_clock::now();
				duration = duration_cast<microseconds>(end - begin);

				grph.wayOut();
				cout << "Время: " << duration.count() << " мкс.";
				break;

			default:
				break;
			}
			file.close();
			break;

			// 2 режим - работа с пользовательским графом
		case '2':
			cin >> grph;
			flag2 = true;

			do {
				cout << "\tВыберите действие:" << endl
					<< "\t1 - Добавить вершину;" << endl
					<< "\t2 - Добавить ребро;" << endl
					<< "\t3 - Удалить вершину;" << endl
					<< "\t4 - Удалить ребро;" << endl
					<< "\t5 - Найти выход." << endl << endl;

				key2 = _getch();

				// редактирование графа
				switch (key2) {
				case '1':
					grph.addVertex();
					cout << "Вершина добавлена." << endl << endl;
					break;

				case '2':
					cout << "Введите индексы двух вершин, между которыми добавить ребро: ";
					cin >> start >> finish;
					grph.addEdge(start, finish);
					cout << "Ребро добавлено." << endl << endl;
					break;

				case '3':
					cout << "Введите индекс вершины, связи которой хотите удалить: ";
					cin >> index;
					grph.delVertex(index);
					cout << "Все связи вершины удалены." << endl << endl;
					break;

				case '4':
					cout << "Введите индексы двух вершин, между которыми удалить ребро: ";
					cin >> start >> finish;
					grph.delEdge(start, finish);
					cout << "Ребро удалено." << endl << endl;
					break;

				case '5':
					flag2 = false;
					break;

				default:
					break;
				}

			} while (flag2);

			cout << "Граф:" << endl << grph << endl;
			cout << "\tВыберите способ нахождения пути:" << endl
				<< "\t1 - Алгоритм поиска в глубину;" << endl
				<< "\t2 - Алгоритм поиска в ширину;" << endl
				<< "\tЛюбая другая клавиша для выхода в главное меню." << endl << endl;

			key2 = _getch();

			if (key2 == '1' || key2 == '2') {
				cout << "Введите стартовую вершину и конечную соответственно: ";
				cin >> start >> finish;
			}

			// нахождение пути выбранным способом
			switch (key2) {
			case '1':
				cout << endl << "Путь найденый алгоритмом поиска в глубину:" << endl;
				begin = high_resolution_clock::now();

				grph.DFS(start, finish);
				end = high_resolution_clock::now();
				duration = duration_cast<microseconds>(end - begin);

				grph.wayOut();
				cout << "Время: " << duration.count() << " мкс.";
				break;

			case '2':
				cout << endl << "Путь найденый алгоритмом поиска в ширину:" << endl;
				begin = high_resolution_clock::now();
				grph.BFS(start, finish);
				end = high_resolution_clock::now();
				duration = duration_cast<microseconds>(end - begin);

				grph.wayOut();
				cout << "Время: " << duration.count() << " мкс.";
				break;

			default:
				break;
			}
			break;

		default:
			flag1 = false;
			break;
		}
	} while (flag1);
}