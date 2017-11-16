#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Test
{
public:
    const std::string name;
    const std::string desc;
    const float points = 0;
    const std::vector<Test> tests;
    
    Test(const string &name, const string &desc, float points, const std::vector<Test> &tests):
    name(name), desc(desc), points(points), tests(tests) {}

    void print(int indent = 0) const {
        for(int i = 0; i < indent; i++) {
            if(i < (indent - 1)) cout << "     ";
            else cout << "  |->";
        }
        cout << "[" << name << "] (" << points << ") " << desc << endl;
        for(auto & test : tests) { test.print(indent + 1); }
    }

    class Builder;
};

class Test::Builder
{
    std::string m_name;
    std::string m_desc;
    float m_points = 0;
    std::vector<Test> m_tests;
public:
    Builder(const std::string &name): m_name(name) {}
    Builder & name(const string &nm) {
        m_name = nm;
        return *this;
    }
    Builder & desc(const string &des) {
        m_desc = des;
        return *this;
    }

    Builder & points(float p) {
        m_points = p;
        return *this;
    }

    Test build() {
        return { m_name, m_desc, m_points, m_tests };
    }

    Builder & add_test(const Test & test) {
        m_tests.push_back(test);
        return *this;
    }
};

int main()
{
    Test ostro_hello = Test::Builder("hello_ostro")
        .desc("Testing hello world functionality naostro")
        .points(1)
        .build();

    Test necisto_hello = Test::Builder("hello_necisto")
        .desc("Testing hello world functionality nanecisto")
        .build();

    Test naostro = Test::Builder("naostro").add_test(ostro_hello).build();
    Test nanecisto = Test::Builder("nanecisto").add_test(necisto_hello).build();
    Test suite = Test::Builder("suite").add_test(naostro).add_test(nanecisto).build();
    
	suite.print();
    return 0;
}




