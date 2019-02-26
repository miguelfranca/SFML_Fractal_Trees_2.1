
#include "node.h"

int randomI(const int begin, const int end) {
	return rand() % (end - begin + 1) + begin;
};

float randomF(const float begin, const float end) {
	return (float)rand() / RAND_MAX * (end - begin) + begin;
};

int myrandom() {
	return randomI(MIN_BRANCHES, MAX_BRANCHES);
}