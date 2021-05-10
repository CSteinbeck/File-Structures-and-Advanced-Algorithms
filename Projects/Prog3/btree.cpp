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
    reset(filename);
    BTNode t;
    t.child[0]= sizeof(BTNode);
    strcpy(treeFileName, filename);
    root.currSize=0;
    rootAddr=t.child[0];
    treeFile.open(filename, ios :: in | ios :: trunc | ios :: out | ios ::binary);
    treeFile.seekg(ios::beg);
    treeFile.write((char *) &t, sizeof(BTNode));
    write++;

}
void BTree :: openTree(char * filename)
{
    BTNode t;
    treeFile.open(filename, ios :: in | ios :: out | ios ::binary);
    treeFile.read((char*) &t, sizeof(BTNode));
    read++;
    rootAddr= t.child[0];
    root=getNode(rootAddr); //Updating the root
}
void BTree :: insert(keyType key)
{
    int adr= findAddr(key, root, rootAddr);
    insert( key, adr, adr, -1);
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
    return height;
}
bool BTree :: search(string key)
{
    BTNode t= getNode(rootAddr);
    return search(key,t, rootAddr);
}
keyType BTree :: retrieve(string key)
{
    return retrieve(key,root, rootAddr);
}
void BTree :: totalio() const
{
    cout<<"Number of reads: "<<read<<endl;
    cout<<"Number of writes: "<<write<<endl;
}
int BTree::countLeaves()
{
    return countLeaves(rootAddr);    
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
    //cout<<"Inorder Traversal"<<endl;
    BTNode t= getNode(rootAddr);
    for(int i=0; i<t.currSize; i++)
        {
            inorder(t.child[i]);
            cout<<t.contents[i]<<endl;
            
        }
        inorder(t.child[t.currSize]);
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

    for(int i =0; i<t.currSize;i++)
    {
        string case1 = key.getUPC();
        string case2 = t.contents[i].getUPC(); //Contents is an array of albums and pulling the UPC for the desire comparision
         
        if(case1 ==case2)
        {
            //cout<<"Identical!"<<endl;
            return tAddr;
        }
        else if(case1 < case2)
        {
            if(t.child[i]== -1) //Checks if it is a leaf node
            {
                //cout<<"Leaf Node, Address is here"<<endl;
                return tAddr;
            }
            else
            {
                //Recursively finds the next address
                //cout<<"Recursion for Find Address"<<endl;
                return findAddr(key,getNode(t.child[i]),t.child[i]);
            }
        }  
    }
    if(t.child[t.currSize]== -1) //Checks if it is a leaf node
    {
        //cout<<"Leaf Node, Address is here"<<endl;
        return tAddr;
    }
    else
    {
        //Recursively finds the next address
        //cout<<"Recursion for Find Address"<<endl;
        return findAddr(key,getNode(t.child[t.currSize]),t.child[t.currSize]);
    }
}
int BTree :: findpAddr(keyType key, BTNode t, int tAddr, int findAddr)
{
    //If the address we are looking for is the root address.
    if(findAddr == rootAddr)
    {
        return -1;
    }
    ///You are the parent
    //Key we are looking for, node we are in, address the node has, and the address we are looking for
    for(int i =0; i <=t.currSize; i++) //Looping over children, less than or equal to
    {
        if(t.child[i] == findAddr) //If the childs address is the address we are looking for
        {
            return tAddr; //We are the parent so we return that address
        }
    }
    //Use this for: search and retrieve
    //Recursively loops through the node and checks the children against the address we are looking for
    for(int i =0; i<t.currSize; i++)
    {
        if(key<t.contents[i] && t.child[i] !=-1)
        {
            return findpAddr(key, getNode(t.child[i]), t.child[i], findAddr);
        }
    }
    //goes to thr right most child for each pass
    if(t.child[t.currSize] !=1)
    {
        return findpAddr(key, getNode(t.child[t.currSize]), t.child[t.currSize], findAddr);
    }

    return -420; //Node doesn't exist or searching for the parent of the root
}
void BTree :: insert (keyType key, int recAddr, int oneAddr, int twoAddr)
{
    //Key is ALBUM
    //3 Cases for insertion: 1) first insertion, 2) Node is not full , 3) Node is full
    
    //Case 1
    if(root.currSize ==0)
    {
        //cout<<"Insert into empty Root"<<endl;
        root.contents[0]= key;
        root.currSize++;
        treeFile.seekg(rootAddr, ios :: beg); //move to the root location
        treeFile.write((char *) &root, sizeof(BTNode));
        write++;
    }

    else
    {
        BTNode t =getNode(recAddr);
        Album temp;
        //Case 2
        if(t.currSize < ORDER-1)
        {
            //Standard Insertion
           //cout<<"Standard Insertion"<<endl;
            t.contents[t.currSize] = key; //Inserts the key into a node
            t.currSize++;
            t.child[t.currSize] = twoAddr;

            // cout << "About to sort in the insert function" << endl;
            // cout << "Size = " << t.currSize << endl;
            // for(int i = 0; i < t.currSize; i++)
            //     cout << "Cont[" << i << "] = " << t.contents[i] << endl;
            // for(int i = 0; i <= t.currSize; i++)
            //     cout << "Child[" << i << "] = " << t.child[i] << endl;


            for(int i= t.currSize-1; i>0; i--)
            { //Bubble Sort
                if(t.contents[i] <t.contents[i-1])
                {
                    //cout<<"Bubble Sort"<<endl;
                    temp = t.contents[i-1];
                    t.contents[i-1] = t.contents[i];
                    t.contents[i]=temp;
                    
                    //cout<<"Interior Node Check"<<endl;
                    int tempAddr= t.child[i+1];
                    t.child[i+1] =t.child[i];
                    t.child[i]= tempAddr;
                }
            }

            // //cout << "After Sorting" << endl;
            // for(int i = 0; i < t.currSize; i++)
            //     cout << "Cont[" << i << "] = " << t.contents[i] << endl;
            // for(int i = 0; i <= t.currSize; i++)
            //     cout << "Child[" << i << "] = " << t.child[i] << endl;


            treeFile.seekg(recAddr, ios:: beg);
            treeFile.write((char*) &t, sizeof(BTNode));
            write++;

            if(recAddr == rootAddr)
            {
                root = t;
            }
        }
        else{
            //cout<<"SPLIT NODE TIME"<<endl;
            splitNode(key,recAddr, oneAddr, twoAddr);
        }
    }
    
}
BTNode BTree:: getNode (int recAddr)
{
    BTNode t;
    treeFile.seekg(recAddr, ios::beg); //Goes to the beginning of the file
    treeFile.read((char *) &t, sizeof(BTNode)); //Reads the node
    read++; //Increments the read
    return t;
}
void BTree ::  printNode(int recAddr)
{
    treeFile.seekg(recAddr, ios::beg);
    BTNode dummy;
    treeFile.read((char *) &dummy, sizeof(BTNode));
    read++;
    cout<<recAddr<<endl;
    cout << "    *** Node of Size: " <<dummy.currSize<< " ***     "<<endl;
    for (int i = 0;  i < dummy.currSize;  i++)
    {
        cout << dummy.contents[i] << endl;
    }

}

