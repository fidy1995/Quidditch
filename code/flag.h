#ifndef _FLAG_
#define _FLAG_

#include "tvector.h"

class Flag {
	TVector pos;

public:
	Flag() : pos(TVector()) {}
	Flag(TVector p) : pos(p) {}

	TVector const getPosition() const { return pos; }
	void setPosition(TVector p) { pos = p; }
};

#endif // _FLAG_