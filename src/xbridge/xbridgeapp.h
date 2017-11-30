//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGEAPP_H
#define XBRIDGEAPP_H

#include "xbridge.h"
#include "xbridgesession.h"
#include "xbridgepacket.h"
#include "uint256.h"
#include "xbridgetransactiondescr.h"
#include "util/xbridgeerror.h"
#include <thread>
#include <atomic>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <queue>

#ifdef WIN32
// #include <Ws2tcpip.h>
#endif

namespace rpc
{
class AcceptedConnection;
}

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridgeApp class
 */
class XBridgeApp
{
    typedef std::vector<unsigned char> UcharVector;
    typedef std::shared_ptr<boost::asio::io_service>       IoServicePtr;
    typedef std::shared_ptr<boost::asio::io_service::work> WorkPtr;

    /**
     * @brief callback
     * @param closure
     * @param event
     * @param info_hash
     * @param data
     * @param data_len
     */
    friend void callback(void *closure, int event,
                         const unsigned char *info_hash,
                         const void *data, size_t data_len);

private:
    /**
     * @brief XBridgeApp
     */
    XBridgeApp();

    /**
     * @brief ~XBridgeApp
     */
    virtual ~XBridgeApp();

public:

    /**
     * @brief instance
     * @return
     */
    static XBridgeApp &instance();

    /**
     * @brief version
     * @return
     */
    static std::string version();

    /**
     * @brief isEnabled
     * @return
     */
    static bool isEnabled();

    /**
     * @brief init
     * @param argc
     * @param argv
     * @return
     */
    bool init(int argc, char *argv[]);

    /**
     * @brief start
     * @return
     */
    bool start();

    /**
     * @brief sendXBridgeTransaction
     * @param from
     * @param fromCurrency
     * @param fromAmount
     * @param to
     * @param toCurrency
     * @param toAmount
     * @param id
     * @return
     */
    xbridge::Error sendXBridgeTransaction(const std::string &from,
                                          const std::string &fromCurrency,
                                          const uint64_t &fromAmount,
                                          const std::string &to,
                                          const std::string &toCurrency,
                                          const uint64_t &toAmount,
                                          uint256 &id);

    /**
     * @brief sendPendingTransaction
     * @param ptr
     * @return
     */
    bool sendPendingTransaction(XBridgeTransactionDescrPtr &ptr);

    /**
     * @brief acceptXBridgeTransaction
     * @param id
     * @param from
     * @param to
     * @param result
     * @return
     */
    xbridge::Error acceptXBridgeTransaction(const uint256 &id,
                                     const std::string &from,
                                     const std::string &to, uint256 &result);

    /**
     * @brief sendAcceptingTransaction
     * @param ptr
     * @return
     */
    bool sendAcceptingTransaction(XBridgeTransactionDescrPtr &ptr);

    /**
     * @brief cancelXBridgeTransaction
     * @param id
     * @param reason
     * @return
     */
    xbridge::Error cancelXBridgeTransaction(const uint256 &id, const TxCancelReason &reason);

    /**
     * @brief sendCancelTransaction
     * @param txid
     * @param reason
     * @return
     */
    bool sendCancelTransaction(const uint256 &txid, const TxCancelReason &reason);

    /**
     * @brief rollbackXBridgeTransaction
     * @param id
     * @return
     */
    xbridge::Error rollbackXBridgeTransaction(const uint256 &id);

    /**
     * @brief sendRollbackTransaction
     * @param txid
     * @return
     */
    bool sendRollbackTransaction(const uint256 &txid);

public:

    /**
     * @brief stop
     * @return
     */
    bool stop();

    /**
     * @brief sessionByCurrency
     * @param currency
     * @return
     */
    XBridgeSessionPtr sessionByCurrency(const std::string &currency) const;

    /**
     * @brief sessionsCurrencies
     * @return
     */
    std::vector<std::string> sessionsCurrencies() const;

    // store session
    /**
     * @brief addSession
     * @param session
     */
    void addSession(XBridgeSessionPtr session);

    // store session addresses in local table
    /**
     * @brief storageStore
     * @param session
     * @param id
     */
    void storageStore(XBridgeSessionPtr session, const std::vector<unsigned char> & id);

    /**
     * @brief isLocalAddress
     * @param id
     * @return
     */
    bool isLocalAddress(const std::vector<unsigned char> &id);

    /**
     * @brief isKnownMessage
     * @param message
     * @return
     */
    bool isKnownMessage(const std::vector<unsigned char> &message);

    /**
     * @brief addToKnown
     * @param message
     */
    void addToKnown(const std::vector<unsigned char> &message);

    /**
     * @brief serviceSession
     * @return
     */
    XBridgeSessionPtr serviceSession();

    /**
     * @brief storeAddressBookEntry
     * @param currency
     * @param name
     * @param address
     */
    void storeAddressBookEntry(const std::string &currency,
                               const std::string &name,
                               const std::string &address);

