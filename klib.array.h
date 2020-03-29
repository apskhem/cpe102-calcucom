#ifndef KLIB_ARRAY_H
#define KLIB_ARRAY_H

template<class any>
class Array {
    friend bool isArray();
    private:
        /* The encrypted data of array class. */
        any *_proto_;
    public:
        /* The length property sets or returns the number of elements in an array. */
        unsigned length;
    
        Array();
        Array(const std::initializer_list<any> &);
        Array(const Array<any> &);
        ~Array();
        
        any& operator[] (const unsigned &);
        
        Array<any> operator= (const std::initializer_list<any> &);
        Array<any> operator= (const Array<any> &);
        
        /* The method is used to join two or more arrays. */
        Array<any> concat(const Array<any> &);
        /* The method copies array elements to another position in the array, overwriting the existing values. */
        /* Note: this method overwrites the original array. */
        Array<any> copyWithin(unsigned, const unsigned=0, unsigned=-1);
        /* The method checks if all elements in an array pass a test (provided as a function). */
        bool every(bool (*)(any,unsigned,Array<any>));
        /* The method fills the specified elements in an array with a static value. */
        Array<any> fill(const any &, const unsigned=0, unsigned=-1);
        /* The method creates an array filled with all array elements that pass a test (provided as a function). */
        Array<any> filter(bool (*)(any,unsigned,Array<any>), const Array<any> & = {});
        /* The method returns the value of the first element in an array that pass a test (provided as a function). */
        any find(bool (*)(any,unsigned,Array<any>), const any & = NULL);
        /* The method returns the index of the first element in an array that pass a test (provided as a function). */
        int findIndex(bool (*)(any,unsigned,Array<any>), const int & = -1);
        /* The method determines whether an array contains a specified element. */
        bool includes(const any &, const unsigned=0);
        /* The method searches the array for the specified item, and returns its position. */
        int indexOf(const any &, const unsigned=0);
        /* The method returns the array as a string. */
        char* join(const char * ="'");
        /* The method returns an Array Iterator object with the keys of an array. */
        Array<unsigned> keys();
        /* The method searches the array for the specified item, and returns its position. */
        int lastIndexOf(const any &, unsigned=-1);
        /* The method creates a new array with the results of calling a function for every array element. */
        Array<any> map(any (*)(any,unsigned,Array<any>), int);
        /* The method executes a provided function for each value of the array (from left-to-right). */
        any reduce(any (*)(any));
        /* The reduce the values of an array to a single value (going right-to-left) */
        any reduceRight(any (*)(any));
        /* The method reverses the order of the elements in an array. */
        Array<any> reverse();
        /* The method returns the selected elements in an array, as a new array object. */
        Array<any> slice(const unsigned=0, unsigned=-1);
        /* The method sorts the items of an array. */
        Array<any> sort();
        /* The method adds/removes items to/from an array, and returns the removed item(s). */
        /* Note: This method changes the original array. */
        Array<any> splice(const unsigned &, const Array<any> & = {});
        Array<any> splice(const unsigned &, const unsigned &, const Array<any> & = {});
        /* The method returns a string with all the array values, separated by commas. */
        char* toString();
        /* method returns the array. */
        Array<any> values();

        /* The method adds new items to the end of an array, and returns the new length. */
        unsigned push(const Array<any> &);
        unsigned push(const any &);
        /* The method removes the last element of an array, and returns that element. */
        any pop();
        /* The method adds new items to the beginning of an array, and returns the new length. */
        unsigned unshift(const Array<any> &);
        unsigned unshift(const any &);
        /* The method removes the first item of an array, and returns that element. */
        any shift();
};

/* constructor */
template<class any>
Array<any>::Array() {
    length = 0;
    _proto_ = NULL;
}

template<class any>
Array<any>::Array(const std::initializer_list<any> &list) {
    _proto_ = new any[length = list.size()]; // list.end()-list.begin()
    
    for (unsigned i = 0; i < length; i++) _proto_[i] = *(list.begin()+i);
}

template<class any>
Array<any>::Array(const Array<any> &list) {
    _proto_ = new any[length = list.length];
    
    for (unsigned i = 0; i < length; i++) _proto_[i] = list._proto_[i];
}

template<class any>
Array<any>::~Array() {
    delete[] _proto_;
}

/* call operators */
template<class any>
any& Array<any>::operator[] (const unsigned &index) { return _proto_[index]; }

/* processing operators: FRIEND */

/* processing operators: OVERLOAD */
template<class any>
Array<any> Array<any>::operator= (const std::initializer_list<any> &list) {
    delete[] _proto_;

    _proto_ = new any[length = list.size()];

    for (unsigned i = 0; i < length; i++) _proto_[i] = *(list.begin()+i);

    return *this;
}

template<class any>
Array<any> Array<any>::operator= (const Array<any> &list) {
    delete[] _proto_;

    _proto_ = new any[length = list.length];
    
    for (unsigned i = 0; i < length; i++) _proto_[i] = list._proto_[i];

    return *this;
}

/* class methods: PRIVATE */

/* class methods: FRIEND */

/* class methods: BUILT-IN */
template<class any>
Array<any> Array<any>::concat(const Array<any> &items) {
    any result[length+items.length];

    for (unsigned i = 0; i < length; i++) result[i] = _proto_[i];
    for (unsigned i = 0; i < items.length; i++) result[length+i] = items[i];

    return result;
}

template<class any>
Array<any> Array<any>::copyWithin(unsigned target, const unsigned start, unsigned end) {
    if (end == -1 || end > length) end = length;

    //++ FIX

    return *this;
}

template<class any>
bool Array<any>::every(bool (*function)(any,unsigned,Array<any>)) {
    for (unsigned i = 0; i < length; i++) if (!(*function)(_proto_[i],i,*this)) return false;

    return true;
}

