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




// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_sal.hxx"
#include <stdio.h>

#include <rtl/process.h>
#include <rtl/bootstrap.hxx>
#include <rtl/string.hxx>
#include <rtl/byteseq.hxx>

#include <osl/process.h>

using namespace ::rtl;


int main( int argc, char *argv[] )
{
	osl_setCommandArgs (argc, argv);

	sal_Int32 nCount = rtl_getAppCommandArgCount();

#if OSL_DEBUG_LEVEL > 1
	fprintf( stdout, "rtl-commandargs (%d) real args:%i ", nCount, argc);
	for( sal_Int32 i = 0 ; i < nCount ; i ++ )
	{
		OUString data;
		rtl_getAppCommandArg( i , &(data.pData) );
		OString o = OUStringToOString( data, RTL_TEXTENCODING_ASCII_US );
		fprintf( stdout, " %s", o.getStr() );
	}
	fprintf( stdout, "\n" );
#endif

	if( nCount == 0 )
	{
		printf( "usage : testbootstrap <checkedValueOfMyBootstrapValue>\n" );
  		exit( 1 );
	}


	OUString iniName;
	Bootstrap::get(OUString(RTL_CONSTASCII_USTRINGPARAM("iniName")), iniName, OUString());

#if OSL_DEBUG_LEVEL > 1
 	if(iniName.getLength())
	{
		OString tmp_iniName = OUStringToOString(iniName, RTL_TEXTENCODING_ASCII_US);
		fprintf(stderr, "using ini: %s\n", tmp_iniName.getStr());
	}
#endif

	Bootstrap bootstrap(iniName);


	OUString name( RTL_CONSTASCII_USTRINGPARAM( "MYBOOTSTRAPTESTVALUE" ));
	OUString myDefault( RTL_CONSTASCII_USTRINGPARAM("$Default"));

	OUString value;
	sal_Bool useDefault;

    OUString aDummy;
	useDefault = bootstrap.getFrom(OUString(RTL_CONSTASCII_USTRINGPARAM("USEDEFAULT")), aDummy);

	sal_Bool result = sal_False;
	sal_Bool found  = sal_True;

	if(useDefault)
		bootstrap.getFrom(name, value, myDefault);

	else
		found = bootstrap.getFrom(name, value);

	if(found)
	{
		OUString para(OUString::createFromAscii( argv[1] ));

		result = para == value;

		if(!result)
		{
			OString para_tmp = OUStringToOString(para, RTL_TEXTENCODING_ASCII_US);
			OString value_tmp = OUStringToOString(value, RTL_TEXTENCODING_ASCII_US);

			fprintf(stderr, "para(%s) != value(%s)\n", para_tmp.getStr(), value_tmp.getStr());
		}
	}
	else
		fprintf(stderr, "bootstrap parameter couldn't be found\n");

	// test the default case
	name = OUString( RTL_CONSTASCII_USTRINGPARAM( "no_one_has_set_this_name" ) );
  	OSL_ASSERT( ! bootstrap.getFrom( name, value ) );
	result = result && !bootstrap.getFrom( name, value );

	myDefault = OUString( RTL_CONSTASCII_USTRINGPARAM( "1" ) );
	OUString myDefault2 = OUString( RTL_CONSTASCII_USTRINGPARAM( "2" ) );

	bootstrap.getFrom( name, value, myDefault );
  	OSL_ASSERT( value == myDefault );
	result = result && (value == myDefault);

	bootstrap.getFrom( name, value, myDefault2 );
  	OSL_ASSERT( value == myDefault2 );
	result = result && (value == myDefault2);

	return result;
}
