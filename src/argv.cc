/*
   Copyright (c) 2018, 2019 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <ostream>

#include <argvcc.h>

namespace {

char *safe_strdup(const char *s)
{
	auto tmp = ::strdup(s);
	if (tmp == nullptr ) {
		throw std::bad_alloc(); // LCOV_EXCL_LINE
	}
	return tmp;
}

template <typename Src, typename Dst, typename FN>
void argv_init(Src const& src, Dst & dst, FN fn)
{
	try {
		transform(src.begin(), src.end(), dst.begin(), fn);
	} catch (...) {
		for_each(dst.begin(), dst.end(), ::free);
		throw;
	}
}

class wrap_argv {
public:
	wrap_argv(int argc, char *argv[])
	{
		if (argc == 0 || argv == nullptr) {
			throw std::bad_alloc();
		}

		begin_ = &argv[0];
		end_ = std::next(begin_, argc);
		if (*end_ != nullptr) {
			throw std::bad_alloc();
		}
	}

	char **begin() const
	{
		return begin_;
	}

	char **end() const
	{
		return end_;
	}

private:
	char **begin_ = nullptr;
	char **end_ = nullptr;
};

}

namespace argvcc {

Argv::Argv() = default;

Argv::Argv(Argv const& o)
:
	argv_(o.argv_.size())
{
	::argv_init(o, argv_, ::safe_strdup);
}

Argv & Argv::operator=(Argv const& o)
{
	if (&o != this) {
		auto tmp = Argv(o);
		swap(argv_, tmp.argv_);
	}
	return *this;
}

Argv::Argv(Argv && o) noexcept
:
	argv_()
{
	swap(argv_, o.argv_);
}

Argv & Argv::operator=(Argv && o) noexcept
{
	swap(argv_, o.argv_);
	return *this;
}

Argv::Argv(std::initializer_list<const char *> l)
:
	argv_(l.size() + 1)
{
	::argv_init(l, argv_, [](const char *s) {
		if (s == nullptr) {
			throw std::bad_alloc();
		}
		return ::safe_strdup(s);
	});
}

Argv::Argv(std::initializer_list<std::string> l)
:
	argv_(l.size() + 1)
{
	::argv_init(l, argv_, [](std::string const& s) {
		return ::safe_strdup(s.c_str());
	});
}

Argv::Argv(int argc, char *argv[])
:
	argv_(argc + 1)
{
	auto wrap = wrap_argv(argc, argv);
	::argv_init(wrap, argv_, [](const char *s) {
		if (s == nullptr) {
			throw std::bad_alloc();
		}
		return ::safe_strdup(s);
	});
}

void Argv::push_back(std::string const& s)
{
	auto tmp = std::unique_ptr<char>(::safe_strdup(s.c_str()));
	argv_.resize(argv_.size() + 1);
	*prev(argv_.end(), 2) = tmp.release();
}

void Argv::push_back(const char *s)
{
	if (s == nullptr) {
		throw std::bad_alloc(); // LCOV_EXCL_LINE
	}
	auto tmp = std::unique_ptr<char>(::safe_strdup(s));
	argv_.resize(argv_.size() + 1);
	*prev(argv_.end(), 2) = tmp.release();
}

auto Argv::erase(const_iterator pos) -> iterator
{
	assert(pos >= begin());
	assert(pos < end());

	::free(*pos);
	return argv_.erase(pos);
}

auto Argv::erase(const_iterator first, const_iterator last) -> iterator
{
	assert(first >= begin());
	assert(first <= end());
	assert(last >= begin());
	assert(last <= end());

	for_each(first, last, ::free);
	return argv_.erase(first, last);
}

void Argv::append(Argv const& o)
{
	auto tmp = Argv(o);
	auto offs = end() - begin();
	argv_.resize(argv_.size() + tmp.size());
	copy(tmp.begin(), tmp.end(), std::begin(argv_) + offs);
	tmp.argv_.clear();
}

size_t Argv::size() const noexcept
{
	return argv_.size() - 1;
}

bool Argv::empty() const noexcept
{
	return argv_.size() == 1;
}

Argv::~Argv() noexcept
{
	for_each(argv_.begin(), argv_.end(), ::free);
}

Argv::operator char* const*() const noexcept
{
	return argv_.data();
}

auto Argv::begin() noexcept -> iterator
{
	return argv_.begin();
}

auto Argv::end() noexcept -> iterator
{
	return argv_.end() - 1;
}

auto Argv::begin() const noexcept -> const_iterator
{
	return cbegin();
}

auto Argv::end() const noexcept -> const_iterator
{
	return cend();
}

auto Argv::cbegin() const noexcept -> const_iterator
{
	return argv_.cbegin();
}

auto Argv::cend() const noexcept -> const_iterator
{
	return argv_.cend() - 1;
}

std::ostream & operator<<(std::ostream & os, Argv const& argv)
{
	std::string sep;
	for (auto s: argv) {
		os << sep << s;
		sep = " ";
	}
	return os;
}

}
