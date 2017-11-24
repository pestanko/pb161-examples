#include <string>
#include <iostream>

/* https://godbolt.org/g/36gwsL  */

using namespace std;

struct Person
{
    std::string name;
    template<typename S, 
    typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>>
    Person(S && nm): name(std::forward<S>(nm)) {}

    Person(const Person &person): name(person.name) {}
};


int main()
{
   auto p = Person("Peter");
   Person p2(p);
}
