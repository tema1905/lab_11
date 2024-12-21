#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <Windows.h>


using namespace std;

enum LogType {
	USER_INPUT,
	LOG_ERROR,
	ATTEMPTS,
	WIN,
	GENERATED_NUMBER,
	RESULT,
	END

};

struct LogEntry {
	LogType type;
	string message;
	string timestamp;

	LogEntry(LogType t, const string& msg) : type(t), message(msg) {
		timestamp = getCurrentTime();
	}

	static string getCurrentTime() {
		time_t now = std::time(nullptr);
		tm localtime;
		localtime_s(&localtime, &now);

		ostringstream oss;
		oss << put_time(&localtime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}
};

void logMessage(const LogEntry& entry, const string& filename) {
	ofstream logFile(filename, ios_base::app);
	if (logFile.is_open()) {
		logFile << "[" << entry.timestamp << "] "
			<< (entry.type == USER_INPUT ? "USER_INPUT" :
				entry.type == LOG_ERROR ? "ERROR" :
				entry.type == RESULT ? "RESULT" :
				entry.type == WIN ? "WIN" :
				entry.type == END ? "END" :
				entry.type == ATTEMPTS ? "ATTEMPTS" : "GENERATED_NUMBER")
			<< ": " << entry.message << endl;
		logFile.close();
	}
	else {
		cerr << "Ошибка открытия файла лога!" << endl;
	}
}

string vibor(int a) {
	if (a == 1) {
		return "Камень";
	}
	if (a == 2) {
		return "Ножницы";
	}
	if (a == 3) {
		return "Бумага";
	}
}

int pobeda(int a, int b) {
	if (a == 1 && b == 1) return 2;
	if (a == 1 && b == 2) return 1;
	if (a == 1 && b == 3) return 0;
	if (a == 2 && b == 2) return 2;
	if (a == 2 && b == 1) return 0;
	if (a == 2 && b == 3) return 1;
	if (a == 3 && b == 3) return 2;
	if (a == 3 && b == 2) return 0;
	if (a == 3 && b == 1) return 1;
}

void igra(int a) {
	int player = 0, komp = 0, komp_figura;
	int player_figura = 0;
	int i = 0, k = 0;
	int j = 0;
	while ((player < a) && (komp < a)) {
		int vibor_igri = 2;
		komp_figura = 0;
		j = 0;
		k = 0;
		if (i >= 1) {
			cout << "\nПродолжать игру?(1 - да, 0 - нет)\n";
			while (j != 2)
			{
				j = 0;
				while (!(cin >> vibor_igri))
				{

					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "\nНеверный ввод!!!\nВведите еще раз: ";
					logMessage(LogEntry(LOG_ERROR, "Unsupported symbol"), "log.txt");
				}
				j += 1;
				if (vibor_igri <= 1 && vibor_igri >= 0) {
					j += 1;
				}
				else {
					cout << "Введите еще раз:";
					logMessage(LogEntry(LOG_ERROR, "Incorrect enter"), "log.txt");
				}
			}
		}
		if (vibor_igri == 0) {
			cout << "\t\tИтоговый счет\n";
			cout << "\tИгрок: " << player << "\t\t\tКомпьютер: " << komp;
			break;
		}
		Sleep(500);
		cout << "Какую фигуру выбираете(1 - Камень, 2 - Ножницы, 3 - Бумага): ";
		while (k != 2)
		{
			k = 0;
			while (!(cin >> player_figura))
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "\nНеверный ввод!!!\nВведите еще раз: ";
				logMessage(LogEntry(LOG_ERROR, "Unsupported symbol"), "log.txt");
			}
			k += 1;
			if (player_figura <= 3 && player_figura >= 1) {
				k += 1;
			}
			else {
				cout << "Введите еще раз:";
				logMessage(LogEntry(LOG_ERROR, "Incorrect enter"), "log.txt");
			}
		}
		komp_figura = (rand() % 3) + 1; cout << "\n\n";
		if (pobeda(player_figura, komp_figura) == 0) {
			komp += 1;
			cout << "\t\t В этом раунде победил компьютер!\n\n";
			logMessage(LogEntry(WIN, "Komp"), "log.txt");
			logMessage(LogEntry(USER_INPUT, to_string(player_figura)), "log.txt"); logMessage(LogEntry(USER_INPUT, vibor(player_figura)), "log.txt");
			logMessage(LogEntry(GENERATED_NUMBER, to_string(komp_figura)), "log.txt"); logMessage(LogEntry(GENERATED_NUMBER, vibor(komp_figura)), "log.txt");
			cout << "\tИгрок: " << vibor(player_figura) << "\t\t\tКомпьютер: " << vibor(komp_figura) << "\n";
			cout << "\tИгрок: " << player << "\t\t\tКомпьютер: " << komp;
			cout << "\n\n";
		}
		if (pobeda(player_figura, komp_figura) == 1) {
			player += 1;
			cout << "\t\t В этом раунде победил игрок!\n\n";
			logMessage(LogEntry(WIN, "Player"), "log.txt");
			logMessage(LogEntry(USER_INPUT, to_string(player_figura)), "log.txt"); logMessage(LogEntry(USER_INPUT, vibor(player_figura)), "log.txt");
			logMessage(LogEntry(GENERATED_NUMBER, to_string(komp_figura)), "log.txt"); logMessage(LogEntry(GENERATED_NUMBER, vibor(komp_figura)), "log.txt");
			cout << "\tИгрок: " << vibor(player_figura) << "\t\t\tКомпьютер: " << vibor(komp_figura) << "\n";
			cout << "\tИгрок: " << player << "\t\t\tКомпьютер: " << komp;
			cout << "\n\n";
		}
		if (pobeda(player_figura, komp_figura) == 2) {
			cout << "\t\t В этом раунде ничья!\n\n";
			logMessage(LogEntry(WIN, "Nichya"), "log.txt");
			logMessage(LogEntry(USER_INPUT, to_string(player_figura)), "log.txt"); logMessage(LogEntry(USER_INPUT, vibor(player_figura)), "log.txt");
			logMessage(LogEntry(GENERATED_NUMBER, to_string(komp_figura)), "log.txt"); logMessage(LogEntry(GENERATED_NUMBER, vibor(komp_figura)), "log.txt");
			cout << "\tИгрок: " << vibor(player_figura) << "\t\t\tКомпьютер: " << vibor(komp_figura) << "\n";
			cout << "\tИгрок: " << player << "\t\t\tКомпьютер: " << komp;
			cout << "\n\n";
		}
		i += 1;
	}
	if (player > komp) {
		cout << "\n\nПоздравляю с победой!!!\n\n";
		logMessage(LogEntry(RESULT, "Player won"), "log.txt");
	}
	else
	{
		cout << "\n\nК сожалению, выйграл компьютер\n\n";
		logMessage(LogEntry(RESULT, "Komp won"), "log.txt");
	}
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int win;

	cout << "\tДобро пожаловать в игру 'Камень ножницы бумага'\n\n";
	cout << "До какого количества побед будете играть?(введите число): ";
	while (!(cin >> win))
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\nНеверный ввод!!!\nВведите еще раз: ";
		logMessage(LogEntry(LOG_ERROR, "Unsupported symbol"), "log.txt");
	}
	logMessage(LogEntry(USER_INPUT, to_string(win)), "log.txt");
	cout << "\n\n";

	igra(win);

	logMessage(LogEntry(END, "\n\n"), "log.txt");

	return 0;
}