bool BTree ::isLeaf (int recAddr)
{
    BTNode t= getNode(recAddr); //Gets the node
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
    //cout<<"Print Tree Time"<<endl;
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

   BTNode newRoot, newFileHeader;
   newRoot.currSize =1;
   newRoot.contents[0]= rootElem; //Reassigned the temp root as the passed in root element
   newRoot.child[0]=oneAddr; //Assigning new children for left and right
   newRoot.child[1]= twoAddr;
   root=newRoot; //Reassigned the real root to the new one
   treeFile.seekg(0,ios::end);
   rootAddr= treeFile.tellg(); //Writes the rootAdr to the new space on file
   //cout<<"New Root Addr: "<<rootAddr<<endl;
   treeFile.write((char*) &root, sizeof(BTNode));
   write++;
   treeFile.seekg(0,ios::beg);
   newFileHeader.child[0] = rootAddr; //Updates the header of the file
   treeFile.write((char*) &newFileHeader, sizeof(BTNode)); //Rewrites the file
   write++;
}

void BTree :: splitNode (keyType& key,int recAddr,int& oneAddr,int& twoAddr)
{
    Album temp;
    keyType rootElem;
    BTNode t =getNode(recAddr);
    BTNode t2;
    BTNode t3;
    //Sorts the table

    // cout << "About to sort in the split function" << endl;
    // cout << "Size = " << t.currSize << endl;
    // for(int i = 0; i < t.currSize; i++)
    //     cout << "Cont[" << i << "] = " << t.contents[i] << endl;
    // cout << "Key = " << key << endl;
    // for(int i = 0; i <= t.currSize; i++)
    //     cout << "Child[" << i << "] = " << t.child[i] << endl;
    // cout << "Right = " << twoAddr << endl;

    if(key < t.contents[3])
    {
        //Swaps key with element
        temp = t.contents[t.currSize-1];
        t.contents[t.currSize-1] = key;
        key=temp;


        int tempAddr= twoAddr;
        twoAddr =t.child[t.currSize];
        t.child[t.currSize]= tempAddr;
        //Key is at the end is the largest of 5 and is sorted
        for(int i= t.currSize-1; i>0; i--)
        { //Bubble Sort
            if(t.contents[i] <t.contents[i-1])
            {
                //cout<<"Bubble Sort (Split Node)"<<endl;
                temp = t.contents[i-1];
                t.contents[i-1] = t.contents[i];
                t.contents[i]=temp;

                    //cout<<"Interior Node Split Check"<<endl;
                    int tempAddr= t.child[i+1];
                    t.child[i+1] =t.child[i];
                    t.child[i]= tempAddr;
            }
        }
    }

    // cout << endl << "After sorting" << endl;
    // for(int i = 0; i < t.currSize; i++)
    //     cout << "Cont[" << i << "] = " << t.contents[i] << endl;
    // cout << "Key = " << key << endl;
    // for(int i = 0; i <= t.currSize; i++)
    //     cout << "Child[" << i << "] = " << t.child[i] << endl;
    // cout << "Right = " << twoAddr << endl;


    rootElem= t.contents[ORDER/2]; //Chooses the element at the third value for the new root
    t.currSize =2; //Resets the current size to two
    t2.currSize = 2;
    t2.contents[0] =t.contents[3];
    t2.contents[1] = key;
    t2.child[0] = t.child[3];
    t2.child[1] = t.child[4]; 
    t2.child[2] = twoAddr;//Right most address is passed in
    t2.child[3] = -1;
    t2.child[4] = -1;
    treeFile.seekg(recAddr, ios::beg); //Finds the recAddr and updates it
    treeFile.write((char*) &t, sizeof(BTNode));

    treeFile.seekg(0, ios ::end);
    int newAddr =treeFile.tellg(); //saves the node from RAM 
    treeFile.write((char*) &t2, sizeof(BTNode));//Writes the new node to disk

    // cout << "In split comparing recAddr to rootAddr" << endl;
    // cout << "recAddr:  " << recAddr << endl;
    // cout << "rootAddr: " << rootAddr << endl;
    if(recAddr == rootAddr)
    {
        //cout<<"Adjusting Root"<<endl;
        adjRoot(rootElem,recAddr,newAddr);
    }
    else{
        //RecAdder is left child and newaddr is right child//
        //cout << "About to insert into parent node" << endl;
        insert(rootElem, findpAddr(key,root, rootAddr, recAddr), recAddr, newAddr);
    }
    
}

