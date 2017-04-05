#include "KeepRunning.h"
#include <iostream>

KeepRunning::~KeepRunning() {
	std::cin.get();
	std::cin.get();
}
