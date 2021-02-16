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
 * \brief picolibrary::I2C interface.
 */

#ifndef PICOLIBRARY_I2C_H
#define PICOLIBRARY_I2C_H

#include <cstdint>

#include "picolibrary/error.h"
#include "picolibrary/result.h"
#include "picolibrary/utility.h"

/**
 * \brief Inter-Integrated Circuit (I2C) facilities.
 */
namespace picolibrary::I2C {

/**
 * \brief Device address.
 */
class Address {
  public:
    /**
     * \brief Device address numeric form tag.
     */
    struct Numeric {
        /**
         * \brief The minimum supported device address in numeric form.
         */
        static constexpr auto MIN = std::uint_fast8_t{ 0b000'0000 };

        /**
         * \brief The maximum supported device address in numeric form.
         */
        static constexpr auto MAX = std::uint_fast8_t{ 0b111'1111 };
    };

    /**
     * \brief Device address transmitted form tag.
     */
    struct Transmitted {
        /**
         * \brief The minimum supported device address in transmitted form.
         */
        static constexpr auto MIN = std::uint_fast8_t{ Numeric::MIN << 1 };

        /**
         * \brief The maximum supported device address in transmitted form.
         */
        static constexpr auto MAX = std::uint_fast8_t{ Numeric::MAX << 1 };
    };

    /**
     * \brief Device address numeric form tag.
     */
    static constexpr auto NUMERIC = Numeric{};

    /**
     * \brief Device address transmitted form tag.
     */
    static constexpr auto TRANSMITTED = Transmitted{};

    /**
     * \brief Get the minimum supported device address.
     *
     * \return The minimum supported device address.
     */
    static constexpr auto min() noexcept
    {
        return Address{ NUMERIC, Numeric::MIN };
    }

    /**
     * \brief Get the maximum supported device address.
     *
     * \return The maximum supported device address.
     */
    static constexpr auto max() noexcept
    {
        return Address{ NUMERIC, Numeric::MAX };
    }

    /**
     * \brief Constructor.
     */
    constexpr Address() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \warning This constructor does not validate its arguments. Use
     *          picolibrary::I2C::make_address( picolibrary::I2C::Address::Numeric,
     *          std::uint_fast8_t ) if argument validation is desired.
     *
     * \param[in] address The device address in numeric form.
     */
    constexpr Address( Numeric, std::uint_fast8_t address ) noexcept :
        m_address{ static_cast<std::uint8_t>( address << 1 ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \warning This constructor does not validate its arguments. Use
     *          picolibrary::I2C::make_address( picolibrary::I2C::Address::Transmitted,
     *          std::uint8_t ) if argument validation is desired.
     *
     * \param[in] address The device address in transmitted form.
     */
    constexpr Address( Transmitted, std::uint8_t address ) noexcept : m_address{ address }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Address( Address && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Address( Address const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Address() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Address && expression ) noexcept -> Address & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Address const & expression ) noexcept -> Address & = default;

    /**
     * \brief Get the device address in numeric form.
     *
     * \return The device address in numeric form.
     */
    constexpr auto numeric() const noexcept -> std::uint_fast8_t
    {
        return m_address >> 1;
    }

    /**
     * \brief Get the device address in transmitted form.
     *
     * \return The device address in transmitted form.
     */
    constexpr auto transmitted() const noexcept
    {
        return m_address;
    }

  private:
    /**
     * \brief The device address in transmitted form.
     */
    std::uint8_t m_address{};
};

/**
 * \brief Construct a picolibrary::I2C::Address.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] address The device address in numeric form.
 *
 * \return The device address if address is less than or equal to
 *         picolibrary::I2C::Address::Numeric::MAX.
 * \return picolibrary::Generic_Error::INVALID_ARGUMENT if address is greater than
 *         picolibrary::I2C::Address::Numeric::MAX.
 */
constexpr auto make_address( Address::Numeric, std::uint_fast8_t address ) noexcept
    -> Result<Address, Error_Code>
{
    if ( address > Address::Numeric::MAX ) {
        return Generic_Error::INVALID_ARGUMENT;
    } // if

    return Address{ Address::NUMERIC, address };
}

/**
 * \brief Construct a picolibrary::I2C::Address.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] address The device address in transmitted form.
 *
 * \return The device address if the least significant bit of address is not set.
 * \return picolibrary::Generic_Error::INVALID_ARGUMENT if the least significant bit of
 *         address is set.
 */
constexpr auto make_address( Address::Transmitted, std::uint8_t address ) noexcept
    -> Result<Address, Error_Code>
{
    if ( address & 0x01 ) {
        return Generic_Error::INVALID_ARGUMENT;
    } // if

    return Address{ Address::TRANSMITTED, address };
}

/**
 * \brief Equality operator.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is equal to rhs.
 * \return false if lhs is not equal to rhs.
 */
constexpr auto operator==( Address lhs, Address rhs ) noexcept
{
    return lhs.transmitted() == rhs.transmitted();
}

/**
 * \brief Inequality operator.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is not equal to rhs.
 * \return false if lhs is equal to rhs.
 */
constexpr auto operator!=( Address lhs, Address rhs ) noexcept
{
    return not( lhs == rhs );
}

/**
 * \brief Less than operator.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is less than rhs.
 * \return false if lhs is not less than rhs.
 */
constexpr auto operator<( Address lhs, Address rhs ) noexcept
{
    return lhs.transmitted() < rhs.transmitted();
}

/**
 * \brief Greater than operator.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is greater than rhs.
 * \return false if lhs is not greater than rhs.
 */
constexpr auto operator>( Address lhs, Address rhs ) noexcept
{
    return rhs < lhs;
}

/**
 * \brief Less than or equal to operator.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is less than or equal to rhs.
 * \return false if lhs is not less than or equal to rhs.
 */
constexpr auto operator<=( Address lhs, Address rhs ) noexcept
{
    return not( lhs > rhs );
}

/**
 * \brief Greater than or equal to operator.
 *
 * \relatedalso picolibrary::I2C::Address
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is greater than or equal to rhs.
 * \return false if lhs is not greater than or equal to rhs.
 */
constexpr auto operator>=( Address lhs, Address rhs ) noexcept
{
    return not( lhs < rhs );
}

/**
 * \brief Operation.
 */
enum class Operation : std::uint8_t {
    READ  = 0b0000'0001, ///< Read.
    WRITE = 0b0000'0000, ///< Write.
};

/**
 * \brief Response.
 */
enum class Response : std::uint_fast8_t {
    ACK  = 0b0, ///< ACK.
    NACK = 0b1, ///< NACK.
};

/**
 * \brief I2C basic controller concept.
 */
class Basic_Controller_Concept {
  public:
    Basic_Controller_Concept() = delete;

    Basic_Controller_Concept( Basic_Controller_Concept && ) = delete;

    Basic_Controller_Concept( Basic_Controller_Concept const & ) = delete;

    ~Basic_Controller_Concept() = delete;

    auto operator=( Basic_Controller_Concept && ) = delete;

    auto operator=( Basic_Controller_Concept const & ) = delete;

    /**
     * \brief Initialize the controller's hardware.
     *
     * \return Nothing if controller hardware initialization succeeded.
     * \return An error code if controller hardware initialization failed. If controller
     *         hardware initialization cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto initialize() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Transmit a start condition.
     *
     * \return Nothing if start condition transmission succeeded.
     * \return An error code if start condition transmission failed. If start condition
     *         transmission cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto start() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Transmit a repeated start condition.
     *
     * \return Nothing if repeated start condition transmission succeeded.
     * \return An error code if repeated start condition transmission failed. If repeated
     *         start condition transmission cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto repeated_start() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Transmit a stop condition.
     *
     * \return Nothing if stop condition transmission succeeded.
     * \return An error code if stop condition transmission failed. If stop condition
     *         transmission cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto stop() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Address a device.
     *
     * \param[in] address The address of the device to address.
     * \param[in] operation The operation that will be performed once the device has been
     *            addressed.
     *
     * \return Nothing if addressing the device succeeded.
     * \return picolibrary::Generic_Error::ARBITRATION_LOST if the controller lost
     *         arbitration while attempting to address the device.
     * \return picolibrary::Generic_Error::NONRESPONSIVE_DEVICE if the device did not
     *         respond when addressed.
     * \return An error code if addressing the device failed for any other reason.
     */
    auto address( Address address, Operation operation ) noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Read data from a device.
     *
     * \param[in] response The response to send after the data is read.
     *
     * \return The read data if the read succeeded.
     * \return An error code if the read failed. If the read cannot fail, return
     *         picolibrary::Result<std::uint8_t, picolibrary::Void>.
     */
    auto read( Response response ) noexcept -> Result<std::uint8_t, Error_Code>;

    /**
     * \brief Write data to a device.
     *
     * \param[in] data The data to write.
     *
     * \return Nothing if the write succeeded.
     * \return picolibrary::Generic_Error::ARBITRATION_LOST if the controller lost
     *         arbitration during the write.
     * \return picolibrary::Generic_Error::NONRESPONSIVE_DEVICE if the device did not
     *         acknowledge the write.
     * \return An error code if the write failed for any other reason.
     */
    auto write( std::uint8_t data ) noexcept -> Result<Void, Error_Code>;
};

} // namespace picolibrary::I2C

#endif // PICOLIBRARY_I2C_H
