/**
 * picolibrary
 *
 * Copyright 2020 Andrew Countryman <apcountryman@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under
 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * \file
 * \brief picolibrary::Output_Stream unit test program.
 */

#include <cstdint>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "picolibrary/error.h"
#include "picolibrary/result.h"
#include "picolibrary/stream.h"
#include "picolibrary/testing/unit/error.h"
#include "picolibrary/testing/unit/random.h"
#include "picolibrary/testing/unit/stream.h"
#include "picolibrary/utility.h"

namespace {

using ::picolibrary::Error_Code;
using ::picolibrary::Generic_Error;
using ::picolibrary::Result;
using ::picolibrary::Void;
using ::picolibrary::Testing::Unit::Mock_Error;
using ::picolibrary::Testing::Unit::Mock_Output_Stream;
using ::picolibrary::Testing::Unit::random;
using ::picolibrary::Testing::Unit::random_container;
using ::testing::A;
using ::testing::Eq;
using ::testing::Return;
using ::testing::SafeMatcherCast;

} // namespace

/**
 * \brief Verify picolibrary::Output_Stream::put( char ) properly handles the presence of
 *        an I/O error and/or a fatal error.
 */
TEST( putChar, errorPresent )
{
    auto stream = Mock_Output_Stream{};

    stream.report_random_error();

    EXPECT_CALL( stream.buffer(), put( A<char>() ) ).Times( 0 );

    auto const result = stream.put( random<char>() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), Generic_Error::IO_STREAM_DEGRADED );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char ) properly handles a put error.
 */
TEST( putChar, putError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), put( A<char>() ) ).WillOnce( Return( error ) );

    auto const result = stream.put( random<char>() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char ) works properly.
 */
TEST( putChar, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const character = random<char>();

    EXPECT_CALL( stream.buffer(), put( SafeMatcherCast<char>( Eq( character ) ) ) )
        .WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.put( character ).is_error() );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char const *, char const * ) properly
 *        handles the presence of an I/O error and/or a fatal error.
 */
TEST( putCharBlock, errorPresent )
{
    auto stream = Mock_Output_Stream{};

    stream.report_random_error();

    EXPECT_CALL( stream.buffer(), put( A<std::string>() ) ).Times( 0 );

    auto const string = random_container<std::string>();
    auto const result = stream.put( &*string.begin(), &*string.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), Generic_Error::IO_STREAM_DEGRADED );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char const *, char const * ) properly
 *        handles a put error.
 */
TEST( putCharBlock, putError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), put( A<std::string>() ) ).WillOnce( Return( error ) );

    auto const string = random_container<std::string>();
    auto const result = stream.put( &*string.begin(), &*string.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char const *, char const * ) works
 *        properly.
 */
TEST( putCharBlock, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const string = random_container<std::string>();

    EXPECT_CALL( stream.buffer(), put( string ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.put( &*string.begin(), &*string.end() ).is_error() );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char const * ) properly handles the
 *        presence of an I/O error and/or a fatal error.
 */
TEST( putNullTerminatedString, errorPresent )
{
    auto stream = Mock_Output_Stream{};

    stream.report_random_error();

    EXPECT_CALL( stream.buffer(), put( A<std::string>() ) ).Times( 0 );

    auto const result = stream.put( random_container<std::string>().c_str() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), Generic_Error::IO_STREAM_DEGRADED );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char const * ) properly handles a put
 *        error.
 */
TEST( putNullTerminatedString, putError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), put( A<std::string>() ) ).WillOnce( Return( error ) );

    auto const result = stream.put( random_container<std::string>().c_str() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( char const * ) works properly.
 */
TEST( putNullTerminatedString, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const string = random_container<std::string>();

    EXPECT_CALL( stream.buffer(), put( string ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.put( string.c_str() ).is_error() );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::uint8_t ) properly handles the
 *        presence of an I/O error and/or a fatal error.
 */
TEST( putUnsignedByte, errorPresent )
{
    auto stream = Mock_Output_Stream{};

    stream.report_random_error();

    EXPECT_CALL( stream.buffer(), put( A<std::uint8_t>() ) ).Times( 0 );

    auto const result = stream.put( random<std::uint8_t>() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), Generic_Error::IO_STREAM_DEGRADED );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::uint8_t ) properly handles a put
 *        error.
 */
TEST( putUnsignedByte, putError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), put( A<std::uint8_t>() ) ).WillOnce( Return( error ) );

    auto const result = stream.put( random<std::uint8_t>() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::uint8_t ) works properly.
 */
