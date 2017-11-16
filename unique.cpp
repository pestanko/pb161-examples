#include <iostream>
#include <string>
#include <memory>
#include <vector>


using namespace std;

struct Object
{
		std::unique_ptr<std::string> name;
		Object(const std::string & name_): name(std::make_unique<std::string>(name_)) { };
};

class Collection
{
		std::vector<Object> m_objects;
public:	
		void add_object(const std::string &name)
		{
				m_objects.emplace_back(name);
		}

		const Object & get_object(size_t index)
		{
				return m_objects[index];
		}
		
};

class CollectionSafe
{
		std::vector<std::unique_ptr<Object> > m_objects;
public:
		void add_object(const std::string &name)
		{
				m_objects.emplace_back(std::make_unique<Object>(name));
		}

		const Object & get_object(size_t index)
		{
				return *m_objects[index];
		}

};


int main()
{
		//using UsedCol = Collection;
		using UsedCol = CollectionSafe;
		UsedCol col;
		col.add_object("first");
		const Object & obj = col.get_object(0);
		cout << *(obj.name) << endl;

		for(int i = 0; i < 1000; i++)
		{
				col.add_object("next ");
		}

		cout << *(obj.name) << endl;

		return 0;
}



