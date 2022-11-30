#include <iostream>
#include <time.h>
#include <string>
#include <map>
#include <conio.h>
using namespace std;

bool FlagAttack1 = 0;  //действие атаки
int GreenLarva, RedLarva, BlackLarva;
int AGreenLich, ARedLich, ABlackLich;
int NumGreenWar = 7, NumGreenWork = 13;
int NumRedWar = 6, NumRedWork = 17;
int NumBlackWar = 8, NumBlackWork = 17;
int RandomLot;
bool FlagOut = 0;

void Description(string Type, int HP, int Armor, int Damage, string QName, char Race)
{
	cout << "---------------------------------------\n---------------------------------------";
	cout << "\nТип: " << Type << endl;
	(Race == 'v') ? cout << "   Параметры: здоровье = " << HP << ", защита = " << Armor << ", урон = " << Damage << endl : cout << "   Параметры: здоровье = " << HP << ", защита = " << Armor << endl;
	cout << "   Королева << " << QName << " >>" << endl;
	cout << "---------------------------------------\n---------------------------------------" << endl;
}



struct Stack  //Структура кучки
{
	int branch;
	int leaf;
	int rock;
	int dew;
};

Stack lot1 = { 39, 37, 32, 41 };   //сами кучки
Stack lot2 = { 13, 0, 0, 38 };
Stack lot3 = { 22, 24, 0 , 27 };
Stack lot4 = { 12, 29, 28, 30 };
Stack lot5 = { 39, 0, 0, 0 };

map <string, int> ResGreen = //ресурсы колоний
{
	{"branch",0},
	{"leaf",0},
	{"rock",0},
	{"dew",0}
};

map <string, int> ResRed =
{
	{"branch",0},
	{"leaf",0},
	{"rock",0},
	{"dew",0}
};

map <string, int> ResBlack =
{
	{"branch",0},
	{"leaf",0},
	{"rock",0},
	{"dew",0}
};

class Ant
{
public:
	char Colony;
	int HP;
	int Armor;
	int GPS;
	int NumRes;
	char Resources[3];
	void Attack(int Damage, int Bites, int vGPS)
	{
		if (vGPS == GPS && HP > 0)
		{
			FlagAttack1 = 1;
			(Armor > 0) ? Armor = Armor - (Damage * Bites) : HP = HP - (Damage * Bites);
		}

	}
	Ant() {}
	Ant(int H, int A, char C, int G)
	{
		HP = H;
		Armor = A;
		Colony = C;
		GPS = G;
	}
	Ant(int H, int A, char C, int G, int NR, char R1, char R2)
	{
		HP = H;
		Armor = A;
		Colony = C;
		GPS = G;
		NumRes = NR;
		this->Resources[0] = R1;
		this->Resources[1] = R2;
	}
	virtual void NLich() {}
	virtual void CollectRes(Stack lotRandom) {}
	void Description(string Type, int HP, int Armor, int Damage, string QName, char Race)
	{
		cout << "---------------------------------------\n---------------------------------------";
		cout << "\nТип: " << Type << endl;
		(Race == 'v') ? cout << "   Параметры: здоровье = " << HP << ", защита = " << Armor << ", урон = " 
			<< Damage << endl : cout << "   Параметры: здоровье = " << HP << ", защита = " << Armor << endl;
		cout << "   Королева << " << QName << " >>" << endl;
		cout << "---------------------------------------\n---------------------------------------" << endl;
	}
};



class Worker : public Ant
{
public:
	int NumRes;
	char Resources[2];

	void Setter_Work(int HP, int Armor, char Colony, int GPS, int CollectRes, char R1, char R2)
	{
		this->HP = HP;
		this->Armor = Armor;
		this->Colony = Colony;
		this->GPS = GPS;
		this->NumRes = CollectRes;
		this->Resources[0] = R1;
		this->Resources[1] = R2;

	}

	virtual void CollectRes(Stack lotRandom)
	{
		for (int i = 0; i < NumRes; i++)
		{
			bool flag = 0;
			for (int j = 0; j < 2; j++)
			{
				if (flag == 0)
				{
					switch (Resources[j])
					{
					case 'B':
					{
						if (lotRandom.branch > 0)
						{
							lotRandom.branch = lotRandom.branch - 1;

							if (Colony == 'g') { ResGreen["branch"]++; }
							if (Colony == 'r') { ResRed["branch"]++; }
							if (Colony == 'b') { ResBlack["branch"]++; }
							flag = 1;
						}
						continue;
						break;
					}
					case 'L':
					{
						if (lotRandom.leaf > 0)
						{
							lotRandom.leaf = lotRandom.leaf - 1;

							if (Colony == 'g') { ResGreen["leaf"]++; }
							if (Colony == 'r') { ResRed["leaf"]++; }
							if (Colony == 'b') { ResBlack["leaf"]++; }
							flag = 1;
						}
						continue;
						break;
					}
					case 'R':
					{
						if (lotRandom.rock > 0)
						{
							lotRandom.rock = lotRandom.rock - 1;

							if (Colony == 'g') { ResGreen["rock"]++; }
							if (Colony == 'r') { ResRed["rock"]++; }
							if (Colony == 'b') { ResBlack["rock"]++; }
							flag = 1;
						}
						continue;
						break;
					}
					case 'D':
					{
						if (lotRandom.dew > 0)
						{
							lotRandom.dew = lotRandom.dew - 1;

							if (Colony == 'g') { ResGreen["dew"]++; }
							if (Colony == 'r') { ResRed["dew"]++; }
							if (Colony == 'b') { ResBlack["dew"]++; }
							flag = 1;
						}
						continue;
						break;
					}
					default:
						break;
					}
				}

			}
		}
		switch (GPS)
		{
		case 1:
			lot1 = lotRandom;
			break;
		case 2:
			lot2 = lotRandom;
			break;
		case 3:
			lot3 = lotRandom;
			break;
		case 4:
			lot4 = lotRandom;
			break;
		case 5:
			lot5 = lotRandom;
			break;

		default:
			break;
		}
	}

	Worker(int H, int A, char C, int G, int NR, char R1, char R2) : Ant(H, A, C, G)
	{
		this->NumRes = NR;
		this->Resources[0] = R1;
		this->Resources[1] = R2;
	}
	Worker() {}
};

