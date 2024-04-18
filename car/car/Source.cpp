#include<iostream>
using namespace std;

#define MIN_TANK_VOL 20
#define MAX_TANK_VOL 120

class tanc
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
	void tank(int volume): VOLUME(volume)
	{
		this->fuel_lvl = 0;
		cout << "tanc is rady" << this << endl;
	}
	void info() const
	{
		cout << "tank volume" << VOLUME << "liters.\n";
		cout << "fuel lvl" << fuel_lvl << "liters.\n";

	}
};
int main()
{
	setlocale(LC_ALL, "");
	tanc tank (-50);
	tanc.info();
}
