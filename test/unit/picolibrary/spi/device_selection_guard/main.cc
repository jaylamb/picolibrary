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
 * \brief picolibrary::SPI::Device_Selection_Guard unit test program.
 */

#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "picolibrary/error.h"
#include "picolibrary/result.h"
#include "picolibrary/spi.h"
#include "picolibrary/testing/unit/error.h"
#include "picolibrary/testing/unit/random.h"
#include "picolibrary/testing/unit/spi.h"
#include "picolibrary/utility.h"

namespace {

using ::picolibrary::Error_Code;
using ::picolibrary::Result;
using ::picolibrary::Void;
using ::picolibrary::SPI::make_device_selection_guard;
using ::picolibrary::Testing::Unit::Mock_Error;
using ::picolibrary::Testing::Unit::random;
using ::picolibrary::Testing::Unit::SPI::Mock_Device_Selector;
using ::testing::Return;

using Device_Selection_Guard = ::picolibrary::SPI::Device_Selection_Guard<Mock_Device_Selector>;

} // namespace

/**
 * \brief Verify picolibrary::SPI::Device_Selection_Guard::Device_Selection_Guard() works
 *        properly.
 */
TEST( constructorDefault, worksProperly )
{
    Device_Selection_Guard{};
}

/**
 * \brief Verify picolibrary::SPI::make_device_selection_guard() properly handles a device
 *        selection error.
 */
TEST( makeDeviceSelectionGuard, selectionError )
{
    auto device_selector = Mock_Device_Selector{};

    auto const error = random<Mock_Error>();

    EXPECT_CALL( device_selector, select() ).WillOnce( Return( error ) );

    auto const result = make_device_selection_guard( device_selector );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify picolibrary::SPI::make_device_selection_guard() works properly.
 */
TEST( makeDeviceSelectionGuard, worksProperly )
{
    auto device_selector = Mock_Device_Selector{};

    EXPECT_CALL( device_selector, select() ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    EXPECT_CALL( device_selector, deselect() ).Times( 0 );

    auto const result = make_device_selection_guard( device_selector );

    EXPECT_FALSE( result.is_error() );

    EXPECT_CALL( device_selector, deselect() ).WillOnce( Return( Result<Void, Error_Code>{} ) );
}

/**
 * \brief Verify picolibrary::SPI::Device_Selection_Guard::Device_Selection_Guard(
 *        picolibrary::SPI::Device_Selection_Guard && ) works properly.
 */
TEST( constructorMove, worksProperly )
{
    {
        Device_Selection_Guard{ Device_Selection_Guard{} };
    }

    {
        auto device_selector = Mock_Device_Selector{};

        EXPECT_CALL( device_selector, select() ).WillOnce( Return( Result<Void, Error_Code>{} ) );

        auto result = make_device_selection_guard( device_selector );

        EXPECT_FALSE( result.is_error() );

        auto const guard = Device_Selection_Guard{ std::move( result ).value() };

        EXPECT_CALL( device_selector, deselect() ).WillOnce( Return( Result<Void, Error_Code>{} ) );
    }
}

/**
 * \brief Verify picolibrary::SPI::Device_Selection_Guard::~Device_Selection_Guard()
 *        properly handles a device deselection error.
 */
TEST( destructor, deselectionError )
{
    auto device_selector = Mock_Device_Selector{};

    EXPECT_CALL( device_selector, select() ).WillOnce( Return( Result<Void, Error_Code>{} ) );

    auto const result = make_device_selection_guard( device_selector );

    EXPECT_FALSE( result.is_error() );

    EXPECT_CALL( device_selector, deselect() ).WillOnce( Return( random<Mock_Error>() ) );
}

/**
 * \brief Execute the picolibrary::SPI::Device_Selection_Guard unit tests.
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
