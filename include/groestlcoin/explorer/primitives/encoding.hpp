/**
 * Copyright (c) 2011-2015 libgroestlcoin developers (see AUTHORS)
 *
 * This file is part of libgroestlcoin-explorer.
 *
 * libgroestlcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_ENCODING_HPP
#define BX_ENCODING_HPP

#include <iostream>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>

namespace libgroestlcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between text and encoding engine.
 */
class encoding
{
public:

    /**
     * Default constructor, sets encoding_engine::info.
     */
    BCX_API encoding();

    /**
     * Initialization constructor.
     * @param[in]  token  The value to initialize with.
     */
    BCX_API encoding(const std::string& token);

    /**
     * Initialization constructor.
     * @param[in]  engine  The value to initialize with.
     */
    BCX_API encoding(encoding_engine engine);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API encoding(const encoding& other);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    BCX_API operator encoding_engine() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    BCX_API friend std::istream& operator>>(std::istream& input,
        encoding& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& output,
        const encoding& argument);

private:

    /**
     * The state of this object's encoding engine data.
     */
    encoding_engine value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libgroestlcoin

#endif