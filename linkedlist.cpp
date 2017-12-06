#include <iostream>
#include <memory>
#include <type_traits>

#if 0
struct NodeCopy { // na demonstraciu static_assert
	std::unique_ptr<NodeCopy> _next;
	NodeCopy *_previous = nullptr;
	int _value = 0;
	~NodeCopy() {
		std::cout << "destructor of NodeCopy has been called" << std::endl;
	}
	NodeCopy() {
		std::cout << "NodeCopy has been created " << std::endl;
	}
	NodeCopy(int val) : _value(val) {
		std::cout << "NodeCopy has been created with a value of " << val << std::endl;
	}
};
#endif

struct Node {
	std::unique_ptr<Node> _next;
	// std::unique_ptr<Node> _previous; // <--- preco nemoze byt unique?
	Node *_previous = nullptr;
	int _value = 0;
	~Node() {
		std::cout << "destructor of Node has been called" << std::endl;
	}
	Node() {
		std::cout << "Node has been created " << std::endl;
	}
	Node(int val) : _value(val) {
		std::cout << "Node has been created with a value of " << val << std::endl;
	}
};

class LinkedList {
	std::unique_ptr<Node> _first;
	Node *_last = nullptr;

	template<typename T>
	static T &get_univ(int index, T &first) {
		static_assert(std::is_base_of<Node, T>::value, "attempting to use an invalid node type");
		T *current = &first;
		for (int i = 0; i < index; ++i) {
			current = current->_next.get();
		}
		return *current;
		// IMPORTANT: requesting an index out of the list's range is undefined behavior (segfault)
	}
public:

	bool empty() const {
		return !_last;
	}

	void append(int val = 0) {
		if (empty()) {
			_first = std::make_unique<Node>(val);
			_last = _first.get();
			return;
		}
		_last->_next = std::make_unique<Node>(val);
		_last->_next->_previous = _last;
		_last = _last->_next.get();
	}

	void print() const {
		Node *current = _first.get();
		while (current) {
			std::cout << current->_value << std::endl;
			current = current->_next.get();
		}
	}

	Node &get_node_at(int index) {
		return get_univ<Node>(index, *_first);
	}

	const Node &get_node_at(int index) const {
		return get_univ<const Node>(index, *_first);
	}

	int get_value_at(int index) const {
		return get_node_at(index)._value;
	}
};

int main(void) {
	#if 1
	auto n = std::make_unique<Node>();
	n->_next = std::make_unique<Node>();
	n->_next->_next = std::make_unique<Node>();
	n->_next->_next->_next = std::make_unique<Node>();
	// previous pointre nas teraz nezaujimaju

	std::cout << "=== nodes have been linked\n";

	// mame zretazenie 4 Nodov

	n.reset(); //co sa stane ked zakomentujem?
	#endif
	#if 0
	LinkedList ll;
	for (int i = 0; i < 5; ++i) {
		ll.append(i * 2);
	}
	std::cout << ll.get_node_at(1)._value << ", " << ll.get_node_at(3)._value << std::endl;
	std::cout << ll.get_value_at(1) << ", " << ll.get_value_at(3) << std::endl;
	// ^^co sa stane, ked prepisem niektory index na 5?
	// ll.print();
	#endif

	std::cout << "=== end of main()\n";
}