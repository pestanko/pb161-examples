#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <utility>

using namespace std;

template<typename T>
struct Type;

template<typename T>
Type<std::remove_cv_t<std::remove_reference_t<T>>> get_info(const T & value) {
    return { value };
}

template<typename T>
struct Type
{
    const T & val;
    std::ostream& operator() (std::ostream& out) const { out << "T - unknown type"; return out; }
};

template<>
struct Type<std::string>
{
    const std::string & val;
    std::ostream& operator() (std::ostream& out) const { out << "T - string type of value: " << val; return out; }
};

template<typename V>
struct Type<std::vector<V>>
{
    const std::vector<V> & val;
    std::ostream& operator() (std::ostream& out) const { V instance;  out << "T - vector type of (" << get_info(instance) << ")"; return out; }
};

template<typename T, size_t S>
struct Type<T[S]>
{
    const T (&val)[S];
    std::ostream& operator() (std::ostream& out) const { out << "T - c array type of (" << get_info<T>({}) << ")"; return out; }
};

template<>
struct Type<int>
{
    int val;
    std::ostream& operator() (std::ostream& out) const { out << "T - int type of value " << val; return out; }
};

// Overloaded operators
template <typename T>
std::ostream& operator<<(std::ostream& os, Type<T>&& val) {
	return val(os);
}

int main()
{
    cout << get_info(std::vector<int>()) << endl;

    cout << get_info(10) << endl;
    cout << get_info(10U) << endl;
    cout << get_info(10L) << endl;
    cout << get_info(10.0) << endl;

    /* Problems with const char*/

    cout << "\n\nStrings:\n";
    cout << get_info(std::string("Ahoj svet!")) << endl;
    const char *hello = "Ahoj svet!";
    cout << get_info(hello) << endl;
    cout << get_info("Ahoj svet") << endl;

    char ahoj[] = "C Ahoj svet!";
    cout << get_info(ahoj) << endl;
    return 0;
}