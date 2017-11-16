#include <iostream>
#include <string>
#include <vector>
#include <cassert>

class Person {
    /* All methods here can be const, but constructor cannot */
public:
    // Immutable
    const std::string name;
    const std::string email;

    Person(const std::string &name, const std::string &email):
        name(name), email(email) {} // initialization

    void print() const {
        std::cout << name << " <" << email << '>' << std::endl;
    }
};


class PersonCollection {
public:
    using col_type = Person;
private:
    std::vector<col_type> collection;

public:
    // Why const not here?
    void add(const col_type & person) { 
        collection.push_back(person); 
    }

    // Why const here?
    const col_type & find(const std::string &email) const {
        for(auto &person: collection) {
            if(person.email == email)
                return person;
        }
        assert(false);
    }

    // Why const return type and also const method?
    const std::vector<col_type> getCollection() const {
        return collection;
    }
};


int main(){
    PersonCollection col;
    col.add(Person("Peter", "peter@example.com"));
    col.add(Person("Jano", "jano@example.com"));
    col.add(Person("Jozef", "jozef@example.com"));

    // Difference ?
    const Person &person = col.find("peter@example.com");
    Person person2 = col.find("jano@example.com");

    person.print();
    person2.print();
    
    return 0;
}

