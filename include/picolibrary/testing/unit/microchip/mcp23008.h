/**
 * picolibrary
 *
 * Copyright 2020-2021, Andrew Countryman <apcountryman@gmail.com> and the picolibrary
 * contributors
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
 * \brief picolibrary::Testing::Unit::Microchip::MCP23008 interface.
 */

#ifndef PICOLIBRARY_TESTING_UNIT_MICROCHIP_MCP23008_H
#define PICOLIBRARY_TESTING_UNIT_MICROCHIP_MCP23008_H

#include <cstdint>

#include "gmock/gmock.h"
#include "picolibrary/microchip/mcp23008.h"
#include "picolibrary/testing/unit/random.h"

namespace picolibrary::Testing::Unit {

/**
 * \brief Generate a pseudo-random Microchip MCP23008 sequential operation mode.
 *
 * \return A pseudo-randomly generated Microchip MCP23008 sequential operation mode.
 */
template<>
inline auto random<Microchip::MCP23008::Sequential_Operation_Mode>()
{
    return static_cast<Microchip::MCP23008::Sequential_Operation_Mode>( random<std::uint8_t>(
        static_cast<std::uint8_t>( Microchip::MCP23008::Sequential_Operation_Mode::ENABLED ),
        static_cast<std::uint8_t>( Microchip::MCP23008::Sequential_Operation_Mode::DISABLED ) ) );
}

/**
 * \brief Generate a pseudo-random Microchip MCP23008 SDA slew rate control configuration.
 *
 * \return A pseudo-randomly generated Microchip MCP23008 SDA slew rate control
 *         configuration.
 */
template<>
inline auto random<Microchip::MCP23008::SDA_Slew_Rate_Control_Configuration>()
{
    return static_cast<Microchip::MCP23008::SDA_Slew_Rate_Control_Configuration>( random<std::uint8_t>(
        static_cast<std::uint8_t>( Microchip::MCP23008::SDA_Slew_Rate_Control_Configuration::ENABLED ),
        static_cast<std::uint8_t>( Microchip::MCP23008::SDA_Slew_Rate_Control_Configuration::DISABLED ) ) );
}

/**
 * \brief Generate a pseudo-random Microchip MCP23008 interrupt mode.
 *
 * \return A pseudo-randomly generated Microchip MCP23008 interrupt mode.
 */
template<>
inline auto random<Microchip::MCP23008::Interrupt_Mode>()
{
    return static_cast<Microchip::MCP23008::Interrupt_Mode>( random<std::uint8_t>(
        static_cast<std::uint8_t>( Microchip::MCP23008::Interrupt_Mode::PUSH_PULL_ACTIVE_LOW ),
        static_cast<std::uint8_t>( Microchip::MCP23008::Interrupt_Mode::OPEN_DRAIN ) ) );
}

} // namespace picolibrary::Testing::Unit

/**
 * \brief Microchip MCP23008 unit testing facilities.
 */
namespace picolibrary::Testing::Unit::Microchip::MCP23008 {

/**
 * \brief Microchip MCP23008 mock register cache.
 */
class Mock_Register_Cache {
  public:
    /**
     * \brief Constructor.
     */
    Mock_Register_Cache() = default;

    Mock_Register_Cache( Mock_Register_Cache && ) = delete;

    Mock_Register_Cache( Mock_Register_Cache const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Mock_Register_Cache() noexcept = default;

    auto operator=( Mock_Register_Cache && ) = delete;

    auto operator=( Mock_Register_Cache const & ) = delete;

    MOCK_METHOD( void, initialize, () );

    MOCK_METHOD( std::uint8_t, iodir, (), ( const ) );

    MOCK_METHOD( void, cache_iodir, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, ipol, (), ( const ) );

    MOCK_METHOD( void, cache_ipol, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, gpinten, (), ( const ) );

    MOCK_METHOD( void, cache_gpinten, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, defval, (), ( const ) );

    MOCK_METHOD( void, cache_defval, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, intcon, (), ( const ) );

    MOCK_METHOD( void, cache_intcon, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, iocon, (), ( const ) );

    MOCK_METHOD( void, cache_iocon, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, gppu, (), ( const ) );

    MOCK_METHOD( void, cache_gppu, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, gpio, (), ( const ) );

    MOCK_METHOD( void, cache_gpio, ( std::uint8_t ) );

    MOCK_METHOD( std::uint8_t, olat, (), ( const ) );

    MOCK_METHOD( void, cache_olat, ( std::uint8_t ) );
};

} // namespace picolibrary::Testing::Unit::Microchip::MCP23008

#endif // PICOLIBRARY_TESTING_UNIT_MICROCHIP_MCP23008_H