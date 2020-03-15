#ifndef KLIB_STRING_H
#define KLIB_STRING_H

#include <cstring>
#include <string> // for iostream

typedef class String {
    friend String operator+ (const char *, const String &);
    friend std::ostream& operator<< (std::ostream &, const String &);
    friend std::istream& operator>> (std::istream &, String &);
    friend std::istream& getline(std::istream &, String &);
    template <class number>
    friend String toString(number);
    private:
        char *_proto_; // c-string data
        void assign(const char*);
    public:
        unsigned length;
        
        String();
        String(const char *str);
        String(const String &str);
        ~String();
        
        operator char*();
        operator const char*();
        operator String();
        operator const String();
        
        char* operator*();
        int* operator&();
        char operator[] (const int);
        String operator+ (const char *);
        String operator+ (const String &str);
        String operator= (const char *);
        String operator= (const String &str);
        String operator+= (const char *);
        String operator+= (const String &str);
        bool operator== (const char *);
        bool operator== (const String &);
        bool operator!= (const char *);
        bool operator!= (const String &);
        String operator* (const unsigned);
        
        int charAt();
        int charCodeAt();
        String concat(const String &);
        String concat(const char *);
        bool endsWith();
        void fromCharCode();
        bool includes();
        int indexOf();
        int lastIndexOf();
        bool localeCompare();
        String match();
        int repeat();
        String replace();
        int search();
        String slice();
        String split();
        bool startsWith();
        String substr();
        String substring();
        String toLocaleLowerCase();
        String toLocaleUpperCase();
        String toLowerCase();
        String toString();
        String toUpperCase();
        String trim();
        String valueOf();
} string;

/* constructor */
String::String() {
    _proto_ = NULL;
    length = 0;
}

String::String(const char *str) {
    this->assign(str);
}

String::String(const String &str) {
    this->assign(str._proto_);
}

String::~String() {
    if (_proto_) delete[] _proto_;
}

/* call operators */
String::operator char*() {return _proto_;}
String::operator const char* () {return _proto_;}
char * String::operator*() {return _proto_;}
int * String::operator&() {return (int*)&_proto_[0];}
char String::operator[] (const int index) {return _proto_[index];}

/* processing operators: FRIEND */
std::ostream& operator<< (std::ostream &out, const String &str) {
    out << str._proto_;
    return out;
}

std::istream& operator>> (std::istream &in, String &str) {
    std::string t;
    in >> t;
    
    str.assign(t.c_str());
    
    return in;
}

std::istream &getline (std::istream &in, String &str) {
    std::string t;
    std::getline(std::cin, t);
    
    str.assign(t.c_str());
    
    return in;
}

/* processing operators: OVERLOAD */
String operator+ (const char *lstr, const String &rstr) {
    String t(lstr);
    return t.concat(rstr);
}

String String::operator+ (const char *str) {
    return this->concat(str);
}

String String::operator+ (const String &str) {
    return this->concat(str);
}

/* ### */

String String::operator= (const char *str) {
    this->assign(str);
    return *this;
}

String String::operator= (const String &str) {
    this->assign(str._proto_);
    return *this;
}

/* ### */

String String::operator+= (const char *str) {
    string newT = this->concat(str);
    
    this->assign((char*) newT);
    
    return newT;
}

String String::operator+= (const String &str) {
    string newT = this->concat(str);
    
    this->assign((char*) newT);
    
    return newT;
}

/* ### */

bool String::operator== (const String &str) {
    if (length != str.length) return false;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str._proto_[i]) return false;
    }
    
    return true;
}

bool String::operator== (const char *str) {
    if (length != strlen(str)) return false;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str[i]) return false;
    }
    
    return true;
}

bool String::operator!= (const String &str) {
    if (length != str.length) return true;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str._proto_[i]) return true;
    }
    
    return false;
}

bool String::operator!= (const char *str) {
    if (length != strlen(str)) return true;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str[i]) return true;
    }
    
    return false;
}

/* ### */

String String::operator* (const unsigned mul) {
    
}

/* class methods: PRIVATE */
void String::assign(const char *str) {
    length = strlen(str);
    _proto_ = new char[length];
    
    for (unsigned i = 0; i < length; i++) {
        _proto_[i] = str[i];
    }
}

/* class methods: FRIEND */

/* class methods: BUILT-IN */
String String::concat(const String &t) {
    int newLength = length + t.length;
    char *newT = new char[newLength];
    
    // concat
    for (unsigned i = 0; i < length; i++) {
        newT[i] = _proto_[i];
    }
    
    for (unsigned i = 0; i < t.length; i++) {
        newT[length + i] = t._proto_[i];
    }
    
    String newTxt(newT);

    return newTxt;
}

String String::concat(const char *t) {
    int inLength = strlen(t);
    char *newT = new char[length + inLength];
    
    // concat
    for (unsigned i = 0; i < length; i++) {
        newT[i] = _proto_[i];
    }
    
    for (unsigned i = 0; i < inLength; i++) {
        newT[length + i] = t[i];
    }
    
    String newTxt(newT);

    return newTxt;
}

/* ### */

#endif