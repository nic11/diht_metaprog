#pragma once


template<class Tp1 = void, class Tp2 = void>
struct List;

template<class Tp, class Tail>
struct List {
    const static Tail tail;
};

template<>
struct List<> {
};


template<class Tp, class TList>
struct GetIndexOf;

template<class Tp>
struct GetIndexOf<Tp, List<> > {
    const static int value = -1;
};

template<class Tp, class Tail>
struct GetIndexOf<Tp, List<Tp, Tail> > {
    const static int value = 0;
};

template<class Tp1, class Tp2, class Tail>
struct GetIndexOf<Tp1, List<Tp2, Tail> > {
    const static int value =
        GetIndexOf<Tp1, Tail>::value == -1
            ? -1
            : GetIndexOf<Tp1, Tail>::value + 1
        ;
};

template<class Tp, class List>
int getIndexOf() {
    return GetIndexOf<Tp, List>::value;
}


template<int N, int M>
struct AssertEqual;

template<int N>
struct AssertEqual<N, N> {
    const static bool value = true;
};
