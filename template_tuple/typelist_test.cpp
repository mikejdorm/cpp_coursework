#include"typelist.h"
#include<iostream>
#include <type_traits> 

using namespace std;
using namespace cspp51044;


struct A {};
struct B : public A {};
struct C : public A {};
struct D : public B {};

int main()
{
  cout << "Printing a typelist:" << endl
       << type_name<typelist<int, float, ostream>>() << endl << endl;

  cout << "prepend<A, cspp51044::typelist<int, float, ostream>>>::type" << "\n  is " 
       << type_name<prepend<A, typelist<int, float, ostream>>::type>() 
	  << endl << endl;

  cout << "Topologically sorting a typelist to have most derived in front" << endl;
  cout << "derived_to_front<cspp51044::typelist<A,B,C,D>>::type \n  is "
       << type_name<derived_to_front<typelist<A,B,C,D>>::type>() << endl << endl;
       
  cout << "append<A, cspp51044::typelist<int, float, ostream>>>::type" << "\n  is " 
       << type_name<append<A, typelist<int, float, ostream>>::type>() 
	  << endl << endl;
	  	
  cout << "erase_all<spp51044::typelist<int, float, int, int, ostream, int>>>::type" << "\n  is " 
       << type_name<erase_all<typelist<int, float, int, int, ostream>, int>::type>() 
	  << endl << endl;

	  cout << "last<cspp51044::typelist<int, float, ostream>>>::type" << "\n  is " 
          << type_name<last<typelist<int, float, ostream>>::type>() 
	  << endl << endl;
	  	  
	  cout << "Remove const from typelist<A, B const, B> " << "\n is " 
			<< type_name<apply_type_trait<remove_const, typelist<A,B,C,D> >::type()
	  << endl << endl;

return 0;
}