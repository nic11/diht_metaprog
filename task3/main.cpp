#include "genscatter.h"

#include <iostream>
#include <string>
#include <type_traits>

int main() {
    using Hier = GenScatterHierarchy<TypeList<int, TypeList<double, TypeList<std::string, TypeList<>>>>, Holder>;
    Hier hier;

    static_assert(std::is_same_v<decltype(GetValue<int>(hier)), int&>);
    static_assert(std::is_same_v<decltype(GetValue<double>(hier)), double&>);
    static_assert(std::is_same_v<decltype(GetValue<std::string>(hier)), std::string&>);

    GetValue<int>(hier) = 42;
    std::cout << GetValue<int>(hier) << "\n";

    GetValue<double>(hier) = 133.7;
    std::cout << GetValue<double>(hier) << "\n";

    GetValue<std::string>(hier) = "hello there";
    std::cout << GetValue<std::string>(hier) << "\n";
}
