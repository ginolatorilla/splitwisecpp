#include "curlwrapper.hpp"
#include <ostream>
#include <cassert>

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

void Curl::set_url(const char* url)
{
    ::curl_easy_setopt(handle, CURLOPT_URL, url);
}

void Curl::perform()
{
    ::curl_easy_perform(handle);
}

}  // namespace splitwisecpp
