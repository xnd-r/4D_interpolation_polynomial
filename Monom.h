#pragma once
#include <stdexcept>

struct Monom
{
	double coef;
	int deg;
	Monom* next;
	
	Monom(double coef_ = 0.0, int deg_ = 0, Monom* next_ = NULL);
	bool Monom::operator==(const Monom& rhs) const;
	bool Monom::operator!=(const Monom& rhs) const;
};

