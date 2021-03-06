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
#include <groestlcoin/explorer/primitives/wif.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>

using namespace po;

namespace libgroestlcoin {
namespace explorer {
namespace primitives {

wif::wif()
    : compressed_(true), value_()
{
}

wif::wif(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

wif::wif(const ec_secret& value, bool compressed=true)
    : compressed_(compressed), value_(value)
{
}

wif::wif(const hd_private_key& value)
    : wif(value.private_key())
{
}

wif::wif(const wif& other)
    : compressed_(other.compressed_), value_(other.value_)
{
}

bool wif::get_compressed() const
{
    return compressed_;
}

wif::operator const ec_secret&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, wif& argument)
{
    std::string base58;
    input >> base58;

    auto value = wif_to_secret(base58);
    if (!verify_private_key(value))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(base58));
    }

    argument.compressed_ = is_wif_compressed(base58);
    std::copy(value.begin(), value.end(), argument.value_.begin());
    return input;
}

std::ostream& operator<<(std::ostream& output, const wif& argument)
{
    output << secret_to_wif(argument.value_, argument.compressed_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libgroestlcoin
