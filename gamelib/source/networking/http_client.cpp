#include "bqpch.h"


bq::http_client::http_client(const std::string& host) : m_host(host) {}

bq::network_result bq::http_client::get(const std::string& path){
    httplib::Client cli(m_host);
    auto result = cli.Get(path);
    int status = bq::BQ_NETWORK_FAILURE;
    std::string body;
    if(result.error() == httplib::Error::Success)
    {
        body = result->body;
        status = result->status;
    }
    else
    {
        body = httplib::to_string(result.error());
    }
    return {status,body};
}