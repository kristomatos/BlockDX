//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGESESSION_H
#define XBRIDGESESSION_H

#include "xbridgepacket.h"
#include "xbridgetransaction.h"
#include "xbridgetransactiondescr.h"
#include "xbridgewallet.h"
#include "uint256.h"
#include "xkey.h"
#include "xbitcointransaction.h"
#include "bitcoinrpcconnector.h"
#include "script/script.h"
#include "xbridgewalletconnector.h"

#include <memory>
#include <set>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>

extern const unsigned int LOCKTIME_THRESHOLD;

//*****************************************************************************
//*****************************************************************************
namespace xbridge
{

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The Session class
 */
class Session
        : public std::enable_shared_from_this<Session>
        , private boost::noncopyable
{
    class Impl;

public:
    /**
     * @brief Session
     */
    Session();
    /**
      * @brief ~Session
      * */
    ~Session();

    /**
     * @brief sessionAddr
     * @return
     */
    const std::vector<unsigned char> & sessionAddr() const;

    /**
     * @brief checkXBridgePacketVersion
     * @param packet
     * @return
     */
    static bool checkXBridgePacketVersion(XBridgePacketPtr packet);

    /**
     * @brief processPacket
     * @param packet
     * @return
     */
    bool processPacket(XBridgePacketPtr packet);

public:
    // service functions
    /**
     * @brief sendListOfTransactions
     */
    void sendListOfTransactions();
    /**
     * @brief checkFinishedTransactions
     */
    void checkFinishedTransactions();
    /**
     * @brief eraseExpiredPendingTransactions
     */
    void eraseExpiredPendingTransactions();
    /**
     * @brief getAddressBook
     */
    void getAddressBook();

private:
    /**
     * @brief init
     */
    void init();

private:
    std::unique_ptr<Impl> m_p;
};

} // namespace xbridge

#endif // XBRIDGESESSION_H
