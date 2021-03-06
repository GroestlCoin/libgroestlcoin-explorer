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
#include <groestlcoin/explorer/primitives/script.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>
#include <groestlcoin/explorer/primitives/base16.hpp>
#include <groestlcoin/explorer/utility.hpp>

using namespace po;

namespace libgroestlcoin {
namespace explorer {
namespace primitives {

script::script()
    : value_()
{
}

script::script(const std::string& mnemonic)
{
    std::stringstream(mnemonic) >> *this;
}

script::script(const script_type& value)
    : value_(value)
{
}

script::script(const data_chunk& value)
{
    try
    {
        value_ = parse_script(value);
    }
    catch (end_of_stream)
    {
        value_ = raw_data_script(value);
    }
}

script::script(const std::vector<std::string>& tokens)
{
    const auto mnemonic = join(tokens);
    std::stringstream(mnemonic) >> *this;
}

script::script(const script& other)
    : script(other.value_)
{
}

const data_chunk script::to_data() const
{
    return save_script(value_);
}

const std::string script::to_string() const
{
    return pretty(value_);
}

script::operator const script_type&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, script& argument)
{
    std::istreambuf_iterator<char> end;
    std::string mnemonic(std::istreambuf_iterator<char>(input), end);
    argument.value_ = unpretty(mnemonic);

    // Test for invalid result sentinel.
    if (argument.value_.operations().size() == 0 && mnemonic.length() > 0)
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(mnemonic));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const script& argument)
{
    output << pretty(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libgroestlcoin
