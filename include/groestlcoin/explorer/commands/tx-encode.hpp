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
#ifndef BX_TX_ENCODE_HPP
#define BX_TX_ENCODE_HPP

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
 * Various localizable strings.
 */
#define BX_TX_ENCODE_LOCKTIME_CONFLICT \
    "The specified lock time is ineffective because all sequences are set to the maximum value."

/**
 * Class to implement the tx-encode command.
 */
class tx_encode 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "tx-encode";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return tx_encode::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    BCX_API virtual const char* category()
    {
        return "TRANSACTION";
    }

    /**
     * The localizable command description.
     */
    BCX_API virtual const char* description()
    {
        return "Encode an unsigned transaction as Base16.";
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
            "lock_time,l",
            value<uint32_t>(&option_.lock_time),
            "The transaction lock time."
        )
        (
            "version,v",
            value<uint32_t>(&option_.version)->default_value(1),
            "The transaction version."
        )
        (
            "input,i",
            value<std::vector<primitives::input>>(&option_.inputs),
            "The set of transaction input points encoded as TXHASH:INDEX:SEQUENCE. TXHASH is a Base16 transaction hash. INDEX is the 32 bit input index in the context of the transaction. SEQUENCE is the optional 32 bit input sequence and defaults to the maximum value."
        )
        (
            "output,o",
            value<std::vector<primitives::output>>(&option_.outputs),
            "The set of transaction output data encoded as TARGET:SATOSHI:SEED. TARGET is an address (including stealth or pay-to-script-hash) or a Base16 script. SATOSHI is the 32 bit spend amount in satoshi. SEED is required for stealth outputs and not used otherwise. The same seed should NOT be used for multiple outputs."
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
     * Get the value of the lock_time option.
     */
    BCX_API virtual uint32_t& get_lock_time_option()
    {
        return option_.lock_time;
    }

    /**
     * Set the value of the lock_time option.
     */
    BCX_API virtual void set_lock_time_option(
        const uint32_t& value)
    {
        option_.lock_time = value;
    }

    /**
     * Get the value of the version option.
     */
    BCX_API virtual uint32_t& get_version_option()
    {
        return option_.version;
    }

    /**
     * Set the value of the version option.
     */
    BCX_API virtual void set_version_option(
        const uint32_t& value)
    {
        option_.version = value;
    }

    /**
     * Get the value of the input options.
     */
    BCX_API virtual std::vector<primitives::input>& get_inputs_option()
    {
        return option_.inputs;
    }

    /**
     * Set the value of the input options.
     */
    BCX_API virtual void set_inputs_option(
        const std::vector<primitives::input>& value)
    {
        option_.inputs = value;
    }

    /**
     * Get the value of the output options.
     */
    BCX_API virtual std::vector<primitives::output>& get_outputs_option()
    {
        return option_.outputs;
    }

    /**
     * Set the value of the output options.
     */
    BCX_API virtual void set_outputs_option(
        const std::vector<primitives::output>& value)
    {
        option_.outputs = value;
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
          : lock_time(),
            version(),
            inputs(),
            outputs()
        {
        }

        uint32_t lock_time;
        uint32_t version;
        std::vector<primitives::input> inputs;
        std::vector<primitives::output> outputs;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libgroestlcoin

#endif
