#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


struct Zadacha {
	string name;//���
	int prioritet; //���������
	int vremya; //����� ����������
	int time; //����� ����� ������ ��������� �������
};

int add_spisok(Zadacha *task) {
	int count;
	ifstream file_in("in.txt", ios::in);

	if (!file_in) {
		cerr << "������ �������� �����" << endl;
		return 0;
	}
	//��������� ������ � ��������� �����
	for (count = 0; !file_in.eof(); count++) {
		file_in >> task[count].name;
		file_in >> task[count].prioritet;
		file_in >> task[count].vremya;
		file_in >> task[count].time;
	}
	return count;
};

void sdvig(Zadacha *F, int &iF) {
	//�������� ������� �� 1
	for (int i = 0; i < iF; i++)
		F[i] = F[i + 1];
	iF--;
};


int main() {
	setlocale(LC_ALL, "rus");
	Zadacha F0[100], F1[100], F2[100], //3 �������
		stack[100], //����
		task[300], //��������� ����� (�� ����� �����������)
		CPU; //��������� ��� ���������� �����
	int iF0 = 0, iF1 = 0, iF2 = 0, iS = 0;
	int timer = 0, count = 0;
	bool newTask = false;

	//��������� ������
	count = add_spisok(task);
	CPU.name = "";

	for (int i = 0; i < count; timer++) {
		//��������� �����
		do {
			newTask = false;
			if (task[i].time == timer) {
				if (iF0 == 100) iF0 = 0;
				if (iF1 == 100) iF1 = 0;
				if (iF2 == 100) iF2 = 0;
				switch (task[i].prioritet) {
				case 0: {F0[iF0] = task[i]; iF0++; break; }
				case 1: {F1[iF1] = task[i]; iF1++; break; }
				case 2: {F2[iF2] = task[i]; iF2++; break; }
				}
				i++; //��������  ��� �� ��� ������
				newTask = true;
			}
		} while (newTask);
		//������ ����������
		if (CPU.name != "") {
			CPU.vremya--;
			if (CPU.vremya <= 0) {
				CPU.name = "";
				CPU.prioritet = 4;
				if (iS > 0) {
					CPU = stack[iS - 1];
					iS--;
				}
			}
		}
		//��������� ������� 0
		if (iF0 > 0) {
			if (CPU.name != "") {
				if (CPU.prioritet > F0[0].prioritet) { //���� ��������� ����� �� �������� � ����
					stack[iS] = CPU;
					iS++;
					CPU = F0[0];
					sdvig(F0, iF0);
				}
			}
			else {
				CPU = F0[0];
				sdvig(F0, iF0);
			}

		}
		//��������� ������� 1
		if (iF1 > 0) {
			if (CPU.name != "") {
				if (CPU.prioritet > F1[0].prioritet) {
					stack[iS] = CPU;
					iS++;
					CPU = F1[0];
					sdvig(F1, iF1);
				}
			}
			else {
				CPU = F1[0];
				sdvig(F1, iF1);
			}
		}
		//��������� ������� 2
		if (iF2 > 0) {
			if (CPU.name != "") {

				if (CPU.prioritet > F2[0].prioritet) {
					stack[iS] = CPU;
					iS++;
					CPU = F2[0];
					sdvig(F2, iF2);
				}
			}
			else {
				CPU = F2[0];
				sdvig(F2, iF2);
			}
		}

		cout << "Timer " << setw(2) << timer << "  CPU=" << setw(1) << CPU.name;
		cout << "  \tF0=";
		for (int i = 0; i < iF0; i++) cout << F0[i].name << ",";
		cout << "\t F1=";
		for (int i = 0; i < iF1; i++) cout << F1[i].name << ",";
		cout << "\t F2=";
		for (int i = 0; i < iF2; i++) cout << F2[i].name << ",";
		cout << "    \t S=";
		for (int i = 0; i < iS; i++) cout << stack[i].name << ",";
		cout << endl;
	}

	system("pause");
	return 0;
}