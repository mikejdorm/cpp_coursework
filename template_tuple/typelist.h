#ifndef TYPELIST_H
#  define TYPELIST_H
#include <iostream>
#include <string>
#include <type_traits>
using std::string;
using std::ostream;
using std::is_base_of;

namespace cspp51044 {
template<typename... T> struct typelist {};

// Recursively calculate the length of a Typelist
// Use of this, and all other templates in this file,
// is shown in Typelist.cpp
template<class TL> struct Length;

template<>
struct Length<typelist<>>
{
    enum { value = 0};
};

template<class T, typename... U>
struct Length<typelist<T,  U...>>
{
    enum { value = 1 + Length<typelist<U...>>::value };
};

// Find the ith element of the Typelist
template<typename TL, int i> struct type_at;

template<class Head, typename... Tail>
struct type_at<typelist<Head, Tail...>, 0>
{
    typedef Head type;
};

template<class Head, typename... Tail, int i>
struct type_at<typelist<Head, Tail...>, i> 
  : public type_at<typelist<Tail...>, i - 1> {
};

// Which number element in the Typelist is Target?
template<class tl, class target> struct index_of;

// If it's not in Typelist, return -1
template<class target>
struct index_of<typelist<>, target>
{
    enum { value = -1 };
};

template<typename... tail, class target>
struct index_of<typelist<target, tail...>, target>
{
    enum { value = 0 };
};

template<typename Head, typename... Tail, typename Target>
struct index_of<typelist<Head, Tail...>, Target>
{
private: // Using a Compile-time temporary int
    enum { temp = index_of<typelist<Tail...>, Target>::value };
public:
    enum { value = temp == -1 ? -1 : 1 + temp };
};


// Prepend/Append a type or a Typelist to a Typelist
template<class first, class TL>
struct prepend;

template<class first, typename... T>
struct prepend<first, typelist<T...>>
{
  typedef typelist<first, T...> type;
};

// Append a type to a typelist
// HW
template<class last, class tl> 
struct append;

template<class last, typename... T>
struct append<last, typelist<T...>>
{
	typedef typelist<T..., last> type;
};


// Return the last type in a Typelist
/* HW */
template<class tl> struct last;

template<>
struct last<typelist<>>
{
    typedef typelist<> type;
};

template<class Head, typename... Tail>
struct last<typelist<Head, Tail...>>{
	 typedef typename last<typelist<Tail...>>::type type;
};
template<class Tail>
struct last<typelist<Tail>>{
	typedef Tail type;
};

// Concatenate two typelists
template<class tl1, class tl2> struct concat;

// Apply a type_trait like remove_pointer that transforms
// one type to another to each element of a Typelist.
// ApplyTypeTrait is the compile-time equivalent of std::transform
template <template<class> class T, class List> struct apply_type_trait;

	
struct apply_type_trait<T, typelist<>> {
  typedef typelist<> type;
};

template <template<class> class T, class Head, typename... Tail>
struct apply_type_trait<T, typelist<Head, Tail...> > {
  typedef 
    typelist<typename T<Head>::type, typename apply_type_trait<T, Tail...>::type>
	 type;
};


// Erase the first occurrence of a given type from a Typelist
template<class TList, class T> struct erase;

template<class T>
struct erase<typelist<>, T>
{
    typedef typelist<> type;
};

template<class T, typename... Tail>
struct erase<typelist<T, Tail...>, T>
{
    typedef typelist<Tail...> type;
};

template<class Head, typename... Tail, class T>
struct erase<typelist<Head, Tail...>, T>
  : public prepend<Head, typename erase<typelist<Tail...>, T>::type> {
};

// Erase all occurrences of a given type from a typelist
template<class TList, class T> struct erase_all;
/* HW */
template<class TList, class T> struct erase_all;

template<class T>
struct erase_all<typelist<>, T>
{
    typedef typelist<> type;
};

template<class T, typename... Tail>
struct erase_all<typelist<T, Tail...>, T>
{
    typedef typename erase_all<typelist<Tail...>, T>::type type;
};

template<class Head, typename... Tail, class T>
struct erase_all<typelist<Head, Tail...>, T>
  : public prepend<Head, typename erase_all<typelist<Tail...>, T>::type> {
};
// Remove duplicates from a typelist
// HW
template<class TL> struct no_duplicates;

// Replace the first occurrence of T in a typelist with U
template<class TL, class T, class U> struct replace;

template<typename T, typename U>
struct replace<typelist<>, T, U> {
  typedef typelist<> type;
};

template<typename... Tail, typename T, typename U>
struct replace<typelist<T, Tail...>, T, U> {
  typedef typelist<U, Tail...> type;
};

template<typename Head, typename... Tail, typename T, typename U>
struct replace<typelist<Head, Tail...>, T, U>
  : public prepend<Head, typename replace<typelist<Tail...>, T, U>::type> {
};

// Replace the all occurrences of T in a typelist with U
// HW
template<class TL, class T, class U> struct replace_all;


// Find a member of TList that is most derived from T.
template<class TL, class T> struct most_derived;

// If no class in TList inherits from T, just return T.
template<class T>
struct most_derived<typelist<>, T>
{
    typedef T type;
};

// select is the compile-time equivalent of the ?: operator
template<bool b, class T, class U> struct select_bool;
template<class T, class U> 
struct select_bool<true, T, U> {
  typedef T type;
};
template<class T, class U> 
struct select_bool<false, T, U> {
  typedef U type;
};

template<class trait, class T, class U>
struct select : public select_bool<trait::value, T, U> {
};

template<class Head, typename... Tail, class T>
struct most_derived<typelist<Head, Tail...>, T>
{
private:
    typedef typename most_derived<typelist<Tail...>, T>::type candidate;
public:
    typedef 
      typename select<is_base_of<candidate, Head>, Head, candidate>::type
      type;
};

// Does a topological sort of a typelist, moving the most derived
// class first. What this means is that if D inherits from B and
// TL is a Typelist containing both D and B, then D is guaranteed
// to appear before B in derived_to_front<TL>::type.
template<class T> struct derived_to_front;

template<>
struct derived_to_front<typelist<>>
{
  typedef typelist<> type;
};

template<class Head, typename... Tail>
struct derived_to_front<typelist<Head, Tail...> >
{
private:
    // Check if something is most derived from the Head
    typedef typename most_derived<typelist<Tail...>, Head>::type the_most_derived;
    // If so, we will swap this with the current head. If not,
    // we will just be swapping it with itself, so no harm done.

    // Firstly, lets move the current head to where the most derived is
    // This ensures that the Tail will contain all the elements except
    // the most derived
    typedef typename replace<typelist<Tail...>, the_most_derived, Head>::type temp;
    // Now, sort the tail
    typedef typename derived_to_front<temp>::type sorted_tail;
public:
    // Finally, we return a typelist with the most derived in the
    // head and the remaining elements recursively sorted.
    typedef typename prepend<the_most_derived, sorted_tail>::type type;
};
}
// Print a type's name in g++. Useful for printing typelists
#ifdef __GNUG__ // Non-portable. Only for g++
#include<typeinfo>
#include<cxxabi.h>
#include<string>
namespace cspp51044 {
template<typename T>
std::string type_name() 
{
  int status;
  return abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
}

#endif
}
#endif
