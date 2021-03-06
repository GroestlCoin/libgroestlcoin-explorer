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
#ifndef BX_BIP39_LANGUAGE_HPP
#define BX_BIP39_LANGUAGE_HPP

#include <iostream>
#include <string>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libgroestlcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between dictionary and string.
 */
class language
{
public:

    /**
     * Default constructor.
     */
    BCX_API language();

    /**
     * Initialization constructor.
     * @param[in]  token  The value to initialize with.
     */
    BCX_API language(const std::string& token);

    /**
     * Initialization constructor.
     * @param[in]  languages  The value to initialize with.
     */
    BCX_API language(bc::dictionary_list& languages);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API language(const language& other);

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    BCX_API operator const bc::dictionary_list&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    BCX_API friend std::istream& operator>>(std::istream& input,
        language& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& output,
        const language& argument);

private:

    /**
     * The state of this object.
     */
    bc::dictionary_list value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libgroestlcoin

#endif
