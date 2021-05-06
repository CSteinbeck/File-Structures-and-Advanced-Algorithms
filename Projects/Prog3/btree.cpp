#include "album.h"
#include "btree.h"

using namespace std;
BTree :: BTree()
{

    height = 0; //height of the tree
    read = 0; //# of reads
    write = 0; //# of writes
}
void BTree :: writeHeader(char *filename)
{
    
}
void BTree :: insert(keyType key)
{
    insert(key);
}
void BTree :: reset (char *filename)
{
    treeFile.clear();
    treeFile.seekg(0);
}
void BTree :: close()
{
    treeFile.close();
}
void BTree :: printTree()
{
    printTree(rootAddr);
}
void BTree :: inorder()
{
    inorder(rootAddr);
}
void BTree :: reverse()
{
    reverse(rootAddr);
}

int BTree :: getHeight()
{
    getHeight();
}
bool BTree :: search(string key)
{
    BTNode t= getNode(rootAddr);
    return search(key,t, rootAddr)
}
keyType BTree :: retrieve(string key)
{
    if(search(key) != 0) //If the Key doesnt exist
    {
        BTNode t;
        for(int i =0; i<=t.currSize; i++)
        {
            //If the key mathches the key in the album tree
            if(strcmp(key.c_str(),t.contents[i].getUPC().c_str())==0)
            {
                return t.contents[i];
            }
        }
    }
}

void BTree :: totalio() const
{
    cout<<"Number of reads: "<<read<<endl;
    cout<<"Number of writes: "<<write<<endl;
}

int BTree::countLeaves()
{
    countLeaves(rootAddr);
}


//Private Methods//
void BTree::printTree(int recAddr)
{
    if (recAddr != -1)
    {
        BTNode dummy = getNode(recAddr);
        printNode(recAddr);
        for (int i = 0;  i <= dummy.currSize;  i++)
        {
            printTree(dummy.child[i]);
        }                   
    }
}


void BTree :: inorder (int rootAddr)
{
    if(rootAddr != -1)
 {
     BTNode t= getNode(rootAddr);
     inorder(t->left);
     cout<<t->rootAddr<<endl;
     inorder(t-> right);    
 }
}

void BTree :: reverse(int rootAddr)
{
    if(rootAddr != -1)
    {
        BTNode t= getNode(rootAddr);
        reverse(t.child[t.currSize]);
        for(int i = t.currSize-1; i>=0; i--)
        {
            cout<<t.contents[i]<<endl;
            reverse(t.child[i]);
        }
    }
}

int BTree :: findAddr (keyType key, BTNode t, int tAddr)
{

}
int BTree :: findpAddr(keyType key, BTNode t, int tAddr)
{

}
void BTree :: insert (keyType key, int recAddr, int oneAddr, int twoAddr)
{

}
BTNode BTree:: getNode (int recAddr)
{
    BTNode t;
    treeFile.seekg(recAddr, ios::beg);
    treeFile.read((char *) &t, sizeof(BTNode));
    read++;
    return t;
}
void BTree ::  printNode(int recAddr)
{
    treeFile.seekg(recAddr, ios::beg);
    BTNode dummy;
    treeFile.read((char *) &dummy, sizeof(BTNode));
    read++;
    cout << "    *** node of size " <<dummy.currSize<< " ***     "<<endl;
    for (int i = 0;  i < dummy.currSize;  i++)
    {
        cout << dummy.contents[i] << endl;
    }

}
void BTree :: placeNode(keyType k,int recAddr,int oneAddr,int twoAddr)
{
    BTNode t;
    treeFile.seekg(recAddr, ios ::beg); //Goes to the beginning of the file
    t.child[0]= oneAddr;
    t.child[1] =twoAddr;
    treeFile.write((char *) &t, sizeof(BTNode)); //Writes the new nodes to the treeFile
    write++; //increments write value
}

bool BTree ::isLeaf (int recAddr)
{
    BTNode t= getNode(recAddr);
    for(int i=0; i<=t.currSize;i++)
    {
        if(t.child[i] != -1)
        {
            return false;
        }
    }
    return true;
}

bool BTree :: isLeaf(BTNode t)
{
    for(int i=0; i<=t.currSize;i++)
    {
        if(t.child[i] != -1)
        {
            return false;
        }
    }
    return true;
}

int BTree :: countLeaves(int recAddr)
{
    BTNode node = getNode(recAddr);
    bool isLeaf = true;
    int sum = 0;
    for(int i = 0; i <= node.currSize; i++)
    {
        if(node.child[i] != -1)
        {
            isLeaf = false;
            sum += countLeaves(node.child[i]);
        }
    }
    return isLeaf ? 1 : sum;
}

void BTree :: adjRoot (keyType rootElem, int oneAddr, int twoAddr)
{

}

void BTree :: splitNode (keyType& key,int recAddr,int& oneAddr,int& twoAddr)
{

}

bool BTree :: search (string key, BTNode t, int tAddr)
{

}