//===---- has_member.hpp -  ---*- C++ -*-===//
//
//              Created by zeta on 16-10-2.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines a template that distinguishes
// if a class has specific embedded type(typedef or embedded class).
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_HAS_MEMBER_HPP
#define TEMPLATECPP_HAS_MEMBER_HPP

#include <gtest/gtest.h>
#include <type_traits>
namespace tpp {
    template<class T>
    struct has_embedded_type {
        template<class U>
        // use std::decay to avoid the return type being void
        static auto helper(U) -> typename std::decay<typename U::type>::type;
        template <class U>
        static void helper(...);

        using type=decltype(helper<T>(std::declval<T>()));
        static const bool value = !std::is_void<type>::value;
    };

    /// standart type
    struct HasMemberTrue0{
        typedef char type;
    };
    struct HasMemberTrue1{
        typedef char *type;
    };
    struct HasMemberTrue2{
        typedef char &type;
    };
    struct HasMemberTrue3{
        typedef char &&type;
    };
    struct HasMemberTrue4{
        typedef char type[5];
    };
    struct HasMemberTrue5{
        typedef const volatile char type;
    };
    /// class has typedef
    struct HasMemberFalse{
    };

#define TRUE_TEST(i) EXPECT_TRUE(has_embedded_type<HasMemberTrue##i>::value)

    TEST(chapter3, has_member_type) {
        TRUE_TEST(0);
        TRUE_TEST(1);
        TRUE_TEST(2);
        TRUE_TEST(3);
        TRUE_TEST(4);
        TRUE_TEST(5);
        EXPECT_FALSE(has_embedded_type<HasMemberFalse>::value);
    }
}

#endif //TEMPLATECPP_HAS_MEMBER_HPP
