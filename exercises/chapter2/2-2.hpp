//===---- 2-2.hpp - Writeup for exercise 2-2 ---*- C++ -*-===//
//
//              Created by zeta on 16-7-30.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines a function template 'polymorphic_downcast'.
// It is a wrap for static_cast.
// When debugging( when NDEBUG is not defined) , before calling static_cast,
// it calls dynamic_cast to check if the cast is valid.
// In release version, for NDEGUG is defined, it behaves completely same with static_cast.
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_2_2_HPP
#define TEMPLATECPP_2_2_HPP

#include <gtest/gtest.h>
#include <boost/type_traits.hpp>
#include <cassert>

/// cast for pointer type
template<class Target, class Source>
inline Target polymorphic_downcast(Source *X) {
    assert(dynamic_cast<Target>(X) == X);
    return static_cast<Target>(X);
};

/// cast for reference type
template<class Target, class Source>
inline Target polymorphic_downcast(Source &X) {
#ifndef NDEBUG
    dynamic_cast<Target>(X);
#endif
    return static_cast<Target>(X);
};

TEST(chapter2, 2_2) {
    struct Base {
        virtual ~Base() {};
    };

    struct Derived : Base {
    };

    /// cast for Base * -> Derived *
    Derived d;
    Base *b_ptr = &d;
    Derived *d_ptr = polymorphic_downcast<Derived *>(b_ptr);

    /// cast for Base & -> Derived &
    Base &b_ref = d;
    Derived &d_ref = polymorphic_downcast<Derived &>(b_ref);

    /// bad cast for Base & -> Derived &
    /// which is expected to throw a std::bad_cast error
    Base b;
    Base &b_bad_ref = b;
    EXPECT_THROW((d_ref = polymorphic_downcast<Derived &>(b_bad_ref)),
                 std::bad_cast);
}

#endif //TEMPLATECPP_2_2_HPP
