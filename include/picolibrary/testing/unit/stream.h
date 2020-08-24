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
 * \brief picolibrary::Testing::Unit::Stream interface.
 */

#ifndef PICOLIBRARY_TESTING_UNIT_STREAM_H
#define PICOLIBRARY_TESTING_UNIT_STREAM_H

#include <cstdint>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "picolibrary/error.h"
#include "picolibrary/result.h"
#include "picolibrary/stream.h"
#include "picolibrary/testing/unit/random.h"
#include "picolibrary/utility.h"

namespace picolibrary::Testing::Unit {

/**
 * \brief Mock I/O stream device access buffer.
 */
class Mock_Stream_Buffer : public Stream_Buffer {
  public:
    /**
     * \brief Constructor.
     */
    Mock_Stream_Buffer() = default;

    /**
     * \todo #29
     */
    Mock_Stream_Buffer( Mock_Stream_Buffer && ) = delete;

    /**
     * \todo #29
     */
    Mock_Stream_Buffer( Mock_Stream_Buffer const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Mock_Stream_Buffer() noexcept = default;

    /**
     * \todo #29
     *
     * \return
     */
    auto operator=( Mock_Stream_Buffer && ) = delete;

    /**
     * \todo #29
     *
     * \return
     */
    auto operator=( Mock_Stream_Buffer const & ) = delete;

    MOCK_METHOD( (Result<Void, Error_Code>), put, (char), ( noexcept, override ) );

    MOCK_METHOD( (Result<Void, Error_Code>), put, ( std::string ) );

    /**
     * \copydoc picolibrary::Stream_Buffer::put( char const *, char const * )
     */
    virtual auto put( char const * begin, char const * end ) noexcept -> Result<Void, Error_Code> override
    {
        return put( std::string{ begin, end } );
    }

    /**
     * \copydoc picolibrary::Stream_Buffer::put( char const * )
     */
    virtual auto put( char const * string ) noexcept -> Result<Void, Error_Code> override
    {
        return put( std::string{ string } );
    }

    MOCK_METHOD( (Result<Void, Error_Code>), put, ( std::uint8_t ), ( noexcept, override ) );

    MOCK_METHOD( (Result<Void, Error_Code>), put, (std::vector<std::uint8_t>));

    /**
     * \copydoc picolibrary::Stream_Buffer::put( std::uint8_t const *, std::uint8_t const * )
     */
    virtual auto put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept
        -> Result<Void, Error_Code> override
    {
        return put( std::vector<std::uint8_t>{ begin, end } );
    }

    MOCK_METHOD( (Result<Void, Error_Code>), put, ( std::int8_t ), ( noexcept, override ) );

    MOCK_METHOD( (Result<Void, Error_Code>), put, (std::vector<std::int8_t>));

    /**
     * \copydoc picolibrary::Stream_Buffer::put( std::int8_t const *, std::int8_t const * )
     */
    virtual auto put( std::int8_t const * begin, std::int8_t const * end ) noexcept
        -> Result<Void, Error_Code> override
    {
        return put( std::vector<std::int8_t>{ begin, end } );
    }

    MOCK_METHOD( (Result<Void, Error_Code>), flush, (), ( noexcept, override ) );
};

/**
 * \brief Mock output stream.
 */
class Mock_Output_Stream : public Output_Stream {
  public:
    /**
     * \brief Constructor.
     */
    Mock_Output_Stream()
    {
        set_buffer( &m_buffer );
    }

    /**
     * \todo #29
     */
    Mock_Output_Stream( Mock_Output_Stream && ) = delete;

    /**
     * \todo #29
     */
    Mock_Output_Stream( Mock_Output_Stream const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Mock_Output_Stream() noexcept = default;

    /**
     * \todo #29
     *
     * \return
     */
    auto operator=( Mock_Output_Stream && ) = delete;

    /**
     * \todo #29
     *
     * \return
     */
    auto operator=( Mock_Output_Stream const & ) = delete;

    /**
     * \brief Get the output stream's I/O stream device access buffer.
     *
     * \return The output stream's I/O stream device access buffer.
     */
    auto & buffer() noexcept
    {
        return m_buffer;
    }

    /**
     * \brief Report an I/O error and/or a fatal error.
     */
    void report_random_error()
    {
        auto const flags = random<std::uint_fast8_t>( 0b01, 0b11 );

        if ( flags & 0b01 ) { report_io_error(); } // if

        if ( flags & 0b10 ) { report_fatal_error(); } // if
    }

  private:
    /**
     * \brief The output stream's I/O stream device access buffer.
     */
    Mock_Stream_Buffer m_buffer{};
};

} // namespace picolibrary::Testing::Unit

#endif // PICOLIBRARY_TESTING_UNIT_STREAM_H