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
        
        _type operator*();
        _type* operator&();
        _type operator[] (const int);
        
        Array<_type> operator= (const std::initializer_list<_type>);
        Array<_type> operator= (const Array<_type> &);
        
        _type concat(const std::initializer_list<_type>);
        _type concat(const Array<_type> &);
        void copyWithin(unsigned, unsigned, unsigned);
        void entries();
        void every();
        void fill();
        void filter();
        void find();
        void findIndex();
        void includes();
        void indexOf();
        void isArray();
        void join();
        void keys();
        void lastIndexOf();
        void map();
        void reduce();
        void reduceRight();
        void reverse();
        void slice();
        void sort();
        void toString();
        void values();
        
        _type push(const std::initializer_list<_type>);
        _type push(const Array<_type> &);
        _type push(const _type);
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
_type* Array<_type>::operator& () {return &_proto_[0];}
template<class _type>
_type Array<_type>::operator[] (const int index) {return _proto_[index];}

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
using array = Array<_type>;

#endif