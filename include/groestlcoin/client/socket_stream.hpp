/**
 * Copyright (c) 2011-2015 libgroestlcoin developers (see AUTHORS)
 *
 * This file is part of libgroestlcoin-client.
 *
 * libgroestlcoin-client is free software: you can redistribute it and/or
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

#ifndef LIBBITCOIN_CLIENT_SOCKET_STREAM_HPP
#define LIBBITCOIN_CLIENT_SOCKET_STREAM_HPP

#include <memory>
#include <czmq++/czmqpp.hpp>
#include <groestlcoin/client/define.hpp>
#include <groestlcoin/client/message_stream.hpp>
//#include <groestlcoin/client/response_stream.hpp>
//#include <groestlcoin/client/request_stream.hpp>

namespace libgroestlcoin {
namespace client {

class socket_stream
  : public message_stream //, public request_stream
{
public:

    BCC_API socket_stream(czmqpp::socket& socket);

    BCC_API virtual ~socket_stream();

    BCC_API virtual void write(const data_stack& data);

//    BCC_API virtual void write(
//        const std::shared_ptr<bc::protocol::request>& request);

    BCC_API virtual bool signal_response(
        std::shared_ptr<message_stream> stream);

//    BCC_API virtual bool signal_response(
//        std::shared_ptr<response_stream> stream);

    BCC_API czmqpp::socket& get_socket();

private:

    czmqpp::socket socket_;
};

}
}

#endif
