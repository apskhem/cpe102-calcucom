#ifndef KLIB_ARRAY_H
#define KLIB_ARRAY_H

template<class _type>
class Array {
    friend bool isArray();
    private:
        _type *_proto_;
    public:
        unsigned length;
    
        Array();
        Array(const std::initializer_list<_type>);
        Array(const Array<_type> &);
        ~Array();
        
        _type& operator[] (const int);
        
        Array<_type> operator= (const std::initializer_list<_type>);
        Array<_type> operator= (const Array<_type> &);
        
        /* The method is used to join two or more arrays. */
        Array<_type> concat(const std::initializer_list<_type>);
        /* The method is used to join two or more arrays. */
        Array<_type> concat(const Array<_type> &);
        /* The method copies array elements to another position in the array, overwriting the existing values. */
        /* Note: this method overwrites the original array. */
        Array<_type> copyWithin(unsigned, const unsigned=0, unsigned=-1);
        /* The method fills the specified elements in an array with a static value. */
        Array<_type> fill(const _type, const unsigned=0, unsigned=-1);
        /* The method determines whether an array contains a specified element. */
        bool includes(const _type, const unsigned=0);
        /* The method searches the array for the specified item, and returns its position. */
        int indexOf(const _type, const unsigned=0);
        /* The method returns the array as a string. */
        // char* join(const char *="'");
        /* The method returns an Array Iterator object with the keys of an array. */
        Array<unsigned> keys();
        /* The method searches the array for the specified item, and returns its position. */
        int lastIndexOf(const char *, unsigned=-1);
        /* The method reverses the order of the elements in an array. */
        Array<_type> reverse();
        /* The method returns the selected elements in an array, as a new array object. */
        Array<_type> slice(const unsigned=0, unsigned=-1);
        /* The method sorts the items of an array. */
        Array<_type> sort();
        /* The method adds/removes items to/from an array, and returns the removed item(s). */
        /* Note: This method changes the original array. */
        // void splice(const unsigned, const unsigned=0, const std::initializer_list<_type>);
        /* The method returns a string with all the array values, separated by commas. */
        char* toString();
        /* method returns the array. */
        Array<_type> values();
        
        unsigned push(const std::initializer_list<_type>);
        unsigned push(const Array<_type> &);
        unsigned push(const _type);
        _type pop();
        _type unshift(const std::initializer_list<_type>);
        _type unshift(const Array<_type> &);
        _type unshift(const _type);
        _type shift();
        _type splice();
};

/* constructor */
template<class _type>
Array<_type>::Array() {
    length = 0;
    _proto_ = NULL;
}

template<class _type>
Array<_type>::Array(const std::initializer_list<_type> list) {
    length = list.size(); // list.end()-list.begin()
    _proto_ = new _type[length];
    
    for (unsigned i = 0; i < length; i++) {
        _proto_[i] = *(list.begin()+i);
    }
}

template<class _type>
Array<_type>::Array(const Array<_type> &list) {
    length = list.length;
    _proto_ = new _type[length];
    
    for (unsigned i = 0; i < length; i++) {
        _proto_[i] = list._proto_[i];
    }
}

template<class _type>
Array<_type>::~Array() {
    delete[] _proto_;
}

/* call operators */
template<class _type>
_type& Array<_type>::operator[] (const int index) {return _proto_[index];}

/* processing operators: FRIEND */

/* processing operators: OVERLOAD */
template<class _type>
Array<_type> Array<_type>::operator= (const std::initializer_list<_type> list) {
    delete[] _proto_;

    length = list.size();
    _proto_ = new _type[length];

    for (unsigned i = 0; i < length; i++) {
        _proto_[i] = *(list.begin()+i);
    }

    return *this;
}

template<class _type>
Array<_type> Array<_type>::operator= (const Array<_type> &list) {
    delete[] _proto_;

    length = list.length;
    _proto_ = new _type[length];
    
    for (unsigned i = 0; i < length; i++) {
        _proto_[i] = list._proto_[i];
    }

    return *this;
}

/* class methods: PRIVATE */

/* class methods: FRIEND */

/* class methods: BUILT-IN */
template<class _type>
unsigned Array<_type>::push(const _type item) {
    _type *old = _proto_;
    _proto_ = new _type[++length];

    for (unsigned i = 0; i < length-1; i++) {
        _proto_[i] = old[i];
    }

    _proto_[length-1] = item;
    delete[] old;

    return length;
}

template<class _type>
using array = Array<_type>;

#endif