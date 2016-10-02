//===---- 3_1_2.hpp - Writeup for exercise 3-1 and 3-2 ---*- C++ -*-===//
//
//              Created by zeta on 16-8-2.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_3_1_2_HPP
#define TEMPLATECPP_3_1_2_HPP

#include <gtest/gtest.h>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal.hpp>

namespace tpp {
    namespace mpl = boost::mpl;
    namespace placeholders = mpl::placeholders;
    typedef typename
    mpl::transform<
            mpl::vector_c<int, 1, 2, 3>,
            mpl::vector_c<int, 1, 1, 1>,
            mpl::plus<placeholders::_1, placeholders::_2>
    >::type
            seq1;

    typedef typename
    mpl::transform<
            mpl::vector_c<int, 1, 2, 3>,
            mpl::vector_c<int, 1, 2, 3>,
            mpl::multiplies<placeholders::_1, placeholders::_2>
    >::type
            seq2;

    TEST(chapter3, 3_1_2) {

        EXPECT_TRUE((mpl::equal < mpl::vector_c < int, 2, 3, 4 >, seq1 > ::value));
        EXPECT_TRUE((mpl::equal < mpl::vector_c < int, 1, 4, 9 >, seq2 > ::value));
    }
}
#endif //TEMPLATECPP_3_1_2_HPP
