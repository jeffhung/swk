// ---------------------------------------------------------------------------
// SWK - A map/reduce framework written in C++.
// Copyright (c) 2010, Jeff Hung
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
//  - Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  - Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of the copyright holders nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ---------------------------------------------------------------------------
// $Date$
// $Rev$
// $Author$
// ---------------------------------------------------------------------------
// revid: "@(#) $Id$"
// ---------------------------------------------------------------------------

#ifndef SWK_DTOOL_HPP_INCLUDED
#define SWK_DEBUG_TOOL_HPP_INCLUDED

#include <swk/config.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

namespace swk {

inline
std::ostream& dout1(const char* file, int line, std::ostream& out = std::cerr)
{
	out << file << "(" << line << "): ";
	return out;
}

class dout2
{
public:

	dout2(const char* file, int line, std::ostream& out = std::cerr)
		: file_(file), line_(line), out_(out)
	{
	}

	~dout2()
	{
		print_();
	}

	template <class T>
	dout2& operator << (const T& x)
	{
		buf_ << x;
//		print_();
		return *this;
	}

private:

	void print_()
	{
		// TODO: mutex protection
		if (!buf_.str().empty()) {
			out_ << file_ << "(" << line_ << "): " << buf_.str() << std::endl;
			// clear buf_
			buf_.str("");
		}
	}

	const char* file_;
	int line_;
	std::ostream& out_;
	std::ostringstream buf_;

}; // class swk::dout2

template <class T>
void dvec(const char* name, const std::vector<T>& v, std::ostream& os = std::cerr)
{
	typename std::vector<T>::size_type n = 0;
	for (typename std::vector<T>::const_iterator it = v.begin();
	     it != v.end();
	     ++it) {
		os << name << "[" << n << "] == " << *it << std::endl;
		++n;
	}
}

template <class K, class V>
void dmap(const char* name, const std::map<K, V>& m, std::ostream& os = std::cerr)
{
	for (typename std::map<K, V>::const_iterator it = m.begin();
	     it != m.end();
	     ++it) {
		os << name << "[" << it->first << "] == " << it->second << std::endl;
	}
}

template <class K, class T>
void dmvec(const char* name, const std::map<K, std::vector<T> >& m, std::ostream& os = std::cerr)
{
	for (typename std::map<K, std::vector<T> >::const_iterator it = m.begin();
	     it != m.end();
	     ++it) {
		std::ostringstream tag;
		tag << name << "[" << it->first << "]";
		os << tag.str() << ":" << std::endl;
		dvec(tag.str().c_str(), it->second, os);
	}
}

} // namespace swk

#define SWK_DOUT swk::dout2(__FILE__, __LINE__)
#define SWK_DVAR(v) do { SWK_DOUT << "{" #v "} " << (v) << "~"; } while (false)
#define SWK_DVEC(v) swk::dvec(#v, (v))
#define SWK_DMAP(m) swk::dmap(#m, (m))
#define SWK_DMVEC(m) swk::dmvec(#m, (m))

#define SWK_STATIC_ASSERT(expr)

#endif /* SWK_DEBUG_TOOL_HPP_INCLUDED */

