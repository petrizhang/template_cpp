//===---- 3_3_4.hpp -  ---*- C++ -*-===//
//
//              Created by zeta on 16-8-2.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//


#ifndef TEMPLATECPP_3_3_4_HPP
#define TEMPLATECPP_3_3_4_HPP

#include <type_traits>
#include "lambda.hpp"

#define twice twice3

/// apply 'twice' twice
template<class T>
struct add_pointer_fourth0 {
    typedef typename twice<add_pointer<_1>, T>::type once;
    typedef typename twice<add_pointer<_1>, once>::type type;
};

/// use 'twice' as an argument of 'twice'
template<class T>
struct add_pointer_fourth1 : twice<twice<add_pointer<_1>, _1>, T> {
};

TEST(chapter3, 3_3_4) {
    EXPECT_TRUE((std::is_same<typename add_pointer_fourth0<int>::type,
            int ****>::value));
    EXPECT_TRUE((std::is_same<typename add_pointer_fourth1<int>::type,
            int ****>::value));
}

#endif //TEMPLATECPP_3_3_4_HPP
