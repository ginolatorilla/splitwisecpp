#include <curl/curl.h>
#include <iosfwd>
#include <json/reader.h>

namespace splitwisecpp
{

namespace detail
{
    struct JsonReaderContext
    {
        ::Json::CharReader* reader;
        ::Json::Value* json;
    };
}

class Curl
{
public:
    Curl();
    ~Curl();

    void set_write_to_stream(std::ostream* stream);
    void set_write_to_json(detail::JsonReaderContext* stream);
    ::CURLcode set_url(const char* url);
    ::CURLcode perform();

private:
    ::CURL* handle;
};

}  // namespace splitwisecpp
