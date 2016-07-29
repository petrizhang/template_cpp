//===---- 2-0.hpp - Writeup for exercise 2-0 ---*- C++ -*-===//
//
//              Created by zeta on 16-7-29.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines a template.
// If the template parameter T is reference type, it returns T itself,
// else it returns type T const &.
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


/// template specifection for reference type
/// T & -> T &
template<class T>
struct add_const_ref<T&> {
    typedef T &type;
};

TEST(chapter2, 2_0) {
    //===--------------------------------------------------------------------===//
    // call with type should get type const &
    //===--------------------------------------------------------------------===//

    EXPECT_EQ((boost::is_same<int const &, typename add_const_ref<int>::type >::value),
              true);
    EXPECT_EQ((boost::is_same<int, typename add_const_ref<int>::type >::value),
              false);

    //===--------------------------------------------------------------------===//
    // call with type & should get type &
    //===--------------------------------------------------------------------===//
    EXPECT_EQ((boost::is_same<int &, typename add_const_ref<int&>::type >::value),
              true);

    //===--------------------------------------------------------------------===//
    // call with type const & should get type const &
    //===--------------------------------------------------------------------===//
    EXPECT_EQ((boost::is_same<int const&, typename add_const_ref<int const&>::type >::value),
              true);
}

#endif //TEMPLATECPP_2_0_HPP
