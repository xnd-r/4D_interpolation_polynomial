#include <iostream>
#include "monom.h"
#include "Polynomial.h"
using namespace std;

unsigned int _size = 5;

double		I[5] = {0.16646, 0.110307, 0.07575, 0.04929, 0.02951};
double		R[5] = { 10., 20., 30., 40., 50 };
Polynomial	_Res;
Polynomial	Res[5];
Polynomial	numerator[5];

double		denominator[5] {1., 1., 1., 1., 1.};
Monom		init(1, 0, NULL);

void init_numer() {
	for (int i(0); i < _size; ++i) {
		numerator[i].add_monom_in_tail(&init);
	}
}

void init_denom() {
	for (int i(0); i < _size; ++i) {
		denominator[i] = 1.;
	}
}

Monom m1(1, 10000, NULL);

void _fractions() {
	for (int i(0); i < _size; ++i) {
		init_numer();
		init_denom();

		for (int j(0); j < _size; ++j) {
			if (i != j) {
				Monom m2(-R[j], 0, NULL);
				Polynomial p;
				p.add_monom_in_tail(&m1);
				p.add_monom_in_tail(&m2);
				numerator[i] = p * numerator[i];
				denominator[i] = (R[i] - R[j]) * denominator[i];
			}
		}
		denominator[i] = I[i] / denominator[i];
		Res[i] = numerator[i] * denominator[i];
		Res[i].bring_similar();
	}
}

Polynomial final_polyn() {
	for (int i(0); i < _size; ++i)
		_Res = _Res + Res[i];

		_Res.bring_similar();
		_Res.bubble_sort();

	return _Res;
}



int main(int argc, char* argv[]){
	_fractions();
	final_polyn();
	Polynomial final_p;
	final_p = _Res.diff();

	std::cout << _Res << endl;
	std::cout << final_p << endl;

return 0;	
}
