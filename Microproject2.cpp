
#include <iostream>
#include <thread>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <ctime>
using namespace std;

// Создание мьютекса.
mutex mtx;

// Создание глобальных переменных - число участков, пройденных садовниками, координаты участков (x - по горизонтали, у - по вертикали), двумерный массив сада и стартовое время работы, равное 0.
int taskNumber_1 = 0;
int taskNumber_2 = 0;
int x_1 = 0;
int y_1 = 0;
int x_2 = 1;
int y_2 = 1;
vector<vector<int>> garden;
int currentTime = 0;

/// <summary>
/// Метод выводит на экран текущее состояние сада.
/// </summary>
void printGarden()
{
	cout << "Current state of the garden:" << endl;
	for (size_t i = 0; i < garden.size(); i++)
	{
		for (size_t j = 0; j < garden[0].size(); j++)
		{
			cout << garden[i][j] << " ";
		}
		cout << endl;
	}
}

/// <summary>
/// Метод выводит на экран сгенерированный план.
/// </summary>
/// <param name="plan"> Сгенерированный план</param>
void printPlan(vector<vector<int>> plan)
{
	cout << "Plan of the garden:" << endl;
	for (size_t i = 0; i < plan.size(); i++)
	{
		for (size_t j = 0; j < plan[0].size(); j++)
		{
			cout << plan[i][j] << " ";
		}
		cout << endl;
	}
}

/// <summary>
/// Метод позволяет садовникам выполнить задачу по реализации нового участка сада и переходу на следующий участок.
/// </summary>
/// <param name="plan">План сада.</param>
/// <param name="threadNumber">Номер садовника (потока).</param>
void addGardenPart(vector<vector<int>> plan, int threadNumber)
{
	srand(time(0));

	// Считываем размеры сада по плану.
	int M = plan.size();
	int N = plan[0].size();

	// Ветка для первого садовника.
	if (threadNumber == 1)
	{
		// Ставим мьютекс, чтобы другой садовник не мешал работе.
		lock_guard<mutex> lock(mtx);

		// Выводим текущее состояние сада перед началом реализации нового участка.
		printGarden();

		// Если участок ещё не реализован, реализуем его за случайное количество секунд от 1 до 5, увеличиваем число пройденных участков, меняем координаты и переходим к следующему участку (если он есть).
		if (garden[y_1][x_1] == 0)
		{
			cout << "Time " << currentTime << ": gardener " << threadNumber << " started work on the plot " << y_1 << " " << x_1 << endl;
			currentTime += rand() % 5 + 1;
			garden[y_1][x_1] = plan[y_1][x_1];
			taskNumber_1++;
			if (x_1 != N - 1)
			{
				x_1++;
			}
			else
			{
				x_1 = 0;
				y_1++;
			}

			if (y_1 <= M - 1)
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " have done this plot and goes on the plot " << y_1 << " " << x_1 << endl;
				currentTime++;
			}
			else
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " have done the last plot and have finished his work in the garden" << endl;
				currentTime++;
			}
		}

		// Если участок уже реализован другим садовником, тратим от 1 до 3 секунд на то, чтобы это понять и переходим к следующему участку, если он есть.
		else
		{
			cout << "Time " << currentTime << ": gardener " << threadNumber << " could not start work on the plot " << y_1 << " " << x_1 << ", because it was done by the other gardener" << endl;
			currentTime += rand() % 3 + 1;
			taskNumber_1++;
			if (x_1 != N - 1)
			{
				x_1++;
			}
			else
			{
				x_1 = 0;
				y_1++;
			}

			if (y_1 <= M - 1)
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " goes on the plot " << y_1 << " " << x_1 << endl;
				currentTime++;
			}
			else
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " have finished his work in the garden" << endl;
				currentTime++;
			}
		}

	}

	// Ветка для второго садовника.
	else
	{
		// Ставим мьютекс, чтобы другой садовник не мешал работе.
		lock_guard<mutex> lock(mtx);

		// Выводим текущее состояние сада перед началом реализации нового участка.
		printGarden();

		// Если участок ещё не реализован, реализуем его за случайное количество секунд от 1 до 5, увеличиваем число пройденных участков, меняем координаты и переходим к следующему участку (если он есть).
		if (garden[y_2][x_2] == 0)
		{
			garden[y_2][x_2] = plan[y_2][x_2];
			cout << "Time " << currentTime << ": gardener " << threadNumber << " started work on the plot " << y_2 << " " << x_2 << endl;
			currentTime += rand() % 5 + 1;

			taskNumber_2++;
			if (y_2 != 0)
			{
				y_2--;
			}
			else
			{
				y_2 = M - 1;
				x_2--;
			}

			if (x_2 >= 0)
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " have done this plot and goes on the plot " << y_2 << " " << x_2 << endl;
				currentTime++;
			}
			else
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " have done the last plor and have finished his work in the garden" << endl;
				currentTime++;
			}
		}

		// Если участок уже реализован другим садовником, тратим от 1 до 3 секунд на то, чтобы это понять и переходим к следующему участку, если он есть.
		else
		{
			cout << "Time " << currentTime << ": gardener " << threadNumber << " could not start work on the plot " << y_2 << " " << x_2 << ", because it was done by the other gardener" << endl;
			currentTime += rand() % 3 + 1;
			taskNumber_2++;
			if (y_2 != 0)
			{
				y_2--;
			}
			else
			{
				y_2 = M - 1;
				x_2--;
			}
			if (x_2 >= 0)
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " goes on the plot " << y_2 << " " << x_2 << endl;
				currentTime++;
			}
			else
			{
				cout << "Time " << currentTime << ": gardener " << threadNumber << " have finished his work in the garden" << endl;
				currentTime++;
			}
		}

	}

}