TEST( putUnsignedByte, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const value = random<std::uint8_t>();

    EXPECT_CALL( stream.buffer(), put( SafeMatcherCast<std::uint8_t>( Eq( value ) ) ) )
        .WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.put( value ).is_error() );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::uint8_t const *, std::uint8_t const
 *        * ) properly handles the presence of an I/O error and/or a fatal error.
 */
TEST( putUnsignedByteBlock, errorPresent )
{
    auto stream = Mock_Output_Stream{};

    stream.report_random_error();

    EXPECT_CALL( stream.buffer(), put( A<std::vector<std::uint8_t>>() ) ).Times( 0 );

    auto const values = random_container<std::vector<std::uint8_t>>();
    auto const result = stream.put( &*values.begin(), &*values.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), Generic_Error::IO_STREAM_DEGRADED );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::uint8_t const *, std::uint8_t const
 *        * ) properly handles a put error.
 */
TEST( putUnsignedByteBlock, putError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), put( A<std::vector<std::uint8_t>>() ) ).WillOnce( Return( error ) );

    auto const values = random_container<std::vector<std::uint8_t>>();
    auto const result = stream.put( &*values.begin(), &*values.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::uint8_t const *, std::uint8_t const
 *        * ) works properly.
 */
TEST( putUnsignedByteBlock, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const values = random_container<std::vector<std::uint8_t>>();

    EXPECT_CALL( stream.buffer(), put( values ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.put( &*values.begin(), &*values.end() ).is_error() );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::int8_t ) properly handles the
 *        presence of an I/O error and/or a fatal error.
 */
TEST( putSignedByte, errorPresent )
{
    auto stream = Mock_Output_Stream{};

    stream.report_random_error();

    EXPECT_CALL( stream.buffer(), put( A<std::int8_t>() ) ).Times( 0 );

    auto const result = stream.put( random<std::int8_t>() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), Generic_Error::IO_STREAM_DEGRADED );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::int8_t ) properly handles a put
 *        error.
 */
TEST( putSignedByte, putError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), put( A<std::int8_t>() ) ).WillOnce( Return( error ) );

    auto const result = stream.put( random<std::int8_t>() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::int8_t ) works properly.
 */
TEST( putSignedByte, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const value = random<std::int8_t>();

    EXPECT_CALL( stream.buffer(), put( SafeMatcherCast<std::int8_t>( Eq( value ) ) ) )
        .WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.put( value ).is_error() );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::int8_t const *, std::int8_t const *
 *        ) properly handles the presence of an I/O error and/or a fatal error.
 */
TEST( putSignedByteBlock, errorPresent )
{
    auto stream = Mock_Output_Stream{};

    stream.report_random_error();

    EXPECT_CALL( stream.buffer(), put( A<std::vector<std::int8_t>>() ) ).Times( 0 );

    auto const values = random_container<std::vector<std::int8_t>>();
    auto const result = stream.put( &*values.begin(), &*values.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), Generic_Error::IO_STREAM_DEGRADED );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::int8_t const *, std::int8_t const *
 *        ) properly handles a put error.
 */
TEST( putSignedByteBlock, putError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), put( A<std::vector<std::int8_t>>() ) ).WillOnce( Return( error ) );

    auto const values = random_container<std::vector<std::int8_t>>();
    auto const result = stream.put( &*values.begin(), &*values.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::put( std::int8_t const *, std::int8_t const *
 *        ) works properly.
 */
TEST( putSignedByteBlock, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const values = random_container<std::vector<std::int8_t>>();

    EXPECT_CALL( stream.buffer(), put( values ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.put( &*values.begin(), &*values.end() ).is_error() );
}

/**
 * \brief Verify picolibrary::Output_Stream::flush() properly handles a flush error.
 */
TEST( flush, flushError )
{
    auto stream = Mock_Output_Stream{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( stream.buffer(), flush() ).WillOnce( Return( error ) );

    auto const result = stream.flush();

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::Output_Stream::flush() works properly.
 */
TEST( flush, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    EXPECT_CALL( stream.buffer(), flush() ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( stream.flush().is_error() );
}

/**
 * \brief Execute the picolibrary::Output_Stream unit tests.
 *
 * \param[in] argc The number of arguments to pass to testing::InitGoogleMock().
 * \param[in] argv The array  of arguments to pass to testing::InitGoogleMock().
 *
 * \return See Google Test's RUN_ALL_TESTS().
 */
int main( int argc, char * argv[] )
{
    ::testing::InitGoogleMock( &argc, argv );

    return RUN_ALL_TESTS();
}