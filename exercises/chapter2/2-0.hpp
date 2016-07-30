//===---- 2-0.hpp - Writeup for exercise 2-0 ---*- C++ -*-===//
//
//              Created by zeta on 16-7-29.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines a template 'add_const_ref'.
// It takes 1 parameter T.
// If T is a reference type, it returns T itself,
// else it returns T const &.
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_2_0_HPP
#define TEMPLATECPP_2_0_HPP

#include <boost/type_traits.hpp>
#include <gtest/gtest.h>

/// main template
/// T -> T const &
template<class T>
struct add_const_ref {
    typedef T const &type;
};


/// template specialization for reference type
/// T & -> T &
template<class T>
struct add_const_ref<T&> {
    typedef T &type;
};

TEST(chapter2, 2_0) {
    //===--------------------------------------------------------------------===//
    // call with type should get type const &
    //===--------------------------------------------------------------------===//

    EXPECT_TRUE((boost::is_same<int const &, typename add_const_ref<int>::type >::value));
    EXPECT_FALSE((boost::is_same<int, typename add_const_ref<int>::type >::value));

    //===--------------------------------------------------------------------===//
    // call with type & should get type &
    //===--------------------------------------------------------------------===//
    EXPECT_TRUE((boost::is_same<int &, typename add_const_ref<int&>::type >::value));

    //===--------------------------------------------------------------------===//
    // call with type const & should get type const &
    //===--------------------------------------------------------------------===//
    EXPECT_TRUE((boost::is_same<int const&, typename add_const_ref<int const&>::type >::value));
}

#endif //TEMPLATECPP_2_0_HPP
