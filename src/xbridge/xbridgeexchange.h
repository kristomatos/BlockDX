//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGEEXCHANGE_H
#define XBRIDGEEXCHANGE_H

#include "uint256.h"
#include "xbridgetransaction.h"
#include "xbridgewallet.h"

#include <string>
#include <set>
#include <map>
#include <list>

#include <boost/cstdint.hpp>
#include <boost/thread/mutex.hpp>

//*****************************************************************************
//*****************************************************************************
typedef std::pair<std::string, std::string> StringPair;

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridgeExchange class
 */
class XBridgeExchange
{
public:
    /**
     * @brief instance
     * @return
     */
    static XBridgeExchange &instance();

protected:
    /**
     * @brief XBridgeExchange
     */
    XBridgeExchange();

    /**
      *
      * */
    ~XBridgeExchange();

public:
    /**
     * @brief init
     * @return
     */
    bool init();

    /**
     * @brief isEnabled
     * @return
     */
    bool isEnabled();

    /**
     * @brief isStarted
     * @return
     */
    bool isStarted();

    /**
     * @brief haveConnectedWallet
     * @param walletName
     * @return
     */
    bool haveConnectedWallet(const std::string &walletName);

    /**
     * @brief connectedWallets
     * @return
     */
    std::vector<std::string> connectedWallets() const;

    // std::vector<unsigned char> walletAddress(const std::string & walletName);

    /**
     * @brief createTransaction
     * @param id
     * @param sourceAddr
     * @param sourceCurrency
     * @param sourceAmount
     * @param destAddr
     * @param destCurrency
     * @param destAmount
     * @param pendingId
     * @param isCreated
     * @return
     */
    bool createTransaction(const uint256     &id,
                           const std::string &sourceAddr,
                           const std::string &sourceCurrency,
                           const uint64_t    &sourceAmount,
                           const std::string &destAddr,
                           const std::string &destCurrency,
                           const uint64_t    &destAmount,
                           uint256           &pendingId,
                           bool              &isCreated);

    /**
     * @brief acceptTransaction
     * @param id
     * @param sourceAddr
     * @param sourceCurrency
     * @param sourceAmount
     * @param destAddr
     * @param destCurrency
     * @param destAmount
     * @param transactionId
     * @return
     */
    bool acceptTransaction(const uint256     &id,
                           const std::string &sourceAddr,
                           const std::string &sourceCurrency,
                           const uint64_t    &sourceAmount,
                           const std::string &destAddr,
                           const std::string &destCurrency,
                           const uint64_t    &destAmount,
                           uint256           &transactionId);

    /**
     * @brief deletePendingTransactions
     * @param id
     * @return
     */
    bool deletePendingTransactions(const uint256 &id);

    /**
     * @brief deleteTransaction
     * @param id
     * @return
     */
    bool deleteTransaction(const uint256 &id);

    /**
     * @brief updateTransactionWhenHoldApplyReceived
     * @param tx
     * @param from
     * @return
     */
    bool updateTransactionWhenHoldApplyReceived(XBridgeTransactionPtr tx,
                                                const std::string &from);

    /**
     * @brief updateTransactionWhenInitializedReceived
     * @param tx
     * @param from
     * @param datatxid
     * @param pk
     * @return
     */
    bool updateTransactionWhenInitializedReceived(XBridgeTransactionPtr tx,
                                                  const std::string &from,
                                                  const uint256 &datatxid,
                                                  const xbridge::CPubKey &pk);

    /**
     * @brief updateTransactionWhenCreatedReceived
     * @param tx
     * @param from
     * @param binTxId
     * @param innerScript
     * @return
     */
    bool updateTransactionWhenCreatedReceived(XBridgeTransactionPtr tx,
                                              const std::string &from,
                                              const std::string &binTxId,
                                              const std::string &innerScript);

    /**
     * @brief updateTransactionWhenConfirmedReceived
     * @param tx
     * @param from
     * @return
     */
    bool updateTransactionWhenConfirmedReceived(XBridgeTransactionPtr tx,
                                                const std::string &from);

    /**
     * @brief updateTransaction
     * @param hash
     * @return
     */
    bool updateTransaction(const uint256 &hash);

    /**
     * @brief transaction
     * @param hash
     * @return
     */
    const XBridgeTransactionPtr transaction(const uint256 &hash);

    /**
     * @brief pendingTransaction
     * @param hash
     * @return
     */
    const XBridgeTransactionPtr pendingTransaction(const uint256 &hash);

    /**
     * @brief pendingTransactions
     * @return
     */
    std::list<XBridgeTransactionPtr> pendingTransactions() const;

    /**
     * @brief transactions
     * @return
     */
    std::list<XBridgeTransactionPtr> transactions() const;

    /**
     * @brief finishedTransactions
     * @return
     */
    std::list<XBridgeTransactionPtr> finishedTransactions() const;

    /**
     * @brief transactionsHistory
     * @return
     */
    std::list<XBridgeTransactionPtr> transactionsHistory() const;

private:
    /**
     * @brief transactions
     * @param onlyFinished
     * @return
     */
    std::list<XBridgeTransactionPtr> transactions(bool onlyFinished) const;

private:
    // connected wallets
    /**
     * @brief WalletList
     */
    typedef std::map<std::string, WalletParam> WalletList;

    /**
     * @brief m_wallets
     */
    WalletList                               m_wallets;

    /**
     * @brief m_pendingTransactionsLock
     */
    mutable boost::mutex                     m_pendingTransactionsLock;

    /**
     * @brief m_pendingTransactions
     */
    std::map<uint256, XBridgeTransactionPtr> m_pendingTransactions;

    /**
     * @brief m_transactionsLock
     */
    mutable boost::mutex                     m_transactionsLock;

    /**
     * @brief m_transactions
     */
    std::map<uint256, XBridgeTransactionPtr> m_transactions;

    /**
     * @brief m_transactionsHistoryLock
     */
    mutable boost::mutex                     m_transactionsHistoryLock;


    /**
     * @brief m_transactionsHistory
     */
    std::map<uint256, XBridgeTransactionPtr> m_transactionsHistory;

    /**
     * @brief m_unconfirmedLock
     */
    mutable boost::mutex                     m_unconfirmedLock;

    /**
     * @brief m_unconfirmed
     */
    std::map<std::string, uint256>           m_unconfirmed;

    // TODO use deque and limit size
    /**
     * @brief m_walletTransactions
     */
    std::set<uint256>                        m_walletTransactions;

    /**
     * @brief m_knownTxLock
     */
    mutable boost::mutex                     m_knownTxLock;

    /**
     * @brief m_knownTransactions
     */
    std::set<uint256>                        m_knownTransactions;
};//class XBridgeExchange

#endif // XBRIDGEEXCHANGE_H
