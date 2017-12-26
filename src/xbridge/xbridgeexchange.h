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
#include <memory>

#include <boost/cstdint.hpp>
#include <boost/thread/mutex.hpp>

//******************************************************************************
//******************************************************************************
namespace xbridge
{

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The Exchange class
 */
class Exchange
{
    class Impl;

public:
    /**
     * @brief instance
     * @return
     */
    static Exchange & instance();

protected:
    /**
     * @brief Exchange - default constructor
     */
    Exchange();
    /**
      * destructor
      * */
    ~Exchange();

public:
    /**
     * @brief init
     * @return
     */
    bool init();

    /**
     * @brief isEnabled
     * @return true, if servicenode mode enabled
     */
    bool isEnabled();
    /**
     * @brief isStarted
     * @return true, if is enabled and servicenode started
     */
    bool isStarted();

    /**
     * @brief haveConnectedWallet
     * @param walletName - name of wallet
     * @return true, if connection with wallet
     */
    bool haveConnectedWallet(const std::string & walletName);
    /**
     * @brief connectedWallets
     * @return list of connected wallets
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
    bool createTransaction(const uint256                    & id,
                           const std::vector<unsigned char> & sourceAddr,
                           const std::string                & sourceCurrency,
                           const uint64_t                   & sourceAmount,
                           const std::vector<unsigned char> & destAddr,
                           const std::string                & destCurrency,
                           const uint64_t                   & destAmount,
                           uint256                          & pendingId,
                           bool                             & isCreated);

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
    bool acceptTransaction(const uint256                    & id,
                           const std::vector<unsigned char> & sourceAddr,
                           const std::string                & sourceCurrency,
                           const uint64_t                   & sourceAmount,
                           const std::vector<unsigned char> & destAddr,
                           const std::string                & destCurrency,
                           const uint64_t                   & destAmount,
                           uint256                          & transactionId);

    /**
     * @brief deletePendingTransactions
     * @param id
     * @return
     */
    bool deletePendingTransactions(const uint256 & id);
    /**
     * @brief deletePendingTransactionsByTransactionId
     * @param id
     * @return
     */
    bool deletePendingTransactionsByTransactionId(const uint256 & id);
    /**
     * @brief deleteTransaction
     * @param id
     * @return
     */
    bool deleteTransaction(const uint256 & id);

    /**
     * @brief updateTransactionWhenHoldApplyReceived
     * @param tx
     * @param from
     * @return
     */
    bool updateTransactionWhenHoldApplyReceived(const TransactionPtr & tx,
                                                const std::vector<unsigned char> & from);
    /**
     * @brief updateTransactionWhenInitializedReceived
     * @param tx
     * @param from
     * @param datatxid
     * @param pk
     * @return
     */
    bool updateTransactionWhenInitializedReceived(const TransactionPtr & tx,
                                                  const std::vector<unsigned char> & from,
                                                  const uint256 & datatxid,
                                                  const std::vector<unsigned char> & pk);
    /**
     * @brief updateTransactionWhenCreatedReceived
     * @param tx
     * @param from
     * @param binTxId
     * @param innerScript
     * @return
     */
    bool updateTransactionWhenCreatedReceived(const TransactionPtr & tx,
                                              const std::vector<unsigned char> & from,
                                              const std::string & binTxId,
                                              const std::vector<unsigned char> & innerScript);
    /**
     * @brief updateTransactionWhenConfirmedReceived
     * @param tx
     * @param from
     * @return
     */
    bool updateTransactionWhenConfirmedReceived(const TransactionPtr & tx,
                                                const std::vector<unsigned char> & from);

    /**
     * @brief transaction
     * @param hash
     * @return
     */
    const TransactionPtr      transaction(const uint256 & hash);
    /**
     * @brief pendingTransaction
     * @param hash
     * @return
     */
    const TransactionPtr      pendingTransaction(const uint256 & hash);
    /**
     * @brief pendingTransactions
     * @return
     */
    std::list<TransactionPtr> pendingTransactions() const;
    /**
     * @brief transactions
     * @return
     */
    std::list<TransactionPtr> transactions() const;
    /**
     * @brief finishedTransactions
     * @return
     */
    std::list<TransactionPtr> finishedTransactions() const;

private:
    /**
     * @brief m_p
     */
    std::unique_ptr<Impl> m_p;
};

} // namespace xbridge

#endif // XBRIDGEEXCHANGE_H
