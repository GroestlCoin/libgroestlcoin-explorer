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
#ifndef BX_INPUT_VALIDATE_HPP
#define BX_INPUT_VALIDATE_HPP

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
#define BX_INPUT_VALIDATE_INDEX_OUT_OF_RANGE \
    "The index does not refer to an existing input."
#define BX_INPUT_VALIDATE_INDEX_VALID_ENDORSEMENT \
    "The endorsement is valid."
#define BX_INPUT_VALIDATE_INDEX_INVALID_ENDORSEMENT \
    "The endorsement is not valid."

/**
 * Class to implement the input-validate command.
 */
class input_validate 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "input-validate";
    }

    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    BCX_API static const char* formerly()
    {
        return "validsig";
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return input_validate::symbol();
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
        return "Validate a transaction input endorsement.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("EC_PUBLIC_KEY", 1)
            .add("CONTRACT", 1)
            .add("ENDORSEMENT", 1)
            .add("TRANSACTION", 1);
    }

	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        const auto raw = requires_raw_input();
        load_input(get_transaction_argument(), "TRANSACTION", variables, input, raw);
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
            "index,i",
            value<uint32_t>(&option_.index),
            "The ordinal position of the input within the transaction, defaults to zero."
        )
        (
            "EC_PUBLIC_KEY",
            value<primitives::ec_public>(&argument_.ec_public_key)->required(),
            "The Base16 EC public key to verify against."
        )
        (
            "CONTRACT",
            value<primitives::script>(&argument_.contract)->required(),
            "The previous output script used in signing. Multiple tokens must be quoted."
        )
        (
            "ENDORSEMENT",
            value<primitives::endorsement>(&argument_.endorsement)->required(),
            "The endorsement to validate."
        )
        (
            "TRANSACTION",
            value<primitives::transaction>(&argument_.transaction),
            "The Base16 transaction. If not specified the transaction is read from STDIN."
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
     * Get the value of the EC_PUBLIC_KEY argument.
     */
    BCX_API virtual primitives::ec_public& get_ec_public_key_argument()
    {
        return argument_.ec_public_key;
    }

    /**
     * Set the value of the EC_PUBLIC_KEY argument.
     */
    BCX_API virtual void set_ec_public_key_argument(
        const primitives::ec_public& value)
    {
        argument_.ec_public_key = value;
    }

    /**
     * Get the value of the CONTRACT argument.
     */
    BCX_API virtual primitives::script& get_contract_argument()
    {
        return argument_.contract;
    }

    /**
     * Set the value of the CONTRACT argument.
     */
    BCX_API virtual void set_contract_argument(
        const primitives::script& value)
    {
        argument_.contract = value;
    }

    /**
     * Get the value of the ENDORSEMENT argument.
     */
    BCX_API virtual primitives::endorsement& get_endorsement_argument()
    {
        return argument_.endorsement;
    }

    /**
     * Set the value of the ENDORSEMENT argument.
     */
    BCX_API virtual void set_endorsement_argument(
        const primitives::endorsement& value)
    {
        argument_.endorsement = value;
    }

    /**
     * Get the value of the TRANSACTION argument.
     */
    BCX_API virtual primitives::transaction& get_transaction_argument()
    {
        return argument_.transaction;
    }

    /**
     * Set the value of the TRANSACTION argument.
     */
    BCX_API virtual void set_transaction_argument(
        const primitives::transaction& value)
    {
        argument_.transaction = value;
    }

    /**
     * Get the value of the index option.
     */
    BCX_API virtual uint32_t& get_index_option()
    {
        return option_.index;
    }

    /**
     * Set the value of the index option.
     */
    BCX_API virtual void set_index_option(
        const uint32_t& value)
    {
        option_.index = value;
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
          : ec_public_key(),
            contract(),
            endorsement(),
            transaction()
        {
        }

        primitives::ec_public ec_public_key;
        primitives::script contract;
        primitives::endorsement endorsement;
        primitives::transaction transaction;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : index()
        {
        }

        uint32_t index;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libgroestlcoin

#endif
