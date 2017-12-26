//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGEAPP_H
#define XBRIDGEAPP_H

#include "xbridgesession.h"
#include "xbridgepacket.h"
#include "uint256.h"
#include "xbridgetransactiondescr.h"
#include "util/xbridgeerror.h"
#include "xbridgewalletconnector.h"
#include "xbridgedef.h"

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

//*****************************************************************************
//*****************************************************************************
namespace xbridge
{

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The App class
 */
class App
{
    class Impl;

private:
    App();
    virtual ~App();

public:
    /**
     * @brief instance - the classical implementation of singletone
     * @return
     */
    static App & instance();

    /**
     * @brief version
     * @return  current version of application
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
     * load xbridge settings; init exchange; init sessions
     * @return always true
     */
    bool start();

    /**
     * @brief stop
     * @return always true
     */
    bool stop();

public:
    // transactions

    /**
     * @brief transaction
     * @param id - transaction id
     * @return pointer to transaction with specifed id, if transaction exists or nullptr
     */
    TransactionDescrPtr transaction(const uint256 & id) const;
    /**
     * @brief transactions
     * @return a list of opened transactions
     */
    std::map<uint256, xbridge::TransactionDescrPtr> transactions() const;
    /**
     * @brief history
     * @return list of historical transactions
     */
    std::map<uint256, xbridge::TransactionDescrPtr> history() const;

    /**
     * @brief appendTransaction - if transaction not exists - append transaction to list,
     * else update transaction timestamp
     * @param ptr - pointer to transaction
     */
    void appendTransaction(const TransactionDescrPtr & ptr);

    /**
     * @brief moveTransactionToHistory - remove transaction from pending and append to
     * list of historical transactions
     * @param id - id of transaction
     */
    void moveTransactionToHistory(const uint256 & id);

    /**
     * @brief sendXBridgeTransaction - checks transaction params and sent brascast message
     *  about  transaction to network
     * @param from - initiator address
     * @param fromCurrency - from currency
     * @param fromAmount - amount of deposit
     * @param to - Responder address
     * @param toCurrency - to currency
     * @param toAmount - amount for
     * @param id - id of new transaction
     * @return xbridge::SUCCESS,  if all params valid and transaction sended to network
     */
    Error sendXBridgeTransaction(const std::string & from,
                                 const std::string & fromCurrency,
                                 const uint64_t & fromAmount,
                                 const std::string & to,
                                 const std::string & toCurrency,
                                 const uint64_t & toAmount,
                                 uint256 & id);
    /**
     * @brief sendPendingTransaction - sent information about pending transaction to network
     * @param ptr - pointer to transaction
     * @return true, if
     */
    bool sendPendingTransaction(const TransactionDescrPtr & ptr);

    /**
     * @brief acceptXBridgeTransaction - checks parameters and sent packet with information about accepting
     * transaction to network
     * @param id - id of transaction
     * @param from - address of initiator
     * @param to - address of responder
     * @return xbridge::SUCCESS if all parameters valid or error code
     */
    Error acceptXBridgeTransaction(const uint256 & id,
                                     const std::string & from,
                                     const std::string & to);
    /**
     * @brief sendAcceptingTransaction sent packet with information about accepting
     * transaction to network
     * @param ptr - pointer of transaction
     * @return  always true
     */
    bool sendAcceptingTransaction(const TransactionDescrPtr & ptr);

    /**
     * @brief cancelXBridgeTransaction - sent packet with information about cancellation transaction,
     * change transaction status and notify UI about it
     * @param id - id of transaction
     * @param reason - the reason for the cancellation of the transaction
     * @return always xbridge::SUCCESS
     */
    xbridge::Error cancelXBridgeTransaction(const uint256 & id, const TxCancelReason & reason);

    /**
     * @brief sendCancelTransaction - sent packet with information about cancellation transaction,
     * @param txid - id of transaction
     * @param reason - the reason for the cancellation of the transaction
     * @return always true
     */
    bool sendCancelTransaction(const uint256 & txid, const TxCancelReason & reason);

    /**
     * @brief rollbackXBridgeTransaction - rollback transaction and sent packet to network
     * @param id - id of transaction
     * @return status of operation
     */
    xbridge::Error rollbackXBridgeTransaction(const uint256 & id);

    /**
     * @brief sendRollbackTransaction - sent packet about rollback transaction to network
     * @param txid - id of transaction
     * @return always true
     */
    bool sendRollbackTransaction(const uint256 & txid);

public:
    // connectors

    /**
     * @brief availableCurrencies
     * @return list of available currencies
     */
    std::vector<std::string> availableCurrencies() const;

    /**
     * @brief hasCurrency -
     * @param currency - currency name
     * @return true, if session currency exists
     */
    bool hasCurrency(const std::string & currency) const;

    /**
     * @brief addConnector - added connector for currency
     * @param conn - connector
     */
    void addConnector(const WalletConnectorPtr & conn);

    /**
     * @brief updateConnector
     * @param conn
     * @param addr
     * @param currency
     */
    void updateConnector(const WalletConnectorPtr & conn,
                         const std::vector<unsigned char> addr,
                         const std::string & currency);
    /**
     * @brief connectorByCurrency
     * @param currency - currency
     * @return pointer of WalletConnctor if exists, or new instance
     */
    WalletConnectorPtr connectorByCurrency(const std::string & currency) const;
    /**
     * @brief connectors
     * @return list of wallet connectors
     */
    std::vector<WalletConnectorPtr> connectors() const;

public:
    // network

    /**
     * @brief isKnownMessage
     * @param message
     * @return true, if message exists
     */
    bool isKnownMessage(const std::vector<unsigned char> & message);
    /**
     * @brief addToKnown - added message to queue
     * @param message
     */
    void addToKnown(const std::vector<unsigned char> & message);

    // send message via xbridge
    /**
     * @brief sendPacket
     * @param packet
     */
    void sendPacket(const XBridgePacketPtr & packet);
    /**
     * @brief sendPacket
     * @param id
     * @param packet
     */
    void sendPacket(const std::vector<unsigned char> & id, const XBridgePacketPtr & packet);


    /**
     * @brief onMessageReceived call when message from xbridge network received
     * @param id
     * @param message
     * @param state
     */
    void onMessageReceived(const std::vector<unsigned char> & id,
                           const std::vector<unsigned char> & message,
                           CValidationState & state);

    /**
     * @brief onBroadcastReceived broadcast message
     * @param message
     * @param state
     */
    void onBroadcastReceived(const std::vector<unsigned char> & message,
                             CValidationState & state);

    /**
     * @brief processLater
     * @param txid
     * @param packet
     * @return
     */
    bool processLater(const uint256 & txid, const XBridgePacketPtr & packet);

    /**
     * @brief removePackets
     * @param txid
     * @return
     */
    bool removePackets(const uint256 & txid);

public:
    // UTXO
    // TODO move to connector
    /**
     * @brief checkUtxoItems
     * @param items
     * @return
     */
    bool checkUtxoItems(const std::vector<wallet::UtxoEntry> & items);

    /**
     * @brief lockUtxoItems
     * @param items
     * @return
     */
    bool lockUtxoItems(const std::vector<wallet::UtxoEntry> & items);

    /**
     * @brief txOutIsLocked
     * @param entry
     * @return
     */
    bool txOutIsLocked(const wallet::UtxoEntry & entry) const;

private:
    std::unique_ptr<Impl> m_p;
};

} // namespace xbridge

#endif // XBRIDGEAPP_H
