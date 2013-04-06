/**
 * ============================================================================
 * 2011/04/01
 * $Id: auto_grab.h 96 2011-08-11 17:36:58Z whirlwind $
 * Умный-указатель, ориентированный на работу с субклассами IReferenceCounted.
 * Выполняет автоматический grab&drop управляемого объекта.
 *
 * ??? Запрещает копирование указателей.
 *
 * Данный класс предназначен для хранения указателей на объекты, требующие
 * захвата (grab) в процессе работы с экземпляром. В остальном, класс полностью
 * повторяет механизм класса auto_drop.
 * ============================================================================
 */

#pragma once
#include <exception>

namespace aquila {
	namespace core {

template<class T>
class auto_grab {
public:

	explicit auto_grab(T* pointer=0) : ptr(pointer) {
		if ( ptr != 0 ) {
			ptr->grab();
		}
	}

	virtual ~auto_grab() {
		if ( ptr != 0 ) ptr->drop();
	}

	T* operator->() {
		if ( ptr != 0 ) return ptr;
		throw std::exception("Pointer not initialized");
    }

	auto_grab& operator=(T* pointer) {
		if ( ptr == 0 ) {
			ptr = pointer;
			ptr->grab();
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

	auto_grab(const auto_grab& r) {
		if ( 0 != r.ptr ) {
			ptr = r.ptr;
			ptr->grab();
		}
	}

private:
	const auto_grab& operator=(const auto_grab&);

	T* ptr;
};

	} // end namespace core
} // end namespace aquila