    /**
     * @brief getAddressBook
     */
    void getAddressBook();

public:// slots:
    // send messave via xbridge
    /**
     * @brief onSend
     * @param packet
     */
    void onSend(const XBridgePacketPtr &packet);

    /**
     * @brief onSend
     * @param id
     * @param packet
     */
    void onSend(const UcharVector &id, const XBridgePacketPtr &packet);

    // call when message from xbridge network received
    /**
     * @brief onMessageReceived
     * @param id
     * @param message
     */
    void onMessageReceived(const std::vector<unsigned char> &id, const std::vector<unsigned char> &message);

    // broadcast message
    /**
     * @brief onBroadcastReceived
     * @param message
     */
    void onBroadcastReceived(const std::vector<unsigned char> &message);

private:
    /**
     * @brief onSend
     * @param id
     * @param message
     */
    void onSend(const UcharVector &id, const UcharVector &message);

public:
    /**
     * @brief sleep
     * @param umilliseconds
     */
    static void sleep(const unsigned int umilliseconds);

private:
    /**
     * @brief m_threads
     */
    boost::thread_group m_threads;

    /**
     * @brief m_bridge
     */
    XBridgePtr        m_bridge;

    /**
     * @brief m_sessionsLock
     */
    mutable boost::mutex m_sessionsLock;

    /**
     * @brief SessionAddrMap
     */
    typedef std::map<std::vector<unsigned char>, XBridgeSessionPtr> SessionAddrMap;

    /**
     * @brief m_sessionAddrs
     */
    SessionAddrMap m_sessionAddrs;

    /**
     * @brief SessionIdMap
     */
    typedef std::map<std::string, XBridgeSessionPtr> SessionIdMap;

    /**
     * @brief m_sessionIds
     */
    SessionIdMap m_sessionIds;

    /**
     * @brief SessionQueue
     */
    typedef std::queue<XBridgeSessionPtr> SessionQueue;

    /**
     * @brief m_sessionQueue
     */
    SessionQueue m_sessionQueue;

    // service session
    /**
     * @brief m_serviceSession
     */
    XBridgeSessionPtr m_serviceSession;

    /**
     * @brief m_messagesLock
     */
    boost::mutex m_messagesLock;

    /**
     * @brief ProcessedMessages
     */
    typedef std::set<uint256> ProcessedMessages;

    /**
     * @brief m_processedMessages
     */
    ProcessedMessages m_processedMessages;

    /**
     * @brief m_addressBookLock
     */
    boost::mutex m_addressBookLock;

    /**
     * @brief AddressBookEntry
     */
    typedef std::tuple<std::string, std::string, std::string> AddressBookEntry;

    /**
     * @brief AddressBook
     */
    typedef std::vector<AddressBookEntry> AddressBook;

    /**
     * @brief m_addressBook
     */
    AddressBook m_addressBook;

    /**
     * @brief m_addresses
     */
    std::set<std::string> m_addresses;

public:
    /**
     * @brief m_txLocker
     */
    static boost::mutex                                  m_txLocker;

    /**
     * @brief m_pendingTransactions
     */
    static std::map<uint256, XBridgeTransactionDescrPtr> m_pendingTransactions;

    /**
     * @brief m_transactions
     */
    static std::map<uint256, XBridgeTransactionDescrPtr> m_transactions;

    /**
     * @brief m_historicTransactions
     */
    static std::map<uint256, XBridgeTransactionDescrPtr> m_historicTransactions;

    /**
     * @brief m_txUnconfirmedLocker
     */
    static boost::mutex                                  m_txUnconfirmedLocker;

    /**
     * @brief m_unconfirmed
     */
    static std::map<uint256, XBridgeTransactionDescrPtr> m_unconfirmed;

    /**
     * @brief m_ppLocker
     */
    static boost::mutex                                  m_ppLocker;

    /**
     * @brief m_pendingPackets
     */
    static std::map<uint256, std::pair<std::string, XBridgePacketPtr> > m_pendingPackets;

  private:
    /**
     * @brief m_historicTransactionsStates - transaction state, in the historical list
     */
    std::list<XBridgeTransactionDescr::State>       m_historicTransactionsStates;

    /**
     * @brief m_services
     */
    std::deque<IoServicePtr> m_services;

    /**
     * @brief m_works
     */
    std::deque<WorkPtr> m_works;

    /**
     * @brief m_timerIo
     */
    boost::asio::io_service m_timerIo;

    /**
     * @brief m_timerIoWork - update historical transactions list timer worker
     */
    std::shared_ptr<boost::asio::io_service::work>  m_timerIoWork;

    /**
     * @brief m_timerThread - timer thread
     */
    boost::thread m_timerThread;

    /**
     * @brief m_timer timer update historical transactions list
     */
    boost::asio::deadline_timer m_timer;

public:
    /**
     * @brief isHistoricState - checks the state of the transaction
     * @param state - current state of transaction
     * @return true, if the transaction is historical
     */
    bool isHistoricState(const XBridgeTransactionDescr::State state);
};

#endif // XBRIDGEAPP_H
