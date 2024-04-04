#ifndef AVL_Tree_H_
#define AVL_Tree_H_
using namespace std;

template<typename T> class TreeNode{//----------------------------TreeNode Class
    public:
        TreeNode<T> *Lchild;
        T Data;
        TreeNode<T> *Rchild;
        int Height;
    TreeNode(T _Data):Lchild(nullptr),Data(_Data),Rchild(nullptr),Height(1){}    
};//----------------------------------------------------------------------------

template<typename T> class AVL_T: public Queue<T>{//Inherits queue class, used in DisplayTreeByLevel 
    private:
        TreeNode<T> *Root = nullptr;//Root pointer 
        int N_Nodes = 0;//Counter - nodes in tree 
    //---------------------------Sub Routines------------------------------------------
    int NodeHeight(TreeNode<T>*P);//--------------Calculate the Height of a node------- 
    int BalanceFactor(TreeNode<T>*P);//-----------Calculate balance factor code--------
    TreeNode<T>*BFCase(TreeNode<T>*P);//----------Perform balance factor case----------
    TreeNode<T>*FindMin(TreeNode<T>*P);//---------Minimum value starting from this node  
    TreeNode<T>*LLRotation(TreeNode<T>*P);//------Perform LLRotation-------------------
    TreeNode<T>*RRotation(TreeNode<T>*P);//-------Perform RRotation-------------------- 
    TreeNode<T>*LRotation(TreeNode<T>*P);//-------Perform LRotation--------------------  
    TreeNode<T>*RLRotation(TreeNode<T>*P);//------Perform RLRotation------------------- 
    
    void DeleteAllTree(TreeNode<T>*P);//----------Delete all the tree for destructor---
    
    public:
        AVL_T():Root(nullptr),N_Nodes(0){}
        ~AVL_T(){DeleteAllTree(Root);}//Destructor, delete all the tree  
    //---Getters---
    TreeNode<T> *GetRoot(){return Root;}
    //---Methods---
    TreeNode<T> *Insert(const T &data,TreeNode<T>*P);//Insert a new element in Tree 
    TreeNode<T> *Delete(const T &key, TreeNode<T>*P);//Search and delete for an element in Tree 
    void DisplayTreeByLevel(void);//-------------------Display the Tree in level order 
    void Inorder(TreeNode<T>*P);//---------------------Display data Inorder
    void Preorder(TreeNode<T>*P);//--------------------Display data Preorder
    void Postorder(TreeNode<T>*P);//-------------------Display data Postorder
};

//--------------Display the data in Inorder Form-------------------------------- 
template<typename T> void AVL_T<T>::Inorder(TreeNode<T>*P){
    if(P!=nullptr){
        Inorder(P->Lchild);
        if(P==Root){
            cout<<"[Root:"<<P->Data<<"] ";
        }else{
            cout<<"["<<P->Data<<"] ";    
        }
        Inorder(P->Rchild);
    }
}//-----------------------------------------------------------------------------

//--------------Display the data in Preorder Form------------------------------- 
template<typename T> void AVL_T<T>::Preorder(TreeNode<T>*P){
    if(P!=nullptr){
        if(P==Root){
            cout<<"[Root:"<<P->Data<<"] ";
        }else{
            cout<<"["<<P->Data<<"] ";    
        }
        Preorder(P->Lchild);
        Preorder(P->Rchild);
    }
}//-----------------------------------------------------------------------------

//--------------Display the data in Postorder Form------------------------------ 
template<typename T> void AVL_T<T>::Postorder(TreeNode<T>*P){
        if(P!=nullptr){
        Postorder(P->Lchild);
        Postorder(P->Rchild);
        if(P==Root){
            cout<<"[Root:"<<P->Data<<"] ";
        }else{
            cout<<"["<<P->Data<<"] ";    
        }
    }
}//-----------------------------------------------------------------------------

