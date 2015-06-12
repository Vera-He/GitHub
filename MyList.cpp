//Program Name : MyList
//Developer : He Qidu
//Date :  2015-06-12
//Development Environment : Dev-C++ 5.9.2


//file name: MyList.h
//defination of class MyList
#ifndef _MYLIST_H
#define _MYLIST_H 
#include <iostream>
using namespace std;

//exception class: the subscript is out of the bounds
class indexExcept{};  
//exception class: the array is empty (can not be popped)
class empty{};       

//utility class 'node' which supports the construction of linked list 
template <class T>
struct node{
    T data;
    node<T> *next;
    node(const T &x, node *n = NULL): data(x), next(n){}
    node(): next(NULL){}
    ~node(){}
};

template <class T> class MyList;
template <class T> MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2);
template <class T> MyList<T> operator + (const MyList<T> &l1, const T &item);
template <class T> ostream & operator << (ostream &os, const MyList<T> &obj);

template <class T>
class MyList{
	friend MyList<T> operator + <>(const MyList<T> &l1, const MyList<T> &l2); 
	friend MyList<T> operator + <>(const MyList<T> &l1, const T &item);
	friend ostream & operator << <>(ostream &os, const MyList<T> &obj);

private:
	node<T> *head;
	node<T> *tail; 
	int size;
	
	//utility function 'QuickSort()' used in 'sort()'
	void QuickSort(node<T> *start, node<T> *end);
	//utility function 'GetPartion()' used in 'sort()'
	node<T> *GetPartion(node<T> *start, node<T> *end);
	
public:
	
	//the constructor with no parameter
    MyList(): size(0){head = tail = new node<T>; tail->next = NULL;}
    //the constructor which creates a list repeating 'item' 'num' times
	MyList(int num, const T &item);
	//the copy constructor	
	MyList(const MyList &l);
	//the constructor which creates a list copy the first 'len' elements in array 'arr'
	MyList(const T* arr, int len);
	
	//add a element 'item' at the end of the list
	void push(const T &item);
	
	//delete the last element and return the value, and if the list is empty, the program will throw an error
	T pop() throw(empty);
	
	//insert an element 'item' at the position of 'index'
	//if the index is out of range, the program will throw an error
	void insert(int index, const T &item) throw(indexExcept);
	
	//empty the list
	void clean();
	
	//get the size of the list
	int get_size() const;
	
	//delete elements from 'start' to 'end' (including 'start' and 'end') 
	//if the index is out of range, the program will throw an error
	void erase(int start, int end) throw(indexExcept);
	
	//get the element at the position of 'index'
	//if the index is out of range, the program will throw an error
	T get_item(int index) const throw(indexExcept);
	
	//get a sublist from 'start' to 'end' (including 'start' and 'end'), and remember negatives are acceptable
	//if the index is out of range, the program will throw an error
	MyList get_item(int start, int end) const throw(indexExcept);
	
	//calculate how many times does 'item' occur in the list
	int count(const T &item) const;
	
	//remove the first 'item' occurring in the list
	void remove(const T &item);
	
	//sort the list ( 'less = true' means from the smallest to the largest)
	void sort(bool less = true);
	
	//reverse the list
	void reverse();
	
	//operator overloading function
	MyList &operator = (const MyList &l);
	MyList &operator += (const T &item);
	MyList &operator += (const MyList &l);
	T &operator [] (int index) throw(indexExcept);
	
	
	// destructor
	~MyList(){ clean(); delete head;}
	
		
};
#endif


//file name: MyList.cpp
//realization of class MyList

template <class T>
MyList<T>::MyList(int num, const T &item):size(num){
	node<T> *now;
	head = tail = new node<T>;
	for(int i = 0; i < size; ++i){
		now = new node<T>(item);
		tail->next = now;
		tail = now;
	}
	tail->next = NULL;
}


