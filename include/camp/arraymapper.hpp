/****************************************************************************
**
** Copyright (C) 2009-2010 TECHNOGERMA Systems France and/or its subsidiary(-ies).
** Contact: Technogerma Systems France Information (contact@technogerma.fr)
**
** This file is part of the CAMP library.
**
** CAMP is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** CAMP is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with CAMP.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/


#ifndef CAMP_ARRAYMAPPER_HPP
#define CAMP_ARRAYMAPPER_HPP


#include <camp/config.hpp>
#include <camp/detail/yesnotype.hpp>
#include <boost/array.hpp>
#include <list>
#include <vector>


namespace camp_ext
{
/**
 * \class ArrayMapper
 *
 * \brief Template providing a mapping between C++ arrays and CAMP ArrayProperty
 *
 * ArrayMapper<T> must define the following members in order to make T fully compliant with the system:
 *
 * \li \c ElementType: type of the elements stored in the array
 * \li \c dynamic(): tells if the array is dynamic (i.e. supports insert and remove)
 * \li \c size(): retrieve the size of the array
 * \li \c get(): get the value of an element
 * \li \c set(): set the value of an element
 * \li \c insert(): insert a new element
 * \li \c remove(): remove an element
 *
 * ValueMapper is specialized for every supported type, and can be specialized
 * for any of your own array types in order to extend the system.
 *
 * By default, ValueMapper supports the following types of array:
 *
 * \li T[]
 * \li boost::array
 * \li std::vector
 * \li std::list
 *
 * Here is an example of mapping for the std::vector class:
 *
 * \code
 * namespace camp_ext
 * {
 *     template <typename T>
 *     struct ArrayMapper<std::vector<T> >
 *     {
 *         typedef T ElementType;
 *         
 *         static bool dynamic()
 *         {
 *             return true;
 *         }
 *
 *         static std::size_t size(const std::vector<T>& arr)
 *         {
 *             return arr.size();
 *         }
 *
 *         static const T& get(const std::vector<T>& arr, std::size_t index)
 *         {
 *             return arr[index];
 *         }
 *
 *         static void set(std::vector<T>& arr, std::size_t index, const T& value)
 *         {
 *             arr[index] = value;
 *         }
 *
 *         static void insert(std::vector<T>& arr, std::size_t before, const T& value)
 *         {
 *             arr.insert(arr.begin() + before, value);
 *         }
 *
 *         static void remove(std::vector<T>& arr, std::size_t index)
 *         {
 *             arr.erase(arr.begin() + index);
 *         }
 *     };
 * }
 * \endcode
 */

/*
 * Generic version -- doesn't define anything
 */
template <typename T>
struct ArrayMapper
{
};

/*
 * Specialization of ArrayMapper for built-in static arrays
 */
template <typename T, std::size_t N>
struct ArrayMapper<T[N]>
{
    typedef T ElementType;

    static bool dynamic()
    {
        return false;
    }

    static std::size_t size(T (&)[N])
    {
        return N;
    }

    static const T& get(T (& arr)[N], std::size_t index)
    {
        return arr[index];
    }

    static void set(T (& arr)[N], std::size_t index, const T& value)
    {
        arr[index] = value;
    }

    static void insert(T (&)[N], std::size_t, const T&)
    {
    }

    static void remove(T (&)[N], std::size_t)
    {
    }
};

/*
 * Specialization of ArrayMapper for boost::array
 */
template <typename T, std::size_t N>
struct ArrayMapper<boost::array<T, N> >
{
    typedef T ElementType;

    static bool dynamic()
    {
        return false;
    }

    static std::size_t size(const boost::array<T, N>&)
    {
        return N;
    }

    static const T& get(const boost::array<T, N>& arr, std::size_t index)
    {
        return arr[index];
    }

    static void set(boost::array<T, N>& arr, std::size_t index, const T& value)
    {
        arr[index] = value;
    }

    static void insert(boost::array<T, N>&, std::size_t, const T&)
    {
    }

    static void remove(boost::array<T, N>&, std::size_t)
    {
    }
};

/*
 * Specialization of ArrayMapper for std::array
 */
template <typename T, std::size_t N>
struct ArrayMapper<std::array<T, N> >
{
    typedef T ElementType;

    static bool dynamic()
    {
        return false;
    }

    static std::size_t size(const std::array<T, N>&)
    {
        return N;
    }

    static const T& get(const std::array<T, N>& arr, std::size_t index)
    {
        return arr[index];
    }

    static void set(std::array<T, N>& arr, std::size_t index, const T& value)
    {
        arr[index] = value;
    }

    static void insert(std::array<T, N>&, std::size_t, const T&)
    {
    }

    static void remove(std::array<T, N>&, std::size_t)
    {
    }
};

/*
 * Specialization of ArrayMapper for std::vector
 */
 template <typename T>
 struct ArrayMapper<std::vector<T> >
 {
    typedef T ElementType;

    static bool dynamic()
    {
        return true;
    }

    static std::size_t size(const std::vector<T>& arr)
    {
        return arr.size();
    }

    static const T& get(const std::vector<T>& arr, std::size_t index)
    {
        return arr[index];
    }

    static void set(std::vector<T>& arr, std::size_t index, const T& value)
    {
        arr[index] = value;
    }

    static void insert(std::vector<T>& arr, std::size_t before, const T& value)
    {
        arr.insert(arr.begin() + before, value);
    }

    static void remove(std::vector<T>& arr, std::size_t index)
    {
        arr.erase(arr.begin() + index);
    }
};

/*
 * Specialization of ArrayMapper for std::list
 */
 template <typename T>
 struct ArrayMapper<std::list<T> >
 {
    typedef T ElementType;

    static bool dynamic()
    {
        return true;
    }

    static std::size_t size(const std::list<T>& arr)
    {
        return arr.size();
    }

    static const T& get(const std::list<T>& arr, std::size_t index)
    {
        typename std::list<T>::const_iterator it = arr.begin();
        std::advance(it, index);
        return *it;
    }

    static void set(std::list<T>& arr, std::size_t index, const T& value)
    {
        typename std::list<T>::iterator it = arr.begin();
        std::advance(it, index);
        *it = value;
    }

    static void insert(std::list<T>& arr, std::size_t before, const T& value)
    {
        typename std::list<T>::iterator it = arr.begin();
        std::advance(it, before);
        arr.insert(it, value);
    }

    static void remove(std::list<T>& arr, std::size_t index)
    {
        typename std::list<T>::iterator it = arr.begin();
        std::advance(it, index);
        arr.erase(it);
    }
};

} // namespace camp_ext


namespace camp
{
namespace detail
{
/**
 * \brief Helper structure to check at compile time if a type is an array
 *
 * This structure check if the specialization of ArrayMapper for the
 * template parameter T exists (i.e. the ElementType member is properly defined).
 */
template <typename T>
struct IsArray
{
    template <typename U> static TypeYes check(typename U::ElementType*);
    template <typename U> static TypeNo  check(...);

    enum {value = sizeof(check<camp_ext::ArrayMapper<T> >(0)) == sizeof(TypeYes)};
};

} // namespace detail

} // namespace camp


#endif // CAMP_ARRAYMAPPER_HPP