//--------------Delete all the nodes in the AVL Tree---------------------------- 
template<typename T> void AVL_T<T>::DeleteAllTree(TreeNode<T>*P){
        if(P!=nullptr){
        DeleteAllTree(P->Lchild);
        DeleteAllTree(P->Rchild);
        delete(P);//The fisrt time you get here, you will be able to delete all the nodes lefting
        N_Nodes--;//Decrease Global counter 
    }
}//-----------------------------------------------------------------------------



//---------------Perform balance factor case if is necesary---------------------
template<typename T> TreeNode<T>*
AVL_T<T>::BFCase(TreeNode<T>*P){
    //=================Get Rotation Case if is unbalanced======================= 
    if((BalanceFactor(P)==2) && (BalanceFactor(P->Lchild)==1)){//LLRotation case 
        P = LLRotation(P);
    }else if((BalanceFactor(P)==-2) && (BalanceFactor(P->Rchild)==-1)){
        P = RRotation(P);
    }else if((BalanceFactor(P)==2) && (BalanceFactor(P->Lchild)==-1)){
        P = LRotation(P);
    }else if((BalanceFactor(P)==-2) && (BalanceFactor(P->Rchild)==1)){
        P = RLRotation(P);
    }
    
    return P;
}//----------------------------------------------------------------------------- 


template<typename T> TreeNode<T>*
AVL_T<T>::Insert(const T &data, TreeNode<T>*P){
    
    //-----------------Step 1) Insert the new node in the Tree------------------
    if(Root==nullptr){//Case 0) --------------- If is the first node in the Tree 
        Root = new TreeNode<T>(data);
        N_Nodes++;
        return Root;
    }else if(P==nullptr){//---------------------When you know where to place the node, create the new node 
        P = new TreeNode<T>(data);
        N_Nodes++;
        return P;//Return the node created whenever the case is at Right or Left 
    }else{
        if(data < P->Data){//Case 1) If the data is minor that the current node, go to left 
            P->Lchild = Insert(data,P->Lchild);//Recursive function use to insert 
        
        }else if(data > P->Data){//Case 2) If the data is greater that the current node, go to right 
            P->Rchild = Insert(data,P->Rchild);//Recursive function call to insert 
        }else{
            cout<<"\nData repeated, is not valid"<<endl;
            return nullptr;
        }
    }
    
    //---------------Step 2) Ensure that the nodes are balanced-----------------
    //----------From down to up, start to check height of each node-------------
    P->Height = NodeHeight(P);//Calculate the current Height
    
    //---------------Step 3) Check if you need to perform a balamce rotation----
    P = BFCase(P);//If the function detects that you need to perform as rotation     
    
    return P;
}

//-------------------Get the height of the node to evaluate---------------------------------------------
template <typename T> int AVL_T<T>::NodeHeight(TreeNode<T> *P){ 
    
    int LeftHight   = (P && P->Lchild)? P->Lchild->Height:0; //If the child exist assign this value
    int RightHeight = (P && P->Rchild)? P->Rchild->Height:0;//If the child exist assign this value 
    
    return (LeftHight > RightHeight)? LeftHight+1:RightHeight+1;//Return the greater value of the two
    //this will update the Height of the Node to be evaluated 
}//-----------------------------------------------------------------------------------------------------

//-------------------Determine the "code" to evaluate if we need to perform a rotation------------------
template <typename T> int AVL_T<T>::BalanceFactor(TreeNode<T> *P){
    
    int LeftHight   = (P && P->Lchild)? P->Lchild->Height:0; //If the child exist assign this value
    int RightHeight = (P && P->Rchild)? P->Rchild->Height:0;//If the child exist assign this value 
    
    return (LeftHight-RightHeight);//Return the subtraction to known what case is 
}
//-------------------------------------------------------------------------------------------------------

//---------------------------Perform LLRotation----------------------------------------------------------
template<typename T> TreeNode<T>*
AVL_T<T>::LLRotation(TreeNode<T>*P){
    TreeNode<T>*PL = P->Lchild;//Left child of P 
    TreeNode<T>*PLR = PL->Rchild;//Posible right child of PL 
    
    //0) Disconnect nodes to re connect 
    P->Lchild  = nullptr; 
    PL->Rchild = nullptr;
    
    //1) Reconnect 
    PL->Rchild = P;
    P->Lchild  = PLR; 
    
    //---Check if you have moved the root. Update if necesary------------------- 
    if(P==Root){//------If the node that  you have moved was the root, update it 
        Root = PL;
    }//------------------------------------------------------------------------- 
    
    return PL;//Return the LLRotation 
}//------------------------------------------------------------------------------------------------------ 