template <class T>
MyList<T>::MyList(const MyList &l):size(l.size){
	node<T> *now, *tmp = l.head;
	head = tail = new node<T>;
	for(int i = 0; i < size; ++i){
		tmp = tmp->next;
		now = new node<T>(tmp->data);
		tail->next = now;
		tail = now;
	}
	tail->next = NULL;
}

template <class T>
MyList<T>::MyList(const T* arr, int len):size(len){
	node<T> *now;
	head = tail = new node<T>;
	for(int i = 0; i < len; ++i){
		now = new node<T>(arr[i]);
		tail->next = now;
		tail = now;
	}
	tail->next = NULL;
}


template <class T>
void MyList<T>::push(const T &item){
	node<T> *q;
	q = new node<T>(item);
	tail->next = q;
	tail = q;
	tail->next = NULL;
	++size;
}


template <class T>
T MyList<T>::pop() throw(empty){
	
	if( size == 0 ) throw empty();
	
	node<T> *p = head;
	for(int i = 0; i < size-1; ++i) p = p->next;
	T tmp = tail->data;
	delete tail;
	tail = p;
	--size;
	
	return tmp;
}


template <class T>
void MyList<T>::insert(int index, const T &item) throw(indexExcept){
	
	if( index < 0 || index >= size) throw indexExcept();
	
	node<T> *p = head, *q;
	for(int i = 0; i < index; ++i) p = p->next;
	q = new node<T>(item);
	q->next = p->next;
	p->next = q;
	++size;
}


template <class T>
void MyList<T>::clean(){
	size = 0;
	node<T> *p = head->next, *q;
	while(p != NULL) { q = p->next; delete p; p = q;}
    head->next = NULL;
	tail = head; 
}


template <class T>
int MyList<T>::get_size() const { return size;}
 
 
template <class T>
void MyList<T>::erase(int start, int end) throw(indexExcept){
	
	if(start >= size || start < 0|| end >= size || end < 0 || start > end ) 
	    throw indexExcept();
	    
	node<T> *p = head, *q, *r;
	for(int i = 0; i < start; ++i) p = p->next;
	q = r = p->next;
	for(int i = start; i <= end; ++i){
		r = q->next;
		delete q;
		q = r;
	}
	p->next = q;
	size -= (end - start + 1);
}

template <class T>
T MyList<T>::get_item(int index) const throw(indexExcept) {
	
	if( index < 0 || index >= size) throw indexExcept();
	
	node<T> *p = head;
	for( int i = 0; i <= index; ++i) p = p->next;
	
	return p->data;
}

template <class T>
MyList<T> MyList<T>::get_item(int start, int end) const throw(indexExcept) {
	
	if( start >= size || start < -size || end >= size || end < -size) throw indexExcept();
	
	MyList<T> list;
	node<T> *p = head;

	start = ( start + size ) % size; //deal with the negatives
	end = ( end + size ) % size;
	if( start > end ) return list;
	
	for( int i = 0; i <= start; ++i) p = p->next;
	for(int i = start; i <= end; ++i){
		list.push(p->data);
		p = p->next;
	}
	
	return list;
}

template <class T>
int MyList<T>::count(const T &item) const {
	node<T> *p = head;
	int count = 0;
	for(int i = 0; i < size; ++i){
        p = p->next; 
		if( p->data == item) ++count; 
	}
	
	return count;
}

template <class T>
void MyList<T>::remove(const T &item){
	node<T> *p = head, *q;
	for(int i = 0; i < size; ++i){
        q = p->next; 
		if( q->data == item) {
			p->next = q->next;
			delete q;
			--size;
			break;
		} 
		p = q;
	}

}


template <class T>
MyList<T> &MyList<T>::operator = (const MyList &l){
	
	if(this == &l) return *this; // prevent the self-copy
	
    clean();
	node<T> *p = l.head;
	for( int i = 0; i < l.size; ++i){
		p = p->next;
		push(p->data);
	}

	return *this;
}


template <class T>
MyList<T> &MyList<T>::operator += (const T &item){
	push(item);	
	return *this;
}


