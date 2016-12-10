#ifndef _EXTENDED_STACK_H_
#define _EXTENDED_STACK_H_

#include <vector>

////==--------------------------------------------------------------------====//
// EXTENDED STACK
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////

namespace engine {

template<class T, class Alloc = std::allocator<T> >
class ExStack {
	private:
		std::vector<T, Alloc> _st;
	public:
		ExStack() = default;
		~ExStack() = default;
		std::size_t size() const;
		bool empty() const;
		void clear(); // clear stack
		std::vector<T, Alloc>& refer(); // refer vector
		const std::vector<T, Alloc>& refer() const; // refer vector
		// access
		T fetch(const std::size_t &pos = 0) const;
		// operation
		void push(const T &data);
		bool drop(const std::size_t &items = 1);
		bool dup(const std::size_t &items = 1);
		bool swap(const std::size_t &pos_a, const std::size_t &pos_b);
		bool roll(const std::size_t &pos);
		bool rolld(const std::size_t &pos);
		bool pick(const std::size_t &pos);
		bool unpick(const std::size_t &pos);
		bool dupn(const std::size_t &items);
		bool nipn(const std::size_t &pos);
};

} // namespace engine

#include "ExStack_det.h"

#endif // ifndef _EXTENDED_STACK_H_
