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

#ifndef SWK_CONFIG_HPP_INCLUDED
#define SWK_CONFIG_HPP_INCLUDED

#define SWK_VERSION_MAJOR 0
#define SWK_VERSION_MINOR 1

#define SWK_USE_THREADED_MAPPER 1

//#define SWK_BLOCK_SIZE (64 * 1024 * 1024) // 64MB
#define SWK_BLOCK_SIZE 256

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct swk_info_t
{
	int version_major;
	int version_minor;
}; // struct swk_info

const swk_info_t& swk_info();

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* SWK_CONFIG_HPP_INCLUDED */

