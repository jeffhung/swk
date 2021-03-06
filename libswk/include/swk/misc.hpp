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

#ifndef SWK_MISC_HPP_INCLUDED
#define SWK_MISC_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/fs_local.hpp>
#include <boost/utility.hpp>
#pragma GCC diagnostic ignored "-Wshadow"
#include <boost/random.hpp>
#pragma GCC diagnostic warning "-Wshadow"
#include <cstdlib>
#include <cassert>

namespace swk {

/**
 * The auto_buffer class creates byte buffer which can allocate statically or
 * dynamically according to requested buffer size. If requested buffer size is
 * greater than @p StaticBytes, auto_buffer will dynamically allocate required
 * memory space for the buffer, instead of statically as a member array.
 *
 * Usually, dynamic allocation gets more overheads, but if requested size is
 * too large, we may exceed stack limit too soon. So, a smarter strategy is to
 * allocate statically if required size is small, and turn to dynamic
 * allocation if required size is big.
 *
 * @attention Since get() will get the internal buffer, we do not provide
 *            thread-safety guarantees.  It is the caller's responsibility to
 *            properly protect the buffer.
 *
 * @todo Make allocation customizable by adding Allocator template parameter.
 *
 * @tparam StaticBytes the buffer size, in number of bytes
 * @tparam Allocator   customizable allocator
 */
template < int StaticBytes = 1024 // in bytes
//       , class Allocator = std::alloc
         >
class auto_buffer : private boost::noncopyable
{
public:

	typedef char byte_type;

	/**
	 * Construct an auto_buffer object, with given required buffer size, @p
	 * nbytes bytes.
	 *
	 * @param[in] nbytes required buffer size, in number of bytes
	 */
	auto_buffer(size_t nbytes = StaticBytes)
		: pbuf_(0)
		, size_(nbytes)
	{
		pbuf_ = (nbytes > StaticBytes)
		      ? reinterpret_cast<byte_type*>(malloc(nbytes))
		      : sbuf_;
		memset(pbuf_, 0, nbytes);
		assert(pbuf_);
	}


	/**
	 * Destruct the auto_buffer object. If the memory was allocated
	 * dynamically, it will be released automatically. This provide extra
	 * exception-safety since code may throw in any point within a function,
	 * and may not be able to reach the point of releasing memory at the end
	 * of function.
	 */
	~auto_buffer()
	{
		assert(pbuf_);
		if (pbuf_ != sbuf_) {
			free(pbuf_);
			pbuf_ = 0;
		}
	}

	/**
	 * Resize the buffer to @p nbytes bytes. Like realloc(), data in original
	 * buffer will be copied to new buffer bit-wisely. That is, the contents
	 * of the memory are unchanged up to the lesser of the new and old sizes.
	 * If the new size is larger, the contents of the newly allocated portion
	 * of the memory are undefined.
	 *
	 * @param[in] nbytes required buffer size, in number of bytes
	 */
	void resize(size_t nbytes)
	{
		assert(pbuf_);
		if (nbytes > StaticBytes) {
			if (pbuf_ != sbuf_) {
				// realloc() will handle the copy
				pbuf_ = reinterpret_cast<byte_type*>(realloc(pbuf_, nbytes));
			}
			else {
				pbuf_ = reinterpret_cast<byte_type*>(malloc(nbytes));
				assert(sizeof(sbuf_) <= nbytes);
				memcpy(pbuf_, sbuf_, sizeof(sbuf_));
			}
		}
		else {
			if (pbuf_ != sbuf_) {
				assert(sizeof(sbuf_) <= nbytes);
				memcpy(sbuf_, pbuf_, sizeof(sbuf_));
				pbuf_ = sbuf_;
			}
		}
		size_ = nbytes;
	}

	/**
	 * Reset to initial size, the size specified in constructor or a default
	 * size if not given.
	 */
	void reset_size()
	{
		resize();
	}

	/**
	 * Get pointer to the actual buffer.
	 * @{
	 */
	byte_type* get()
	{
		assert(pbuf_);
		return pbuf_;
	}

	const byte_type* get() const
	{
		assert(pbuf_);
		return const_cast<const byte_type*>(pbuf_);
	}
	/** @} */

	/**
	 * Get size of the buffer, in number of bytes.
	 */
	size_t size() const
	{
		assert(pbuf_);
		return size_;
	}

private:

	byte_type* pbuf_; //!< pointer point to the actural buffer
	size_t     size_; //!< buffer size of @p pbuf_, in number of bytes
	byte_type  sbuf_[StaticBytes]; //!< static allocated buffer, used when size_ is small enough

}; // class swk::auto_buffer

/**
 * Wraps Boost.Random to make it easier to use.
 */
class boost_random
{
private:

	typedef boost::mt19937       engine_type;
	typedef boost::uniform_int<> distribution_type;

public:

	boost_random(int min, int max)
		: engine_(std::time(0))
		, distribution_(min, max)
		, generator_(engine_, distribution_)
	{
	}

	int operator()() const
	{
		return generator_();
	}

private:

	mutable engine_type engine_;
	mutable distribution_type distribution_;
	mutable boost::variate_generator<engine_type&, distribution_type> generator_;

}; // class boost_random

} // namespace swk

#endif /* SWK_MISC_HPP_INCLUDED */

