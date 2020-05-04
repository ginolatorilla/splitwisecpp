#include <curl/curl.h>
#include <iosfwd>

namespace splitwisecpp
{

class Curl
{
public:
    Curl();
    ~Curl();

    void set_write_to_stream(std::ostream* stream);
    void set_url(const char* url);
    void perform();

private:
    ::CURL* handle;
};

}  // namespace splitwisecpp