/// <summary>
/// Метод, запускающий и останавливающий потоки, с помощью которых моделируется работа садовников по реализации сада.
/// </summary>
/// <param name="plan"> План сада.</param>
void work(vector<vector<int>> plan)
{
	thread gardener_1;
	thread gardener_2;
	int M = plan.size();
	int N = plan[0].size();

	// Задаём изначальные координаты второго садовника (для первого садовника они равни 0 и 0 и заданы выше).
	x_2 = N - 1;
	y_2 = M - 1;

	// Работаем до тех пор, пока оба садовника не пройдут весь сад по участкам.
	while (taskNumber_1 < M * N || taskNumber_2 < M * N)
	{
		thread gardener_1(addGardenPart, plan, 1);
		thread gardener_2(addGardenPart, plan, 2);
		gardener_1.join();
		gardener_2.join();

	}

}

int main(int argc, char* argv[])
{
	srand(time(0));

	// Двумерный массив для хранения плана сада.
	vector<vector<int>> plan;

	int M = atoi(argv[1]);
	int N = atoi(argv[2]);
	if (M <= 0 || N <= 0 || M > 20 || N > 20)
	{
		cout << "Wrong input! You should write two integers from 1 to 20 by spaces after writing the name of .exe-file" << endl;
	}
	else
	{

		// Заполняем план случайными числами от 1 до 9.
		for (int i = 0; i < M; i++)
		{
			vector <int> planLine;
			vector <int> gardenLine;
			for (int j = 0; j < N; j++)
			{
				int gardenPart = rand() % 9 + 1;
				planLine.push_back(gardenPart);
				gardenLine.push_back(0);
			}
			plan.push_back(vector <int>());
			garden.push_back(vector <int>());
			plan[i] = planLine;
			garden[i] = gardenLine;
		}

		// Выводим сгенерированный план на экран.
		printPlan(plan);

		// Начинаем работу.
		work(plan);

		// Фиксируеи время окончания.
		cout << "Work was finished at time " << currentTime << endl;

		// Выводим получившийся сад для проверки на соответствие плану.
		printGarden();
	}
}

