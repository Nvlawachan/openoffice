/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#include "precompiled_sal.hxx"
#include "sal/config.h"

#include <cstddef>
#include <stdio.h> // C99 snprintf not necessarily in <cstdio>
#include <string.h> // wntmsci10 does not know <cstring> std::strcmp

#include "testshl/simpleheader.hxx"
#include "sal/types.h"

namespace {

template< typename T > void testPrintf(
    char const * result, char const * format, T argument)
{
    std::size_t const bufsize = 1000;
    char buf[bufsize];
    int n = snprintf(buf, bufsize, format, argument);
    CPPUNIT_ASSERT(n >= 0 && sal::static_int_cast< unsigned int >(n) < bufsize);
    CPPUNIT_ASSERT(strcmp(buf, result) == 0);
}

class Test: public CppUnit::TestFixture {
public:
    void test();

    CPPUNIT_TEST_SUITE(Test);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

void Test::test() {
    testPrintf("-2147483648", "%" SAL_PRIdINT32, SAL_MIN_INT32);
    testPrintf("4294967295", "%" SAL_PRIuUINT32, SAL_MAX_UINT32);
    testPrintf("ffffffff", "%" SAL_PRIxUINT32, SAL_MAX_UINT32);
    testPrintf("FFFFFFFF", "%" SAL_PRIXUINT32, SAL_MAX_UINT32);
    testPrintf("-9223372036854775808", "%" SAL_PRIdINT64, SAL_MIN_INT64);
    testPrintf("18446744073709551615", "%" SAL_PRIuUINT64, SAL_MAX_UINT64);
    testPrintf("ffffffffffffffff", "%" SAL_PRIxUINT64, SAL_MAX_UINT64);
    testPrintf("FFFFFFFFFFFFFFFF", "%" SAL_PRIXUINT64, SAL_MAX_UINT64);
    testPrintf("123", "%" SAL_PRI_SIZET "u", static_cast< std::size_t >(123));
    testPrintf(
        "-123", "%" SAL_PRI_PTRDIFFT "d", static_cast< std::ptrdiff_t >(-123));
    testPrintf("-123", "%" SAL_PRIdINTPTR, static_cast< sal_IntPtr >(-123));
    testPrintf("123", "%" SAL_PRIuUINTPTR, static_cast< sal_uIntPtr >(123));
    testPrintf("abc", "%" SAL_PRIxUINTPTR, static_cast< sal_uIntPtr >(0xabc));
    testPrintf("ABC", "%" SAL_PRIXUINTPTR, static_cast< sal_uIntPtr >(0xabc));
}

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(Test, "alltests");

}

NOADDITIONAL;