class Warrior : public Ant
{
public:
	int Damage;
	int Target;
	int Bites;

	void Setter_Warrior(int HP, int Armor, char Colony, int GPS, int Damage, int Target, int Bites)
	{
		this->HP = HP;
		this->Armor = Armor;
		this->Colony = Colony;
		this->GPS = GPS;
		this->Damage = Damage;
		this->Target = Target;
		this->Bites = Bites;
	}

	Warrior(int H, int A, char C, int G, int D, int T, int B) : Ant(H, A, C, G)
	{
		Target = T;
		Bites = B;
		Damage = D;
	}
	Warrior() {} //Конструктор

};

Worker GreenWorker[500] = { Worker(8, 4, 'g', 0, 2, 'R', 'D'), Worker(8, 4, 'g', 0, 2, 'R', 'D'), Worker(8, 4, 'g', 0, 2, 'R', 'D') , Worker(8, 4, 'g', 0, 2, 'R', 'D') , Worker(8, 4, 'g', 0, 2, 'R', 'D'),
Worker(8, 4, 'g', 0, 2, 'R', 'D'), Worker(1, 0, 'g', 0, 1, 'B', 'z'), Worker(1, 0, 'g', 0, 1, 'B', 'z'), Worker(1, 0, 'g', 0, 1, 'B', 'z'), Worker(1, 0, 'g', 0, 1, 'B', 'z'), Worker(1, 0, 'g', 0, 1, 'B', 'z'), Worker(1, 0, 'g', 0, 1, 'B', 'z'), Worker(1, 0, 'g', 0, 1, 'B', 'z') };

Worker RedWorker[500] = { Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'),
Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(1, 0, 'r', 0, 1, 'R', 'z'), Worker(2, 1, 'r', 0, 1, 'B', 'R'), Worker(2, 1, 'r', 0, 1, 'B', 'R'),
Worker(2, 1, 'r', 0, 1, 'B', 'R'), Worker(2, 1, 'r', 0, 1, 'B', 'R'), Worker(2, 1, 'r', 0, 1, 'B', 'R'), Worker(2, 1, 'r', 0, 1, 'B', 'R'), Worker(2, 1, 'r', 0, 1, 'B', 'R') };

Worker BlackWorker[500]{ Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'),
Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'), Worker(2, 1, 'b', 0, 1, 'B', 'L'),
Worker(2, 1, 'b', 0, 1, 'R', 'D'), Worker(2, 1, 'b', 0, 1, 'R', 'D'), Worker(2, 1, 'b', 0, 1, 'R', 'D'), Worker(2, 1, 'b', 0, 1, 'R', 'D'), Worker(2, 1, 'b', 0, 1, 'R', 'D'), Worker(2, 1, 'b', 0, 1, 'R', 'D'), };

Warrior GreenWarrior[400] = { Warrior(10, 6, 'g', 0, 4, 3, 1), Warrior(10, 6, 'g', 0, 4, 3, 1), Warrior(10, 6, 'g', 0, 4, 3, 1), Warrior(10, 6, 'g', 0, 4, 3, 1), Warrior(10, 6, 'g', 0, 4, 3, 1), Warrior(1, 0, 'g', 0, 1, 1, 1), Warrior(1, 0, 'g', 0, 1, 1, 1) };

Warrior RedWarrior[400] = { Warrior(8, 4, 'r', 0, 3, 2, 2), Warrior(8, 4, 'r', 0, 3, 2, 2), Warrior(8, 4, 'r', 0, 3, 2, 2), Warrior(8, 4, 'r', 0, 3, 2, 2), Warrior(8, 4, 'r', 0, 3, 2, 2), Warrior(6, 2, 'r', 0, 3, 2, 1) };

Warrior BlackWarrior[400] = { Warrior(10, 6, 'b', 0, 4, 3, 1), Warrior(10, 6, 'b', 0, 4, 3, 1), Warrior(10, 6, 'b', 0, 4, 3, 1), Warrior(10, 6, 'b', 0, 4, 3, 1), Warrior(10, 6, 'b', 0, 4, 3, 1), Warrior(6, 2, 'b', 0, 3, 2, 1),
Warrior(6, 2, 'b', 0, 3, 2, 1), Warrior(6, 2, 'b', 0, 3, 2, 1) };



class Special : public Ant
{
public:
	int Damage;
	int Target;
	int Bites;
	Special(int H, int A, char C, int G, int NR, char R1, char R2, int D, int T, int B) : Ant(H, A, C, G)
	{
		this->NumRes = NR;
		this->Resources[0] = R1;
		this->Resources[1] = R2;
		Damage = D;
		Target = T;
		Bites = B;
	}
};

class Queen : public Ant
{
public:
	int Damage;
	string Name;
	int LarvaGrowth;
	virtual void Cycle_larva()
	{
		int Numlarv = 1 + rand() % (11 - 1);
		if (Colony == 'g')
		{
			AGreenLich = Numlarv;
			GreenLarva = Numlarv;
		}
		if (Colony == 'r')
		{
			ARedLich = Numlarv;
			RedLarva = Numlarv;
		}
		if (Colony == 'b')
		{
			ABlackLich = Numlarv;
			BlackLarva = Numlarv;
		}
		for (int i = 0; i < Numlarv; i++)
		{
			int RandomTemp = rand() % 2;
			if (RandomTemp == 0)
			{
				if (Colony = 'g')
				{
					GreenWarrior[NumGreenWar].Setter_Warrior(10, 6, 'g', 0, 4, 3, 1);
					NumGreenWar++;
				}
				if (Colony = 'r')
				{
					RedWarrior[NumRedWar].Setter_Warrior(8, 4, 'r', 0, 3, 2, 2);
					NumRedWar++;
				}
				if (Colony = 'b')
				{
					BlackWarrior[NumBlackWar].Setter_Warrior(10, 6, 'b', 0, 4, 3, 1);
					NumBlackWar++;
				}
			}
			else
			{
				if (Colony = 'g')
				{
					GreenWorker[NumGreenWork].Setter_Work(8, 4, 'g', 0, 2, 'R', 'D');
					NumGreenWar++;
				}
				if (Colony = 'r')
				{
					RedWorker[NumRedWork].Setter_Work(1, 0, 'r', 0, 1, 'R', 'z');
					NumRedWar++;
				}
				if (Colony = 'b')
				{
					BlackWorker[NumBlackWork].Setter_Work(2, 1, 'b', 0, 1, 'B', 'L');
					NumBlackWar++;
				}
			}
		}
	}