//---------------------------Perform RRotation-----------------------------------------------------------
template<typename T> TreeNode<T>*
AVL_T<T>::RRotation(TreeNode<T>*P){
    TreeNode<T> *PR = P->Rchild;//Right child of P 
    TreeNode<T> *PRL = PR->Lchild;//Posible Left child of PR 
    
    //0) Disconnect
    P->Rchild = nullptr;
    PR->Lchild = nullptr;
    
    //1) Reconnect
    PR->Lchild = P;
    P->Rchild = PRL;
    
    //---Check if you have moved the root. Update if necesary------------------- 
    if(P==Root){//------If the node that  you have moved was the root, update it 
        Root = PR;
    }//------------------------------------------------------------------------- 
    
    
    return PR;
}//------------------------------------------------------------------------------------------------------ 


//---------------------------Perform LRotation-----------------------------------------------------------
template<typename T> TreeNode<T>*
AVL_T<T>::LRotation(TreeNode<T>*P){
    TreeNode<T>* PL = P->Lchild;//Left child of P 
    TreeNode<T>* PLR = PL->Rchild;//Right child of PL 
    //Save posible childs of PLR
    TreeNode<T>* PLRch1 = PLR->Lchild; TreeNode<T>* PLRch2 = PLR->Rchild;
    
    //0) Disconnect
    P->Lchild = nullptr;
    PL->Rchild = nullptr;
    PLR->Lchild = nullptr; 
    PLR->Rchild = nullptr;
    
    //1) Reconnect
    PLR->Lchild = PL;
    PLR->Rchild = P; 
    PL->Rchild = PLRch1;
    P->Lchild= PLRch2;
    
    //---Check if you have moved the root. Update if necesary------------------- 
    if(P==Root){//------If the node that  you have moved was the root, update it 
        Root = PLR;
    }//-------------------------------------------------------------------------
    
    return PLR;
}//------------------------------------------------------------------------------------------------------ 


//---------------------------Perform RLRotation-----------------------------------------------------------
template<typename T> TreeNode<T>*
AVL_T<T>::RLRotation(TreeNode<T>*P){
    TreeNode<T> *PR = P->Rchild;//P Rchild
    TreeNode<T> *PRL = PR->Lchild;//PR Lchild
    //Save posible childs of PRL
    TreeNode<T> *PRLch1 = PRL->Lchild; TreeNode<T> *PRLch2 = PRL->Rchild;//Save the possible childs of PRL 
    
    //0) Disconnect
    P->Rchild =  nullptr;
    PR->Lchild = nullptr; 
    PRL->Lchild= nullptr;
    PRL->Rchild= nullptr;
    
    //1) Connect 
    PRL->Lchild = P; 
    PRL->Rchild = PR; 
    P->Rchild = PRLch1; 
    PR->Lchild = PRLch2; 
    
    //---Check if you have moved the root. Update if necesary------------------- 
    if(P==Root){//------If the node that  you have moved was the root, update it 
        Root = PRL;
    }//-------------------------------------------------------------------------
    
    return PRL;
    
}//------------------------------------------------------------------------------------------------------

