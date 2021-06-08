#include "doctest.h"
#include "BinaryTree.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace ariel;
using namespace std;

TEST_CASE("check tree build ints and preorder,inorder,postorder") // regular balanced int tree -------------------------
{
    BinaryTree<int> btree;

    CHECK_NOTHROW(btree.add_root(1)); // tree build
    CHECK_NOTHROW(btree.add_left(1, 2));
    CHECK_NOTHROW(btree.add_right(1, 3));
    CHECK_NOTHROW(btree.add_left(2, 4));
    CHECK_NOTHROW(btree.add_right(2, 5));
    CHECK_NOTHROW(btree.add_left(3, 6));
    CHECK_NOTHROW(btree.add_right(3, 7));

    /*
             1
            / \
           2   3
          / \ / \
         4  5 6  7
    */

    string intTree;

    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it) //check preorder  P L R
    {
        intTree += *it + ' ';
    }
    CHECK_EQ(intTree, "1 2 4 5 3 6 7");

    intTree = " ";

    for (auto it = btree.begin_inorder(); it != btree.end_inorder(); ++it) //check inorder L P R
    {
        intTree += *it + ' ';
    }
    CHECK_EQ(intTree, "4 2 5 1 6 3 7");
    intTree = " ";
    for (auto it = btree.begin_postorder(); it != btree.end_postorder(); ++it) //check postorder L R P
    {
        intTree += *it + ' ';
    }
    CHECK_EQ(intTree, "4 5 2 6 7 3 1");
    intTree = " ";

    // check if numbers changed in input
    CHECK_NOTHROW(btree.add_root(12));   // change root shouldnt throw
    CHECK_NOTHROW(btree.add_left(2, 8)); // change leafs
    CHECK_NOTHROW(btree.add_left(3, 9));
    CHECK_NOTHROW(btree.add_right(2, 10));
    CHECK_NOTHROW(btree.add_right(3, 11));
    CHECK_NOTHROW(btree.add_right(12, 20)); // change parent
    /*
             12
            /  \
           2    20
          / \  / \
         8  10 9  11
    */
    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it)
    { //check preorder  P L R
        intTree += *it + ' ';
    }
    CHECK_EQ(intTree, "12 2 8 10 20 9 11");

    intTree = " ";

    // THROW CHECK ----------------------------------------------------------

    CHECK_NOTHROW(btree.add_root(12));     // replaces 12 with 12 or just does nothing
    CHECK_THROWS(btree.add_left(8, 12));   // 12 already exists so dont add and throw
    CHECK_THROWS(btree.add_right(14, 15)); // 14 doesnt exist
    CHECK_THROWS(btree.add_left(14, 15));  // 14 doesnt exist

    // check unblanaced tree ------------------------------------------------------
    CHECK_NOTHROW(btree.add_right(8, 13));
    CHECK_NOTHROW(btree.add_left(13, 14));
    /*
             12
            /  \
           2    20
          / \   / \
         8  10  9  11
          \
          13
          /
        14
    */

    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it) //check preorder  P L R
    {
        intTree += *it + ' ';
    }
    CHECK_EQ(intTree, "12 2 8 14 13 20 9 11");

    intTree = " ";

    for (auto it = btree.begin_inorder(); it != btree.end_inorder(); ++it) //check inorder L P R
    {
        intTree += *it + ' ';
    }
    CHECK_EQ(intTree, "8 14 13 2 10 12 9 20 11");
    intTree = " ";
    for (auto it = btree.begin_postorder(); it != btree.end_postorder(); ++it) //check postorder L R P
    {
        intTree += *it + ' ';
    }
    CHECK_EQ(intTree, "14 13 8 10 2 9 11 20 12");
    intTree = " ";
}

