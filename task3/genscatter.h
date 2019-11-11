#pragma once


// type list

template<class T1 = void, class T2 = void>
struct TypeList;

template<class TpHead, class TpTail>
struct TypeList {
    using Head = TpHead;
    using Tail = TpTail;
};

template<>
struct TypeList<> {
};


// holder

template<class T>
struct Holder {
    T value;
};


// hierarchy

template <class TList, template <class> class Unit>
struct GenScatterHierarchy;

template <class T1, class T2, template <class> class Unit>
struct GenScatterHierarchy<TypeList<T1, T2>, Unit> :
        public GenScatterHierarchy<T1, Unit>,
        public GenScatterHierarchy<T2, Unit> {
    using TList = TypeList<T1, T2>;
    using LeftBase = GenScatterHierarchy<T1, Unit>;
    using RightBase = GenScatterHierarchy<T2, Unit>;
};

template <class AtomicType, template <class> class Unit>
struct GenScatterHierarchy : public Unit<AtomicType> {
    using LeftBase = Unit<AtomicType>;
};

template <template <class> class Unit>
struct GenScatterHierarchy<TypeList<>, Unit> {};


// get value

template<class Key, class List, template<class> class Unit>
struct GetValueImpl;

template<class Key, class Head, class Tail, template<class> class Unit>
struct GetValueImpl<Key, TypeList<Head, Tail>, Unit> {
    static Key& GetValue(GenScatterHierarchy<TypeList<Head, Tail>, Unit>& h) {
        return GetValueImpl<Key, Tail, Unit>::GetValue(h);
    }
};

template<class Key, class Tail, template<class> class Unit>
struct GetValueImpl<Key, TypeList<Key, Tail>, Unit> {
    static Key& GetValue(Unit<Key>& h) {
        return h.value;
    }
};

template<class Key, class Head, class Tail, template<class> class Unit>
Key& GetValue(GenScatterHierarchy<TypeList<Head, Tail>, Unit>& h) {
    return GetValueImpl<Key, TypeList<Head, Tail>, Unit>::GetValue(h);
}