template <class T>
MyList<T> &MyList<T>::operator += (const MyList &l){
	node<T> *p = l.head;
	for( int i = 0; i < l.size; ++i){
		p = p->next;
		push(p->data);
	}
	return *this;
}


template <class T>
T &MyList<T>::operator [] (int index) throw(indexExcept) {
	
	if( index < 0 || index >= size ) throw indexExcept();
	
	node<T> *p = head;
	for( int i = 0; i <= index; ++i) p = p->next;
	
	return p->data;
}


template <class T> 
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2){
	MyList<T> tmp(l1);
    node<T> *p = l2.head;
	for( int i = 0; i < l2.size; ++i){
		p = p->next;
		tmp.push(p->data); 
	}
	return tmp;
}


template <class T> 
MyList<T> operator + (const MyList<T> &l1, const T &item){
	MyList<T> tmp(l1);
	tmp.push(item);
}


template <class T> 
ostream & operator<<(ostream &os, const MyList<T> &obj){

	node<T> *p = obj.head;
	if( !p->next ) { cout<<"[]"; return os;}
	
	os << '[';
	for( int i = 0; i < obj.size - 1; ++i){
		p = p->next;
		os << p->data;
		os << ',';
	}
	os << p->next->data;
	os << ']';
	
	return os;
}


template <class T>
node<T> *MyList<T>::GetPartion(node<T> *start, node<T> *end){  
     int key = start->data;  

	 node<T> *p = start, *q = p->next;     
     while(q != end){  
         if(q->data < key){ 
		     p = p->next;   
             T tmp = p->data;
			 p->data = q->data;
			 q->data = tmp;  
         }  
         q = q->next;  
     }  
     start->data = p->data;
	 p->data = key;
	 
     return p;  
}  

template <class T>
void MyList<T>::QuickSort(node<T> *start, node<T> *end){  
     if(start != end){  
         node<T> *partion = GetPartion(start, end);  
         QuickSort(start, partion);  
         QuickSort(partion->next, end);  
     }  
}

template <class T>
void MyList<T>::sort(bool less){
    QuickSort( head, NULL);	
    if(less == 0) reverse();
}

template <class T>
void MyList<T>::reverse(){
	node<T> *p = head,*q,*r;
	tail = head->next;
	p = p->next;		
	while(p){			
	    r = q;	
		q = p;
		p = p->next;
		q->next = r;		
	}	
    head = new node<T>;
    head->next = q;
    tail->next = NULL;
}

int main(){
	try{ 
       	MyList<int> a, b;
	    int i;
	    for (i=0; i<5; ++i)
		    a.push(i);
        // a = [0, 1, 2, 3, 4]
	    a[3] = 15; // a = [0, 1, 2, 15, 4]
	    a.sort(); // a = [0, 1, 2, 4, 15]
	    a.reverse(); // a = [15, 4, 2, 1, 0]
	    a += 12; // a = [15, 4, 2, 1, 0, 12]
	    for (i=0; i<a.get_size(); ++i)
		    cout<<a[i]<<endl;
        b = a.get_item(4, -3); // b = [] *Èôstart > end£¬·µ»Ø¿ÕÊý×é
	    b = a.get_item(3, -1); // b = [1, 0, 12] 
	    a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	    for (i=0; i<a.get_size(); ++i)
		    cout<<a.get_item(i)<<endl;
	    cout<<a.count(5)<<endl;
	    b.clean(); // b = []
	    cout<<b.get_size()<<endl;
	    a.erase(2, 5); // a = [15, 4, 0, 12]
	    b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	    b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	    b.remove(4); // b = [15, 0, 116, ...]
	    cout<<b<<endl;
	    MyList<double> c(10, 3.14);
	    for (i=0; i<100; ++i)
		    c.push(1.1*i);
	    cout<<c.get_item(100, 105)<<endl;
	}
	catch(indexExcept){
		cerr<<"Error: List Index Out Of Range!"<<endl;
	}
	catch(empty){
		cerr<<"Error: Empty List!"<<endl;
	}
	
	return 0;
}



