//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGE_H
#define XBRIDGE_H

#include <deque>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridge class
 */
class XBridge
{
    enum
    {
        THREAD_COUNT = 2,
        TIMER_INTERVAL = 60
    };

    /**
     * @brief IoServicePtr
     */
    typedef std::shared_ptr<boost::asio::io_service>       IoServicePtr;

    /**
     * @brief WorkPtr
     */
    typedef std::shared_ptr<boost::asio::io_service::work> WorkPtr;

public:
    /**
     * @brief Socket
     */
    typedef boost::asio::ip::tcp::socket                  Socket;

    /**
     * @brief SocketPtr
     */
    typedef std::shared_ptr<boost::asio::ip::tcp::socket> SocketPtr;

public:
    /**
     * @brief XBridge
     */
    XBridge();

    /**
     * @brief stop
     */
    void stop();

private:
    /**
     * @brief onTimer
     */
    void onTimer();

private:
    /**
     * @brief m_services
     */
    std::deque<IoServicePtr>                        m_services;

    /**
     * @brief m_works
     */
    std::deque<WorkPtr>                             m_works;

    /**
     * @brief m_threads
     */
    boost::thread_group                             m_threads;

    /**
     * @brief m_timerIo
     */
    boost::asio::io_service                         m_timerIo;

    /**
     * @brief m_timerIoWork
     */
    std::shared_ptr<boost::asio::io_service::work>  m_timerIoWork;

    /**
     * @brief m_timerThread
     */
    boost::thread                                   m_timerThread;

    /**
     * @brief m_timer
     */
    boost::asio::deadline_timer                     m_timer;
};//class XBridge

typedef std::shared_ptr<XBridge> XBridgePtr;

#endif // XBRIDGE_H
