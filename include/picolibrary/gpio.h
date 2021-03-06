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
 * \brief picolibrary::GPIO interface.
 */

#ifndef PICOLIBRARY_GPIO_H
#define PICOLIBRARY_GPIO_H

#include <cstdint>

#include "picolibrary/error.h"
#include "picolibrary/result.h"
#include "picolibrary/void.h"

/**
 * \brief General Purpose Input/Output (GPIO) facilities.
 */
namespace picolibrary::GPIO {

/**
 * \brief Initial internal pull-up resistor state.
 */
enum class Initial_Pull_Up_State : std::uint_fast8_t {
    ENABLED,  ///< Enabled.
    DISABLED, ///< Disabled.
};

/**
 * \brief Initial pin state.
 */
enum class Initial_Pin_State : std::uint_fast8_t {
    HIGH, ///< High.
    LOW,  ///< Low.
};

/**
 * \brief Pin state.
 */
class Pin_State {
  public:
    Pin_State() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] is_high The pin state.
     */
    constexpr Pin_State( bool is_high ) noexcept : m_is_high{ is_high }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Pin_State( Pin_State && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Pin_State( Pin_State const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Pin_State() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Pin_State && expression ) noexcept -> Pin_State & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Pin_State const & expression ) noexcept -> Pin_State & = default;

    /**
     * \brief Check if the pin is high.
     *
     * \return true if the pin is high.
     * \return false if the pin is low.
     */
    constexpr auto is_high() const noexcept
    {
        return m_is_high;
    }

    /**
     * \brief Check if the pin is low.
     *
     * \return true if the pin is low.
     * \return false if the pin is high.
     */
    constexpr auto is_low() const noexcept
    {
        return not m_is_high;
    }

  private:
    /**
     * \brief The pin state.
     */
    bool m_is_high;
};

/**
 * \brief Input pin concept.
 *
 * \attention picolibrary assumes that the high pin/signal state is the active pin/signal
 *            state. All input pin implementations should use this assumption. If the high
 *            pin/signal state is not the active pin/signal state,
 *            picolibrary::GPIO::Active_Low_Input_Pin can be used to invert an input pin
 *            implementation's behavior.
 */
class Input_Pin_Concept {
  public:
    /**
     * \brief Constructor.
     */
    Input_Pin_Concept() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    Input_Pin_Concept( Input_Pin_Concept && source ) noexcept = default;

    Input_Pin_Concept( Input_Pin_Concept const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Input_Pin_Concept() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( Input_Pin_Concept && expression ) noexcept -> Input_Pin_Concept & = default;

    auto operator=( Input_Pin_Concept const & ) = delete;

    /**
     * \brief Initialize the pin's hardware.
     *
     * \return Nothing if pin hardware initialization succeeded.
     * \return An error code if pin hardware initialization failed. If pin hardware
     *         initialization cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto initialize() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Get the state of the pin.
     *
     * \return High if the pin is high.
     * \return Low if the pin is low.
     * \return An error code if getting the state of the pin failed. If getting the state
     *         of the pin cannot fail, return
     *         picolibrary::Result<picolibrary::GPIO::Pin_State, picolibrary::Void>.
     */
    auto state() const noexcept -> Result<Pin_State, Error_Code>;
};

/**
 * \brief Internally pulled-up input pin concept.
 *
 * \attention picolibrary assumes that the high pin/signal state is the active pin/signal
 *            state. All input pin implementations should use this assumption. If the high
 *            pin/signal state is not the active pin/signal state,
 *            picolibrary::GPIO::Active_Low_Input_Pin can be used to invert an input pin
 *            implementation's behavior.
 */
class Internally_Pulled_Up_Input_Pin_Concept {
  public:
    /**
     * \brief Constructor.
     */
    Internally_Pulled_Up_Input_Pin_Concept() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    Internally_Pulled_Up_Input_Pin_Concept( Internally_Pulled_Up_Input_Pin_Concept && source ) noexcept = default;

