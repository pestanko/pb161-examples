#ifndef VISITOR_H
#define VISITOR_H

struct Visitor;

struct Base {
	virtual void getVisited(const Visitor &vis) const;
	virtual void reportThyself() const;
};

struct Derived_1 : public Base {
	virtual void getVisited(const Visitor &vis) const override;
	virtual void reportThyself() const override;
};

struct Derived_11 : public Derived_1 {
	void getVisited(const Visitor &vis) const override;
	void reportThyself() const override;
	void sayHello() const;
};

struct Derived_12 : public Derived_1 {
	void getVisited(const Visitor &vis) const override;
	void reportThyself() const override;
	void sayHello() const;
};

struct Visitor {
	void visitBase(const Base &obj) const;
	void visitDerived_1(const Derived_1 &obj) const;
	void visitDerived_11(const Derived_11 &obj) const;
	void visitDerived_12(const Derived_12 &obj) const;
};


#endif