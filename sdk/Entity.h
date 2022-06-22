#pragma once

#include "Vector.h"

struct Entity {
public:
	char __padding0[0x160];
	Vector position;
	char __padding1[0x60];
	int health;
	int max_health;
};