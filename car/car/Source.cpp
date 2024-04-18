#include<iostream>
#include<conio.h>
using namespace std;

#define MIN_TANK_VOL 20
#define MAX_TANK_VOL 120

class Tank
{
	const int VOLUME;
	double fuel_lvl;
public:
	const int get_VOLUME() const
	{
		return  VOLUME;
	}
	double get_fuel_lvl() const
	{
		return  fuel_lvl;
	}
	void fill(double amount)
	{
		if (amount < 0)return;
		if (fuel_lvl + amount < VOLUME) fuel_lvl += amount;
		else fuel_lvl = VOLUME;
	}
	double give_fuel(double amount)
	{
		if (amount < 0)return fuel_lvl;
		fuel_lvl -= amount;
		if (fuel_lvl < 0) fuel_lvl = 0;
		return fuel_lvl;
	}
	Tank(int volume)
		:VOLUME(
		volume<MIN_TANK_VOL?MIN_TANK_VOL:
		volume>MAX_TANK_VOL?MAX_TANK_VOL:
		volume)
	{
		true;
		this->fuel_lvl = 0;
		cout << "tanc is rady" << this << endl;
	}
	~Tank()
	{
		cout << "tank is over" << endl;
	}
	void info() const
	{
		cout << "tank volume " << VOLUME << " liters.\n";
		cout << "fuel lvl " << fuel_lvl << " liters.\n";

	}

};

#define MIN_ENG_CONSUMP 3
#define MAX_ENG_CONSUMP 30
class Engine
{
	const double CONSUMP;
	double consump_per_sec;
	bool is_start;
public:
	double get_consump()const
	{
		return CONSUMP;
	}

	double get_consumpper_sec()const
	{
		return consump_per_sec;
	}
	Engine(double consump)
		:CONSUMP
		(
			consump < MIN_ENG_CONSUMP ? MIN_ENG_CONSUMP :
			consump > MAX_ENG_CONSUMP ? MAX_ENG_CONSUMP :
			consump
		),
		consump_per_sec(CONSUMP * 3e-5),is_start(false)
	{
		

		cout << "engine is redy " << this << endl;
	}
	~Engine() 
	{
		cout << "engine is over " << this << endl;
	}
	void start()
	{
		is_start = true;
	}
	void stop()
	{
		is_start = false;
	}
	bool started() const
	{
		return is_start;
	}
	void info() const
	{
		cout << "consuption: " << CONSUMP << " liters/100km" << endl;
		cout << "consuption: " << consump_per_sec << " liters/sec" << endl;
		cout << "engine is  " << (is_start ? "started" : "stopped") << endl;
	}

};

class Car 
{
	Engine engine;
	Tank tank;
	bool driver_inside;
public:
	Car(int consump = 10, int vol = 60) : engine(consump), tank(vol), driver_inside(false) 
	{
		cout << "your car is ready to go" << endl;
	}
	~Car()
	{
		cout << "your car is over" << endl;
	}
	void get_in() 
	{
		driver_inside = true;
		panel();
	}
	void get_out()
	{
		driver_inside = false;
		cout << "out of the car" << endl;
	}
	void control()
	{
		char key;
		do
		{
			key = _getch();
			switch (key) 
			{
			case 13:driver_inside ? get_out() : get_in();break;
					
			}

		} while (key!=27);

	}
	void panel()const 
	{
		while (driver_inside) 
		{
			system("CLS");
			cout << "fuel lvl :\t" << tank.get_fuel_lvl() << "liters.\n";
			cout << "engine is " << (engine.started() ? "started" : "stoped") << endl;
		}
	}
	void info()const
	{
		engine.info();
		tank.info();
	}
};

//#define TANK_CHECK
//#define ENGINE
int main()
{
	setlocale(LC_ALL, "");
#ifdef TANK_CHECK
	Tank tank(85);
	int fuel;
	do
	{
		cout << "введите объем топлива: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();

	} while (fuel > 0);
#endif
#ifdef ENGINE
	Engine engine(10);
	engine.info();
#endif

	Car bmw;
	bmw.info();
	bmw.control();

}

