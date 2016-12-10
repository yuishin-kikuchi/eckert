#ifndef _EXSTACK_DET_H_
#define _EXSTACK_DET_H_

#include "ExStack.h"
#include <algorithm>

namespace engine {

////==--------------------------------------------------------------------====//
// EXTENDED STACK / SIZE
// [ description ]
// Get the size of stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
std::size_t ExStack<T, Alloc>::size() const {
	return _st.size();
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / EMPTY
// [ description ]
// Judge if stack is empty.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::empty() const {
	return _st.empty();
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / CLEAR
// [ description ]
// Clear stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
void ExStack<T, Alloc>::clear() {
	_st.clear();
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / REFER STACK
// [ description ]
// Refer stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
std::vector<T, Alloc>& ExStack<T, Alloc>::refer() {
	return _st;
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / REFER STACK (const)
// [ description ]
// Refer stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
const std::vector<T, Alloc>& ExStack<T, Alloc>::refer() const {
	return _st;
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / FETCH
// [ description ]
// Fetch last n-th item of stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
T ExStack<T, Alloc>::fetch(const std::size_t &pos) const {
	return *(_st.rbegin() + pos);
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / PUSH
// [ description ]
// Push one item to stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
void ExStack<T, Alloc>::push(const T &data) {
	_st.push_back(data);
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / DROP
// [ description ]
// Drop from stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::drop(const std::size_t &items) {
	std::size_t stack_items = _st.size();
	if (stack_items >= items) {
		for (std::size_t ucnt = items; ucnt; --ucnt) {
			_st.pop_back();
		}
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / DUPLICATE
// [ description ]
// Duplicate the last item in stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::dup(const std::size_t &items) {
	std::size_t stack_items = _st.size();
	if (0 != stack_items) {
		const auto last = *_st.rbegin();
		for (std::size_t ucnt = items; ucnt; --ucnt) {
			_st.push_back(last);
		}
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / SWAP
// [ description ]
// Swap the selected 2 items in stack.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::swap(const std::size_t &pos_a, const std::size_t &pos_b) {
	std::size_t stack_items = _st.size();
	if ((pos_a < stack_items) && (pos_b < stack_items)) {
		const auto rb = _st.rbegin();
		auto itr_a = rb + pos_a;
		auto itr_b = rb + pos_b;
		std::iter_swap(itr_a, itr_b);
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / ROLL
// [ description ]
// Roll the stack between the last and the selected point.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::roll(const std::size_t &pos) {
	std::size_t stack_items = _st.size();
	if (pos < stack_items) {
		auto start = _st.rbegin() + pos;
		auto stop = _st.rbegin();
		for (auto itr = start; itr != stop; --itr) {
			auto next = itr - 1;
			std::iter_swap(itr, next);
		}
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / ROLLD
// [ description ]
// Roll the stack between the last and the selected point.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::rolld(const std::size_t &pos) {
	std::size_t stack_items = _st.size();
	if (pos < stack_items) {
		auto start = _st.rbegin();
		auto stop = _st.rbegin() + pos;
		for (auto itr = start; itr != stop; ++itr) {
			auto next = itr + 1;
			std::iter_swap(itr, next);
		}
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / PICK
// [ description ]
// Pick the selected item and push it.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::pick(const std::size_t &pos) {
	std::size_t stack_items = _st.size();
	if (pos < stack_items) {
		auto item = _st.rbegin() + pos;
		_st.push_back(*item);
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / UNPICK
// [ description ]
// Replace the selected item by the last one and drop one.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::unpick(const std::size_t &pos) {
	std::size_t stack_items = _st.size();
	if ((0 != pos) && (pos < stack_items)) {
		auto &last = *(_st.rbegin());
		auto &item = *(_st.rbegin() + pos);
		item = last;
		_st.pop_back();
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / DUPLICATE N ITEMS
// [ description ]
// Replace the selected item by the last one and drop one.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::dupn(const std::size_t &items) {
	std::size_t stack_items = _st.size();
	if (items <= stack_items) {
		for (std::size_t pos = items; 0 != pos; --pos) {
			_st.push_back(fetch(items - 1));
		}
		return false;
	}
	else {
		return true;
	}
}

////==--------------------------------------------------------------------====//
// EXTENDED STACK / NIP N-th ITEM
// [ description ]
// Erase the selected item.
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
template<class T, class Alloc>
bool ExStack<T, Alloc>::nipn(const std::size_t &pos) {
	std::size_t stack_items = _st.size();
	if (pos < stack_items) {
		auto itr = _st.begin() + stack_items - pos - 1;
		_st.erase(itr);
		return false;
	}
	else {
		return true;
	}
}

} // namespace engine

#endif // ifndef _EXSTACK_DET_H_
