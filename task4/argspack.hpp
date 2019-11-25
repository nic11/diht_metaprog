#pragma once

#include <utility>

namespace {

template<class T>
T* CastToPtr(T& t) {
    return &t;
}

template<class T>
T* CastToPtr(T* t) {
    return t;
}

template<class T>
T& CastToRef(T* t) {
    return *t;
}

template<class T>
T& CastToRef(T& t) {
    return t;
}

}  // namespace

template<class... Tail>
class ArgsPack;

template<>
class ArgsPack<> {
public:
    ArgsPack() {}

    template<class Delegate, class... Args>
    auto Call(const Delegate& delegate, Args&&... args)
            -> decltype(delegate(args...)) {
        return delegate(args...);
    }
};

template<class Head, class... Tail>
class ArgsPack<Head, Tail...> : ArgsPack<Tail...> {
private:
    Head m_Param;
    typedef ArgsPack<Tail...> PackTail;

public:
    template<class _Head, class... _Tail>
    ArgsPack(_Head&& head, _Tail&&... tail)
        : PackTail(std::forward<_Tail>(tail)...),
        m_Param(std::forward<Head>(head))
    {}

    template<class Delegate, class... Args>
    auto Call(const Delegate& delegate, Args&&... args)
            -> decltype(PackTail::Call(delegate, args..., CastToPtr(m_Param))) {
        return PackTail::Call(delegate, args..., CastToPtr(m_Param));
    }

    template<class Delegate, class... Args>
    auto Call(const Delegate& delegate, Args&&... args)
            -> decltype(PackTail::Call(delegate, args..., CastToRef(m_Param))) {
        return PackTail::Call(delegate, args..., CastToRef(m_Param));
    }
};
