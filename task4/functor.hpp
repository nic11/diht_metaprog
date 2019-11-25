#pragma once

#include "argspack.hpp"

namespace {

template<class TObject, class TCE>
struct SimpleDelegate {
private:
    TObject& m_Object;
    TCE m_CallableEntity;
public:
    SimpleDelegate(TObject& object, const TCE& ptr)
        : m_Object(object), m_CallableEntity(ptr)
    {}
    
    template<class... T>
    auto operator()(T... args) const
            -> decltype((m_Object.*m_CallableEntity) (args...)) {
        return (m_Object.*m_CallableEntity) (args...);
    }
};

template <class TCE>
struct CEWrapper {
private:
    TCE m_CallableEntity;
public:
    CEWrapper(const TCE& ptr) : m_CallableEntity(ptr) {}
    template<typename... T>
    auto operator()(T... args) const -> decltype(m_CallableEntity(args...)) {
        return m_CallableEntity(args...);
    }
};

}  // namespace

template<class TCE, class... Args>
struct Functor {
private:
    TCE m_CallableEntity;
    ArgsPack<Args...> m_Args;
public:
    Functor(const TCE& callable, Args&&... args)
        : m_CallableEntity(callable), m_Args(std::forward<Args>(args)...)
    {}

    template<class TObject>
    auto Call(TObject& object) 
            -> decltype(m_Args.Call(SimpleDelegate<TObject, TCE>(
                object, m_CallableEntity))) const {
        return m_Args.Call(SimpleDelegate<TObject, TCE>(object, m_CallableEntity));
    }

    template <class TCE_ = TCE>
    auto Call() -> decltype(m_Args.Call(CEWrapper<TCE_>(m_CallableEntity))) const {
        return m_Args.Call(m_CallableEntity);
    }
};

template<class TCE, class... Args>
auto make_functor(const TCE& callable, Args&&... args) {
    return Functor<TCE, Args...>(callable, std::forward<Args>(args)...);
}
