/*
   Copyright (c) 2018, Andreas Fett
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ARGVCC_H
#define ARGVCC_H

#include <iosfwd>
#include <string>
#include <vector>

namespace argvcc {

// A dynamic array of char* terminated by nullptr.
// The char* elements are duplicated and managed by this class.
// Failure to allocate will throw std::bad_alloc() and leave
// the object in a state as if the allocating method was never called.

class Argv {
public:
	Argv();
	Argv(Argv const&);
	Argv & operator=(Argv const&);

	// The moved from object will only be suitable for
	// destruction or assignment.
	Argv(Argv &&) noexcept;
	Argv & operator=(Argv &&) noexcept;

	// Passing nullptr will throw std::bad_alloc().
	explicit Argv(std::initializer_list<const char *>);
	explicit Argv(std::initializer_list<std::string>);
	Argv(int, char *[]);

	~Argv() noexcept;

	// Passing nullptr will throw std::bad_alloc().
	void push_back(const char *s);
	void push_back(std::string const&);

	void append(Argv const&);

	// The terminating nullptr is implicit and not counted.
	size_t size() const noexcept;
	bool empty() const noexcept;

	// The result is suitable for passing to exec(3).
	operator char* const*() const noexcept;

	// The terminating nullptr is located at end().next().
	std::vector<char *>::const_iterator begin() const noexcept;
	std::vector<char *>::const_iterator end() const noexcept;

private:
	std::vector<char *> argv_;
};

// An empty argument will yield an empty string.
std::ostream & operator<<(std::ostream &, Argv const&);

}

#endif
