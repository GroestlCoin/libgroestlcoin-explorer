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
#ifndef BX_COMMAND_HPP
#define BX_COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>
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

#define BX_CONFIG_VARIABLE "config"
#define BX_HELP_VARIABLE "help"
#define BX_PROGRAM_NAME "gx"

static boost::filesystem::path default_config_path()
{
#ifdef _MSC_VER
    const auto directory = config::windows_config_directory();
#else
    // SYSCONFDIR must be defined at compile for this project, so do not move
    // this definition into libgroestlcoin.
    const auto directory = std::string(SYSCONFDIR);
#endif
    // This subdirectory and file name must stay in sync with the path for the
    // configuration file distributed via the build.
    return boost::filesystem::path(directory) / "libgroestlcoin" / "bx.cfg";
}

/**
 * Base class for definition of each Bitcoin Explorer command.
 */
class command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "not-implemented";
    }

    /**
     * The symbolic (not localizable) command name, lower case.
     * @return  Example: "fetch-transaction"
     */
    BCX_API virtual const char* name()
    {
        return symbol();
    }

    /**
     * The localizable command category name, upper case.
     * @return  Example: "ONLINE"
     */
    BCX_API virtual const char* category()
    {
        return "not-implemented";
    }

    /**
     * The localizable command description.
     * @return  Example: "Get transactions by hash."
     */
    BCX_API virtual const char* description()
    {
        return "not-implemented";
    }

    /**
     * Declare whether the command has been obsoleted.
     * @return  True if the command is obsolete
     */
    BCX_API virtual bool obsolete()
    {
        return false;
    }

    /**
     * Determines if STDIN is required to be raw.
     * @return  True if the type of the STDIN argument is primitive::raw.
     */
    BCX_API virtual bool requires_raw_input()
    {
        return false;
    }

    /**
     * Determines if STDOUT is required to be raw.
     * @return  True if the type of the STDOUT argument is primitive::raw.
     */
    BCX_API virtual bool requires_raw_output()
    {
        return false;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    BCX_API virtual console_result invoke(std::ostream& output,
        std::ostream& error)
    {
        return console_result::failure;
    }

    /**
     * Load command argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return argument_metadata_;
    }

    /**
     * Load environment variable definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    BCX_API virtual void load_environment(options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
        (
            /* This composes with the command line options. */
            BX_CONFIG_VARIABLE, 
            value<boost::filesystem::path>()
                ->composing()->default_value(default_config_path()),
            "The path to the configuration settings file."
        );
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
    }

    /**
     * Load command option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded option definitions.
     */
    BCX_API virtual options_metadata& load_options()
    {
        return option_metadata_;
    }

    /**
     * Load configuration setting definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    BCX_API virtual void load_settings(options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
        (
            "general.network",
            value<std::string>(&setting_.general.network)->default_value(BX_NETWORK),
            "The network to use, either 'mainnet' or 'testnet'. Defaults to match the build."
        )
        (
            "general.retries",
            value<primitives::byte>(&setting_.general.retries),
            "Number of times to retry contacting the server before giving up."
        )
        (
            "general.wait",
            value<uint32_t>(&setting_.general.wait)->default_value(2000),
            "Milliseconds to wait for a response from the server."
        )
        (
            "logging.debug_file",
            value<boost::filesystem::path>(&setting_.logging.debug_file)->default_value("debug.log"),
            "The path to the debug log file, used by send-tx-p2p."
        )
        (
            "logging.error_file",
            value<boost::filesystem::path>(&setting_.logging.error_file)->default_value("error.log"),
            "The path to the error log file, used by send-tx-p2p."
        )
        (
            "mainnet.url",
            value<primitives::uri>(&setting_.mainnet.url)->default_value({ "tcp://obelisk.airbitz.co:9091" }),
            "The URL of the Libbitcoin/Obelisk mainnet server."
        )
        (
            "mainnet.server_cert_key",
            value<primitives::cert_key>(&setting_.mainnet.server_cert_key),
            "The Z85-encoded public key of the server certificate."
        )
        (
            "mainnet.cert_file",
            value<boost::filesystem::path>(&setting_.mainnet.cert_file),
            "The path to the ZPL-encoded client private certificate file."
        )
        (
            "testnet.url",
            value<primitives::uri>(&setting_.testnet.url)->default_value({ "tcp://obelisk-testnet.airbitz.co:9091" }),
            "The URL of the Libbitcoin/Obelisk testnet server."
        )
        (
            "testnet.server_cert_key",
            value<primitives::cert_key>(&setting_.testnet.server_cert_key),
            "The Z85-encoded public key of the server certificate."
        )
        (
            "testnet.cert_file",
            value<boost::filesystem::path>(&setting_.testnet.cert_file),
            "The path to the ZPL-encoded client private certificate file."
        );
    }

    /**
     * Load streamed value as parameter fallback.
     * @param[in]  input      The input stream for loading the parameter.
     * @param[in]  variables  The loaded variables.
     */
    BCX_API virtual void load_stream(std::istream& input, po::variables_map& variables)
    {
    }

    /**
     * Write the help for this command to the specified stream.
     * @param[out] output  The output stream.
     */
    BCX_API virtual void write_help(std::ostream& output)
    {
        const auto& options = get_option_metadata();
        const auto& arguments = get_argument_metadata();
        config::printer help(options, arguments, BX_PROGRAM_NAME, description(),
            name());
        help.initialize();
        help.commandline(output);
    }

    /* Properties */
    
    /**
     * Get command line argument metadata.
     */
    BCX_API virtual arguments_metadata& get_argument_metadata()
    {
        return argument_metadata_;
    }

    /**
     * Get command line option metadata.
     */
    BCX_API virtual options_metadata& get_option_metadata()
    {
        return option_metadata_;
    }

    /**
     * Get the value of the general.network setting.
     */
    BCX_API virtual std::string get_general_network_setting() const
    {
        return setting_.general.network;
    }

    /**
     * Set the value of the general.network setting.
     */
    BCX_API virtual void set_general_network_setting(std::string value)
    {
        setting_.general.network = value;
    }

    /**
     * Get the value of the general.retries setting.
     */
    BCX_API virtual primitives::byte get_general_retries_setting() const
    {
        return setting_.general.retries;
    }

    /**
     * Set the value of the general.retries setting.
     */
    BCX_API virtual void set_general_retries_setting(primitives::byte value)
    {
        setting_.general.retries = value;
    }

    /**
     * Get the value of the general.wait setting.
     */
    BCX_API virtual uint32_t get_general_wait_setting() const
    {
        return setting_.general.wait;
    }

    /**
     * Set the value of the general.wait setting.
     */
    BCX_API virtual void set_general_wait_setting(uint32_t value)
    {
        setting_.general.wait = value;
    }

    /**
     * Get the value of the logging.debug_file setting.
     */
    BCX_API virtual boost::filesystem::path get_logging_debug_file_setting() const
    {
        return setting_.logging.debug_file;
    }

    /**
     * Set the value of the logging.debug_file setting.
     */
    BCX_API virtual void set_logging_debug_file_setting(boost::filesystem::path value)
    {
        setting_.logging.debug_file = value;
    }

    /**
     * Get the value of the logging.error_file setting.
     */
    BCX_API virtual boost::filesystem::path get_logging_error_file_setting() const
    {
        return setting_.logging.error_file;
    }

    /**
     * Set the value of the logging.error_file setting.
     */
    BCX_API virtual void set_logging_error_file_setting(boost::filesystem::path value)
    {
        setting_.logging.error_file = value;
    }

    /**
     * Get the value of the mainnet.url setting.
     */
    BCX_API virtual primitives::uri get_mainnet_url_setting() const
    {
        return setting_.mainnet.url;
    }

    /**
     * Set the value of the mainnet.url setting.
     */
    BCX_API virtual void set_mainnet_url_setting(primitives::uri value)
    {
        setting_.mainnet.url = value;
    }

    /**
     * Get the value of the mainnet.server_cert_key setting.
     */
    BCX_API virtual primitives::cert_key get_mainnet_server_cert_key_setting() const
    {
        return setting_.mainnet.server_cert_key;
    }

    /**
     * Set the value of the mainnet.server_cert_key setting.
     */
    BCX_API virtual void set_mainnet_server_cert_key_setting(primitives::cert_key value)
    {
        setting_.mainnet.server_cert_key = value;
    }

    /**
     * Get the value of the mainnet.cert_file setting.
     */
    BCX_API virtual boost::filesystem::path get_mainnet_cert_file_setting() const
    {
        return setting_.mainnet.cert_file;
    }

    /**
     * Set the value of the mainnet.cert_file setting.
     */
    BCX_API virtual void set_mainnet_cert_file_setting(boost::filesystem::path value)
    {
        setting_.mainnet.cert_file = value;
    }

    /**
     * Get the value of the testnet.url setting.
     */
    BCX_API virtual primitives::uri get_testnet_url_setting() const
    {
        return setting_.testnet.url;
    }

    /**
     * Set the value of the testnet.url setting.
     */
    BCX_API virtual void set_testnet_url_setting(primitives::uri value)
    {
        setting_.testnet.url = value;
    }

    /**
     * Get the value of the testnet.server_cert_key setting.
     */
    BCX_API virtual primitives::cert_key get_testnet_server_cert_key_setting() const
    {
        return setting_.testnet.server_cert_key;
    }

    /**
     * Set the value of the testnet.server_cert_key setting.
     */
    BCX_API virtual void set_testnet_server_cert_key_setting(primitives::cert_key value)
    {
        setting_.testnet.server_cert_key = value;
    }

    /**
     * Get the value of the testnet.cert_file setting.
     */
    BCX_API virtual boost::filesystem::path get_testnet_cert_file_setting() const
    {
        return setting_.testnet.cert_file;
    }

    /**
     * Set the value of the testnet.cert_file setting.
     */
    BCX_API virtual void set_testnet_cert_file_setting(boost::filesystem::path value)
    {
        setting_.testnet.cert_file = value;
    }

