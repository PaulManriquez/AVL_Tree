//Programmer: Paul Manriquez
//Date: March 2024

#include <iostream>
#include "QueueClass.h"
#include "AVL_Tree.h"

using namespace std;

/*This is an implementation of the data structure AVL_Tree
This programm touch very important subjects like:
*Recursion          *Inheritence
*Dynamic Memory     *Faster data retrieve analisys 
I tried to write this programm the most readible possible
Digital notes will be also added to undestand the Rotation
and the deletion of the nodes.
Enjoy it.
*/


int main(){
    
    AVL_T<int> MyTreeAVL;
    
    MyTreeAVL.Insert(12,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(5,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(15,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(3,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(7,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(13,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(17,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(14,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(16,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(1,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(9,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(20,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(8,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(11,MyTreeAVL.GetRoot() );
    MyTreeAVL.Insert(18,MyTreeAVL.GetRoot() );
    
    cout<<"Displaying Inorder:"<<endl;
    MyTreeAVL.Inorder(MyTreeAVL.GetRoot());//Display Inorder
    cout<<"\nDisplaying Preorder:"<<endl;
    MyTreeAVL.Preorder(MyTreeAVL.GetRoot());//Display Preorder
    cout<<"\nDisplaying Postorder:"<<endl;
    MyTreeAVL.Postorder(MyTreeAVL.GetRoot());//Display Postorder
    cout<<endl;
    
    MyTreeAVL.DisplayTreeByLevel();
    
    MyTreeAVL.Delete(18,MyTreeAVL.GetRoot());//Delete Leaf node 
    MyTreeAVL.DisplayTreeByLevel();
    
    MyTreeAVL.Delete(3,MyTreeAVL.GetRoot());//Delete one child node case 
    MyTreeAVL.DisplayTreeByLevel();
    
    MyTreeAVL.Delete(12,MyTreeAVL.GetRoot());//Delete parent node case 
    MyTreeAVL.DisplayTreeByLevel();
    
    return 0;
}






