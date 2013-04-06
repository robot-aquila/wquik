/**
 * ============================================================================
 * 2011/04/01
 * $Id: auto_drop.h 96 2011-08-11 17:36:58Z whirlwind $
 * Умный-указатель, ориентированный на работу с субклассами IReferenceCounted.
 * Выполняет автоматический drop управляемого объекта.
 *
 * ??? Запрещает копирование указателей.
 *
 * Данный класс предназначен для работы с указателями на объект, требующий
 * освобождения (drop) при выходе из области действия объекта-указателя.
 * ============================================================================
 */

#pragma once
#include <exception>

namespace aquila {
	namespace core {

template<class T>
class auto_drop {
public:

	explicit auto_drop(T* pointer=0) : ptr(pointer) {
	}

	virtual ~auto_drop() {
		if ( ptr != 0 ) ptr->drop();
	}

	T* operator->() {
		if ( ptr != 0 ) return ptr;
		throw std::exception("Pointer not initialized");
    }

	auto_drop& operator=(T* pointer) {
		if ( ptr == 0 ) {
			ptr = pointer;
			return *this;
		}
		throw std::exception("Pointer already assigned");
	}

	operator T*() {
		return ptr;
	}

	T* get() {
		return ptr;
	}

	auto_drop(const auto_drop& r) {
		if ( 0 != r.ptr ) {
			ptr = r.ptr;
			ptr->grab();
		}
	}

private:
	const auto_drop& operator=(const auto_drop&);

	T* ptr;
};

	} // end namespace core
} // end namespace aquila