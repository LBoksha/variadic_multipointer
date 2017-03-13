#ifndef MULTIPOINTER_H
#define MULTIPOINTER_H

#include <ostream>
#include <typeinfo>
#include <type_traits>
#include <cxxabi.h>

// m_ptr, a pointer type that can point to objects with the right base classes

template<class... Ts>
struct m_ptr
{
	m_ptr() = default;
	template<class S> m_ptr(S* t) {}
	template<class... Ss> m_ptr(m_ptr<Ss...> t) {}

	template<class S>
	S * get() const {
		// This normally never gets called; the static assertion in the derived
		// class will stop it.
		return nullptr;
	}

	template<class S>
	m_ptr & operator =(S* t)
	{
		// Derived classes set their own pointer; nothing to do here.
		return *this;
	}

	m_ptr & operator =(std::nullptr_t)
	{
		// Derived classes set their own pointer; nothing to do here.
		return *this;
	}

	template<class... Ss>
	bool set_dynamically(m_ptr<Ss...> t)
	{
		// Derived classes set their own pointer; nothing to do here.
		return true;
	}
};

template<class T, class... Ts>
struct m_ptr<T, Ts...> : public m_ptr<Ts...>
{
	static_assert(std::has_virtual_destructor<T>::value,
		"cannot use class with non-virtual destructor with m_ptr");

	T* ptr;

	m_ptr() = default;
	template<class S> m_ptr(S* t) : m_ptr<Ts...>(t), ptr(t) {}
	template<class... Ss> m_ptr(m_ptr<Ss...> t) : m_ptr<Ts...>(t), ptr(t.get<T>()) {}

	template<class S = T>
	typename std::enable_if<std::is_base_of<S, T>::value, S>::type * get() const
	{
		// We have a pointer of the right or a compatible type, so return it.
		return ptr;
	}

	template<class S>
	typename std::enable_if<!std::is_base_of<S, T>::value, S>::type * get() const
	{
		static_assert(!std::is_base_of<m_ptr<Ts...>, m_ptr<>>::value,
			"incompatible pointer type");
		// We don't serve pointers of type S, so delegate to base class.
		return m_ptr<Ts...>::template get<S>();
	}

	template<class S>
	m_ptr & operator =(S* t)
	{
		// Downcast. Every class in our inheritance chain must be able to do this
		ptr = t;
		m_ptr<Ts...>::operator =(t);
		return *this;
	}

	template<class... Ss>
	m_ptr & operator =(m_ptr<Ss...> t)
	{
		// Match the different classes
		ptr = t.get<T>();
		m_ptr<Ts...>::operator =(t);
		return *this;
	}

	m_ptr & operator =(std::nullptr_t)
	{
		// Go through inheritance chain to set everything to nullptr
		ptr = nullptr;
		m_ptr<Ts...>::operator =(nullptr);
		return *this;
	}

	template<class... Ss>
	bool set_dynamically(m_ptr<Ss...> t)
	{
		// Since one m_ptr always points to the same object, only try
		// dynamically casting the pointer in the most derived m_ptr.
		T* new_ptr = dynamic_cast<T*>(t.ptr);
		if (new_ptr && m_ptr<Ts...>::set_dynamically(t))
		{
			ptr = new_ptr;
			return true;
		}
		else
		{
			ptr = nullptr;
			m_ptr<Ts...>::operator =(nullptr);
		}
		return ptr;
	}

	T* operator ->()
	{
		// Allow directly using the pointer to the first class in
		// m_ptr<Class1, Class2, ...>
		return ptr;
	}

	operator bool() const
	{
		return ptr;
	}

	template<class... Ss>
	bool operator ==(m_ptr<Ss...> t)
	{
		// This works even if T and the type of t.ptr are incompatible; as long
		// as ptr and t.ptr point to the same object, RTTI will match them.
		return (ptr == dynamic_cast<T*>(t.ptr));
	}

	template<class... Ss>
	m_ptr<Ss...> do_dynamic_cast() const
	{
		m_ptr<Ss...> out;
		out.set_dynamically(*this);
		return out;
	}
};

template<class... Ss, class... Ts>
m_ptr<Ss...> do_dynamic_cast(m_ptr<Ts...> const& o)
{
	return o.template do_dynamic_cast<Ss...>();
}

template<class... Ts>
std::ostream& operator <<(std::ostream& t, m_ptr<Ts...> const& p)
{
	return t;
}

template<class T, class... Ts>
std::ostream& operator <<(std::ostream& t, m_ptr<T, Ts...> const& p)
{
	// Some ugly C stuff and g++ specific stuff to get the unmangled class name
	int status;
	char * class_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
	t << class_name << ":" << p.ptr << " ";
	free(class_name);
	
	// For some reason, the below version becomes recursive and never terminates:
	// operator << <Ts...>(t, p);
	// The below version does terminate correctly:
	t << static_cast<m_ptr<Ts...>>(p);
	return t;
}

#endif // #ifndef MULTIPOINTER_H
