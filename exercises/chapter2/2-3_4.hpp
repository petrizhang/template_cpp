//===---- 2-3_4.hpp - Writeup for exercise 2-3 and 2-4 ---*- C++ -*-===//
//
//              Created by zeta on 16-7-30.
//
// This file is distributed under the GPLv3 Open Source
// License. See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines a class template 'type_descriptor'.
// Which takes a type parameter T, and overload the operator '<<'.
// When the instance of 'type_descriptor<T>' is streamed,
// it will output a short description about type 'T'.
// e.g.
// std::cout<<type_descriptor<int>                              -> int
// std::cout<<type_descriptor<int *>                            -> int*
// std::cout<<type_descriptor<int [6]>                          -> int[6]
// std::cout<<type_descriptor<int const volatile ***[6][6]>    -> int const volatile***[6][6]
//
// This template works well with several types:
// short, int, long ,long long and all unsigned type of them
// and bool, char, float, double.
// If you want to makes it work for your class or type,
// you need to implement the 'typename_trait' template.
// e.g.
// \code
// template<>
// struct typename_trait<YourType>{
//     static constexpr const char *type_name = "YourType's name";
// };
// \endcode
//
// Note: Currently, type_descriptor doesn't support function type.
//===----------------------------------------------------------------------===//

#ifndef TEMPLATECPP_2_3_4_HPP
#define TEMPLATECPP_2_3_4_HPP

#include <iostream>
#include <sstream>

template<class T>
struct typename_trait {
    static constexpr const char *type_name = "<unrecognized type>";
};

template<>
struct typename_trait<bool> {
    static constexpr const char *type_name = "bool";
};

template<>
struct typename_trait<char> {
    static constexpr const char *type_name = "char";
};

template<>
struct typename_trait<short> {
    static constexpr const char *type_name = "short";
};

template<>
struct typename_trait<int> {
    static constexpr const char *type_name = "int";
};

template<>
struct typename_trait<long> {
    static constexpr const char *type_name = "long";
};

template<>
struct typename_trait<long long> {
    static constexpr const char *type_name = "long long";
};

template<>
struct typename_trait<unsigned short> {
    static constexpr const char *type_name = "unsigned short";
};

template<>
struct typename_trait<unsigned int> {
    static constexpr const char *type_name = "unsigned int";
};

template<>
struct typename_trait<unsigned long> {
    static constexpr const char *type_name = "unsigned long";
};

template<>
struct typename_trait<unsigned long long> {
    static constexpr const char *type_name = "unsigned long long";
};

template<>
struct typename_trait<float> {
    static constexpr const char *type_name = "float";
};

template<>
struct typename_trait<double> {
    static constexpr const char *type_name = "double";
};

template<class T>
struct type_descriptor {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << typename_trait<T>::type_name;
        return os;
    }
};

/// Template specializition for const descriptor
template<class T>
struct type_descriptor<T const> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T>() << " const";
        return os;
    }
};

/// Template specializition for volatile descriptor
template<class T>
struct type_descriptor<T volatile> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T>() << " volatile";
        return os;
    }
};

/// Template specializition for const + volatile descriptor
template<class T>
struct type_descriptor<T const volatile> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T>() << " const volatile";
        return os;
    }
};

/// Template specializition for pointer type
template<class T>
struct type_descriptor<T *> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T>() << "*";
        return os;
    }
};

/// Template specializition for reference type
template<class T>
struct type_descriptor<T &> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T>() << "&";
        return os;
    }
};

/// Template specializition for array type
template<class T, unsigned N>
struct type_descriptor<T[N]> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T>() << "[" << N << "]";
        return os;
    }
};

template<class T, unsigned N>
struct type_descriptor<T const[N]> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T const>() << "[" << N << "]";
        return os;
    }
};

template<class T, unsigned N>
struct type_descriptor<T volatile[N]> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T volatile>() << "[" << N << "]";
        return os;
    }
};

template<class T>
struct type_descriptor<T[]> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T>() << "[]";
        return os;
    }
};

template<class T>
struct type_descriptor<T const[]> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T const>() << "[]";
        return os;
    }
};

template<class T>
struct type_descriptor<T volatile[]> {
    friend std::ostream &operator<<(std::ostream &os, const type_descriptor &a) {
        os << type_descriptor<T volatile>() << "[]";
        return os;
    }
};

/// TODO: Template specializition for function type


class UserClass {
};

template<>
struct typename_trait<UserClass> {
    static constexpr const char *type_name = "UserClass";
};

TEST(chapter2, 2_3_4) {
    std::ostringstream oss;

    /// int
    oss << type_descriptor<int>();
    EXPECT_STREQ("int", oss.str().c_str());

    /// user-defined type that has a 'TypeName' attrivute
    /// UserClass
    oss.str("");
    oss.clear();
    oss << type_descriptor<UserClass>();
    EXPECT_STREQ("UserClass", oss.str().c_str());

    /// int*
    oss.str("");
    oss.clear();
    oss << type_descriptor<int **>();
    EXPECT_STREQ("int**", oss.str().c_str());

    /// int&
    oss.str("");
    oss.clear();
    oss << type_descriptor<int &>();
    EXPECT_STREQ("int&", oss.str().c_str());

    //===--------------------------------------------------------------------===//
    // test cases for array type
    //===--------------------------------------------------------------------===//

    /// int[]
    oss.str("");
    oss.clear();
    oss << type_descriptor<int[]>();
    EXPECT_STREQ("int[]", oss.str().c_str());
    /// int const volatile***[6][6]
    oss.str("");
    oss.clear();
    oss << type_descriptor<int const volatile ***[6][6]>();
    EXPECT_STREQ("int const volatile***[6][6]", oss.str().c_str());

    //===--------------------------------------------------------------------===//
    // test cases for function type
    //===--------------------------------------------------------------------===//
    /// TODO

}

#endif //TEMPLATECPP_2_3_4_HPP
