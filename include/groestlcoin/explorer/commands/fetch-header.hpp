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
#ifndef BX_FETCH_HEADER_HPP
#define BX_FETCH_HEADER_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/command.hpp>
#include <groestlcoin/explorer/define.hpp>
#include <groestlcoin/explorer/generated.hpp>
#include <groestlcoin/explorer/primitives/address.hpp>
#include <groestlcoin/explorer/primitives/base16.hpp>
#include <groestlcoin/explorer/primitives/base2.hpp>
#include <groestlcoin/explorer/primitives/base58.hpp>
#include <groestlcoin/explorer/primitives/base64.hpp>
#include <groestlcoin/explorer/primitives/base85.hpp>
#include <groestlcoin/explorer/primitives/btc.hpp>
#include <groestlcoin/explorer/primitives/btc160.hpp>
#include <groestlcoin/explorer/primitives/btc256.hpp>
#include <groestlcoin/explorer/primitives/byte.hpp>
#include <groestlcoin/explorer/primitives/cert_key.hpp>
#include <groestlcoin/explorer/primitives/ec_private.hpp>
#include <groestlcoin/explorer/primitives/ec_public.hpp>
#include <groestlcoin/explorer/primitives/encoding.hpp>
#include <groestlcoin/explorer/primitives/endorsement.hpp>
#include <groestlcoin/explorer/primitives/hashtype.hpp>
#include <groestlcoin/explorer/primitives/hd_key.hpp>
#include <groestlcoin/explorer/primitives/hd_priv.hpp>
#include <groestlcoin/explorer/primitives/hd_pub.hpp>
#include <groestlcoin/explorer/primitives/header.hpp>
#include <groestlcoin/explorer/primitives/input.hpp>
#include <groestlcoin/explorer/primitives/language.hpp>
#include <groestlcoin/explorer/primitives/output.hpp>
#include <groestlcoin/explorer/primitives/point.hpp>
#include <groestlcoin/explorer/primitives/raw.hpp>
#include <groestlcoin/explorer/primitives/script.hpp>
#include <groestlcoin/explorer/primitives/signature.hpp>
#include <groestlcoin/explorer/primitives/stealth.hpp>
#include <groestlcoin/explorer/primitives/transaction.hpp>
#include <groestlcoin/explorer/primitives/uri.hpp>
#include <groestlcoin/explorer/primitives/wif.hpp>
#include <groestlcoin/explorer/primitives/wrapper.hpp>
#include <groestlcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libgroestlcoin {
namespace explorer {
namespace commands {

/**
 * Class to implement the fetch-header command.
 */
class fetch_header 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "fetch-header";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return fetch_header::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    BCX_API virtual const char* category()
    {
        return "ONLINE";
    }

    /**
     * The localizable command description.
     */
    BCX_API virtual const char* description()
    {
        return "Get the block header from the specified hash or height. Height is ignored if both are specified. Requires a Libbitcoin/Obelisk server connection.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata();
    }

	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
    }

    /**
     * Load program option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    BCX_API virtual options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
        (
            BX_HELP_VARIABLE ",h",
            value<bool>()->zero_tokens(),
            "Get a description and instructions for this command."
        )
        (
            BX_CONFIG_VARIABLE ",c",
            value<boost::filesystem::path>(),
            "The path to the configuration settings file."
        )
        (
            "format,f",
            value<primitives::encoding>(&option_.format),
            "The output format. Options are 'info', 'json' and 'xml', defaults to 'info'."
        )
        (
            "hash,s",
            value<primitives::btc256>(&option_.hash),
            "The Base16 block hash."
        )
        (
            "height,t",
            value<uint32_t>(&option_.height),
            "The block height."
        );

        return options;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    BCX_API virtual console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the format option.
     */
    BCX_API virtual primitives::encoding& get_format_option()
    {
        return option_.format;
    }

    /**
     * Set the value of the format option.
     */
    BCX_API virtual void set_format_option(
        const primitives::encoding& value)
    {
        option_.format = value;
    }

    /**
     * Get the value of the hash option.
     */
    BCX_API virtual primitives::btc256& get_hash_option()
    {
        return option_.hash;
    }

    /**
     * Set the value of the hash option.
     */
    BCX_API virtual void set_hash_option(
        const primitives::btc256& value)
    {
        option_.hash = value;
    }

    /**
     * Get the value of the height option.
     */
    BCX_API virtual uint32_t& get_height_option()
    {
        return option_.height;
    }

    /**
     * Set the value of the height option.
     */
    BCX_API virtual void set_height_option(
        const uint32_t& value)
    {
        option_.height = value;
    }

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
        {
        }

    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : format(),
            hash(),
            height()
        {
        }

        primitives::encoding format;
        primitives::btc256 hash;
        uint32_t height;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libgroestlcoin

#endif
