#include "Monom.h"

Monom::Monom(double coef_, int deg_, Monom* next_)
{
	if (deg_ > 999999) {
		throw std::logic_error("Int overflow");
	}
	else {
		coef = coef_;
		deg = deg_;
		next = next_;

	}
}

bool Monom::operator==(const Monom& rhs) const {
return (this->coef == rhs.coef && this->deg == rhs.deg);
}

bool Monom::operator!=(const Monom& rhs) const {
	if (*this == rhs)
	{
		return false;
	}
	else { return true; }
}