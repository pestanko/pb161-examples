#include <iostream>
#include "visitor.h"

void Base::getVisited(const Visitor &vis) const {
	vis.visitBase(*this);
}

void Base::reportThyself() const {
	std::cout << "Base class reporting\n";
}

void Derived_1::getVisited(const Visitor &vis) const {
	vis.visitDerived_1(*this);
}

void Derived_1::reportThyself() const {
	std::cout << "Derived_1 reporting\n";
}

void Derived_11::getVisited(const Visitor &vis) const {
	vis.visitDerived_11(*this);
}

void Derived_11::reportThyself() const {
	std::cout << "Derived_11 reporting\n";
}

void Derived_11::sayHello() const {
	std::cout << "Derived_11 says hello\n";
}

void Derived_12::getVisited(const Visitor &vis) const {
	vis.visitDerived_12(*this);
}

void Derived_12::reportThyself() const {
	std::cout << "Derived_12 reporting\n";
}

void Derived_12::sayHello() const {
	std::cout << "Derived_12 says hello\n";
}

void Visitor::visitBase(const Base &obj) const {
	obj.reportThyself();
}

void Visitor::visitDerived_1(const Derived_1 &obj) const {
	obj.reportThyself();
}

void Visitor::visitDerived_11(const Derived_11 &obj) const {
	obj.reportThyself();
	obj.sayHello();
}

void Visitor::visitDerived_12(const Derived_12 &obj) const {
	obj.reportThyself();
	obj.sayHello();
}

int main(void) {
	Base b;
	Derived_1 d1;
	Derived_11 d11;
	Derived_12 d12;
	Visitor vis;

	b.getVisited(vis);
	d1.getVisited(vis);
	d11.getVisited(vis);
	d12.getVisited(vis);

	std::cout << "\n==========\n\n";

	Base &ref = d12;

	ref.getVisited(vis);
}
