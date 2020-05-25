#include "curlwrapper.hpp"
#include <ostream>
#include <cassert>
#include <json/writer.h>

namespace splitwisecpp
{

namespace detail
{
    int write_to_ostream(char* data, size_t size, size_t nmemb, void* stream)
    {
        assert(stream != nullptr);
        reinterpret_cast<std::ostream*>(stream)->write(data, size * nmemb);
        return size * nmemb; 
    }

    int write_to_json_reader(char* data, size_t size, size_t nmemb, void* context)
    {
        assert(context != nullptr);
        auto* reader = reinterpret_cast<JsonReaderContext*>(context)->reader;
        auto* json = reinterpret_cast<JsonReaderContext*>(context)->json;
        reader->parse(data, data + size * nmemb, json, nullptr);
        return size * nmemb; 
    }
}

Curl::Curl() : handle(curl_easy_init())
{
    ::curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);
    ::curl_easy_setopt(handle, CURLOPT_DEFAULT_PROTOCOL, "https");
}

Curl::~Curl()
{
    ::curl_easy_cleanup(handle);
}

void Curl::set_write_to_stream(std::ostream* stream)
{
    ::curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, detail::write_to_ostream);
    ::curl_easy_setopt(handle, CURLOPT_WRITEDATA, stream);
}

void Curl::set_write_to_json(detail::JsonReaderContext* context)
{
    ::curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, detail::write_to_json_reader);
    ::curl_easy_setopt(handle, CURLOPT_WRITEDATA, context);
}

::CURLcode Curl::set_url(const char* url)
{
    return ::curl_easy_setopt(handle, CURLOPT_URL, url);
}

::CURLcode Curl::perform()
{
    auto perf_res = ::curl_easy_perform(handle);
    if (placeholder != nullptr)
    {
        ::curl_slist_free_all(placeholder);
        placeholder = nullptr;
    }
    return perf_res;
}

::CURLcode Curl::set_to_GET()
{
    return ::curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L);
}

::CURLcode Curl::set_to_POST(const char* auth_header, const ::Json::Value* data)
{
    ::curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "POST");

    placeholder = ::curl_slist_append(placeholder, auth_header);
    placeholder = ::curl_slist_append(placeholder, "Content-Type: application/json");
    auto res = ::curl_easy_setopt(handle, CURLOPT_HTTPHEADER, placeholder);

    if (data != nullptr)
    {
        ::Json::StreamWriterBuilder wb;
        wb["indentation"] = "";
        std::unique_ptr<::Json::StreamWriter> writer(wb.newStreamWriter());
        std::stringstream output;
        writer->write(*data, &output);
        post_data = output.str();
        return ::curl_easy_setopt(handle, CURLOPT_POSTFIELDS, post_data.c_str());
    }
    else
    {
        return res;
    }
    
}

}  // namespace splitwisecpp