    Internally_Pulled_Up_Input_Pin_Concept( Internally_Pulled_Up_Input_Pin_Concept const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Internally_Pulled_Up_Input_Pin_Concept() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( Internally_Pulled_Up_Input_Pin_Concept && expression ) noexcept
        -> Internally_Pulled_Up_Input_Pin_Concept & = default;

    auto operator=( Internally_Pulled_Up_Input_Pin_Concept const & ) = delete;

    /**
     * \brief Initialize the pin's hardware.
     *
     * \param[in] initial_pull_up_state The initial state of the pin's internal pull-up
     *            resistor.
     *
     * \return Nothing if pin hardware initialization succeeded.
     * \return An error code if pin hardware initialization failed. If pin hardware
     *         initialization cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto initialize( Initial_Pull_Up_State initial_pull_up_state = Initial_Pull_Up_State::DISABLED ) noexcept
        -> Result<Void, Error_Code>;

    /**
     * \brief Enable the pin's internal pull-up resistor.
     *
     * \return Nothing if enabling the pin's internal pull-up resistor succeeded.
     * \return An error code if enabling the pin's internal pull-up resistor failed. If
     *         enabling the pin's internal pull-up resistor cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto enable_pull_up() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Disable the pin's internal pull-up resistor.
     *
     * \return Nothing if disabling the pin's internal pull-up resistor succeeded.
     * \return An error code if disabling the pin's internal pull-up resistor failed. If
     *         disabling the pin's internal pull-up resistor cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto disable_pull_up() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Get the state of the pin.
     *
     * \return High if the pin is high.
     * \return Low if the pin is low.
     * \return An error code if getting the state of the pin failed. If getting the state
     *         of the pin cannot fail, return
     *         picolibrary::Result<picolibrary::GPIO::Pin_State, picolibrary::Void>.
     */
    auto state() const noexcept -> Result<Pin_State, Error_Code>;
};

/**
 * \brief Output pin concept.
 *
 * \attention picolibrary assumes that the high pin/signal state is the active pin/signal
 *            state. All output pin implementations should use this assumption. If the
 *            high pin/signal state is not the active pin/signal state,
 *            picolibrary::GPIO::Active_Low_Output_Pin can be used to invert an output pin
 *            implementation's behavior.
 */
class Output_Pin_Concept {
  public:
    /**
     * \brief Constructor.
     */
    Output_Pin_Concept() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    Output_Pin_Concept( Output_Pin_Concept && source ) noexcept = default;

