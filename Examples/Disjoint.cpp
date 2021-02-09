class DisjSets {
  public :
     DisjSets (int numelements);
     ~DisjSets();
     int find (int x);
     void unionSets (int root1, int root2);
  protected :
     int *a;
     int n;
};

DisjSets::DisjSets(int numelements)
{
  int i;

  n = numelements;
  a = new int[n];
  for (i = 0;  i < n;  i++)
       a[i] = -1;
}

DisjSets::~DisjSets()
{
  delete d;
}

void DisjSets::unionSets(int root1, int root2)
{
  a[root1] = root2;
}

int DisjSets::find(int x) //Version 1, uses recursion (Recursive Linear Search)
{
  if (a[x] < 0) //If negative, retunr what set belong to
     return x;
  else
     return find(a[x]);
}

int DisjSets::find(int x) //Version 2, Alternative and modifies array//
{
  if (a[x] == -1)
      return x;

  a[x] = find(a[x]);  //setting self-adjustment where the set being searched is now directly attached to the root//
                      //This process is called Path Compression: Goal is to improve future search times//
  return x;
}

