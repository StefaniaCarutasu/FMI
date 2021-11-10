#include "bst.h"
#include "node.h"

#include <iostream>

using namespace std;

int main()
{
    BST A(4);
    A.insertUnique(5);

    cout << A.search(6);

    return 0;
}