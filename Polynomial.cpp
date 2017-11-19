#pragma once
#include "Polynomial.h"

Polynomial::Polynomial() {
	size = 1; head = new Monom(-1.0, -1, NULL);
	tail = head;
	tail->next = head;
}
Polynomial::Polynomial(const Polynomial& p) {
	head = new Monom(-1.0, -1, NULL);
	tail = head;
	tail->next = head;
	size = 1;

	Monom*  temp = p.head->next;
	while (temp != p.head)
	{

		Monom* new_node = new Monom(temp->coef, temp->deg,
			temp->next);
		size++;

		tail->next = new_node;
		tail = new_node;

		temp = temp->next;

	}
	tail->next = head;

}
void Polynomial::Input_poly() {
	int f = -1;
	int curr_coef = -1;
	int curr_x = -1;
	int curr_y = -1;
	int curr_z = -1;
	
	while (f != 1) {
		Monom* new_node = new Monom();
		for (;;) {
			cout << "Enter another coefficient: " << endl;
			cin >> curr_coef;
			if (std::cin.fail())
			{
				std::cout << "Invalid input, repeat" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				new_node->coef = curr_coef;
				break;
			}
		}


		for (;;) {
			cout << "enter another degree of x: " << endl;
			cin >> curr_x;
			if (std::cin.fail() || curr_x < 0)
			{
				std::cout << "Invalid input, repeat" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				new_node->deg = curr_x * 10000;
				break;
			}
		}

		for (;;) {
			cout << "enter another degree of y: " << endl;
			cin >> curr_y;
			if (std::cin.fail() || curr_y < 0)
			{
				std::cout << "Invalid input, repeat" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				new_node->deg += curr_y * 100;
				break;
			}
		}

		for (;;) {
			cout << "enter another degree of z: " << endl;
			cin >> curr_z;
			if (std::cin.fail() || curr_z < 0)
			{
				std::cout << "Invalid input, repeat" << '\n';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				new_node->deg += curr_z;
				break;
			}
		}

		new_node->next = head;

		if (size == 1)
		{
			tail = new_node;
			head->next = tail;
			tail->next = head;
			size = 2;
		}
		else {
			tail->next = new_node;
			tail = new_node;
			tail->next = head;
			size++;
		}
		cout << "Is Input ended? // 0 means no, 1 means yes " << endl;
		cin >> f;
	}
	this->bring_similar();
	this->bubble_sort();
}
void Polynomial::bubble_sort() {
	Monom *ptr1 = this->head->next, *ptr2;
	while (ptr1 != head) {
		ptr2 = ptr1->next;
		while (ptr2 != head) {
			if ((ptr1->deg) < (ptr2->deg)) { //MAGIC! sorting by max!
				swap_(ptr1, ptr2);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}
void Polynomial::swap_(Monom* m1, Monom* m2) {
	double coef_buf;
	coef_buf = m1->coef;
	m1->coef = m2->coef;
	m2->coef = coef_buf;
	int deg_buf;
	deg_buf = m1->deg;
	m1->deg = m2->deg;
	m2->deg = deg_buf;
}
void Polynomial::add_monom_in_tail(Monom* m)
{
	if (tail == head)
	{
		Monom* new_monom = new Monom(m->coef, m->deg, NULL);
		tail = new_monom;
		head->next = tail;
		tail->next = head;
		size++;
	}
	else {
		Monom* new_monom = new Monom(m->coef, m->deg, NULL);
		tail->next = new_monom;
		tail = new_monom;
		tail->next = head;
		size++;
	}
}
void Polynomial::del_monom(Monom *ptr2) {
	Monom* tmp = this->head->next;
	while (tmp->next != ptr2) {
		tmp = tmp->next;
	}
	Monom* buf = tmp->next->next;
	delete ptr2;
	tmp->next = buf;
	size--;
}
const Polynomial& Polynomial::operator = (const Polynomial &p) {
	if (this == &p) {
		return *this;
	}

	while (head != tail)
	{
		Monom* temp = head->next;
		delete head;
		head = temp;
		tail->next = head;
	}
	head->coef = -1.0;
	head->deg = -1;
	size = 1;

	Monom*  temp = p.head->next;
	while (temp != p.head)
	{
		add_monom_in_tail(new Monom(temp->coef, temp->deg, temp->next));

		temp = temp->next;

	}

	return *this;
}
Polynomial Polynomial::operator + (Polynomial p) {
	Monom* m1 = (this->head)->next;
	Monom* m2 = p.head->next;
	Polynomial res;
	while (m1 != head && m2 != p.head)
	{
		if (m1->deg > m2->deg) {
			res.add_monom_in_tail(m1);
			m1 = m1->next;
		}
		else if (m1->deg == m2->deg) {
			res.add_monom_in_tail(m1);
			res.tail->coef += m2->coef;
			m1 = m1->next;
			m2 = m2->next;
		}
		else {
			res.add_monom_in_tail(m2);
			m2 = m2->next;
		}

	}
	if (m1->deg != -1) {
		m2 = m1;
	}
	else if (m2->deg != -1)
	{
		m1 = m2;
	}

	while (m1->deg != -1) {
		res.add_monom_in_tail(m1);
		m1 = m1->next;
	}
	res.bring_similar();
	return res;
}
Polynomial Polynomial::operator - (Polynomial m) {
	return *this + m*(-1);
}
Polynomial Polynomial::operator * (double d) {
	Polynomial res = *this;
	Monom *buf = res.head->next;
	while (buf != res.head) {
		buf->coef *= d;
		buf = buf->next;
	}
	return res;
}

Polynomial Polynomial::diff() {
	Polynomial res = *this;
	Monom *buf = res.head->next;
	while (buf != res.head) {
		if (buf->deg / 10000 > 0) {
			buf->coef *= (buf->deg / 10000);
			buf->deg = buf->deg - 10000;
			buf = buf->next;
		}
		else {
			buf->coef = 0;
			buf = buf->next;
		}

	}
	return res;
}


Polynomial Polynomial::operator * (Monom m) {
	if (size == 1) {
		throw std::logic_error("Empty Polyn!");
	}
	else {
		Polynomial res = *this;
		Monom *new_monom = res.head->next;
		while (new_monom != res.head) {
			new_monom->coef *= m.coef;
			if (new_monom->deg + m.deg > 999999) {
				throw std::logic_error("Deg overflow");
				break;
			}
			else {
				new_monom->deg += m.deg;
			}
			new_monom = new_monom->next;
		}

		return res;
	}
}
Polynomial Polynomial::operator * (Polynomial m) {
	Polynomial res;
	Monom *buf = m.head->next;

	res = *this * *buf;
	buf = buf->next;
	while (buf != m.head) {
		res = res + (*this * *buf);
		buf = buf->next;
	}
	bring_similar();
	return res;
}
void Polynomial::Print_poly() {
	Monom* temp = head->next;

	while (temp != head) {
		if (temp->coef == 0.0) { cout << "Empty polynomial" << endl; }
		if (temp->coef == 1.0) { cout << ""; }
		else
			cout << temp->coef;
		if (temp->deg / 10000)
		{
			cout << "x^" << temp->deg / 10000;
		}
		if (temp->deg / 100 % 100)
		{
			cout << "y^" << temp->deg / 100 % 100;
		}
		if (temp->deg % 100)
		{
			cout << "z^" << temp->deg % 100;
		}

		if ((temp->next) && (temp->next->coef > 0) && (temp->coef != 0)) {
			printf(" + ");
		}
		temp = temp->next;
	}

}
void Polynomial::bring_similar() {
	Monom *ptr1 = this->head->next, *ptr2;
	while (ptr1 != head) {
		ptr2 = ptr1->next;
		while (ptr2 != head) {
			if (ptr1->deg == ptr2->deg) {
				if (ptr2->next != head) {
					Monom *buf = ptr2->next;
					ptr1->coef += ptr2->coef;
					this->del_monom(ptr2);
					ptr2 = buf;
				}
				else
				{
					Monom* tmp = this->head->next;
					ptr1->coef += ptr2->coef;
					while (tmp->next != ptr2) {
						tmp = tmp->next;
					}
					tail = tmp;
					tail->next = head;
					delete ptr2;
					ptr2 = head;
				}
			}
			else {
				ptr2 = ptr2->next;
			}
		}
		if (ptr1->coef == 0.0) {
			if (ptr1->next != head) {
				Monom *buf1 = ptr1->next;
				this->del_monom(ptr1);
				ptr1 = buf1;
			}
			else
			{
				Monom* tmp = this->head->next;
				while (tmp->next != ptr1) {
					tmp = tmp->next;
				}
				tail = tmp;
				tail->next = head;
				delete ptr1;
				ptr1 = head;

			}

		}
		else {
			ptr1 = ptr1->next;
		}
	}
}
bool Polynomial::operator==(const Polynomial& rhs) const {
	Monom* temp1 = this->head->next;
	Monom* temp2 = rhs.head->next;
	while (temp1 != this->head && temp2 != rhs.head) {
		if (*temp1 != *temp2) { return false; }

		temp1 = temp1->next;
		temp2 = temp2->next;

	}
	return true;
}
Polynomial::~Polynomial() {

	while (head != tail)
	{
		Monom* temp = head->next;
		delete head;
		head = temp;
		tail->next = head;
	}
	delete head; 
	size = 0;
}
ostream& operator << (ostream& os, const Polynomial& p) {
	
		Monom* temp = p.head->next;

	while (temp != p.head) {

			os << temp->coef;
		if (temp->deg / 10000)
		{
			os << "x^" << temp->deg / 10000;
		}
		if (temp->deg / 100 % 100)
		{
			os << "y^" << temp->deg / 100 % 100;
		}
		if (temp->deg % 100)
		{
			os << "z^" << temp->deg % 100;
		}

		if ((temp->next) && (temp->next->coef > 0) && (temp->coef != 0)) {
			os <<" + ";
		}
		temp = temp->next;
	}
	return os;
}