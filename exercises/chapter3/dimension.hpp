//===---- dimension.hpp -  ---*- C++ -*-===//
//
//              Created by zeta on 16-10-3.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file uses boost integral constant wrappers to construct a type system.
//  of different physical quantity
// in operation process is illegal.
//
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_DIMENSION_HPP
#define TEMPLATECPP_DIMENSION_HPP

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/lambda.hpp>
#include <gtest/gtest.h>

namespace quantity {
    using namespace boost::mpl;
    using namespace boost::mpl::placeholders;

    typedef vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;
    typedef vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;//m
    typedef vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;//m
    typedef vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;//s
    typedef vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;//A
    typedef vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;//K
    typedef vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;//cd
    typedef vector_c<int, 0, 0, 0, 0, 0, 0, 1> amount_of_substance;//mol

    typedef vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;// length/time
    typedef vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;// length/ time^2
    typedef vector_c<int, 0, 1, 1, -1, 0, 0, 0> momentum;// mass*lenght/time
    typedef vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;// mass*lenght/ time^2

/// T: the type of quantity( e.g. int/float/double)
/// Dimensions: the type of dimension of this quantity
    template<class Type, class Dimensions>
    struct quantity
    {

        /// explicit constructor
        explicit quantity(Type x) : m_value(x) {}

        /// implicit converter
        template<class OtherDimensions>
        quantity(const quantity<Type,OtherDimensions> &rhs)
        :m_value(rhs.value())
        {
            BOOST_STATIC_ASSERT(
                    (equal<Dimensions,OtherDimensions>::type::value)
            );
        }

        Type value() const {
            return m_value;
        }

        /// +
        template<class T,class D>
        quantity<T, D>
        operator+(const quantity<T, D > &rhs)
        {
            return quantity<T,D>(m_value+rhs.value());
        };

        template<class T,long ... Other>
        quantity<T, vector_c<int ,Other...>>
        operator+(const quantity<T, vector_c<int,Other...> > &rhs)
        {
            return quantity<T,vector_c<int,Other...>>(m_value+rhs.value());
        };

        /// -
        template<class T, class D>
        quantity<T, D>
        operator-(const quantity<T, D> &rhs)
        {
            return quantity<T,D>(m_value-rhs.value());
        };

        template<class T,long ... Other>
        quantity<T, vector_c<int ,Other...>>
        operator-(const quantity<T, vector_c<int,Other...> > &rhs)
        {
            return quantity<T,vector_c<int,Other...>>(m_value-rhs.value());
        };

        /// *
        template<class T, class D1, class D2>
        friend
        quantity<T,
                typename transform<D1, D2, plus<_1,_2> >::type
        >
        operator*(const quantity<T, D1> &x, const quantity<T, D2> &y);

        /// /
        template<class T, class D1, class D2>
        friend
        quantity<T,
                typename transform<D1, D2, minus<_1,_2> >::type
        >
        operator/(const quantity<T, D1> &x, const quantity<T, D2> &y);
    private:
        Type m_value;
    };


    template<class T, class D1, class D2>
    quantity<T,
            typename transform<D1, D2, plus<_1,_2> >::type
    >
    operator*(const quantity<T, D1> &x, const quantity<T, D2> &y) {
        using R = typename transform<D1, D2, plus<_1,_2> >::type;
        return quantity<T, R>(x.value() * y.value());
    };

    /// /
    template<class T, class D1, class D2>
    quantity<T,
            typename transform<D1, D2, minus<_1,_2> >::type
    >
    operator/(const quantity<T, D1> &x, const quantity<T, D2> &y)
    {
        using R = typename transform<D1, D2, minus<_1,_2> >::type;
        return quantity<T, R>(x.value() / y.value());
    };


    TEST(chapter3, dimension) {
        quantity<float, mass> m1(0.5f);
        quantity<float, mass> m2(0.3f);
        quantity<float, acceleration> a(10.0f);
        quantity<float, force> f = m1*a;
        f = m1*a + m1*a;
        EXPECT_EQ(0.8f,(m1 + m2).value());
        EXPECT_EQ(0.15f,(m1 * m2).value());
        EXPECT_EQ(5.0f,(m1 * a).value());
        EXPECT_EQ(a.value()*2,(f / m1).value());
    }

}
#endif //TEMPLATECPP_DIMENSION_HPP
