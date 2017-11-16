#include <iostream>
#include <vector>
#include <functional>
#include <string>

struct EventData {
	virtual ~EventData() = default;
};

struct NameData : EventData {
    const std::string name;
    NameData(const std::string & name): name(name) {}
};

class Publisher
{
    using FunctionType = std::function<void(const EventData &)>;
    using EmptyFunctionType = std::function<void()>;
    std::vector<FunctionType> functions;
public:
    Publisher() {}

    void subscribe(const FunctionType & func) {
        functions.push_back(func);
    }

    void subscribe(const EmptyFunctionType & func) {
        subscribe([&](const EventData &){ func(); });
    }

    void notify(const EventData & data) {
        std::for_each(functions.begin(), functions.end(), 
            [&](auto & func){ func(data); });
    }
};


int main()
{
    Publisher publ;
    publ.subscribe([](){ std::cout << "Hello world" << std::endl; });
    publ.subscribe([&](const EventData & data){
        const NameData *named = dynamic_cast<const NameData*>(&data);
        if(named){
            std::cout << named->name << std::endl;
        }
        });

    NameData named("Martin Novak");
    publ.notify(named);
    return 0;
}




