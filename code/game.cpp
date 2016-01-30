#include "game.h"
#include <iostream>
#include <Windows.h>

Game::Game()
{
	// build spheres
	spheres.resize(14, NULL);
	double m = defaultMass, r = defaultRange, p = paddle, h = defaultHeight;
	spheres[0] = new Sphere(CUE, m, r, TVector(0, r, ZSTD + r), TVector());
	spheres[1] = new Sphere(QUIET, m, r, TVector(0, r, -ZSTD), TVector());
	spheres[2] = new Sphere(QUIET, m, r, TVector(2 * r + p, r, -ZSTD - 2 * r - p), TVector());
	spheres[3] = new Sphere(QUIET, m, r, TVector(-2 * r - p, r, -ZSTD - 2 * r - p), TVector());
	spheres[4] = new Sphere(QUIET, m, r, TVector(0, r, -ZSTD - 4 * r - 2 * p), TVector());
	spheres[5] = new Sphere(QUIET, m, r, TVector(4 * r + 2 * p, r, -ZSTD - 4 * r - 2 * p), TVector());
	spheres[6] = new Sphere(QUIET, m, r, TVector(-4 * r - 2 * p, r, -ZSTD - 4 * r - 2 * p), TVector());
	spheres[7] = new Sphere(NOISE, m, r, TVector(-4 * r - 2 * p, r, -ZSTD), TVector(0.0f, 0.0f, defaultVelocity));
	spheres[8] = new Sphere(NOISE, m, r, TVector(4 * r + 2 * p, r, -ZSTD), TVector(0.0f, 0.0f, defaultVelocity));
	spheres[9] = new Sphere(NOISE, m, r, TVector(6 * r + 3 * p, r, -ZSTD - 2 * r - p), TVector(0.71 * defaultVelocity, 0.0f, 0.71 * defaultVelocity));
	spheres[10] = new Sphere(NOISE, m, r, TVector(-6 * r - 3 * p, r, -ZSTD - 2 * r - p), TVector(-0.71 * defaultVelocity, 0.0f, 0.71 * defaultVelocity));
	spheres[11] = new Sphere(NOISE, m, r, TVector(2 * r + p, r, -ZSTD - 6 * r - 3 * p), TVector(defaultVelocity, 0.0f, 0.0f));
	spheres[12] = new Sphere(NOISE, m, r, TVector(-2 * r - p, r, -ZSTD - 6 * r - 3 * p), TVector(-defaultVelocity, 0.0f, 0.0f));
	spheres[13] = new Sphere(GOLD, m, r, TVector(0.0f, h, 0.0f), TVector());

	table = new Table(tableLength / RATIO, tableWidth / RATIO);
	flag = new Flag(TVector(-tableWidth / RATIO / 2, 0, -tableLength / RATIO / 2));
	batCount = 0;
	score = 0;
}

void Game::run(double timeDelta) {
	move(timeDelta);
	bump();
}

void Game::move(double timeDelta) {
	for (int i = 0; i < spheres.size(); i++) {
		spheres[i]->move(spheres, timeDelta);
	}
}

void Game::bump() {
	for (int i = 0; i < spheres.size(); i++) {
		for (int j = 0; j < spheres.size(); j++) {
			int k = spheres[i]->bump(*spheres[j]);
			if (k) {
				score += k;
			}
		}
		table->bump(*spheres[i]);
	}
	// when the gold is bumped, it will immediately disappear
	if (spheres.size() == 14 && spheres[13]->getType() == DEFAULT) {
		spheres.pop_back();
	}
}

void Game::setBat(const Bat &b) {
	if (bat) {
		delete bat;
	}
	Bat *bat = new Bat(b.getForce());
	bat->hit(*spheres[0]);
	batCount++;
}

void Game::setBatCount(const int count) {
	batCount = count;
}

Sphere const Game::getSphere(int index) const {
	if (index >= spheres.size()) {
		cout << "getSphere: index out of size\n";
		return Sphere();
	}
	return *spheres[index];
}

unsigned int const Game::getSphereNumber() const {
	return spheres.size();
}

Bat const Game::getBat() const {
	return *bat;
}

Table const Game::getTable() const {
	return *table;
}

Flag const Game::getFlag() const {
	return *flag;
}

int const Game::getScore() const {
	return score;
}

int const Game::getBatCount() const {
	return batCount;
}

bool const Game::stopped() const {
	for (int i = 0; i < 7; i++) {
		if (spheres[i]->getVelocity() != TVector(0, 0, 0)) {
			return false;
		}
	}
	for (int i = 7; i < 13; i++) {
		if (spheres[i]->getVelocity().model() - 0.125 > 0.00001
			|| spheres[i]->getVelocity().model() - 0.125 < -0.00001) {
			return false;
		}
	}
	return true;
}