//-----------------------------------------DisplayTreeByLevel--------------------------------------------
//------------7
//----------3--10
template<typename T> void 
AVL_T<T>::DisplayTreeByLevel(void){
    TreeNode<T> *P = Root;
    if(P==nullptr) return;//If there is nothing in the tree, you cant display anything, thus return 
    
    //1) Declare your queue name and the data type will be pushed and dequeued
    Queue <TreeNode<T>*> MyQueue;
    TreeNode<T>*Current = nullptr;//Current pointer to show tree nodes 
    
    //2) Displaying proccess 
    cout<<"\nDisplaying Tree by level order:"<<endl;
    MyQueue.Enqueue(P);//First node 
    MyQueue.Enqueue(nullptr);//Delimeter
    
    //3) Show the rest of the elements till reach to the end 
    while(!MyQueue.IsEmpty()){
        Current = MyQueue.Dequeue();//Retrieve the current last element in the queue 
        
        if(Current!=nullptr){//If there is an element, display it 
            cout<<Current->Data<<" | ";
            if(Current->Lchild!=nullptr){//If this node has a lchild, add to the queue 
                MyQueue.Enqueue(Current->Lchild);
            }
            if(Current->Rchild!=nullptr){//If this node has a Rchild, add to the queue 
                MyQueue.Enqueue(Current->Rchild);
            }
        }else{
            cout<<endl;//New level to display, Tree level traversal
            
            if(MyQueue.IsEmpty()){//If the queue is empty 
                break; //There is not more elements to display******************Finish displaying levels tree
            }
            
            MyQueue.Enqueue(nullptr);//Add a new level delimeter    
        }
    }
}//----------------------------------------------------------------------------- 

template <typename T> TreeNode<T>* 
AVL_T<T>::FindMin(TreeNode<T>*P){
    while(P->Lchild != NULL) P = P->Lchild;
	
	return P;
}

template<typename T> TreeNode<T>*
AVL_T<T>::Delete(const T &key,TreeNode<T>*P){
    
    //===========================0) Searching proccess========================================================================
    if(P==nullptr){//If the data was not in the tree or if there are no element in tree 
        return P;
    }
    else if(key<P->Data) P->Lchild = Delete(key,P->Lchild);//If the key to delete is minor than the actual node, go to left 
    else if(key>P->Data) P->Rchild = Delete(key,P->Rchild);//If the key to delete is greater than the actual node, go to right 
    else if(key==P->Data){//========================1) If we have found the data============================================== 
        //Determine if the node to delete is a leaf node | has one child | or is a parent node 
        
        if((P->Lchild==nullptr) && (P->Rchild==nullptr)){//---------------------0) Leaf node, has no childs
            delete(P);//Delete the actual node 
            P=nullptr;//Ensure to handling the unexpected behaviors 
            N_Nodes--;//Decrese actual number of nodes in the Tree 
            
        }
        else if((P->Rchild)&&(P->Lchild==nullptr)){//---------------------------1) One child | Right child 
            TreeNode<T> *Temp = P;//Dont loose track of the original node 
            //
            P=P->Rchild;
            //In Case you have deleted the root 
            if(Temp==Root) Root = P;
            
            delete(Temp);//Delete node 
            N_Nodes--;//Decrease actual numbers of nodes in Tree 
        }else if((P->Lchild)&&(P->Rchild==nullptr)){//--------------------------1) One child | Left child
            TreeNode<T> *Temp = P;//Dont loose track of the original node 
            //
            P=P->Lchild;
            //In Case you have deleted the root 
            if(Temp==Root) Root = P;
            
            delete(Temp);//Delete node 
            N_Nodes--;//Decrease actual numbers of nodes in Tree 
        }else{//----------------------------------------------------------------2) Parent node 
            TreeNode<T> *Temp = FindMin(P->Rchild);//Find the new node data to replace the actual data of the parent node  
            P->Data = Temp->Data;//Repace data of the parent node 
            P->Rchild = Delete(Temp->Data,P->Rchild);//Search for the Datata value that was replaced to delete and re arrenge 
        
            //No longer need Temp 
            //delete (Temp);
            //Temp = nullptr;//Avoid unexpected behaviors
        }
    }
    
    //Before you return you need to be sure that is correctly balanced the Tree
    //A deletion can cause an unbalance Tree
    //Calculate the current Height of the node before you return
    if(P!=nullptr){
        P->Height = NodeHeight(P);//1) Calculate the actual height 
        P = BFCase(P);//------------2) If the function detects that you need to perform as rotation 
    }
    
    return P;
}
#endif