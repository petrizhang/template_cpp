//===---- 4-0_1.hpp -  ---*- C++ -*-===//
//
//              Created by zeta on 16-10-4.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines 2 templates named 'logical_or' and 'logical_and'.
// The 2 templates calculate on boost integral constant wrappers(typically bool_<bool>),
// and have short-circuit/lazy evaluation features.
//
// Usage:
// logical_or/logical_and<T1, T2 (, T3, T4, T5 optional)>;
//
// Generally, Tx should have a static bool member named value,
// which means the expression Tx::value must be legal.
// But when short-circuit calculation occurs, using Tx that doens't satisfy the limit
// could also work.
// For example, logical_or< true_, Tx...>::value will always be true
// regardless of what Tx's type is.
//
// Examples:
// bool b0 = logical_and< is_pointer<int*>, is_scalar<int>>(); //b0 will be true
// bool b1 = logical_and< is_pointer<int*>, is_scalar<int>>::value; //b1 will be true
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_4_0_1_HPP
#define TEMPLATECPP_4_0_1_HPP

#include <gtest/gtest.h>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>

namespace chp4_0_1 {
    using namespace boost;
    using namespace boost::mpl;
    struct A{};

    template <bool b, class T>
    struct and_helper{
        static const bool value = b && T::value;
    };

    template <class T>
    struct and_helper<false,T>
    {
        static const bool value = false;
    };

    template <bool b, class T>
    struct or_helper{
        static const bool value = b && T::value;
    };

    template <class T>
    struct or_helper<true,T>
    {
        static const bool value = true;
    };

    // using and_helper to implement lazy evaluation
    template<class T1, class T2=true_, class T3=true_, class T4=true_, class T5 = true_>
    struct logical_and:bool_< and_helper<T1::value, logical_and<T2,T3,T4,T5> >::value >
    {};

    // using or_helper to implement lazy evaluation
    template<class T1, class T2=false_, class T3=false_, class T4=false_, class T5 = false_>
    struct logical_or:bool_< or_helper<T1::value, logical_and<T2,T3,T4,T5> >::value >
    {};


    TEST(chapter4, 4_0_1)
    {
        // as a result of and_'s short-circuit evalution,
        // this example won't cause a compile error
        EXPECT_FALSE(
                (and_<is_scalar<int>,
                      is_scalar<A>,
                      int,
                      int
                     >())
        );

        EXPECT_FALSE(
                (logical_and<is_scalar<int>,
                             is_scalar<A>,
                             int,
                             int
                            >())
        );

        // as a result of or_'s short-circuit evalution,
        // this example won't cause a compile error
        EXPECT_TRUE(
                (or_<is_scalar<int>,
                     int
                >())
        );

        EXPECT_TRUE(
                (logical_or<is_scalar<int>,
                            int
                           >())
        );
    }
}
#endif //TEMPLATECPP_4_0_1_HPP
