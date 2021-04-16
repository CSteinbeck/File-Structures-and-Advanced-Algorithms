Project 3 README
Colton Steinbeck

B Tree Creation and Updating:
This general algorithm goes over how the btree is created and updated.

Creation: 
The BTree is created based on the BTree Nodes and will be inserted. The insert will be done based on the key that the user implements when Btree.insert() method is called. That specific key is the UPC, which can allow for a unique identifer for album and file. Each key will be loaded into a btree ValueArray (top level). It will fill up until a split is required. The split will send the middle UPC, based on the comparisions. It will be sent into a second IndexArray and split it accordingly. It will increases the height (getHeight() method) until based on the split and do a preorder traversal to make sure it is in the correct order. 

Updating:
To update the btree, we need to utilize the search, retrieveKey, and preorder to update the tree. We can search for a specific UPC based on the boolean search method. If true, the retrieveKey method can be used and pull that specific key info. If not, a new key can be inserted and the tree be updated through the preorder travsersal, updating the number of splits and the height. 