	Queen(int H, int A, char C, int G, int D, string N, int Cy) : Ant(H, A, C, G)
	{
		Name = N;
		Damage = D;
		LarvaGrowth = Cy;
	}
};

int main()
{
	int Today = 0;

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));


	Queen GreenQueen(29, 8, 'g', 0, 28, "Нефертити", 3);
	Queen RedQueen(16, 6, 'r', 0, 26, "Мария", 4);
	Queen BlackQueen(23, 7, 'b', 0, 20, "Беатрикс", 2);

	Special Bee(28, 8, 'g', 0, 1, 'R', 'z', 0, 0, 0);
	Special Thicklegged(20, 9, 'r', 0, 2, 'L', 'L', 0, 0, 0);
	Special Cricket(21, 4, 'b', 0, 0, 'z', 'z', 7, 1, 1);

	for (int day = 0; day < 10; day++)
	{
		int RedBranch = ResRed["branch"], RedLeaf = ResRed["leaf"], RedRock = ResRed["rock"], RedDew = ResRed["dew"];
		int GreenBranch = ResGreen["branch"], GreenLeaf = ResGreen["leaf"], GreenRock = ResGreen["rock"], GreenDew = ResGreen["dew"];
		int BlackBranch = ResBlack["branch"], BlackLeaf = ResBlack["leaf"], BlackRock = ResBlack["rock"], BlackDew = ResBlack["dew"];
		bool FlagDop = 0;
		FlagOut = 0;

		if (day == 3 || day == 6 || day == 9)
		{
			GreenQueen.Cycle_larva();
			RedQueen.Cycle_larva();
			BlackQueen.Cycle_larva();
		}
		//****************************НАЧАЛО ДОЖДЯ*****************************************
		if (day > 5 && day < 8)
		{
			NumGreenWork = NumGreenWork / 2;
			NumRedWork = NumRedWork / 2;
			NumBlackWork = NumBlackWork / 2;

			NumGreenWar = NumGreenWar / 2;
			NumRedWar = NumRedWar / 2;
			NumBlackWar = NumBlackWar / 2;
			FlagDop = 1;
		}
		//****************************НАЧАЛО ДОЖДЯ*****************************************

		//****************************НАЧАЛО СБОРА РЕСУРСОВ*****************************************
		for (int i = 0; i < NumGreenWork; i++)
		{
			if (GreenWorker[i].HP > 0)
			{
				int LotRandom = rand() % 5;
				GreenWorker[i].GPS = LotRandom + 1;
				switch (GreenWorker[i].GPS)
				{
				case 1:
				{
					GreenWorker[i].CollectRes(lot1);
					break;
				}
				case 2:
				{
					GreenWorker[i].CollectRes(lot2);
					break;
				}
				case 3:
				{
					GreenWorker[i].CollectRes(lot3);
					break;
				}
				case 4:
				{
					GreenWorker[i].CollectRes(lot4);
					break;
				}
				case 5:
				{
					GreenWorker[i].CollectRes(lot5);
					break;
				}
				default:
					break;
					int Sleep = rand() % 2;
					if (GreenWorker[i].NumRes == 1 && Sleep == 1) //*****обычный сонный*****
					{
						if (GreenWorker[i].GPS > 0)
						{
							Today = day;
							if (Today == day) continue;
						}
					}
				}
			}
		}
		for (int i = 0; i < NumRedWork; i++)
		{
			if (RedWorker[i].HP > 0)
			{
				int LotRandom = rand() % 5;
				RedWorker[i].GPS = LotRandom + 1;
				switch (RedWorker[i].GPS)
				{
				case 1:
				{
					RedWorker[i].CollectRes(lot1);
					break;
				}
				case 2:
				{
					RedWorker[i].CollectRes(lot2);
					break;
				}
				case 3:
				{
					RedWorker[i].CollectRes(lot3);
					break;
				}
				case 4:
				{
					RedWorker[i].CollectRes(lot4);
					break;
				}
				case 5:
				{
					RedWorker[i].CollectRes(lot5);
					break;
				}
				default:
					break;
				}
			}
		}
		for (int i = 0; i < NumBlackWork; i++)
		{
			if (BlackWorker[i].HP > 0)
			{
				int LotRandom = rand() % 5;
				BlackWorker[i].GPS = LotRandom + 1;
				switch (BlackWorker[i].GPS)
				{
				case 1:
				{
					BlackWorker[i].CollectRes(lot1);
					break;
				}
				case 2:
				{
					BlackWorker[i].CollectRes(lot2);
					break;
				}
				case 3:
				{
					BlackWorker[i].CollectRes(lot3);
					break;
				}
				case 4:
				{
					BlackWorker[i].CollectRes(lot4);
					break;
				}
				case 5:
				{
					BlackWorker[i].CollectRes(lot5);
					break;
				}
				default:
					break;
				}
				if (BlackWorker[i].Resources[0] == 'D') //*****старший бригадир*****
				{
					for (int j = 0; j < 40; j++)
					{
						BlackWorker[j].NumRes = 2;
					}
				}
			}
		}
		if (Bee.HP > 0)
		{
			int LotRandom = rand() % 5;
			Bee.GPS = LotRandom + 1;
			switch (Bee.GPS)
			{
			case 1:
			{
				Bee.CollectRes(lot1);
				break;
			}
			case 2:
			{
				Bee.CollectRes(lot2);
				break;
			}
			case 3:
			{
				Bee.CollectRes(lot3);
				break;
			}
			case 4:
			{
				Bee.CollectRes(lot4);
				break;
			}
			case 5:
			{
				Bee.CollectRes(lot5);
				break;
			}
			default:
				break;
			}
		}
		if (Thicklegged.HP > 0)
		{
			int LotRandom = rand() % 5;
			Thicklegged.GPS = LotRandom + 1;
			switch (Thicklegged.GPS)
			{
			case 1:
			{
				Thicklegged.CollectRes(lot1);
				break;
			}
			case 2:
			{
				Thicklegged.CollectRes(lot2);
				break;
			}
			case 3:
			{
				Thicklegged.CollectRes(lot3);
				break;
			}
			case 4:
			{
				Thicklegged.CollectRes(lot4);
				break;
			}
			case 5:
			{
				Thicklegged.CollectRes(lot5);
				break;
			}
			default:
				break;
			}
		}
		//****************************КОНЕЦ СБОРА РЕСУРСОВ*****************************************
		//****************************КОНЕЦ ДОЖДЯ*****************************************
		if (day < 6 && day > 9)
		{
			NumGreenWork = NumGreenWork * 2;
			NumRedWork = NumRedWork * 2;
			NumBlackWork = NumBlackWork * 2;

			NumGreenWar = NumGreenWar * 2;
			NumRedWar = NumRedWar * 2;
			NumBlackWar = NumBlackWar * 2;
		}
		//****************************КОНЕЦ ДОЖДЯ*****************************************

		//Распределение на кучку для пчелы
		for (int stack = 1; stack < 6; stack++)
		{
			int l = 0;
			for (int K = 0; K < 40; K++)
			{
				if (RedWorker[K].GPS == stack) l++;
				if (BlackWorker[K].GPS == stack) l++;
				if (RedWarrior[K].GPS == stack) l++;
				if (BlackWarrior[K].GPS == stack) l++;
				if (Thicklegged.GPS == stack) l++;
				if (Cricket.GPS == stack) l++;
				if (l == 0) Bee.GPS == stack;
			}
		}
		//Распределение на кучку для пчелы

		//****************************АТАКА*****************************************
		for (int m = 0; m < 40; m++)
		{
			GreenWarrior[m].GPS = rand() % 5 + 1;
			RedWarrior[m].GPS = rand() % 5 + 1;
			BlackWarrior[m].GPS = rand() % 5 + 1;
		}
		Bee.GPS = rand() % 5 + 1;
		Thicklegged.GPS = rand() % 5 + 1;
		Cricket.GPS = rand() % 5 + 1;

		for (int g = 0; g < NumGreenWar; g++) //цикл атаки зелёных
		{
			if (GreenWarrior[g].HP > 0)
			{
				for (int t = 0; t < GreenWarrior[g].Target; t++)
				{
					FlagAttack1 = 0;
					for (int r = 0; r < NumRedWar; r++)
					{
						RedWarrior[r].Attack(GreenWarrior[g].Damage, GreenWarrior[g].Bites, GreenWarrior[g].GPS);
						if (FlagAttack1 == 1)
						{
							break;
						}
					}
					if (FlagAttack1 == 0)
					{
						for (int w = 0; w < NumRedWork; w++)
						{
							if (RedWorker[w].HP > 0 && RedWorker[w].Resources[0] == 'B')
							{
								RedWorker[w].Attack(GreenWarrior[g].Damage, GreenWarrior[g].Bites - 1, GreenWarrior[g].GPS);
							}
							else
							{
								RedWorker[w].Attack(GreenWarrior[g].Damage, GreenWarrior[g].Bites, GreenWarrior[g].GPS);
							}
							if (FlagAttack1 == 1) break;
						}
					}
					if (FlagAttack1 == 0) Thicklegged.Attack(GreenWarrior[g].Damage, GreenWarrior[g].Bites, GreenWarrior[g].GPS);
				}
				for (int t = 0; t < GreenWarrior[g].Target; t++)
				{
					FlagAttack1 = 0;
					for (int b = 0; b < NumBlackWar; b++)
					{
						BlackWarrior[b].Attack(GreenWarrior[g].Damage, GreenWarrior[g].Bites, GreenWarrior[g].GPS); //*****ФЕНИКСЫ*****
						if (FlagAttack1 == 1)
						{
							break;
						}
						if (BlackWarrior[b].Damage == 3 && BlackWarrior[b].HP <= 0)
						{
							BlackWarrior[b].HP == 3;
						}
					}
					if (FlagAttack1 == 0)
					{
						for (int w = 0; w < NumBlackWork; w++)
						{
							BlackWorker[w].Attack(GreenWarrior[g].Damage, GreenWarrior[g].Bites, GreenWarrior[g].GPS);
							if (FlagAttack1 == 1) break;
						}
					}
					if (FlagAttack1 == 0) Cricket.Attack(GreenWarrior[g].Damage, GreenWarrior[g].Bites, GreenWarrior[g].GPS);
				}
			}
		}
		for (int r = 0; r < NumRedWar; r++) //цикл атаки красных
		{
			if (RedWarrior[r].HP > 0)
			{
				for (int t = 0; t < RedWarrior[r].Target; t++)
				{
					FlagAttack1 = 0;
					for (int g = 0; g < NumGreenWar; g++)
					{
						GreenWarrior[g].Attack(RedWarrior[r].Damage, RedWarrior[r].Bites, RedWarrior[r].GPS);
						if (FlagAttack1 == 1)
						{
							break;
						}
					}
					if (FlagAttack1 == 0)
					{
						for (int w = 0; w < NumGreenWork; w++)
						{
							GreenWorker[w].Attack(RedWarrior[r].Damage, RedWarrior[r].Bites, RedWarrior[r].GPS);
							if (FlagAttack1 == 1) break;
						}
					}
				}
				for (int t = 0; t < RedWarrior[r].Target; t++)
				{
					FlagAttack1 = 0;
					for (int b = 0; b < NumBlackWar; b++)
					{
						BlackWarrior[b].Attack(RedWarrior[r].Damage, RedWarrior[r].Bites, RedWarrior[r].GPS);
						if (FlagAttack1 == 1)
						{
							break;
						}
						if (BlackWarrior[b].Damage == 3 && BlackWarrior[b].HP <= 0)
						{
							BlackWarrior[b].HP == 3;
						}
					}
					if (FlagAttack1 == 0)
					{
						for (int w = 0; w < NumBlackWork; w++)
						{
							BlackWorker[w].Attack(RedWarrior[r].Damage, RedWarrior[r].Bites, RedWarrior[r].GPS);
							if (FlagAttack1 == 1) break;

						}
					}
					if (FlagAttack1 == 0) Cricket.Attack(RedWarrior[r].Damage, RedWarrior[r].Bites, RedWarrior[r].GPS);
				}
				if (RedWarrior[r].Bites == 1) //*****продвинутый худой*****
				{
					for (int w = 0; w < RedWarrior[r].Target; w++)
					{
						FlagAttack1 = 0;
						for (int a = 0; a < NumRedWar; a++)
						{
							RedWarrior[r].Attack(RedWarrior[r].Damage, RedWarrior[r].Bites, RedWarrior[r].GPS);
							if (FlagAttack1 == 1) break;
						}
						if (FlagAttack1 == 0)
						{
							for (int aw = 0; aw < NumRedWork; aw++)
							{
								RedWorker[aw].Attack(RedWarrior[r].Damage, RedWarrior[r].Bites, RedWarrior[r].GPS);
								if (FlagAttack1 == 1) break;
							}
						}
					}
				}
			}
		}
		for (int b = 0; b < NumBlackWar; b++) //цикл атаки чёрных
		{
			if (BlackWarrior[b].HP > 0)
			{
				for (int t = 0; t < BlackWarrior[b].Target; t++)
				{
					FlagAttack1 = 0;
					for (int g = 0; g < NumGreenWar; g++)
					{
						GreenWarrior[g].Attack(BlackWarrior[b].Damage, BlackWarrior[b].Bites, BlackWarrior[b].GPS);
						if (FlagAttack1 == 1)
						{
							break;
						}
					}
					if (FlagAttack1 == 0)
					{
						for (int w = 0; w < NumGreenWork; w++)
						{
							GreenWorker[w].Attack(BlackWarrior[b].Damage, BlackWarrior[b].Bites, BlackWarrior[b].GPS);
							if (FlagAttack1 == 1) break;
						}
					}
				}
				for (int t = 0; t < BlackWarrior[b].Target; t++)
				{
					FlagAttack1 = 0;
					for (int r = 0; r < NumRedWar; r++)
					{
						RedWarrior[r].Attack(BlackWarrior[b].Damage, BlackWarrior[b].Bites, BlackWarrior[b].GPS);
						if (FlagAttack1 == 1)
						{
							break;
						}
					}
					if (FlagAttack1 == 0)
					{
						for (int w = 0; w < NumRedWork; w++)
						{
							RedWorker[w].Attack(BlackWarrior[b].Damage, BlackWarrior[b].Bites, BlackWarrior[b].GPS);
							if (FlagAttack1 == 1) break;
						}
					}
					if (FlagAttack1 == 0) Thicklegged.Attack(BlackWarrior[b].Damage, BlackWarrior[b].Bites, BlackWarrior[b].GPS);
				}
			}
		}
		for (int s = 0; s < Cricket.Target; s++)  //цикл атаки сверчка
		{
			FlagAttack1 = 0;
			for (int g = 0; g < NumGreenWar; g++)
			{
				GreenWarrior[g].Attack(Cricket.Damage, Cricket.Bites, Cricket.GPS);
				if (FlagAttack1 == 1) break;
			}
			if (FlagAttack1 == 0)
			{
				for (int w = 0; w < NumGreenWork; w++)
				{
					GreenWorker[w].Attack(Cricket.Damage, Cricket.Bites, Cricket.GPS);
					if (FlagAttack1 == 1) break;
				}
			}
		}
		for (int s = 0; s < Cricket.Target; s++)
		{
			for (int r = 0; r < NumRedWar; r++)
			{
				RedWarrior[r].Attack(Cricket.Damage, Cricket.Bites, Cricket.GPS);
				if (FlagAttack1 == 1)
				{
					break;
				}
			}
			if (FlagAttack1 == 0)
			{
				for (int w = 0; w < NumRedWork; w++)
				{
					RedWorker[w].Attack(Cricket.Damage, Cricket.Bites, Cricket.GPS);
					if (FlagAttack1 == 1) break;
				}
			}
		}
		//****************************АТАКА*****************************************

		cout << "****************************************************************";
		cout << "\n------------------------------------------------------------";
		cout << "\n\t\t\x1b[33mНачало дня:\x1b[0m";
		cout << "\nДень " << day + 1 << " до засухи осталось " << 9 - day << " дней" << endl;
		cout << endl;

		int WarGreen = 0; int WorkGreen = 0; int WarRed = 0; int WorkRed = 0; int WarBlack = 0; int WorkBlack = 0;
		int special1 = 0, special2 = 0, special3 = 0;

		for (int wr = 0; wr < 35; wr++)
		{
			if (GreenWarrior[wr].HP > 0) WarGreen++;
			if (RedWarrior[wr].HP > 0) WarRed++;
			if (BlackWarrior[wr].HP > 0) WarBlack++;
		}
		for (int wo = 0; wo < 40; wo++)
		{
			if (GreenWorker[wo].HP > 0) WorkGreen++;
			if (RedWorker[wo].HP > 0) WorkRed++;
			if (BlackWorker[wo].HP > 0) WorkBlack++;
		}
		if (Bee.HP > 0) special1++;
		if (Thicklegged.HP > 0) special2++;
		if (Cricket.HP > 0) special3++;



		cout << "Колония <<Зелёные>> :\n" << "    Королева <Нефертити>, личинки = " << GreenLarva << endl;
		cout << "    Ресурсы : branch = " << ResGreen["branch"] << " leaf = " << ResGreen["leaf"] << " rock = " << ResGreen["rock"] << " dew = " << ResGreen["dew"] << endl;
		cout << "    Популяция " << WarGreen + WorkGreen + special1 << ": Рабочие = " << WorkGreen << ", Воины = " << WarGreen << ", Насекомое = " << special1 << " ; \n" << endl;

		cout << "Колония <<Красные>> :\n" << "    Королева <Мария>, личинки = " << RedLarva << endl;
		cout << "    Ресурсы : branch = " << ResRed["branch"] << " leaf = " << ResRed["leaf"] << " rock = " << ResRed["rock"] << " dew = " << ResRed["dew"] << endl;
		cout << "    Популяция " << WarRed + WorkRed + special2 << ": Рабочие = " << WorkRed << ", Воины = " << WarRed << ", Насекомое = " << special2 << " ; \n" << endl;

		cout << "Колония <<Чёрные>> :\n" << "    Королева <Беатрикс>, личинки = " << BlackLarva << endl;
		cout << "    Ресурсы : branch = " << ResBlack["branch"] << " leaf = " << ResBlack["leaf"] << " rock = " << ResBlack["rock"] << " dew = " << ResBlack["dew"] << endl;
		cout << "    Популяция " << WarBlack + WorkBlack + special3 << ": Рабочие = " << WorkBlack << ", Воины = " << WarBlack << ", Насекомое = " << special3 << " ; \n" << endl;

		cout << "Куча 1: " << "branch = " << lot1.branch << " leaf = " << lot1.leaf << " rock = " << lot1.rock << " dew = " << lot1.dew << endl;
		cout << "Куча 2: " << "branch = " << lot2.branch << " leaf = " << lot2.leaf << " rock = " << lot2.rock << " dew = " << lot2.dew << endl;
		cout << "Куча 3: " << "branch = " << lot3.branch << " leaf = " << lot3.leaf << " rock = " << lot3.rock << " dew = " << lot3.dew << endl;
		cout << "Куча 4: " << "branch = " << lot4.branch << " leaf = " << lot4.leaf << " rock = " << lot4.rock << " dew = " << lot4.dew << endl;
		cout << "Куча 5: " << "branch = " << lot5.branch << " leaf = " << lot5.leaf << " rock = " << lot5.rock << " dew = " << lot5.dew << endl;
		if (FlagDop) cout << "\n\x1b[5mГлобальный Эффект:\x1b[0m\n\x1b[36m< Дождь > - до кучи в походе доходит только половина всех муравьев\x1b[0m" << endl;
		if (day == 9)
		{
			cout << "\n\x1b[93mНаступила Засуха\x1b[0m\n";
			int ResGreenStack = ResGreen["branch"] + ResGreen["leaf"] + ResGreen["rock"] + ResGreen["dew"];
			int ResRedStack = ResRed["branch"] + ResRed["leaf"] + ResRed["rock"] + ResRed["dew"];
			int ResBlackStack = ResBlack["branch"] + ResBlack["leaf"] + ResBlack["rock"] + ResBlack["dew"];

			if (ResGreenStack > ResRedStack)
			{
				(ResGreenStack > ResBlackStack) ? cout << "\x1b[32mКолония зелёных победила!\x1b[0m" : cout << "\x1b[90mКолония чёрных победила!\x1b[0m ";
			}
			else
			{
				(ResRedStack > ResBlackStack) ? cout << "\x1b[31mКолония красных победила!\x1b[0m" : cout << "\x1b[90mКолония чёрных победила!\x1b[0m ";
			}
		}
		if (day != 10)
		{
			cout << "\n\n\t" << "\x1b[33mНажмите <1>(статистика зеленой колонии), <2>(статистика красной колонии), <3>(статистика чёрной колонии),\n\t<4>(Подробная статистика дня) или <5>(Информация о муравье)\x1b[0m" << "\n\n" << endl;
			int ap = _getch();
			switch (ap)
			{
			case 49: //green
				cout << "<<<------------------------------------------>>>" << endl;
				cout << "\t\t\x1b[96mСтатистика\x1b[0m" << endl;
				cout << ">>>------------------------------------------<<<" << endl;
				cout << "Колония < \x1b[32mЗелёные\x1b[0m > :\n" << "\x1b[36m   Королева < Нефертити > :\x1b[0m" << endl;
				cout << "     здоровье = " << GreenQueen.HP << ", защита = " << GreenQueen.Armor << ", урон = " << GreenQueen.Damage << endl;
				cout << "Ресурсы (шт.): Ветка = " << ResGreen["branch"] << "  Листик = " << ResGreen["leaf"] << "  Камень = " << ResGreen["rock"] << "  Росинка = " << ResGreen["dew"] << endl;
				cout << "--------->\x1b[33m Рабочий \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Элитный\x1b[0m\n" << "   Параметры: здоровье = 8, защита = 4" << endl;
				cout << "\x1b[36mtype: Обычный сонный\x1b[0m\n" << "   Параметры: здоровье = 1, защита = 0" << endl;
				cout << "\x1b[95mмодификатор: по пути в колонию может уснуть и вернуться на следующий день\x1b[0m" << endl;
				cout << "--------->\x1b[33m Воин \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Легендарный\x1b[0m\n" << "   Параметры: здоровье = 10, защита = 6, урон = 4" << endl;
				cout << "\x1b[36mtype: Обычный неряшливый\x1b[0m\n" << "   Параметры: здоровье = 1, защита = 0, урон = 1" << endl;
				cout << "\x1b[95mмодификатор: защита уменьшена в двое\x1b[0m" << endl;
				cout << "--------->\x1b[33m Специальный \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Трудолюбивый неуязвимый мирный любимчик королевы - Пчела\x1b[0m\n" << "   Параметры: здоровье = 28, защита = 8" << endl;
				cout << "\x1b[95mмодификаторы: \n*не может быть атакован войнами; всегда отправляется только на ту кучу где нет вражеских воинов.\x1b[0m" << endl;
				cout << "_________________________________________________" << endl;
				cout << "|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
				FlagOut = 1;
				break;
			case 50: //red
				cout << "<<<------------------------------------------>>>" << endl;
				cout << "\t\t\x1b[96mСтатистика\x1b[0m" << endl;
				cout << ">>>------------------------------------------<<<" << endl;
				cout << "Колония < \x1b[31mКрасные\x1b[0m > :\n" << "\x1b[36m   Королева < Мария > :\x1b[0m" << endl;
				cout << "     здоровье = " << RedQueen.HP << ", защита = " << RedQueen.Armor << ", урон = " << RedQueen.Damage << endl;
				cout << "Ресурсы (шт.): Ветка = " << ResRed["branch"] << "  Листик = " << ResRed["leaf"] << "  Камень = " << ResRed["rock"] << "  Росинка = " << ResRed["dew"] << endl;
				cout << "--------->\x1b[33m Рабочий \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Обычный\x1b[0m\n" << "   Параметры: здоровье = 1, защита = 0" << endl;
				cout << "\x1b[36mtype: Старший коренастый\x1b[0m\n" << "   Параметры: здоровье = 2, защита = 1" << endl;
				cout << "\x1b[95mмодификатор: может пережить 1 любой укус.\x1b[0m" << endl;
				cout << "--------->\x1b[33m Воин \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Элитный\x1b[0m\n" << "   Параметры: здоровье = 8, защита = 4, урон = 3" << endl;
				cout << "\x1b[36mtype: Продвинутый худой\x1b[0m\n" << "   Параметры: здоровье = 6, защита = 2, урон = 3" << endl;
				cout << "\x1b[95mмодификатор: весь урон перенаправляется на союзников\x1b[0m" << endl;
				cout << "--------->\x1b[33m Специальный \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Трудолюбивый обычный мирный талантливый - Толстоножка\x1b[0m\n" << "   Параметры: здоровье = 20, защита = 9" << endl;
				cout << "\x1b[95mмодификаторы: \n*может быть атакован войнами; всегда находит нужный ресурс в куче, даже если его больше нет.\x1b[0m" << endl;
				cout << "_________________________________________________" << endl;
				cout << "|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
				FlagOut = 1;
				break;
			case 51: // black
				
				cout << "<<<------------------------------------------>>>" << endl;
				cout << "\t\t\x1b[96mСтатистика\x1b[0m" << endl;
				cout << ">>>------------------------------------------<<<" << endl;
				cout << "Колония < \x1b[90mЧёрные\x1b[0m > :\n" << "\x1b[36m   Королева < Беатрикс > :\x1b[0m" << endl;
				cout << "     здоровье = " << BlackQueen.HP << ", защита = " << BlackQueen.Armor << ", урон = " << BlackQueen.Damage << endl;
				cout << "Ресурсы (шт.): Ветка = " << ResBlack["branch"] << "  Листик = " << ResBlack["leaf"] << "  Камень = " << ResBlack["rock"] << "  Росинка = " << ResBlack["dew"] << endl;
				cout << "--------->\x1b[33m Рабочий \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Старший\x1b[0m\n" << "   Параметры: здоровье = 2, защита = 1" << endl;
				cout << "\x1b[36mtype: Старший бригадир\x1b[0m\n" << "   Параметры: здоровье = 2, защита = 1" << endl;
				cout << "\x1b[95mмодификатор: все рабочие могут брать +1 ресурс\x1b[0m" << endl;
				cout << "--------->\x1b[33m Воин \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Легендарный\x1b[0m\n" << "   Параметры: здоровье = 10, защита = 6, урон = 4" << endl;
				cout << "\x1b[36mtype: Продвинутый феникс\x1b[0m\n" << "   Параметры: здоровье = 6, защита = 2, урон = 3" << endl;
				cout << "\x1b[95mмодификатор: защита уменьшена в двое\x1b[0m" << endl;
				cout << "--------->\x1b[33m Специальный \x1b[0m<---------" << endl;
				cout << "\x1b[36mtype: Ленивый обычный агрессивный неряшливый - Сверчок\x1b[0m\n" << "   Параметры: здоровье=21, защита=9, урон=7" << endl;
				cout << "\x1b[95mмодификаторы: не может брать ресурсы; может быть атакован войнами; \n  атакует врагов(1 цель за раз и наносит 1 укус); защита уменьшена в двое.\x1b[0m" << endl;
				cout << "_________________________________________________" << endl;
				cout << "|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
				FlagOut = 1;
				break;
			case 52: //поход
			{
				FlagOut = 1;
				cout << "\x1b[33mНачало Похода:\x1b[0m\n" << endl;
				int GWorker = 0, GWarrior = 0, RWorker = 0, RWarrior = 0, BWorker = 0, BWarrior = 0;
				bool RedS = 0, GreenS = 0, BlackS = 0;
				for (int one = 0; one < 5; one++)
				{
					GWorker = 0; GWarrior = 0; GreenS = 0;
					for (int i = 0; i < 40; i++)
					{
						(GreenWorker[i].GPS == (one + 1) && GreenWorker[i].HP > 0) ? GWorker++ : GWorker = GWorker;
						(GreenWarrior[i].GPS == (one + 1) && GreenWarrior[i].HP > 0) ? GWarrior++ : GWarrior = GWarrior;
					}
					(Bee.GPS == (one + 1) && Bee.HP > 0) ? GreenS = 1 : GreenS = GreenS;

					if (GWorker > 0 || GWarrior > 0 || GreenS > 0)
					{
						if (day > 5 && day < 8)
							cout << "-С колонии \x1b[32mЗелёные\x1b[0m отправились: Рабочие = " << GWorker / 2 << ", Воины = " << GWarrior / 2 << ",\n Насекомое = " << GreenS << " на кучу " << one + 1 << endl;
						else
							cout << "-С колонии \x1b[32mЗелёные\x1b[0m отправились: Рабочие = " << GWorker << ", Воины = " << GWarrior << ",\n Насекомое = " << GreenS << " на кучу " << one + 1 << endl;
					}
				}
				for (int two = 0; two < 5; two++)
				{
					RWorker = 0; RWarrior = 0; RedS = 0;
					for (int i = 0; i < 40; i++)
					{
						(RedWorker[i].GPS == (two + 1) && RedWorker[i].HP > 0) ? RWorker++ : RWorker = RWorker;
						(RedWarrior[i].GPS == (two + 1) && RedWarrior[i].HP > 0) ? RWarrior++ : RWarrior = RWarrior;
					}
					(Thicklegged.GPS == (two + 1) && Thicklegged.HP > 0) ? RedS = 1 : RedS = RedS;

					if (RWorker > 0 || RWarrior > 0 || RedS > 0)
					{
						if (day > 5 && day < 8)
							cout << "-С колонии \x1b[31mКрасные\x1b[0m отправились: Рабочие = " << RWorker / 2 << ", Воины = " << RWarrior / 2 << ",\n Насекомое = " << RedS << " на кучу " << two + 1 << endl;
						else
							cout << "-С колонии \x1b[31mКрасные\x1b[0m отправились: Рабочие = " << RWorker << ", Воины = " << RWarrior << ",\n Насекомое = " << RedS << " на кучу " << two + 1 << endl;
					}
				}
				for (int three = 0; three < 5; three++)
				{
					BWorker = 0; BWarrior = 0; BlackS = 0;
					for (int i = 0; i < 40; i++)
					{
						(BlackWorker[i].GPS == (three + 1) && BlackWorker[i].HP > 0) ? BWorker++ : BWorker = BWorker;
						(BlackWarrior[i].GPS == (three + 1) && BlackWarrior[i].HP > 0) ? BWarrior++ : BWarrior = BWarrior;
					}
					(Cricket.GPS == (three + 1) && Cricket.HP > 0) ? BlackS = 1 : BlackS = BlackS;

					if (BWorker > 0 || BWarrior > 0 || BlackS > 0)
					{
						if (day > 5 && day < 8)
							cout << "-С колонии \x1b[90mЧёрные\x1b[0m отправились:  Рабочие = " << BWorker / 2 << ", Воины = " << BWarrior / 2 << ",\n Насекомое = " << BlackS << " на кучу " << three + 1 << endl;
						else
							cout << "-С колонии \x1b[90mЧёрные\x1b[0m отправились:  Рабочие = " << BWorker << ", Воины = " << BWarrior << ",\n Насекомое = " << BlackS << " на кучу " << three + 1 << endl;
					}
				}
				cout << "\n\x1b[33mКонец Похода:\x1b[0m" << endl;
				int RetGreenWorker = 0, RetGreenWarrior = 0, RetRedWorker = 0, RetRedWarrior = 0, RetBlackWorker = 0, RetBlackWarrior = 0;
				bool RetGreenS = 0, RetRedS = 0, RetBlackS = 0;
				for (int i = 0; i < 40; i++)
				{
					(GreenWorker[i].HP > 0) ? RetGreenWorker++ : RetGreenWorker = RetGreenWorker;
					(GreenWarrior[i].HP > 0) ? RetGreenWarrior++ : RetGreenWarrior = RetGreenWarrior;
				}
				for (int i = 0; i < 40; i++)
				{
					(RedWorker[i].HP > 0) ? RetRedWorker++ : RetRedWorker = RetRedWorker;
					(RedWarrior[i].HP > 0) ? RetRedWarrior++ : RetRedWarrior = RetRedWarrior;
				}
				for (int i = 0; i < 40; i++)
				{
					(BlackWorker[i].HP > 0) ? RetBlackWorker++ : RetBlackWorker = RetBlackWorker;
					(BlackWarrior[i].HP > 0) ? RetBlackWarrior++ : RetBlackWarrior = RetBlackWarrior;
				}
				cout << "\nВ колонию \x1b[32mЗелёных\x1b[0m вернулись :\n    рабочие = " << RetGreenWorker << ", воины = " << RetGreenWarrior << ", насекомые = " << RetGreenS << endl;
				cout << "   Добыто ресурсов: Ветка = " << ResGreen["branch"] - GreenBranch << ", листик = " << ResGreen["leaf"] - GreenLeaf << ", \nкамень = " << ResGreen["rock"] - GreenRock << ", росинка = " << ResGreen["dew"] - GreenDew << endl;
				(AGreenLich > 0) ? cout << "   Новые личинки: " << AGreenLich << endl : cout << "   Выросли: Еще растут" << endl;
				cout << "В колонию \x1b[31mКрасных\x1b[0m вернулись :\n    рабочие = " << RetRedWorker << ", воины = " << RetRedWarrior << ", насекомые = " << RetRedS << endl;
				cout << "   Добыто ресурсов: Ветка = " << ResRed["branch"] - RedBranch << ", листик = " << ResRed["leaf"] - RedLeaf << ", \nкамень = " << ResRed["rock"] - RedRock << ", росинка = " << ResRed["dew"] - RedDew << endl;
				(ARedLich > 0) ? cout << "   Новые личинки: " << ARedLich << endl : cout << "   Выросли: Еще растут" << endl;
				cout << "В колонию \x1b[90mЧёрных\x1b[0m вернулись :\n    рабочие = " << RetBlackWorker << ", воины = " << RetBlackWarrior << ", насекомые = " << RetBlackS << endl;
				cout << "   Добыто ресурсов: Ветка = " << ResBlack["branch"] - BlackBranch << ", листик = " << ResBlack["leaf"] - BlackLeaf << ", \nкамень = " << ResBlack["rock"] - BlackRock << ", росинка = " << ResBlack["dew"] - BlackDew << endl;
				(ABlackLich > 0) ? cout << "   Новые личинки: " << ABlackLich << endl : cout << "   Выросли: Еще растут" << endl;
				break;
			}
			case 53:
			{
				FlagOut = 1;
				cout << "\x1b[32m1)Элитный рабочий\t2)Обычный сонный рабочий\t3)Легендарный воин\t4)Обычный неряшливый воин\x1b[0m" << endl;
				cout << "\x1b[31m5)Обычный рабочий\t6)Старший коренастый рабочий\t7)Элитный воин\t8)Продвинутый худой воин\x1b[0m" << endl;
				cout << "\x1b[90m9)Старший рабочий\t0)Старший бригадир рабочий\t-)Легендарный воин\t+)Продвинутый феникс\x1b[0m" << endl;
				int info = _getch();
				switch (info)
				{
				case 49:
					Description("Элитный рабочий", 8, 4, 0, "Нефертити", 'g');
					break;
				case 50:
					Description("Обычный сонный рабочий", 1, 0, 0, "Нефертити", 'g');
					break;
				case 51:
					Description("Легендарный воин", 10, 6, 4, "Нефертити", 'g');
					break;
				case 52:
					Description("Обычный неряшливый воин", 1, 0, 1, "Нефертити", 'g');
					break;
				case 53:
					Description("Обычный рабочий", 1, 0, 0, "Мария", 'r');
					break;
				case 54:
					Description("Старший коренастый рабочий", 2, 1, 0, "Мария", 'r');
					break;
				case 55:
					Description("Элитный воин", 8, 4, 3, "Мария", 'r');
					break;
				case 56:
					Description("Продвинутый худой воин", 6, 2, 3, "Мария", 'r');
					break;
				case 57:
					Description("Старший рабочий", 2, 1, 0, "Беатрикс", 'b');
					break;
				case 48:
					Description("Старший бригадир рабочий", 2, 1, 0, "Беатрикс", 'b');
					break;
				case '-':
					Description("Легендарный воин", 10, 6, 4, "Беатрикс", 'b');
					break;
				case '+':
					Description("Продвинутый феникс", 6, 2, 3, "Беатрикс", 'b');
					break;
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
			if (FlagOut == 1) int b = _getch();
		}
	}
	return 0;
}