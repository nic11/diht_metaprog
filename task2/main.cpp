#include "indexof.h"

#include <iostream>
#include <string>

int main() {
    // Usage of class
    AssertEqual<GetIndexOf<int, List<> >::value, -1>();
    AssertEqual<GetIndexOf<int, List<int, List<> > >::value, 0>();
    AssertEqual<GetIndexOf<char, List<int, List<> > >::value, -1>();
    AssertEqual<GetIndexOf<int, List<char, List<int, List<> > > >::value, 1>();
    AssertEqual<GetIndexOf<int, List<int, List<int, List<> > > >::value, 0>();
    AssertEqual<GetIndexOf<int, List<char, List<std::string, List<unsigned, List<int, List<List<std::ios, List<> > > > > > > >::value, 3>();

    AssertEqual<GetIndexOf<std::string, List<char, List<int, List<> > > >::value, -1>();
    AssertEqual<GetIndexOf<std::string, List<char, List<std::string, List<std::string, List<> > > > >::value, 1>();

    // Usage of function
    std::cout << getIndexOf<int, List<> >() << "\n";
    std::cout << getIndexOf<int, List<int, List<> > >() << "\n";
}
