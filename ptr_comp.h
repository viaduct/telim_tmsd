#pragma once
#include <type_traits>
#include <memory>

namespace telimtmsd {

template <typename T>
struct PtrComp final
{
	using is_transparent = std::true_type;
	struct Adapt final
	{
		T const* ptr;
		Adapt(T const* in) : ptr(in) {}
		Adapt(std::shared_ptr<T const> const& in) : ptr(in.get()) {}
		Adapt(std::unique_ptr<T const> const& in) : ptr(in.get()) {}
		Adapt(std::shared_ptr<T> const& in) : ptr(in.get()) {}
		Adapt(std::unique_ptr<T> const& in) : ptr(in.get()) {}
	};
	bool operator ()(Adapt first, Adapt second) const
	{
		return first.ptr < second.ptr;
	}
};

}