    Output_Pin_Concept( Output_Pin_Concept const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Output_Pin_Concept() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( Output_Pin_Concept && expression ) noexcept -> Output_Pin_Concept & = default;

    auto operator=( Output_Pin_Concept const & ) = delete;

    /**
     * \brief Initialize the pin's hardware.
     *
     * \param[in] initial_pin_state The initial state of the pin.
     *
     * \return Nothing if pin hardware initialization succeeded.
     * \return An error code if pin hardware initialization failed. If pin hardware
     *         initialization cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto initialize( Initial_Pin_State initial_pin_state = Initial_Pin_State::LOW ) noexcept
        -> Result<Void, Error_Code>;

    /**
     * \brief Transition the pin to the high state.
     *
     * \return Nothing if transitioning the pin to the high state succeeded.
     * \return An error code if transitioning the pin to the high state failed. If
     *         transitioning the pin to the high state cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto transition_to_high() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Transition the pin to the low state.
     *
     * \return Nothing if transitioning the pin to the low state succeeded.
     * \return An error code if transitioning the pin to the low state failed. If
     *         transitioning the pin to the low state cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto transition_to_low() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Toggle the pin state.
     *
     * \return Nothing if toggling the pin state succeeded.
     * \return An error code if toggling the pin state failed. If toggling the pin state
     *         cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto toggle() noexcept -> Result<Void, Error_Code>;
};

/**
 * \brief Input/Output (I/O) pin concept.
 *
 * \attention picolibrary assumes that the high pin/signal state is the active pin/signal
 *            state. All I/O pin implementations should use this assumption. If the high
 *            pin/signal state is not the active pin/signal state,
 *            picolibrary::GPIO::Active_Low_IO_Pin can be used to invert an I/O pin
 *            implementation's behavior.
 */
class IO_Pin_Concept {
  public:
    /**
     * \brief Constructor.
     */
    IO_Pin_Concept() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    IO_Pin_Concept( IO_Pin_Concept && source ) noexcept = default;

    IO_Pin_Concept( IO_Pin_Concept const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~IO_Pin_Concept() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( IO_Pin_Concept && expression ) noexcept -> IO_Pin_Concept & = default;

    auto operator=( IO_Pin_Concept const & ) = delete;

    /**
     * \brief Initialize the pin's hardware.
     *
     * \param[in] initial_pin_state The initial state of the pin.
     *
     * \return Nothing if pin hardware initialization succeeded.
     * \return An error code if pin hardware initialization failed. If pin hardware
     *         initialization cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto initialize( Initial_Pin_State initial_pin_state = Initial_Pin_State::LOW ) noexcept
        -> Result<Void, Error_Code>;

    /**
     * \brief Get the state of the pin.
     *
     * \return High if the pin is high.
     * \return Low if the pin is low.
     * \return An error code if getting the state of the pin failed. If getting the state
     *         of the pin cannot fail, return
     *         picolibrary::Result<picolibrary::GPIO::Pin_State, picolibrary::Void>.
     */
    auto state() const noexcept -> Result<Pin_State, Error_Code>;

    /**
     * \brief Transition the pin to the high state.
     *
     * \return Nothing if transitioning the pin to the high state succeeded.
     * \return An error code if transitioning the pin to the high state failed. If
     *         transitioning the pin to the high state cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto transition_to_high() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Transition the pin to the low state.
     *
     * \return Nothing if transitioning the pin to the low state succeeded.
     * \return An error code if transitioning the pin to the low state failed. If
     *         transitioning the pin to the low state cannot fail, return
     *         picolibrary::Result<picolibrary::Void, picolibrary::Void>.
     */
    auto transition_to_low() noexcept -> Result<Void, Error_Code>;

    /**
     * \brief Toggle the pin state.
     *
     * \return Nothing if toggling the pin state succeeded.
     * \return An error code if toggling the pin state failed. If toggling the pin state
     *         cannot fail, return picolibrary::Result<picolibrary::Void,
     *         picolibrary::Void>.
     */
    auto toggle() noexcept -> Result<Void, Error_Code>;
};

/**
 * \brief Active low input pin adapter.
 *
 * \attention picolibrary assumes that the high pin/signal state is the active pin/signal
 *            state. All input pin implementations should use this assumption. If the high
 *            pin/signal state is not the active pin/signal state, this class can be used
 *            to invert an input pin implementation's behavior.
 *
 * \tparam Input_Pin The type of input pin being adapted.
 */
template<typename Input_Pin>
class Active_Low_Input_Pin : public Input_Pin {
  public:
    using Input_Pin::Input_Pin;

    /**
     * \brief Get the state of the pin.
     *
     * \return Low if the pin is high.
     * \return High if the pin is low.
     * \return The error reported by the underlying pin if getting the state of the
     *         underlying pin failed.
     */
    auto state() const noexcept -> decltype( Input_Pin::state() )
    {
        auto result = Input_Pin::state();

        if ( result.is_error() ) {
            return result;
        } // if

        return not result.value().is_high();
    }
};

/**
 * \brief Active low output pin adapter.
 *
 * \attention picolibrary assumes that the high pin/signal state is the active pin/signal
 *            state. All output pin implementations should use this assumption. If the
 *            high pin/signal state is not the active pin/signal state, this class can be
 *            used to invert an output pin implementation's behavior.
 *
 * \tparam Output_Pin The type of output pin being adapted.
 */
template<typename Output_Pin>
class Active_Low_Output_Pin : public Output_Pin {
  public:
    using Output_Pin::Output_Pin;

    /**
     * \brief Initialize the pin's hardware.
     *
     * \param[in] initial_pin_state The initial state of the pin.
     *
     * \return Nothing if pin hardware initialization succeeded.
     * \return The error reported by the underlying pin if pin hardware initialization
     *         failed.
     */
    auto initialize( Initial_Pin_State initial_pin_state = Initial_Pin_State::LOW ) noexcept
    {
        return Output_Pin::initialize(
            initial_pin_state == Initial_Pin_State::HIGH ? Initial_Pin_State::LOW
                                                         : Initial_Pin_State::HIGH );
    }

    /**
     * \brief Transition the pin to the low state.
     *
     * \return Nothing if transitioning the pin to the low state succeeded.
     * \return The error reported by the underlying pin if transitioning the pin to the
     *         low state failed.
     */
    auto transition_to_high() noexcept
    {
        return Output_Pin::transition_to_low();
    }

    /**
     * \brief Transition the pin to the high state.
     *
     * \return Nothing if transitioning the pin to the high state succeeded.
     * \return The error reported by the underlying pin if transitioning the pin to the
     *         high state failed.
     */
    auto transition_to_low() noexcept
    {
        return Output_Pin::transition_to_high();
    }
};

/**
 * \brief Active low I/O pin adapter.
 *
 * \attention picolibrary assumes that the high pin/signal state is the active pin/signal
 *            state. All I/O pin implementations should use this assumption. If the high
 *            pin/signal state is not the active pin/signal state, this class can be used
 *            to invert an I/O pin implementation's behavior.
 *
 * \tparam IO_Pin The type of I/O pin being adapted.
 */
template<typename IO_Pin>
class Active_Low_IO_Pin : public Active_Low_Output_Pin<Active_Low_Input_Pin<IO_Pin>> {
  public:
    using Active_Low_Output_Pin<Active_Low_Input_Pin<IO_Pin>>::Active_Low_Output_Pin;
};

} // namespace picolibrary::GPIO

#endif // PICOLIBRARY_GPIO_H
