//*****************************************************************************
//*****************************************************************************

#ifndef UTIL_H
#define UTIL_H

#include "uint256.h"
#include "logger.h"

#include <string>

//*****************************************************************************
//*****************************************************************************
namespace util
{
    /**
     * @brief init
     */
    void init();

    /**
     * @brief wide_string
     * @param s
     * @return
     */
    std::wstring wide_string(std::string const &s);//, std::locale const &loc);
    // std::string narrow_string(std::wstring const &s, char default_char = '?');//, std::locale const &loc, char default_char = '?');

    /**
     * @brief mb_string
     * @param s
     * @return
     */
    std::string mb_string(std::string const &s);

    /**
     * @brief mb_string
     * @param s
     * @return
     */
    std::string mb_string(std::wstring const &s);

    /**
     * @brief base64_encode
     * @param s
     * @return
     */
    std::string base64_encode(const std::vector<unsigned char> &s);

    /**
     * @brief base64_encode
     * @param s
     * @return
     */
    std::string base64_encode(const std::string &s);

    /**
     * @brief base64_decode
     * @param s
     * @return
     */
    std::string base64_decode(const std::string &s);

    /**
     * @brief to_str
     * @param obj
     * @return
     */
    template<class _T>
    std::string to_str(const _T &obj)
    {
        return util::base64_encode(std::string((char *)(obj.begin()),
                                               (char *)(obj.end())));
    }

} // namespace

#endif // UTIL_H