template<class any>
Array<any> Array<any>::fill(const any &value, const unsigned start, unsigned end) {
    if (end == -1 || end > length) end = length;

    for (unsigned i = start; i < end; i++) _proto_[i] = value;

    return *this;
}

template<class any>
Array<any> Array<any>::filter(bool (*function)(any,unsigned,Array<any>), const Array<any> &thisValue) {
    unsigned count = 0;
    for (unsigned i = 0; i < length; i++) if (!(*function)(_proto_[i],i,*this)) count++;

    if (!count) thisValue;

    any result[count];
    count = 0;
    for (unsigned i = 0; i < length; i++) if (!(*function)(_proto_[i],i,*this)) result[count++] = _proto_[i];

    return result;
}

template<class any>
any Array<any>::find(bool (*function)(any,unsigned,Array<any>), const any &thisValue) {
    for (unsigned i = 0; i < length; i++) if ((*function)(_proto_[i],i,*this)) return _proto_[i];

    return thisValue;
}

template<class any>
int Array<any>::findIndex(bool (*function)(any,unsigned,Array<any>), const int &thisValue) {
    for (unsigned i = 0; i < length; i++) if ((*function)(_proto_[i],i,*this)) return i;

    return thisValue;
}

template<class any>
bool Array<any>::includes(const any &element, const unsigned start) {
    for (unsigned i = start; i < length; i++) if (_proto_[i] == element) return true;

    return false;
}

template<class any>
int Array<any>::indexOf(const any &item, const unsigned start) {
    for (unsigned i = start; i < length; i++) if (_proto_[i] == item) return i;

    return -1;
}

template<class any>
char* Array<any>::join(const char *separator) {

}

template<class any>
Array<unsigned> Array<any>::keys() {
    
}

template<class any>
int Array<any>::lastIndexOf(const any &item, unsigned atlength) {

}

template<class any>
Array<any> Array<any>::map(any (*function)(any,unsigned,Array<any>), int) {

}

template<class any>
any Array<any>::reduce(any (*function)(any)) {

}

template<class any>
any Array<any>::reduceRight(any (*function)(any)) {

}

template<class any>
Array<any> Array<any>::reverse() {

}

template<class any>
Array<any> Array<any>::slice(const unsigned start, unsigned end) {
    if (end == -1) end = length;
    if (end-start <= 0) return {};

    any result[end-start];

    unsigned j = 0;
    for (unsigned i = start; i < end; i++) result[j++] = _proto_[i];

    return result;
}

template<class any>
Array<any> Array<any>::sort() {

}

template<class any>
Array<any> Array<any>::splice(const unsigned &index, const Array<any> &items) {
    any *old = _proto_;
    _proto_ = new any[length+items.length];

    for (unsigned i = 0; i < index; i++)  _proto_[i] = old[i];
    for (unsigned i = 0; i < items.length; i++) _proto_[index+i] = items[i];
    for (unsigned i = index; i < length; i++) _proto_[items.length+i] = old[i];

    length += items.length;
    delete[] old;

    return *this;
}

template<class any>
Array<any> Array<any>::splice(const unsigned &index, const unsigned &howmany, const Array<any> &items) {
    any *old = _proto_;
    _proto_ = new any[length + items.length - (howmany > (length - index) ? length - index : howmany)];

    for (unsigned i = 0; i < index; i++)  _proto_[i] = old[i];
    for (unsigned i = 0; i < items.length; i++) _proto_[index+i] = items[i];
    for (unsigned i = index+howmany; i < length; i++) _proto_[items.length+i] = old[i];

    length += items.length - (howmany > (length - index) ? length - index : howmany);
    delete[] old;

    return *this;
}

template<class any>
char* Array<any>::toString() {

}

template<class any>
Array<any> Array<any>::values() {

}

template<class any>
unsigned Array<any>::push(const Array<any> &items) {
    any *old = _proto_;
    _proto_ = new any[length+items.length];

    for (unsigned i = 0; i < length; i++) _proto_[i] = old[i];
    for (unsigned i = 0; i < items.length; i++) _proto_[length+i] = items[i];

    length += items.length;
    delete[] old;

    return length;
}

template<class any>
unsigned Array<any>::push(const any &item) {
    any *old = _proto_;
    _proto_ = new any[++length];

    for (unsigned i = 0; i < length-1; i++) _proto_[i] = old[i];

    _proto_[length-1] = item;
    delete[] old;

    return length;
}

template<class any>
any Array<any>::pop() {
    any itemToReturn = _proto_[--length];
    any *old = _proto_;
    _proto_ = new any[length];

    for (unsigned i = 0; i < length; i++) _proto_[i] = old[i];

    delete[] old;

    return itemToReturn;
}

template<class any>
unsigned Array<any>::unshift(const Array<any> &items) {
    any *old = _proto_;
    _proto_ = new any[length+items.length];

    for (unsigned i = 0; i < items.length; i++) _proto_[i] = items[i];
    for (unsigned i = 0; i < length; i++) _proto_[items.length+i] = old[i];

    length += items.length;
    delete[] old;

    return length;
}

template<class any>
unsigned Array<any>::unshift(const any &item) {
    any *old = _proto_;
    _proto_ = new any[++length];

    for (unsigned i = 1; i < length; i++) _proto_[i] = old[i];

    _proto_[0] = item;
    delete[] old;

    return length;
}

template<class any>
any Array<any>::shift() {
    any itemToReturn = _proto_[0];
    any *old = _proto_;
    _proto_ = new any[--length];

    for (unsigned i = 0; i < length; i++) _proto_[i] = old[i+1];

    delete[] old;

    return itemToReturn;
}

template<class any>
using array = Array<any>;

#endif