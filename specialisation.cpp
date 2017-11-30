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
    std::ostream& operator() (std::ostream& out) const { out << "unknown type"; return out; }
};

template<>
struct Type<std::string>
{
    const std::string & val;
    std::ostream& operator() (std::ostream& out) const { out << "string type of value: " << val; return out; }
};

template<typename V>
struct Type<std::vector<V>>
{
    const std::vector<V> & val;
    std::ostream& operator() (std::ostream& out) const { V instance;  out << "vector type of (" << get_info(instance) << ")"; return out; }
};

template<typename T, size_t S>
struct Type<T[S]>
{
    const T (&val)[S];
    std::ostream& operator() (std::ostream& out) const { out << "c array type of size " << S << " and type (" << get_info<T>({}) << ")"; return out; }
};

template<>
struct Type<int>
{
    int val;
    std::ostream& operator() (std::ostream& out) const { out << "int type of value " << val; return out; }
};

template<>
struct Type<char>
{
    int val;
    std::ostream& operator() (std::ostream& out) const { out << "char type"; return out; }
};


// Overloaded operators
template <typename T>
std::ostream& operator<<(std::ostream& os, Type<T>&& val) {
	return val(os);
}

#define PRINTER(EXPR) cout << #EXPR << ": " << EXPR << endl

int main()
{
    PRINTER(get_info(std::vector<int>()));

    PRINTER(get_info(10));
    PRINTER(get_info(10U));
    PRINTER(get_info(10L));
    PRINTER(get_info(10.0));

    /* Problems with const char*/

    cout << "\n\nStrings:\n";
    PRINTER(get_info(std::string("Ahoj svet!")));
    const char *const_char_array = "Ahoj svet!";
    PRINTER(get_info(const_char_array));
    PRINTER(get_info("Ahoj svet"));

    char ahoj[] = "C Ahoj svet!";
    PRINTER(get_info(ahoj));
    return 0;
}