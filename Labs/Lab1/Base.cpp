#include <iostream>
#include <cstdlib>

using namespace std;


class Base
{
    public:
    virtual void iam();
};
class BaseBoosted : public Base //Extends Base
{
    public:
    void iam();
    void iam2();
};

class BaseBoostedMax : public Base //Extends Base
{
    public:
        void iam();
        void iam2();
};


void Base :: iam()
{
    cout<<"base"<<endl;
}

void BaseBoosted :: iam()
{
    cout<<"BaseBoosted"<<endl;
}
void BaseBoostedMax :: iam()
{
    cout<<"BaseBoostedMax"<<endl;
}

void BaseBoosted :: iam2()
{
    Base :: iam();
}
void BaseBoostedMax :: iam2()
{
    Base :: iam();
}

int main(int argc, char *argv[])
{
    BaseBoosted One;
    BaseBoostedMax Two;
    One.iam();
    Two.iam();
    Base* Three = &One; //Pointing the values in base onw 
    Base* Four = &Two;
    Three->iam();
    Four->iam();
    
}
