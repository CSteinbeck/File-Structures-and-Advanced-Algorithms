#include <iostream>
#include <cstdlib>
#define ORDER 4


using namespace std;

typedef int keyType;
typedef int IndexArray[ORDER];
typedef keyType ValueArray[ORDER-1];
struct BTNode
{
    int currSize;
    ValueArray contents;
    IndexArray child;
};

BTNode getNode (int recAddr);

int countLeaves (int recAddr)
{
    int count;

    if(recAddr == -1)
    {
        return 1;
    }
    else{}
        BTNode b1= getNode(recAddr);
        for(int i=0; i<= b1.currSize; i++) //b1.currsize is the node
        {
            if(b1.child ==0)
            {
              count++  
            }
            else{
                countLeaves(b1.contents.getNode(recAddr));
            }
        }
            return 0;
    }