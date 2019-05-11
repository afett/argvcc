/*
   Copyright (c) 2018 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include <stdlib.h>
#include <algorithm>
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

}

namespace argvcc {

Argv::Argv()
:
	argv_(1)
{}

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

std::vector<char *>::const_iterator Argv::begin() const noexcept
{
	return argv_.begin();
}

std::vector<char *>::const_iterator Argv::end() const noexcept
{
	return argv_.end() - 1;
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