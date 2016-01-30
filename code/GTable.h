#ifndef _G_TABLE_
#define _G_TABLE_

#include "table.h"
#include "GTex.h"
#include "perlin.h"

class GTable {
	Table *table;
	GLfloat color[64][64];
public:
	GTable() :table(NULL) {}
	GTable(Table t, Perlin *p) {
		table = new Table(t.getLength(), t.getWidth());
		for (int x = 0; x < 64; x++) {
			for (int y = 0; y < 64; y++) {
				color[x][y] = p->getValue(x, y);
			}
		}
	}

	void GDrawTable(GTex *g);
};

#endif // _G_TABLE_