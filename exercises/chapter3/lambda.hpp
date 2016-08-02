//===---- lambda.hpp - practice of 'lambda' in c++ template meta-programming ---*- C++ -*-===//
//
//              Created by zeta on 16-8-2.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file demonstrates the lambda concept in c++ template meta-programming.
// Don't ask me the details...
// I also can't understand what I've written...
//
// In my view, the only thing chapter3 tells us is that
// c++ template could simulate the behavior of function programming world's lambda
// through a very STUPID and TEDIOUS way ^_^
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_LAMBDA_HPP
#define TEMPLATECPP_LAMBDA_HPP

#include <gtest/gtest.h>
#include <type_traits>
//===--------------------------------------------------------------------===//
// Placeholders these could deal with at most 2 template arguments
//===--------------------------------------------------------------------===//

/// Forward declarations
template<unsigned N>
struct Arg;

struct void_ {
    typedef void_ type;
};

/// Placeholder _1 that holds the 1st template argument
/// Which means that -
/// _1::template apply<T1, T2>::type = T1
template<>
struct Arg<1> {
    template<class A1, class A2 = void_>
    struct apply {
        typedef A1 type;
    };
};
typedef Arg<1> _1;

/// Placeholder _2 that holds the 2nd template argument
/// Which means that -
/// _2::template apply<T1, T2>::type = T2
template<>
struct Arg<2> {
    template<class A1, class A2>
    struct apply {
        typedef A2 type;
    };
};
typedef Arg<2> _2;

/// Template GetArg.
/// Usage: GetArg<A> ,
/// if A is a instantiation of Arg<N>,
/// then GetArg<A>::apply<T1,T2,...Tn> = Arg<N>::apply<T1,T2,...Tn>
/// else GetArg<A>::apply<T1,T2,...Tn> = A
template<class A>
struct GetArg {
    template<class T, class ... Remain>
    struct apply {
        typedef A type;
    };
};

template<unsigned N>
struct GetArg<Arg<N> > : Arg<N> {
};

//===--------------------------------------------------------------------===//
// Template 'lambda' which deals with templates that take at most 2 arguments.
//===--------------------------------------------------------------------===//

/// Lambda deals with a meta-function ( wrapper for a raw template),
/// such as add_pointer_f defined below.
template<class F, class ... PlaceHolders>
struct lambda : F {
    typedef lambda<F, PlaceHolders...> type;
};

/// Lambda deals with raw template that takes 1 argument,
// such as add_pointer defined below.
template<template<class> class F, class X>
struct lambda<F<X> > {
    template<class A = void_>
    struct apply {
        typedef typename F<
                typename GetArg<X>::template apply<A>::type
        >::type type;
    };
    typedef lambda<F<X> > type;
};

/// Lambda deals with raw template that takes 2 argument.
template<template<class, class> class F, class X, class Y>
struct lambda<F<X, Y> > {
    template<class A1 = void_, class A2 = void_>
    struct apply {
        typedef typename F<
                typename GetArg<X>::template apply<A1, A2>::type,
                typename GetArg<Y>::template apply<A1, A2>::type
        >::type type;
    };
    typedef lambda<F<X, Y> > type;
};

//===--------------------------------------------------------------------===//
// Usage of template lambda
//===--------------------------------------------------------------------===//

/// Template adds * to type T(T -> T*).
template<class T>
struct add_pointer {
    typedef T *type;
};

/// Wrapper for 'add_pointer'.
struct add_pointer_f {
    template<class T>
    struct apply {
        typedef typename add_pointer<T>::type type;
    };
};

//===--------------------------------------------------------------------===//
// Optional implementation for twice( which satisfies twice<F,X> = F(F(X)) )
//===--------------------------------------------------------------------===//

/// Option 0: direct definition
template<class F, class X>
struct twice0 {
    typedef typename F::template apply<X>::type once;     /// f(x)
    typedef typename F::template apply<once>::type type;  /// f(f(x))
};

/// Option 1: using meta-function forwarding
template<class F, class X>
struct twice1 : F::template apply<
        typename F::template apply<X>::type
> {
};

/// Option2: add a wrapper for 'apply' to simplify tempalte parameters

/// apply1<F, X> = F::apply<X>
template<class F, class X>
struct apply1 : F::template apply<X> {
};

template<class F, class X>
struct twice2 : apply1<
        F,
        typename apply1<F, X>::type
> {
};

/// Option3: use 'lambda' to define twice.
/// We can do that because lambda works well with both
/// meta-functions use a wrapper( e.g. add_pointer_f )
/// or these use a placeholder( e.g. add_pointer<_1> ).
template<class F, class X>
struct twice3 : apply1<
        typename lambda<F>::type,
        typename apply1<
                typename lambda<F>::type,
                X
        >::type
> {
};


//===--------------------------------------------------------------------===//
// More usages of 'lambda'
//===--------------------------------------------------------------------===//

/// Template that represent a int
template<int N>
struct int_ {
    static const int value = N;
};

template<class Int1, class Int2>
struct plus_ {
    typedef int_<Int1::value + Int2::value> type;
};

/// Partional function application
typedef lambda<plus_<_1, _1>> mul2;
typedef lambda<plus_<_1, int_<10>>> add10;

//===--------------------------------------------------------------------===//
// test cases
//===--------------------------------------------------------------------===//
TEST(chapter3, lambda) {
    /// test for twice0
    EXPECT_TRUE((std::is_same<int **, typename twice0<add_pointer_f, int>::type>::value));
    /// test for twice1
    EXPECT_TRUE((std::is_same<int **, typename twice1<add_pointer_f, int>::type>::value));
    /// test for twice2
    EXPECT_TRUE((std::is_same<int **, typename twice2<add_pointer_f, int>::type>::value));
    /// tests for lambda and twice3
    EXPECT_TRUE((std::is_same<int **, typename twice3<add_pointer<_1>, int>::type>::value));
    EXPECT_TRUE((std::is_same<int **, typename twice3<add_pointer_f, int>::type>::value));

    /// tests for plus_
    EXPECT_TRUE((std::is_same<int_<2>, typename plus_<int_<1>, int_<1>>::type>::value));
    /// tests for partional function application
    EXPECT_TRUE((std::is_same<int_<2>, typename mul2::apply<int_<1>>::type>::value));
    EXPECT_TRUE((std::is_same<int_<11>, typename add10::apply<int_<1>>::type>::value));
}

#endif //TEMPLATECPP_LAMBDA_HPP