TEST_CASE("check tree build double and preorder,inorder,postorder") // regular balanced double tree -------------------------------
{
    BinaryTree<double> btree;

    CHECK_NOTHROW(btree.add_root(0.1)); // build tree
    CHECK_NOTHROW(btree.add_left(0.1, 0.2));
    CHECK_NOTHROW(btree.add_right(0.1, 0.3));
    CHECK_NOTHROW(btree.add_left(0.2, 0.4));
    CHECK_NOTHROW(btree.add_right(0.2, 0.5));
    CHECK_NOTHROW(btree.add_left(0.3, 0.6));
    CHECK_NOTHROW(btree.add_right(0.3, 0.7));

    /*
             0.1
            /   \
          0.2    0.3
          / \    / \
       0.4 0.5  0.6  0.7
    */

    string doubleTree;

    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it) //check preorder  P L R
    {
        doubleTree += *it + ' ';
    }
    CHECK_EQ(doubleTree, "0.1 0.2 0.4 0.5 0.3 0.6 0.7");

    doubleTree = " ";

    for (auto it = btree.begin_inorder(); it != btree.end_inorder(); ++it) //check inorder L P R
    {
        doubleTree += *it + ' ';
    }
    CHECK_EQ(doubleTree, "0.4 0.2 0.5 0.1 0.6 0.3 0.7");
    doubleTree = " ";
    for (auto it = btree.begin_postorder(); it != btree.end_postorder(); ++it) //check postorder L R P
    {
        doubleTree += *it + ' ';
    }
    CHECK_EQ(doubleTree, "0.4 0.5 0.2 0.6 0.7 0.3 0.1");
    doubleTree = " ";

    // check if numbers changed in input
    CHECK_NOTHROW(btree.add_root(0.12));     // change root shouldnt throw
    CHECK_NOTHROW(btree.add_left(0.2, 0.8)); // change leafs
    CHECK_NOTHROW(btree.add_left(0.3, 0.9));
    CHECK_NOTHROW(btree.add_right(0.2, 0.10));
    CHECK_NOTHROW(btree.add_right(0.3, 0.11));
    CHECK_NOTHROW(btree.add_right(0.12, 0.21)); // change parent
    CHECK_NOTHROW(btree.add_right(0.8, 0.22));  // add unblanaced tree
    CHECK_NOTHROW(btree.add_left(0.22, 0.23));
    /*
             0.12
            /     \
           0.2      0.21
           / \       / \
         0.8  0.10  0.9  0.11
          \
          0.22
          /
        0.23
    */
    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it)
    { //check preorder  P L R
        doubleTree += *it + ' ';
    }
    CHECK_EQ(doubleTree, "0.12 0.2 0.8 0.23 0.22 0.10 0.21 0.9 0.11");

    doubleTree = " ";

    // THROW CHECK ----------------------------------------------------------

    CHECK_NOTHROW(btree.add_root(0.12));       //replaces 0.12 with 0.12
    CHECK_THROWS(btree.add_left(0.8, 0.12));   // 0.12 already exists so dont add and throw
    CHECK_THROWS(btree.add_right(0.14, 0.15)); // 0.14 doesnt exist
    CHECK_THROWS(btree.add_left(0.14, 0.15));  // 0.14 doesnt exist
}

