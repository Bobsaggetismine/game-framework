#pragma once

namespace bq
{
    constexpr int BQ_NETWORK_FAILURE = -99999;
    class http_client
    {
        std::string m_host;

    public:

        http_client(const std::string& host);

        bq::network_result get(const std::string& path);
    };
}