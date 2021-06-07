#include <iostream>
using namespace std;

//_______________________________NESTED CONST_ITERATOR CLASS________________________


// Default zero-parameter constructor set pointer to NULL
template <typename T>
List<T>::const_iterator:: const_iterator():current{nullptr}
{

}


// Returns reference to the corresponding element in list
template <typename T>
const T& List<T>::const_iterator:: operator*() const
{
  return retrieve();
}


// Prefix and Postfix increment operators
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator:: operator++()
{
  current=current->next;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>:: const_iterator::operator++(int)
{
  List<T>::const_iterator old=*this;
  ++(*this);
  return old;
}


// Prefix and Postfix decrement operators
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator:: operator--()
{
  current=current->prev;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator:: operator--(int)
{
  List<T>::const_iterator old=*this;
  --(*this);
  return old;
}


// Two iterators are equal if referring to same element
template <typename T>
bool List<T>::const_iterator:: operator==(const List<T>::const_iterator & rhs)const
{
  return current==rhs.current;
}


// Two iterators are not equal if not referring to same element
template <typename T>
bool List<T>::const_iterator:: operator!=(const List<T>::const_iterator & rhs)const
{
  return !(*this==rhs);
}


// Return a reference to corresponding element in the list
template <typename T>
T & List<T>::const_iterator:: retrieve()const
{
  return current->data;
}


template <typename T>
List<T>::const_iterator:: const_iterator(Node *p):current{p}
{

}



//___________________________________NESTED ITERATOR CLASS____________________________


// Default zero parameter constructor
template <typename T>
List<T>::iterator:: iterator()
{
}



// Returns a reference to corresponding element in list
template <typename T>
T & List<T>::iterator:: operator*()
{
  return List<T>::const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator:: operator*() const
{
  return List<T>::const_iterator::operator*();
}



// Prefix and postfix increment
template <typename T>
typename List<T>::iterator& List<T>::iterator:: operator++()
{
  this->current=this->current->next;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator:: operator++(int)
{
  List<T>::iterator old=*this;
  ++(*this);
  return old;
}

// Prefix and postfix decrement
template <typename T>
typename List<T>::iterator& List<T>::iterator:: operator--()
{
  this->current=this->current->prev;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator:: operator--(int)
{
  List<T>::iterator old=*this;
  --(*this);
  return old;
}

template <typename T>
List<T>::iterator::iterator(Node *p):List<T>::const_iterator{p}
{

}


//_________________________________LIST CLASS_________________________________________



// Default zero parameter constructor calls init
template <typename T>
List<T>::List()
{
  init();
}


// Copy constructor creates new list using elements from list rhs
template<typename T>
List<T>::List(const List &rhs)
{
  init();
  for(auto & x:rhs)
    push_back(x);
}


// Move constructor 
template <typename T>
List<T>::List(List && rhs): theSize{rhs.theSize},head{rhs.head},tail{rhs.tail}
{
  rhs.theSize=0;
  rhs.head=nullptr;
  rhs.tail=nullptr;
}


// Constructs a list with num elements all initialized with value val
template <typename T>
List<T>::List(int num, const T & val)
{
  init();
  int count;
  for(count=0;count!=num;++count)
    push_front(val);
}


// Construct a list with elements from another list between start and end [start, end)
template <typename T>
List<T>::List(const_iterator start, const_iterator end)
{
  init();
  for(const_iterator itr=start;itr!=end;++itr)
    push_back(*itr);
}


// Destructor 
template <typename T>
List<T>::~List()
{
  clear();
  delete head;
  delete tail;
}


// Copy assignment operator
template <typename T>
const typename List<T>::List& List<T>::operator=(const List &rhs)
{
  List copy=rhs;
  std::swap(*this,copy);
  return *this;
}


// Move assignment operator
template <typename T>
typename List<T>::List& List<T>::operator=(List && rhs)
{
  std::swap(theSize, rhs.theSize);
  std::swap(head, rhs.head);
  std::swap(tail, rhs.tail);

  return *this;
}


// Initiates the list 
template <typename T>
void List<T>::init()
{
  theSize=0;
  head=new Node;
  tail=new Node;
  head->next=tail;
  tail->prev=head;
}


// Returns the number of elements in the List
template <typename T>
int List<T>::size() const
{
  return theSize;
}


// Returns if empty
template <typename T>
bool List<T>::empty() const
{
  return size()==0;
}


// Deletes all the elements in the List
template <typename T>
void List<T>::clear()
{
  while(!empty())
    pop_front();
}


// Reverses the order of the elements in the list
template <typename T>
void List<T>::reverse()
{
  List<T> revlist;

  for(auto itr=--end();itr!=head;itr--)
    {
      revlist.push_back(*itr);
    }

  std::swap(head, revlist.head);
  std::swap(tail, revlist.tail);
}


// Return reference to the first element in the List
template <typename T>
T& List<T>::front()
{
  return *begin();
}

template <typename T>
const T& List<T>::front() const
{
  return *begin();
}


// Return reference to the last element in the List
template <typename T>
T& List<T>::back() 
{
  return *--end();
}

template <typename T>
const T& List<T>::back() const
{
  return *--end();
}


// Insert new object as the first
template <typename T>
void List<T>::push_front(const T & val)
{
  insert(begin(),val);
}


// Insert new object as the first, move version
template <typename T>
void List<T>::push_front(T && val)
{
  insert(begin(),std::move(val));
}


// Insert new object as the last
template <typename T>
void List<T>::push_back(const T & val)
{
  insert(end(),val);
}


// Insert new object as the last, move version
template <typename T>
void List<T>::push_back(T && val)
{
  insert(end(),std::move(val));
}


// Delete first element
template <typename T>
void List<T>::pop_front()
{
  erase(begin());
}


// Delete last element
template <typename T>
void List<T>::pop_back()
{
  erase(--end());
}


// Delete all nodes with value equal to val
template <typename T>
void List<T>::remove(const T &val)
{
  for(auto itr=begin();itr!=end();)
    {
      if(*itr==val)
	itr=erase(itr);
      else
	++itr;
    }
}


// Print all elements in the List
template <typename T>
void List<T>::print(std::ostream &os, char ofc) const
{
  Node * mon=head;
  int i;

  for(i=0;i<theSize;i++)
    {
      mon =mon->next;
      os<<(mon->data)<<ofc;
    }
}


// Return iterator to first element in the List
template <typename T>
typename List<T>::iterator List<T>::begin()
{
  return {head->next};
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
  return {head->next};
}


// Return iterator to last element in the List
template <typename T>
typename List<T>::iterator List<T>::end()
{
  return {tail};
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
  return {tail};
}


// Insert value val ahead of the node
template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, const T &val)
{
  Node *p=itr.current;
  theSize++;
  return {p->prev=p->prev->next=new Node {val, p->prev,p}};
}


// Insert value val ahead of the node, move version
template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, T && val)
{
  Node *p=itr.current;
  theSize++;
  return {p->prev=p->prev->next=new Node {std::move(val),p->prev,p}};
}


// Delete node refferred to by itr
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator itr)
{
  Node *p=itr.current;
  List<T>::iterator retVal{p->next};
  p->prev->next=p->next;
  p->next->prev=p->prev;
  delete p;
  theSize--;

  return retVal;
}


// Delete all nodes between [start,end)
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start,List<T>::iterator end)
{
  List<T>::iterator itr;
  for(itr=start;itr!=end;)
    itr=erase(itr);

  return end;
}


//____________________ NON CLASS GLOBAL FUNCTIONS _________________________
// Check if two lists contain the same sequence of elements

template <typename T>
bool operator==(const List<T> & lhs, const List<T> & rhs)
{
  if (lhs.size() != rhs.size())
    return false;

  auto left=lhs.begin();
  auto right=rhs.begin();

  while (left != lhs.end() && right != rhs.end())
    {
      if(*left!=*right)
	return false;
      left++;
      right++;
    }

  return true;
}

// Opposite of equal
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> & rhs)
{
  return !(lhs==rhs);
}

// Print out all elemends in list l by calling List class print function
template <typename T>
std::ostream & operator<<(std::ostream & os, const List<T> &l)
{
  l.print(os);
  return os;
}
