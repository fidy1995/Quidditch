#ifndef _GAME_
#define _GAME_

#include "bat.h"
#include "naivePhy.h"
#include "sphere.h"
#include "table.h"
#include "tvector.h"
#include "flag.h"

#include <vector>

using namespace std;

const double ZSTD = 2.0f;
const double paddle = 0.1f;
const double td = 0.01f;

class Game {
	vector<Sphere *> spheres;
	Bat *bat;
	Table *table;
	Flag *flag;

	int batCount;
	int score;

	void move(double timeDelta);
	void bump();

public:
	Game();

	void run(double timeDelta);

	//void setSphere(const Sphere &s, int index);
	void setBat(const Bat &b);
	void setBatCount(const int count);
	//void setTable(const Table &t);

	bool const stopped() const;

	Sphere const getSphere(int index) const;
	unsigned int const getSphereNumber() const;
	Bat const getBat() const;
	Table const getTable() const;
	Flag const getFlag() const;
	int const getScore() const;
	int const getBatCount() const;
};

#endif // _GAME_