TEST_CASE("check tree build chars and preorder,inorder,postorder") // regular balanced char tree --------------------------
{
    BinaryTree<char> btree;

    CHECK_NOTHROW(btree.add_root('a'));
    CHECK_NOTHROW(btree.add_left('a', 'b'));
    CHECK_NOTHROW(btree.add_right('a', 'c'));
    CHECK_NOTHROW(btree.add_left('b', 'd'));
    CHECK_NOTHROW(btree.add_right('b', 'e'));
    CHECK_NOTHROW(btree.add_left('c', 'f'));
    CHECK_NOTHROW(btree.add_right('c', 'g'));

    /*
             a
            / \
           b   c
          / \ / \
         d  e f  g
    */

    string charTree;

    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it) //check preorder  P L R
    {
        charTree += *it + ' ';
    }
    CHECK_EQ(charTree, "a b d e c f g");

    charTree = " ";

    for (auto it = btree.begin_inorder(); it != btree.end_inorder(); ++it) //check inorder L P R
    {
        charTree += *it + ' ';
    }
    CHECK_EQ(charTree, "d b e a f c g");
    charTree = " ";
    for (auto it = btree.begin_postorder(); it != btree.end_postorder(); ++it) //check postorder L R P
    {
        charTree += *it + ' ';
    }
    CHECK_EQ(charTree, "d e b f g c a");
    charTree = " ";

    // check if numbers changed in input
    CHECK_NOTHROW(btree.add_root('h'));      // change root shouldnt throw
    CHECK_NOTHROW(btree.add_left('b', 'i')); // change leafs
    CHECK_NOTHROW(btree.add_left('c', 'j'));
    CHECK_NOTHROW(btree.add_right('b', 'k'));
    CHECK_NOTHROW(btree.add_right('c', 'l'));
    CHECK_NOTHROW(btree.add_right('h', 'z')); // change parent
    CHECK_NOTHROW(btree.add_right('i', 'q')); // add unblanaced tree
    CHECK_NOTHROW(btree.add_left('q', 'r'));
    /*
             h
            / \
           b   z
          / \ / \
         i  j k  l
          \
           q
          /
          r
    */
    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it)
    { //check preorder  P L R
        charTree += *it + ' ';
    }
    CHECK_EQ(charTree, "h b i r q j z k l");

    charTree = " ";

    // THROW CHECK ----------------------------------------------------------

    CHECK_NOTHROW(btree.add_root('h'));      // change root to h from h
    CHECK_NOTHROW(btree.add_left('i', 'h')); //  h already exists so dont add and throw
    CHECK_THROWS(btree.add_right('m', 'o')); // m doesnt exist
    CHECK_THROWS(btree.add_left('m', 'o'));  // m doesnt exist
}

TEST_CASE("check tree build strings and preorder,inorder,postorder") // unbalanced string tree --------------------------------
{
    BinaryTree<string> btree;

    CHECK_NOTHROW(btree.add_root("P"));
    CHECK_NOTHROW(btree.add_left("P", "L"));
    CHECK_NOTHROW(btree.add_right("P", "R"));
    CHECK_NOTHROW(btree.add_left("L", "LL"));
    CHECK_NOTHROW(btree.add_right("L", "LR"));
    CHECK_NOTHROW(btree.add_left("R", "RL"));
    CHECK_NOTHROW(btree.add_right("R", "RR"));
    CHECK_NOTHROW(btree.add_left("LL", "LLL"));
    CHECK_NOTHROW(btree.add_left("LLL", "LLLL"));

    /*
             P
            / \
           L   R
          / \ / \
       LL  LR RL  RR
       /
      LLL
      / 
     LLLL

    */

    string stringTree;

    for (auto it = btree.begin_preorder(); it != btree.end_preorder(); ++it) //check preorder  P L R
    {
        stringTree += *it + " ";
    }
    CHECK_EQ(stringTree, "P L LL LLL LLLL LR R RL RR");

    stringTree = " ";

    for (auto it = btree.begin_inorder(); it != btree.end_inorder(); ++it) //check inorder L P R
    {
        stringTree += *it + " ";
    }
    CHECK_EQ(stringTree, "LLLL LLL LL L LR P RL R RR");
    stringTree = " ";
    for (auto it = btree.begin_postorder(); it != btree.end_postorder(); ++it) //check postorder L R P
    {
        stringTree += *it + " ";
    }
    CHECK_EQ(stringTree, "LLLL LLL LL LR L P RL RR R P");
    stringTree = " ";

    // THROW CHECK ------------------------------------------------------------------------------------

    CHECK_NOTHROW(btree.add_root("P"));         // change root from P to P
    CHECK_NOTHROW(btree.add_root("PP"));        // change root to PP shouldnt throw
    CHECK_THROWS(btree.add_left("LLLL", "PP")); //  PP already exists so dont add and throw
    CHECK_THROWS(btree.add_right("RRR", "L"));  // RRR doesnt exist
    CHECK_THROWS(btree.add_left("RRR", "L"));   // RRR doesnt exist
    CHECK_NOTHROW(btree.add_left("PP", "L*"));  // change parent

    /*
             PP
            / \
           L*   R
          / \ / \
       LL  LR RL  RR
       /
      LLL
      / 
     LLLL
     

    */
}