#ifndef TUPLE2_H
#  define TUPLE2_H
// A tuple that is accessed by type
namespace cspp51044 {

// For accessing by type, we can just look for
// the appropriate holder in the inheritance hierarchy
// of the tuple
template<typename T>
struct holder {
  T value;
};

template<typename... T> class tuple;

template<> class tuple<> {
};

template<typename Head, typename... Tail>
class tuple<Head, Tail...>
  : public tuple<Tail...>, public holder<Head> {
};

template<typename T, typename... TupleTypes>
T &
get(tuple<TupleTypes...> &t)
{
  holder<T> &h = t;
  return h.value;
}
/*
template<class... Types>
	tuple<Types...> make_tuple(Types&... t)	// this definition is somewhat simplified (see standard 20.5.2.2)
	{
		//return tuple<Types...>(t...);
		return tuple<Types...>;
	}
	*/
}
#endif
