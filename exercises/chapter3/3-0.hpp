//===---- 3_0.hpp.hpp - Writeup for exercise 3-0 ---*- C++ -*-===//
//
//              Created by zeta on 16-8-2.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines a template 'binary',
// which takes 1 unsigned parameter N consists of 1 and 0
// and could convert N to decimal base number.
//
// e.g.
// binary<10>::value = 2
// binary<101>::value = 5
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_3_0_HPP
#define TEMPLATECPP_3_0_HPP

#include <gtest/gtest.h>
#include <boost/static_assert.hpp>
namespace tpp {
    template<unsigned N>
    struct binary {
        BOOST_STATIC_ASSERT(N % 10 == 1 || N % 10 == 0);
        static unsigned const value = 2 * binary<N / 10>::value +
                                      binary<N % 10>::value;
    };

    template<>
    struct binary<0> {
        static unsigned const value = 0;
    };

    template<>
    struct binary<1> {
        static unsigned const value = 1;
    };


    TEST(chapter3, 3_0) {
        EXPECT_TRUE((binary<0>::value == 0));
        EXPECT_TRUE((binary<1>::value == 1));
        EXPECT_TRUE((binary<111>::value == 7));
    }
}
#endif //TEMPLATECPP_3_0_HPP
