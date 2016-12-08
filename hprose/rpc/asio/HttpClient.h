/**********************************************************\
|                                                          |
|                          hprose                          |
|                                                          |
| Official WebSite: http://www.hprose.com/                 |
|                   http://www.hprose.org/                 |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * hprose/rpc/asio/HttpClient.h                           *
 *                                                        *
 * hprose asio http client for cpp.                       *
 *                                                        *
 * LastModified: Dec 8, 2016                              *
 * Author: Chen fei <cf@hprose.com>                       *
 *                                                        *
\**********************************************************/

#pragma once

#include <hprose/rpc/Client.h>

namespace hprose {
namespace rpc {
namespace asio {

class HttpClient : public Client {
public:
    HttpClient(const std::string &uri)
        : Client(uri) {
    }

protected:
    std::string sendAndReceive(const std::string &request, const ClientContext &context);

};

}
}
} // hprose::rpc::asio
