//===---- 3-6.hpp -  ---*- C++ -*-===//
//
//              Created by zeta on 16-10-3.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//


#ifndef TEMPLATECPP_3_6_HPP
 #define TEMPLATECPP_3_6_HPP

#include <gtest/gtest.h>
#include <boost/mpl/apply.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
namespace chp3_6{
    using namespace boost;
    using namespace boost::mpl;
    using namespace boost::mpl::placeholders;

    template<class T>
    struct twice: apply<apply<add_pointer<_1>, _1>, T>
    {};

    TEST(chapter3, 3_6)
    {
        EXPECT_TRUE(
                (is_same<apply<add_pointer<_1>, typename apply<add_pointer<_1>,int>::type>::type,
                         int**>::value)
                );
    }
}

#endif //TEMPLATECPP_3_6_HPP
