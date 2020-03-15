#ifndef KLIB_ARRAY_H
#define KLIB_ARRAY_H

template<class _type>
class Array {
    private:
        _type *data;
    public:
        unsigned length;
    
        Array(const std::initializer_list<_type> list);
        
        _type push();
        _type pop();
        _type shift();
        _type unshift();
};

template<class _type>
Array<_type>::Array(const std::initializer_list<_type> list) {
    length = list.size(); //list.end()-list.begin()
    
    data = new _type[length];
    
    for (unsigned i = 0; i < length; i++) {
        std::cout << *(list.begin()+i) << "\n";
    }
}

template<class _type>
using array = Array<_type>;

#endif