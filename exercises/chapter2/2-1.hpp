//===---- 2-1.hpp - Writeup for exercise 2-1 ---*- C++ -*-===//
//
//              Created by zeta on 16-7-30.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines a template 'replace_type'.
// The template has 3 type parameters <class C,class X,class Y>
// and it replaces all type X in compound type C with type Y.
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_2_1_HPP
#define TEMPLATECPP_2_1_HPP

#include <gtest/gtest.h>
#include <boost/type_traits.hpp>

/// Main template
template<class C, class X, class Y>
struct replace_type {
    typedef C type;
};

/// Replace X with Y directly
template<class X, class Y>
struct replace_type<X, X, Y> {
    typedef Y type;
};

/// Remove the '&' definition from 'C&',
/// then replace X in C with Y recursively
template<class C, class X, class Y>
struct replace_type<C &, X, Y> {
    typedef typename replace_type<C, X, Y>::type &type;
};
template<class X, class Y>
struct replace_type<X &, X, Y> {
    typedef Y &type;
};

/// Deduct '*' definition recursively
template<class C, class X, class Y>
struct replace_type<C *, X, Y> {
    typedef typename replace_type<C, X, Y>::type *type;
};
template<class X, class Y>
struct replace_type<X *, X, Y> {
    typedef Y *type;
};

/// Deduct '[N]' definition recursively
template<class C, class X, class Y, unsigned N>
struct replace_type<C[N], X, Y> {
    typedef typename replace_type<C, X, Y>::type type[N];
};
template<unsigned N, class X, class Y>
struct replace_type<X[N], X, Y> {
    typedef Y type[N];
};


TEST(chapter2, 2_1) {
    //===--------------------------------------------------------------------===//
    // Test for unrelated types
    //===--------------------------------------------------------------------===//
    EXPECT_TRUE((boost::is_same<int,
            typename replace_type<int, long, double>::type>::value));

    //===--------------------------------------------------------------------===//
    // Test for '&' definition
    //===--------------------------------------------------------------------===//
    EXPECT_TRUE((boost::is_same<int &,
            typename replace_type<long &, long, int>::type>::value));
    EXPECT_TRUE((boost::is_same<int &,
            typename replace_type<long const &, long const, int>::type>::value));

    //===--------------------------------------------------------------------===//
    // Test for deduction of '*' definition
    //===--------------------------------------------------------------------===//
    EXPECT_TRUE((boost::is_same<int ******,
            typename replace_type<long ******, long, int>::type>::value));
    EXPECT_TRUE((boost::is_same<int ******,
            typename replace_type<long const ******, long const, int>::type>::value));

    //===--------------------------------------------------------------------===//
    // Test for deduction of '[N]' definition
    //===--------------------------------------------------------------------===//
    EXPECT_TRUE((boost::is_same<int[1][2][3][4][5][6],
            typename replace_type<long[1][2][3][4][5][6], long, int>::type>::value));
    EXPECT_TRUE((boost::is_same<int[1][2][3][4][5][6],
            typename replace_type<long const[1][2][3][4][5][6], long const, int>::type>::value));

    //===--------------------------------------------------------------------===//
    // Test for replacement for compound type
    //===--------------------------------------------------------------------===//
    EXPECT_TRUE((boost::is_same<int **[6][6],
            typename replace_type<long **[6][6], long, int>::type>::value));
    EXPECT_TRUE((boost::is_same<int **&,
            typename replace_type<long **&, long, int>::type>::value));

}

#endif //TEMPLATECPP_2_1_HPP