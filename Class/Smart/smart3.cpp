
#include <memory>
#include <iostream>
using namespace std;

class Entity
{
	public:
		Entity() {  cout << "Created Entity!" << endl; } //Used to show every time the constructor/deconstructor is called
		~Entity() {  cout << "Destroyed Entity!" << endl; }
                void Print() { cout << "Mardi Gras!" << endl; }
};

int main()
{

	unique_ptr<Entity> entity(new Entity());
        entity -> Print(); //-> is a reference operator and printed

        shared_ptr<Entity> sharedEntity = make_shared<Entity>();
        shared_ptr<Entity> e0 = sharedEntity; //e0 is an alias

	return 0;
}
