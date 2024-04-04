#ifndef QueueClass_h
#define QueueClass_h
using namespace std;

template<typename T> class Node{
    public:
        T Data;
        Node<T> *Next;
        Node<T> *Before;
    
    Node(T _data): Data(_data),Next(nullptr),Before(nullptr){}//Constructor 
};

template<typename T> class Queue{
    private: 
        Node<T> *Front = nullptr;
        Node<T> *Rear  = nullptr;
        int NEQ = 0;//Number of elements in the queue 
    
    public:
        Queue():Front(nullptr),Rear(nullptr),NEQ(0){}//Constructor
        //ADD destructor 
    //---Getters---
    int NelementsInQ(void){return NEQ;}//Return the number of elements in the queue 
    T Peek(void);
    bool IsEmpty(void){return NEQ==0;}
    //---Methods---
    void Enqueue(const T &data);//Add a new element to the queue 
    T Dequeue(void);//Dequeue an element from the queue     
};

template<typename T> void Queue<T>::Enqueue(const T &data){//------------Enqueue
    
    if(Front==nullptr){//If is the first element in the queue 
        Front = new Node<T>(data);
        Rear  = Front;
        NEQ++;//New element in the queue 
    }else{
        Rear->Next = new Node<T>(data);//Add a new data to the rear 
        Rear = Rear->Next;//Update rear 
        NEQ++;//New element in the queue 
    }
}//-----------------------------------------------------------------------------

template<typename T> T Queue<T>::Dequeue(void){//Dequeue an element from the queue 
    
    //If the queue is empty, return 
    if(Front==nullptr){cout<<"There are no more elements in the queue |error| "<<endl; return 0;}
    
    
    Node<T>*P = Front->Next; //Save the next element  
    T data = Front->Data;//Data to dequeue 
    
    //Deallocate the front element 
    delete Front;
    NEQ--;//Decrese global count number 
    if(NEQ==0){//If the last element was dequeued, ensure to not undetermine the pointers 
        Front=nullptr;
        Rear=nullptr;
    }else{
        Front = P;//Now this is the new front element 
    }
    
    return data;
}//----------------------------------------------------------------------------- 

template<typename T> T Queue<T>::Peek(void){
    if(Front!=nullptr){//If front exist
        return Front->Data;
    }else{
        cout<<"The Front element doesnt exist| error"<<endl; 
        return 0;
    }
}

#endif