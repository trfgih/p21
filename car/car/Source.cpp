#include<iostream>
#include<conio.h>
#include<thread>
#include<Windows.h>
using namespace std;

#define Enter 13
#define Escape 27

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
	double set_consumpper_sec(int speed)
	{
		if (speed > 200)consump_per_sec = CONSUMP * 3e-5 * 10;
		else if (speed > 140)consump_per_sec = CONSUMP * 3e-5 * 25 / 3;
		else if (speed > 100)consump_per_sec = CONSUMP * 3e-5 * 20 / 3;
		else if (speed > 60)consump_per_sec = CONSUMP * 3e-5 * 14 / 3;
		else if (speed > 0)consump_per_sec = CONSUMP * 3e-5 * 20 / 3;
		else consump_per_sec = CONSUMP * 3e-5;
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


#define MAX_SPEED_LOW_LIMIT 50
#define MAX_SPEED_HIGH_LIMIT 447
class Car 
{
	Engine engine;
	Tank tank;
	bool driver_inside;
	struct 
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
		std::thread free_wheeling_thread;
	}threads;
	int speed;
	const int MAX_SPEED;
	const int ACCELERATE;
	struct
	{
		bool reverse = false;
	}transmission;
public:
	Car(int consump = 10, int vol = 60, int max_speed=250):
		engine(consump),
		tank(vol),
		driver_inside(false),
		speed(0),
		ACCELERATE(MAX_SPEED/20),
		MAX_SPEED
		(
			max_speed <MAX_SPEED_LOW_LIMIT? MAX_SPEED_LOW_LIMIT:
			max_speed >MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
			max_speed
		)
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
		threads.panel_thread = std::thread(&Car::panel,this);
	}
	void get_out()
	{

		driver_inside = false;
		if(threads.panel_thread.joinable())threads.panel_thread.join();
		system("CLS");
		cout << "out of the car" << endl;
	}
	void start() 
	{
		if (tank.get_fuel_lvl())
		{
			engine.start();
			threads.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
		
	}
	void stop() 
	{
		engine.stop();
		if (threads.engine_idle_thread.joinable())threads.engine_idle_thread.join();
	}
	void accelerate() 
	{
		if (engine.started()) 
		{
			speed += ACCELERATE;
			if (speed > MAX_SPEED)speed = MAX_SPEED;
			if (transmission.reverse && speed > MAX_SPEED / 7)speed = MAX_SPEED / 7;
			if (!threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
			std::this_thread::sleep_for(1s);
		}
		
	}
	void slow_down()
	{
		speed -= ACCELERATE;
		if (speed < 0)speed = 0;
		if (speed == 0 && threads.free_wheeling_thread.joinable())
			threads.free_wheeling_thread.join();
		std::this_thread::sleep_for(1s);
	
	}
	void control()
	{
		char key;
		do
		{
			key = 0;
			if(_kbhit())key = _getch();
			switch (key) 
			{
			case'F':case'f':
			if (driver_inside) 
			{
				cout << "get out of the car";
			}
			else
			{

				double fuel;
				cout << "введите уровень топлива: "; cin >> fuel;
				tank.fill(fuel);
			}
			case Enter:driver_inside ? get_out() : get_in();break;
			case'I':case 'i': engine.started() ? stop() : start(); break;
			case'W':case'w': accelerate(); break;
			case'S':case's': slow_down(); break;
			case'R':case'r': if (speed == 0)transmission.reverse = !transmission.reverse; break;
			case Escape: 
				speed = 0;
				stop(); 
				get_out(); 
				break;	
			}
			if (tank.get_fuel_lvl() == 0)stop();
			if (speed < 0)speed = 0;
			if (speed == 0 && threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread.join();

		} while (key!=27);

	}
	void free_wheeling() 
	{
		while (speed)
		{	
			if (speed < 0) speed = 0;
			
			std::this_thread::sleep_for(1s);
		}
	}
	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.set_consumpper_sec(speed)))
			this_thread::sleep_for(1s);

	}
	void panel()const 
	{
		while (driver_inside) 
		{
			system("CLS");
			for (int i = 0; i < speed / 3; i++)cout << "|"; cout << endl;;
			cout << "Speed: " << speed << "km/h\t";
			cout << (transmission.reverse ? "R" : " ");
			cout << endl;

			cout << "engine is " << (engine.started() ? "started" : "stoped") << endl;
			cout << "fuel lvl :\t" << tank.get_fuel_lvl() << "liters.\t";
			if (tank.get_fuel_lvl() < 5) 
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << " LOW FUEL ";
				SetConsoleTextAttribute(hConsole, 0xC7);
			}
			cout << endl;
			cout << "consump: " << engine.get_consumpper_sec() << " liters/sec\n";
			std::this_thread::sleep_for(100ms);
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

	Car bmw(35,85,290);
	bmw.info();
	bmw.control();

}

