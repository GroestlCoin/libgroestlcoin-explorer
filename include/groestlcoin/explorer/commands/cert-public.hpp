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
#ifndef BX_CERT_PUBLIC_HPP
#define BX_CERT_PUBLIC_HPP

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
#define BX_CERT_PUBLIC_INVALID \
    "Certificate is not valid: %1%."
#define BX_CERT_PUBLIC_SAVE_FAIL \
    "Failed to save certificate file: %1%."

/**
 * Class to implement the cert-public command.
 */
class cert_public 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "cert-public";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return cert_public::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    BCX_API virtual const char* category()
    {
        return "MATH";
    }

    /**
     * The localizable command description.
     */
    BCX_API virtual const char* description()
    {
        return "Create a derived public Curve ZMQ certificate for use with a Libbitcoin/Obelisk server.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("PRIVATE_CERT", 1)
            .add("PUBLIC_CERT", 1);
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
            "metadata,m",
            value<std::vector<std::string>>(&option_.metadatas),
            "The set of name-value pairs to add as metadata to the new certificate, encoded as NAME:VALUE."
        )
        (
            "PRIVATE_CERT",
            value<boost::filesystem::path>(&argument_.private_cert)->required(),
            "The path to read the private certificate file."
        )
        (
            "PUBLIC_CERT",
            value<boost::filesystem::path>(&argument_.public_cert)->required(),
            "The path to write the public certificate file."
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
     * Get the value of the PRIVATE_CERT argument.
     */
    BCX_API virtual boost::filesystem::path& get_private_cert_argument()
    {
        return argument_.private_cert;
    }

    /**
     * Set the value of the PRIVATE_CERT argument.
     */
    BCX_API virtual void set_private_cert_argument(
        const boost::filesystem::path& value)
    {
        argument_.private_cert = value;
    }

    /**
     * Get the value of the PUBLIC_CERT argument.
     */
    BCX_API virtual boost::filesystem::path& get_public_cert_argument()
    {
        return argument_.public_cert;
    }

    /**
     * Set the value of the PUBLIC_CERT argument.
     */
    BCX_API virtual void set_public_cert_argument(
        const boost::filesystem::path& value)
    {
        argument_.public_cert = value;
    }

    /**
     * Get the value of the metadata options.
     */
    BCX_API virtual std::vector<std::string>& get_metadatas_option()
    {
        return option_.metadatas;
    }

    /**
     * Set the value of the metadata options.
     */
    BCX_API virtual void set_metadatas_option(
        const std::vector<std::string>& value)
    {
        option_.metadatas = value;
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
          : private_cert(),
            public_cert()
        {
        }

        boost::filesystem::path private_cert;
        boost::filesystem::path public_cert;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : metadatas()
        {
        }

        std::vector<std::string> metadatas;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libgroestlcoin

#endif
