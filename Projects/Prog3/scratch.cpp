    
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