#ifndef KLIB_ARRAY_H
#define KLIB_ARRAY_H

template<class _type>
class Array {
    friend bool isArray();
    private:
        _type *_proto_;
        void assign(const _type *, const _type *);
    public:
        unsigned length;
    
        Array(const std::initializer_list<_type>);
        Array(const Array<_type> &);
        ~Array();
        
        char* operator*();
        int* operator&();
        char operator[] (const int);
        
        bool operator= (const std::initializer_list<_type>);
        bool operator= (const Array<_type> &);
        
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
Array<_type>::Array(const std::initializer_list<_type> list) {
    length = list.size(); // list.end()-list.begin()
    _proto_ = new _type[length];
    
    for (unsigned i = 0; i < length; i++) {
        _proto_[i] = *(list.begin()+i);
    }
}

template<class _type>
Array<_type>::Array(const Array<_type> &list) {
    length = list.length; // list.end()-list.begin()
    _proto_ = new _type[length];
    
    for (unsigned i = 0; i < length; i++) {
        _proto_[i] = list._proto_[i];
    }
}

template<class _type>
Array<_type>::~Array() {
    if (_proto_) delete[] _proto_;
}

/* call operators */

/* processing operators: FRIEND */

/* processing operators: OVERLOAD */

/* class methods: PRIVATE */
template<class _type>
void Array<_type>::assign(const _type *iterator_begin, const _type *iterator_end) {

}

/* class methods: FRIEND */

/* class methods: BUILT-IN */

template<class _type>
using array = Array<_type>;

#endif