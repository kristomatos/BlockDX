//******************************************************************************
//******************************************************************************

#ifndef TXLOG_H
#define TXLOG_H

#include <sstream>
#include <boost/pool/pool_alloc.hpp>


//******************************************************************************
//******************************************************************************
/**
 * @brief The TXLOG class
 */
class TXLOG : public std::basic_stringstream<char, std::char_traits<char>,
        boost::pool_allocator<char> > // std::stringstream
{
public:
    /**
     * @brief TXLOG
     */
    TXLOG();

    /**
     * @brief ~TXLOG
     */
    virtual ~TXLOG();

    /**
     * @brief logFileName
     * @return
     */
    static std::string logFileName();

private:

    /**
     * @brief makeFileName
     * @return
     */
    static std::string makeFileName();

private:

    /**
     * @brief m_logFileName
     */
    static std::string m_logFileName;
};

#endif // TXLOG_H
