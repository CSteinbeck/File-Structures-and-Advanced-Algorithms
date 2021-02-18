
#include <iostream>
#include <memory>
#include <utility>
using namespace std;

int main()
{
	unique_ptr<int> valuePtr(new int(15)); //Shared Pointer
        valuePtr.reset(new int(25)); //.reset changes the pointer value
	unique_ptr<int> valuePtrNow(move(valuePtr)); //

        cout << "valuePtrNow = " << *valuePtrNow << endl;
        cout << "Has valuePtr an associated object? "
             << boolalpha << " "
             << (bool)(valuePtr) << endl; //Ddes a true or false on a ptr
        cout << "Has valuePtrNow an associated object? "
             << (bool)(valuePtrNow) << endl;

        return 0;
}
      