protected:

    /**
     * This base class is abstract but not pure virtual, so prevent direct 
     * construction here.
     */
    BCX_API command()
    {
    }

private:
    
    /**
     * Command line argument metadata.
     */
    arguments_metadata argument_metadata_;

    /**
     * Command line option metadata.
     */
    options_metadata option_metadata_;

    /**
     * Environment variable bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct environment
    {
        environment()
        {
        }

    } environment_;

    /**
     * Configuration setting file bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct setting
    {
        struct general
        {
            general()
              : network(),
                retries(),
                wait()
            {
            }

            std::string network;
            primitives::byte retries;
            uint32_t wait;
        } general;

        struct logging
        {
            logging()
              : debug_file(),
                error_file()
            {
            }

            boost::filesystem::path debug_file;
            boost::filesystem::path error_file;
        } logging;

        struct mainnet
        {
            mainnet()
              : url(),
                server_cert_key(),
                cert_file()
            {
            }

            primitives::uri url;
            primitives::cert_key server_cert_key;
            boost::filesystem::path cert_file;
        } mainnet;

        struct testnet
        {
            testnet()
              : url(),
                server_cert_key(),
                cert_file()
            {
            }

            primitives::uri url;
            primitives::cert_key server_cert_key;
            boost::filesystem::path cert_file;
        } testnet;

        setting()
          : general(),
            logging(),
            mainnet(),
            testnet()
        {
        }
    } setting_;
};

} // namespace explorer
} // namespace libgroestlcoin

#endif
