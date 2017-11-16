#include <iostream>
#include <vector>
#include <functional>
#include <string>

using param_type = const std::string &;

std::string call(const std::function<std::string(param_type)> &func, param_type str)
{
    std::string result = func(str);
    std::cout << result << std::endl;
    return result;
}

std::string greet_function(param_type str) {
    return "Hello from function " + str;
}

struct GreetFunctor {
    const std::string greet;
    GreetFunctor(std::string greet): greet(std::move(greet)) {}

    std::string operator()(param_type str) { return greet + " " + str; }
};


struct Greet{
    const std::string greet;
    Greet(std::string greet): greet(std::move(greet)) {}

    std::string greet_me(param_type str) { return greet + " " + str; }
};

/* Out of scope */

// advanced version
template<typename func_t>
std::string templated_call(func_t func, param_type str)
{
    std::string result =  func(str);
    std::cout << result << std::endl;
    return result;
}


// ultra hyper advanced
template<typename func_t, typename param_t>
auto auto_call(func_t func, param_t str)
{
    auto result = func(str);
    std::cout << result << std::endl;
    return result;
}

int main()
{
    call([](param_type name){ return "Hello from lambda " + name; }, "Peter");
    call(GreetFunctor("Hello from functor human"), "Peter");
    call(greet_function, "Peter");

    
    Greet greet("Hello from method pointer");
    call(std::bind(&Greet::greet_me, &greet, std::placeholders::_1), "Peter");

    std::cout << std::endl << "Templated version:" << std::endl;
    templated_call([](param_type name){ return "Hello from lambda " + name; }, "Peter");
    templated_call(GreetFunctor("Hello from functor human"), "Peter");
    templated_call(greet_function, "Peter");

     std::cout << std::endl << "Auto version:" << std::endl;
    auto_call([](param_type name){ return "Hello from lambda " + name; }, "Peter");
    auto_call(GreetFunctor("Hello from functor human"), "Peter");
    auto_call(greet_function, "Peter");
    return 0;
}