bool BTree :: search (string key, BTNode t, int tAddr)
{
    for(int i =0; i<t.currSize; i++)
    {
        if (key == t.contents[i].getUPC()) //If this is the album we are looking for
        {
            return true;
        }
        if(key<t.contents[i].getUPC() && t.child[i] !=-1)
        {
            return search(key, getNode(t.child[i]), t.child[i]);
        }
    }
    //goes to thr right most child for each pass
    if(t.child[t.currSize] != -1)
    {
        return search(key, getNode(t.child[t.currSize]), t.child[t.currSize]);
    }

    return false; //Defaults to the basic album constructor;
}

keyType BTree ::  retrieve (string key, BTNode t, int tAddr)
{
    for(int i =0; i<t.currSize; i++)
    {
        if (key == t.contents[i].getUPC()) //If this is the album we are looking for
        {
            return t.contents[i];
        }
        if(key<t.contents[i].getUPC() && t.child[i] !=-1)
        {
            return retrieve(key, getNode(t.child[i]), t.child[i]);
        }
    }
    //goes to thr right most child for each pass
    if(t.child[t.currSize] != -1)
    {
        return retrieve(key, getNode(t.child[t.currSize]), t.child[t.currSize]);
    }

    return keyType(); //Defaults to the basic album constructor
}