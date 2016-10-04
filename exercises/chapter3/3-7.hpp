//===---- 3-7.hpp -  ---*- C++ -*-===//
//
//              Created by zeta on 16-10-4.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_3_7_HPP
#define TEMPLATECPP_3_7_HPP

#include <gtest/gtest.h>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <vector>
namespace chp3_7 {
    using namespace boost;
    using namespace boost::mpl;
    using namespace boost::mpl::placeholders;

    typedef lambda<lambda<_1>>::type t1;
    typedef apply<_1, plus<_1,_2> >::type t2;
    typedef apply<_1, std::vector<int> >::type t3;
    typedef apply<_1, std::vector<_1> >::type t4;
    typedef apply<lambda<_1>, std::vector<int> >::type t5;
    typedef apply<lambda<_1>, std::vector<_1> >::type t6;
    typedef apply<lambda<_1>, plus<_1,_2> >::type t7;
    typedef apply<_1, lambda<plus<_1,_2> > >::type t8;

    /* answers */
    // t1::apply<T>::type = lambda<T>::type
    // t2 = plus<_1,_2>
    // t3 = std::vector<int>
    // t4 = std::vector<_1>
    // t5 = lambda<vecotr<int>> = std::vector<int>
    // t6::type = lambda<std::vector<_1>>::type
    // t7::type = lambda<plus<_1,_2>>::type
    // t8::type = lambda<plus<_1,_2>>::type = t7::type

    TEST(chapter3, 3_7)
    {
        // t1::apply<T>::type = lambda<T>::type
        EXPECT_TRUE(
                (is_same< t1::apply<add_pointer<_1> >::type, lambda<add_pointer<_1> >::type >::value)
        );
        t1::apply<add_pointer<_1>>::type::apply<int>::type a1;
        EXPECT_TRUE(
                (is_same<decltype(a1), int*>::value)
        );

        // t2 = plus<_1,_2>
        EXPECT_TRUE(
                (is_same<t2,plus<_1,_2> >::value)
        );
        // t3 = std::vector<int>
        EXPECT_TRUE(
                (is_same<t3,std::vector<int> >::value)
        );
        // t4 = std::vector<_1>
        EXPECT_TRUE(
                (is_same<t4,std::vector<_1> >::value)
        );
        // t5 = std::vector<int>
        EXPECT_TRUE(
                (is_same<t5,std::vector<int> >::value)
        );
        // t6::type = lambda<std::vector<_1>>::type>
        EXPECT_TRUE(
                (is_same<t6::type,lambda<std::vector<_1>>::type >::value)
        );
        // t7::type = lambda<plus<_1,_2>>::type
        EXPECT_TRUE(
                (is_same<t7::type, lambda<plus<_1,_2>>::type >::value)
        );
        // t8::type = lambda<plus<_1,_2>>::type = t7::type
        EXPECT_TRUE(
                (is_same<t8::type, t7::type >::value)
        );
    }
}
#endif //TEMPLATECPP_3_7_HPP
