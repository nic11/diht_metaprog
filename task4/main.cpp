#include "argspack.hpp"
#include "functor.hpp"

#include <iostream>
#include <string>
#include <type_traits>

struct Test {
    void foo(int a, int b) {
        std::cout << "test foo " << a << " " << b << "\n";
    }
};

void func0() {
    std::cout << "func()\n";
}

void func2(int a, std::string b) {
    std::cout << "func(int=" << a << ", string=" << b << ")\n";
}

int main() {

    Test test1;
    Test test2;

    ArgsPack<Test*, Test> pack(&test1, test2);
    pack.Call([](Test*, Test*) {std::cout << "hi**\n";});
    pack.Call([](Test*, Test&) {std::cout << "hi*&\n";});
    pack.Call([](Test&, Test*) {std::cout << "hi&*\n";});
    pack.Call([](Test&, Test&) {std::cout << "hi&&\n";});

    auto print_str_fnr = make_functor(
        [](const std::string& s) {
            std::cout << s << "\n";
        },
        "Hello from str-functor"
    );
    print_str_fnr.Call();

    auto foo = make_functor(&Test::foo, 1, 2);
    foo.Call(test1);

    auto bar = make_functor(&func0);
    bar.Call();

    make_functor(&func2, 3, "hello").Call();
}
