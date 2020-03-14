#ifndef KHEMS_STRING_H
#define KHEMS_STRING_H

#include <cstring>

typedef class String {
    friend String operator+ (const char *, const String &);
    friend String operator+ (const String &, const char *);
    private:
        char *cstr;
    public:
        unsigned length;
        
        String();
        String(const char *str);
        String(const String &str);
        ~String();
        
        operator char*();
        operator const char*();
        operator String();
        
        char* operator*();
        int* operator&();
        char operator[] (const int);
        bool operator== (const char *);
        bool operator== (const String &);
        bool operator!= (const char *);
        bool operator!= (const String &);
        char* operator* (const unsigned int &);
        
        int charAt();
        int charCodeAt();
        String concat(const String &);
        bool endsWith();
        void fromCharCode();
        bool includes();
        int indexOf();
        int lastIndexOf();
        bool localeCompare();
        char* match();
        int repeat();
        char* replace();
        int search();
        char* slice();
        char* split();
        bool startsWith();
        char* substr();
        char* substring();
        char* toLocaleLowerCase();
        char* toLocaleUpperCase();
        char* toLowerCase();
        char* toString();
        char* toUpperCase();
        char* trim();
        char* valueOf();
} string;

/* constructor */
String::String() {
    cstr = NULL;
    length = 0;
}

String::String(const char *str) {
    length = strlen(str);
    cstr = new char[length];
    
    // copy str
    for (unsigned int i = 0; i < length; i++) {
        cstr[i] = str[i];
    }
}

String::String(const String &str) {
    length = strlen(str.cstr)+1;
    cstr = new char[length];
    
    // copy str
    for (unsigned int i = 0; i < length; i++) {
        cstr[i] = str.cstr[i];
    }
}

String::~String() {
    if(cstr) delete[] cstr;
}

/* call operators */
String::operator char*() {
    return cstr;
}

String::operator const char* () {
    return cstr;
}

char * String::operator*() {
    return cstr;
}

int * String::operator&() {
    return (int*)&cstr[0];
}

/* processing operators */
String operator+ (const char *lstr, const String &rstr) {
    String ltxt = lstr;

    return ltxt.concat(rstr);
}

String operator+ (const String &lstr, const char *rstr) {
    return strcat(lstr.cstr,rstr);
}

char String::operator[] (const int index) {
    return cstr[index];
}

/* extension operators */
String String::concat(const String &t) {
    int newLength = length + t.length;
    char *newT = new char[newLength];
    
    // concat
    for (unsigned i = 0; i < length; i++) {
        newT[i] = cstr[i];
    }
    
    for (unsigned i = 0; i < t.length; i++) {
        newT[length + i] = t.cstr[i];
    }
    
    String newTxt = newT;

    return newTxt;
}

#endif