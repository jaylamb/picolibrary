# picolibrary
#
# Copyright 2020-2021, Andrew Countryman <apcountryman@gmail.com> and the picolibrary
# contributors
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
# file except in compliance with the License. You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under
# the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the specific language governing
# permissions and limitations under the License.

# File: test/unit/picolibrary/indicator/gpio_output_pin_fixed_intensity_indicator/CMakeLists.txt
# Description: picolibrary::Indicator::GPIO_Output_Pin_Fixed_Intensity_Indicator unit
#       tests CMake rules.

# build the picolibrary::Indicator::GPIO_Output_Pin_Fixed_Intensity_Indicator unit tests
if( ${PICOLIBRARY_ENABLE_UNIT_TESTING} )
    add_executable(
        test-unit-picolibrary-indicator-gpio_output_pin_fixed_intensity_indicator
        main.cc
    )
    target_link_libraries(
        test-unit-picolibrary-indicator-gpio_output_pin_fixed_intensity_indicator
        picolibrary
    )
    add_test(
        NAME    test-unit-picolibrary-indicator-gpio_output_pin_fixed_intensity_indicator
        COMMAND test-unit-picolibrary-indicator-gpio_output_pin_fixed_intensity_indicator --gtest_color=yes
    )
endif( ${PICOLIBRARY_ENABLE_UNIT_TESTING} )
