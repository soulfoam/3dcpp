//  Created on 10.04.19.
#pragma once

#include <type_traits>
#include <iostream>
#include <limits>

template<class T>
using nrof = T;

template<class T, int name = std::numeric_limits<int>::max()>
struct rof : public T {
    void p(const char *str) {
        if (name != std::numeric_limits<int>::max()) {
            std::cout << "#" << name << "'s ";
        }
        std::cout << str << "\n";
    }
public:
    
    template<class = std::enable_if_t<std::is_default_constructible<T>::value>>
    rof() {
        p("default ctor");
    }
    
    template<class = std::enable_if_t<std::is_move_constructible<T>::value>>
    rof(T &&o) : T(std::move(o)) {
        p("move ctor");
    }
    
    template<int N, class = std::enable_if_t<std::is_move_constructible<T>::value>>
    rof(rof<T, N> &&o) : T(std::move(o)) {
        p("move ctor");
    }
    
    template<class = std::enable_if_t<std::is_copy_constructible<T>::value>>
    rof(const T &o) : T(o) {
        p("copy ctor");
    }
    
    template<int N, class = std::enable_if_t<std::is_copy_constructible<T>::value>>
    rof(const rof<T, N> &o) : T(o) {
        p("copy ctor");
    }
    
    template<class = std::enable_if_t<std::is_move_assignable<T>::value>>
    rof &operator=(T &&o) {
        T::operator=(std::move(o));
        p("move op=");
        return *this;
    }
    
    template<int N, class = std::enable_if_t<std::is_move_assignable<T>::value>>
    rof &operator=(rof<T, N> &&o) {
        T::operator=(std::move(o));
        p("move op=");
        return *this;
    }
    
    template<class = std::enable_if_t<std::is_copy_assignable<T>::value>>
    rof &operator=(const T &o) {
        T::operator=(o);
        p("copy op=");
        return *this;
    }
    
    template<int N, class = std::enable_if_t<std::is_copy_assignable<T>::value>>
    rof &operator=(const rof<T, N> &o) {
        T::operator=(o);
        p("copy op=");
        return *this;
    }
    
    ~rof() {
        p("dtor");
    }
    
    template<class ...Args>
    rof(Args &&... args) : T(std::forward<Args>(args)...) {
        p("other ctor");
    }
};

