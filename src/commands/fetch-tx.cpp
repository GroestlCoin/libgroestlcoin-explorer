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

#include <groestlcoin/explorer/commands/fetch-tx.hpp>

#include <iostream>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/callback_state.hpp>
#include <groestlcoin/explorer/define.hpp>
#include <groestlcoin/explorer/display.hpp>
#include <groestlcoin/explorer/obelisk_client.hpp>
#include <groestlcoin/explorer/primitives/btc256.hpp>
#include <groestlcoin/explorer/primitives/transaction.hpp>
#include <groestlcoin/explorer/prop_tree.hpp>
#include <groestlcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result fetch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& hash = get_hash_argument();
    const auto connection = get_connection(*this);

    obelisk_client client(connection);

    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    auto on_done = [&state](const tx_type& tx)
    {
        state.output(prop_tree(tx));
    };

    auto on_error = [&state](const std::error_code& error)
    {
        state.handle_error(error);
    };

    client.get_codec()->fetch_transaction(on_error, on_done, hash);
    client.resolve_callbacks();

    return state.get_result();
}

