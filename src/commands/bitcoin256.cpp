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

#include <groestlcoin/explorer/commands/bitcoin256.hpp>

#include <iostream>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>
#include <groestlcoin/explorer/primitives/base16.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result bitcoin256::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& data = get_base16_argument();

    const auto hash = groestlcoin_hash(data);

    output << btc256(hash) << std::endl;
    return console_result::okay;
}
