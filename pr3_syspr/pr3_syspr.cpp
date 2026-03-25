#include <iostream>

using namespace std;

struct FemaleData {

	short birthday;
};

struct MaleData {

	short status; // 0 - холост, 1 - женат
	short children;
};

union PersonData {

	FemaleData femaleData;
	MaleData maleData;
};

struct Person {

	char surname[50];
	short gender; // 0 - женский, 1 - мужской
	PersonData data;
};

int inputPeople(Person people[]) {

	int n;
	cout << "Введите количество человек: ";
	cin >> n;

	if (n > 100) n = 100;

	for (int i = 0; i < n; i++) {

		cout << "\n--- Человек " << i + 1 << " ---" << endl;

		cout << "Фамилия: ";
		cin >> people[i].surname;

		cout << "Пол (0 - женский, 1 - мужской): ";
		cin >> people[i].gender;

		if (people[i].gender == 0) {

			cout << "Год рождения: ";
			cin >> people[i].data.femaleData.birthday;
		}
		else if (people[i].gender == 1) {

			cout << "Семейное положение (0 - холост, 1 - женат): ";
			cin >> people[i].data.maleData.status;

			cout << "Количество детей: ";
			cin >> people[i].data.maleData.children;
		}
	}
	
	return n;
}

void printPerson(Person& people) {

	cout << "Фамилия: " << people.surname << endl;

	if (people.gender == 0) {

		cout << "Пол: Женский\nГод рождения: " << people.data.femaleData.birthday << endl;
	}
	else if (people.gender == 1) {
		cout << "Пол: Мужской\nСтатус: " << people.data.maleData.status << "\nКоличество детей: " << people.data.maleData.children << endl;
	}

	cout << endl;
}

void printAll(Person people[], int n) {

	cout << "\n--- Все анкеты ---" << endl;
	for (int i = 0; i < n; i++) {

		printPerson(people[i]);
	}
}

void sort(Person people[], int n) {

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n - i - 1; j++) {

			if (strcmp(people[j].surname, people[j + 1].surname) > 0) {
				Person temp = people[j];
				people[j] = people[j + 1];
				people[j + 1] = temp;
			}
		}
	}
}

int filter(Person people[], int n, Person result[]) {

	int count = 0;

	for (int i = 0; i < n; i++) {

		if (people[i].gender == 1 && people[i].data.maleData.status == 0 && people[i].data.maleData.children == 0) {

			result[count] = people[i];
			count++;
		}
	}

	return count;
}

int main() 
{
	setlocale(LC_ALL, "ru");

	Person people[100];
	Person result[100];

	int n = inputPeople(people);

	printAll(people, n);

	sort(people, n);

	int resultCount = filter(people, n, result);

	if (resultCount == 0) {

		cout << "=======================================" << endl;
		cout << "Холостых мужчин без детей не обнаружено" << endl;
	}
	else {

		cout << "==========================" << endl;
		cout << "Холостые мужчины без детей" << endl;

		for (int i = 0; i < resultCount; i++) {

			cout << i + 1 << ". " << result[i].surname << endl;
		}
	}
}