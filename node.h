#pragma once

#include <cstdlib> //NULL, rand()

#include "Global.h"


int randomI(int begin, int end);
float randomF(float begin, float end);
int myrandom();

class node {
public:


	node(const unsigned n = 1, const float xx = 0.f, const float yy = 0.f, const float l = 0.f) : x(xx), y(yy), L(l) {
		create(n);
	}

	node*& operator[](const unsigned i) { return to[i]; }
	unsigned getN() { return N; }
	float& X() { return x; }
	float& Y() { return y; }
	float& length() { return L; }

	~node() {
		for (unsigned i = 0; i < N; i++)
			//this will call ~node() for each to[i] and delete the pointer (which was missing by just calling ~node() )
			if (to[i] != NULL)	delete to[i];
		delete[] to;
	}

	unsigned height() const {
		unsigned max = 0;
		for (unsigned i = 0; i < N; i++) {
			unsigned temp = (to[i] == NULL) ? 1 : to[i]->height();
			if (max < temp) max = temp;
		}
		return max + 1;
	}

	unsigned full() const {
		unsigned size = 0;
		for (unsigned i = 0; i < N; i++)
			size += (to[i] == NULL) ? 1 : to[i]->full();
		return size + 1;
	}

	/*void generate(const float prob){
		for(unsigned i=0; i<N; i++){
			if(to[i]==NULL && (float)(rand())/RAND_MAX <= prob){
				to[i]=new node(N);
				to[i]->generate(prob);
			}
		}
	}*/


	void tree(const float angle, const float spread = DEFAULT_ANGLE) {

		if (N == 0) create(myrandom());

		for (unsigned i = 0; i < N; i++) {
			if (to[i] == NULL) {
				float new_angle = angle + (N == 1 ? 0.f : (i / ((N - 1.f) / 2.f) - 1.f)) * spread;
				float newLength = randomF(min_contraction, max_contraction) * L;

				create_branch(i, newLength, new_angle);
				if (minLength <= newLength * max_contraction) to[i]->tree(new_angle, spread);
			}
		}
	}

	void create_branch(const unsigned i, const float length, const float angle) {

		float new_x = x + length * cos(angle * PI / 180.f);
		float new_y = y + length * sin(angle * PI / 180.f);

		int a = (minLength <= length * max_contraction) ? myrandom() : 0;
		to[i] = new node(a, new_x, new_y, length);
	}

	void create(const unsigned n) {
		if (to != NULL) this->~node();

		N = n;
		if (N == 0) {
			to = NULL;
			return;
		}
		to = new node*[N];
		for (unsigned i = 0; i < N; i++)
			to[i] = NULL;
	}
private:

	float x, y;
	unsigned N; //how many branches
	node** to; 	//pointer to N new nodes
	float L;
};