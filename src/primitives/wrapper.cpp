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
#include <groestlcoin/explorer/primitives/wrapper.hpp>

#include <iostream>
#include <boost/program_options.hpp>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>
#include <groestlcoin/explorer/primitives/base16.hpp>
#include <groestlcoin/explorer/utility.hpp>

using namespace po;

namespace libgroestlcoin {
namespace explorer {
namespace primitives {

wrapper::wrapper()
    : value_()
{
}

wrapper::wrapper(const std::string& wrapped)
{
    std::stringstream(wrapped) >> *this;
}

wrapper::wrapper(const data_chunk& wrapped)
{
    unwrap(value_, base16(wrapped));
}

wrapper::wrapper(const wrapped_data& wrapped)
    : value_(wrapped)
{
}

wrapper::wrapper(const payment_address& address)
    : wrapper(address.version(), 
    data_chunk(address.hash().begin(), address.hash().end()))
{
}

wrapper::wrapper(uint32_t version, const data_chunk& payload)
{
    value_.version = version;
    value_.payload = payload;
    value_.checksum = groestlcoin_checksum(payload);
}

wrapper::wrapper(const wrapper& other)
    : value_(other.value_)
{
}

const data_chunk wrapper::to_data() const
{
    return wrap(value_);
}

wrapper::operator const wrapped_data&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, wrapper& argument)
{
    std::string hexcode;
    input >> hexcode;

    // wrapper base16 is a private encoding in bx, used to pass between commands.
    if (!unwrap(argument.value_, base16(hexcode)))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const wrapper& argument)
{
    const auto wrapped = wrap(argument.value_);

    // wrapper base16 is a private encoding in bx, used to pass between commands.
    output << base16(wrapped);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libgroestlcoin
