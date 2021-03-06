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
 * \brief picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin unit test
 *        program.
 */

#include <cstdint>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "picolibrary/error.h"
#include "picolibrary/gpio.h"
#include "picolibrary/microchip/mcp23008.h"
#include "picolibrary/result.h"
#include "picolibrary/testing/unit/error.h"
#include "picolibrary/testing/unit/microchip/mcp23008.h"
#include "picolibrary/testing/unit/random.h"
#include "picolibrary/void.h"

namespace {

using ::picolibrary::Error_Code;
using ::picolibrary::Result;
using ::picolibrary::Void;
using ::picolibrary::GPIO::Initial_Pull_Up_State;
using ::picolibrary::Testing::Unit::Mock_Error;
using ::picolibrary::Testing::Unit::random;
using ::picolibrary::Testing::Unit::Microchip::MCP23008::Mock_Driver;
using ::testing::_;
using ::testing::Return;

using Internally_Pulled_Up_Input_Pin = ::picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin<Mock_Driver>;

} // namespace

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::Internally_Pulled_Up_Input_Pin()
 *        works properly.
 */
TEST( constructorDefault, worksProperly )
{
    Internally_Pulled_Up_Input_Pin{};
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::Internally_Pulled_Up_Input_Pin(
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin && ) works
 *        properly.
 */
TEST( constructorMove, worksProperly )
{
    {
        Internally_Pulled_Up_Input_Pin{ Internally_Pulled_Up_Input_Pin{} };
    }

    {
        auto       driver = Mock_Driver{};
        auto const mask   = random<std::uint8_t>();

        auto source = Internally_Pulled_Up_Input_Pin{ driver, mask };

        EXPECT_CALL( driver, disable_pull_up( _ ) ).Times( 0 );

        auto const pin = Internally_Pulled_Up_Input_Pin{ std::move( source ) };

        EXPECT_CALL( driver, disable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::~Internally_Pulled_Up_Input_Pin()
 *        properly handles an internal pull-up resistor disable error.
 */
TEST( destructor, disablePullUpError )
{
    auto driver = Mock_Driver{};

    auto const pin = Internally_Pulled_Up_Input_Pin{ driver, random<std::uint8_t>() };

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( random<Mock_Error>() ) );
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::operator=(
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin && ) properly
 *        handles an internal pull-up resistor disable error.
 */
TEST( assignmentOperatorMove, disablePullUpError )
{
    {
        auto driver = Mock_Driver{};

        auto expression = Internally_Pulled_Up_Input_Pin{};
        auto object = Internally_Pulled_Up_Input_Pin{ driver, random<std::uint8_t>() };

        EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( random<Mock_Error>() ) );

        object = std::move( expression );
    }

    {
        auto driver_expression = Mock_Driver{};
        auto driver_object     = Mock_Driver{};

        auto expression = Internally_Pulled_Up_Input_Pin{ driver_expression, random<std::uint8_t>() };
        auto object = Internally_Pulled_Up_Input_Pin{ driver_object, random<std::uint8_t>() };

        EXPECT_CALL( driver_object, disable_pull_up( _ ) ).WillOnce( Return( random<Mock_Error>() ) );

        object = std::move( expression );

        EXPECT_CALL( driver_expression, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::operator=(
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin && ) works
 *        properly.
 */
TEST( assignmentOperatorMove, worksProperly )
{
    {
        auto expression = Internally_Pulled_Up_Input_Pin{};
        auto object     = Internally_Pulled_Up_Input_Pin{};

        object = std::move( expression );
    }

    {
        auto driver = Mock_Driver{};
        auto mask   = random<std::uint8_t>();

        auto expression = Internally_Pulled_Up_Input_Pin{ driver, mask };
        auto object     = Internally_Pulled_Up_Input_Pin{};

        EXPECT_CALL( driver, disable_pull_up( _ ) ).Times( 0 );

        object = std::move( expression );

        EXPECT_CALL( driver, disable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }

    {
        auto driver = Mock_Driver{};
        auto mask   = random<std::uint8_t>();

        auto expression = Internally_Pulled_Up_Input_Pin{};
        auto object     = Internally_Pulled_Up_Input_Pin{ driver, mask };

        EXPECT_CALL( driver, disable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

        object = std::move( expression );

        EXPECT_CALL( driver, disable_pull_up( _ ) ).Times( 0 );
    }

    {
        auto       driver_expression = Mock_Driver{};
        auto const mask_expression   = random<std::uint8_t>();
        auto       driver_object     = Mock_Driver{};
        auto const mask_object       = random<std::uint8_t>();

        auto expression = Internally_Pulled_Up_Input_Pin{ driver_expression, mask_expression };
        auto object = Internally_Pulled_Up_Input_Pin{ driver_object, mask_object };

        EXPECT_CALL( driver_expression, disable_pull_up( _ ) ).Times( 0 );
        EXPECT_CALL( driver_object, disable_pull_up( mask_object ) )
            .WillOnce( Return( Result<Void, Error_Code>{} ) );

        object = std::move( expression );

        EXPECT_CALL( driver_object, disable_pull_up( _ ) ).Times( 0 );
        EXPECT_CALL( driver_expression, disable_pull_up( mask_expression ) )
            .WillOnce( Return( Result<Void, Error_Code>{} ) );
    }

    {
        auto pin = Internally_Pulled_Up_Input_Pin{};

        pin = std::move( pin );
    }

    {
        auto       driver = Mock_Driver{};
        auto const mask   = random<std::uint8_t>();

        auto pin = Internally_Pulled_Up_Input_Pin{ driver, mask };

        EXPECT_CALL( driver, disable_pull_up( _ ) ).Times( 0 );

        pin = std::move( pin );

        EXPECT_CALL( driver, disable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::initialize()
 *        handles an internal pull-up resistor enable error.
 */
TEST( initialize, enablePullUpError )
{
    auto driver = Mock_Driver{};

    auto pin = Internally_Pulled_Up_Input_Pin{ driver, random<std::uint8_t>() };

    auto const error = random<Mock_Error>();

    EXPECT_CALL( driver, enable_pull_up( _ ) ).WillOnce( Return( error ) );

    auto const result = pin.initialize( Initial_Pull_Up_State::ENABLED );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::initialize()
 *        handles an internal pull-up resistor disable error.
 */
TEST( initialize, disablePullUpError )
{
    auto driver = Mock_Driver{};

    auto pin = Internally_Pulled_Up_Input_Pin{ driver, random<std::uint8_t>() };

    auto const error = random<Mock_Error>();

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( error ) );

    auto const result = pin.initialize( Initial_Pull_Up_State::DISABLED );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::initialize()
 *        works properly.
 */
TEST( initialize, worksProperly )
{
    {
        auto       driver = Mock_Driver{};
        auto const mask   = random<std::uint8_t>();

        auto pin = Internally_Pulled_Up_Input_Pin{ driver, mask };

        EXPECT_CALL( driver, disable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

        EXPECT_FALSE( pin.initialize().is_error() );

        EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }

    {
        auto       driver = Mock_Driver{};
        auto const mask   = random<std::uint8_t>();

        auto pin = Internally_Pulled_Up_Input_Pin{ driver, mask };

        EXPECT_CALL( driver, enable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

        EXPECT_FALSE( pin.initialize( Initial_Pull_Up_State::ENABLED ).is_error() );

        EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }

    {
        auto       driver = Mock_Driver{};
        auto const mask   = random<std::uint8_t>();

        auto pin = Internally_Pulled_Up_Input_Pin{ driver, mask };

        EXPECT_CALL( driver, disable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

        EXPECT_FALSE( pin.initialize( Initial_Pull_Up_State::DISABLED ).is_error() );

        EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::enable_pull_up()
 *        properly handles an internal pull-up resistor enable error.
 */
TEST( enablePullUp, enablePullUpError )
{
    auto driver = Mock_Driver{};

    auto pin = Internally_Pulled_Up_Input_Pin{ driver, random<std::uint8_t>() };

    auto const error = random<Mock_Error>();

    EXPECT_CALL( driver, enable_pull_up( _ ) ).WillOnce( Return( error ) );

    auto const result = pin.enable_pull_up();

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::enable_pull_up()
 *        works properly.
 */
TEST( enablePullUp, worksProperly )
{
    auto       driver = Mock_Driver{};
    auto const mask   = random<std::uint8_t>();

    auto pin = Internally_Pulled_Up_Input_Pin{ driver, mask };

    EXPECT_CALL( driver, enable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( pin.enable_pull_up().is_error() );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::disable_pull_up()
 *        properly handles an internal pull-up resistor disable error.
 */
TEST( disablePullUp, disablePullUpError )
{
    auto driver = Mock_Driver{};

    auto pin = Internally_Pulled_Up_Input_Pin{ driver, random<std::uint8_t>() };

    auto const error = random<Mock_Error>();

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( error ) );

    auto const result = pin.disable_pull_up();

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify
 *        picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::disable_pull_up()
 *        works properly.
 */
TEST( disablePullUp, worksProperly )
{
    auto       driver = Mock_Driver{};
    auto const mask   = random<std::uint8_t>();

    auto pin = Internally_Pulled_Up_Input_Pin{ driver, mask };

    EXPECT_CALL( driver, disable_pull_up( mask ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    EXPECT_FALSE( pin.disable_pull_up().is_error() );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::state()
 *        properly handles a state get error.
 */
TEST( state, getStateError )
{
    auto driver = Mock_Driver{};

    auto const pin = Internally_Pulled_Up_Input_Pin{ driver, random<std::uint8_t>() };

    auto const error = random<Mock_Error>();

    EXPECT_CALL( driver, state( _ ) ).WillOnce( Return( error ) );

    auto const result = pin.state();

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin::state()
 *        works properly.
 */
TEST( state, worksProperly )
{
    auto       driver = Mock_Driver{};
    auto const mask   = random<std::uint8_t>();

    auto const pin = Internally_Pulled_Up_Input_Pin{ driver, mask };

    auto const state = random<std::uint8_t>();

    EXPECT_CALL( driver, state( mask ) ).WillOnce( Return( state ) );

    auto const result = pin.state();

    EXPECT_TRUE( result.is_value() );
    EXPECT_EQ( result.value().is_high(), static_cast<bool>( state ) );

    EXPECT_CALL( driver, disable_pull_up( _ ) ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Execute the picolibrary::Microchip::MCP23008::Internally_Pulled_Up_Input_Pin
 *        unit tests.
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
