//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGESESSION_H
#define XBRIDGESESSION_H

#include "xbridge.h"
#include "xbridgepacket.h"
#include "xbridgetransaction.h"
#include "xbridgetransactiondescr.h"
#include "xbridgewallet.h"
#include "FastDelegate.h"
#include "uint256.h"
#include "xkey.h"
#include "xbitcointransaction.h"
#include "bitcoinrpcconnector.h"
#include "script/script.h"

#include <memory>
#include <set>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>

extern const unsigned int LOCKTIME_THRESHOLD;

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridgeSession class
 */
class XBridgeSession
        : public std::enable_shared_from_this<XBridgeSession>
        , private boost::noncopyable
{
public:
    /**
     * @brief XBridgeSession - constructor
     */
    XBridgeSession();

    /**
     * @brief XBridgeSession
     * @param wallet
     */
    XBridgeSession(const WalletParam &wallet);

    /**
     * @brief ~XBridgeSession
     */
    virtual ~XBridgeSession();

    /**
     * @brief sessionAddr
     * @return
     */
    const std::vector<unsigned char> &sessionAddr() const { return m_myid; }

    /**
     * @brief currency
     * @return
     */
    std::string currency() const  { return m_wallet.currency; }

    /**
     * @brief minAmount
     * @return
     */
    double minAmount() const { return  static_cast<double>(m_wallet.minAmount) / 100000; }

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
    /**
     * @brief toXAddr
     * @param addr
     * @param currency
     * @return
     */
    static std::vector<unsigned char> toXAddr(const std::string &addr, const std::string &currency);

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

    /**
     * @brief requestAddressBook
     */
    void requestAddressBook();

    /**
     * @brief checkAmount
     * @param amount
     * @return
     */
    bool checkAmount(const uint64_t amount) const;

    /**
     * @brief checkAmountAndGetInputs
     * @param amount
     * @param inputs
     * @return
     */
    bool checkAmountAndGetInputs(const uint64_t amount,
                                 std::vector<rpc::Unspent> &inputs) const;

    /**
     * @brief getWalletBalance
     * @return
     */
    double getWalletBalance() const;

    /**
     * @brief rollbacktXBridgeTransaction
     * @param id
     * @return
     */
    bool rollbacktXBridgeTransaction(const uint256 &id);

protected:
    // reimplement for currency
    // virtual std::string fromXAddr(const std::vector<unsigned char> & xaddr) const = 0;

    /**
     * @brief toXAddr
     * @param addr
     * @return
     */
    virtual std::vector<unsigned char> toXAddr(const std::string & addr) const = 0;

    /**
     * @brief lockTime
     * @param role
     * @return
     */
    virtual uint32_t lockTime(const char role) const = 0;

    /**
     * @brief createTransaction
     * @return
     */
    virtual xbridge::CTransactionPtr createTransaction() const = 0;

    /**
     * @brief createTransaction
     * @param inputs
     * @param outputs
     * @param lockTime
     * @return
     */
    virtual xbridge::CTransactionPtr createTransaction(const std::vector<std::pair<std::string, int> > &inputs,
                                                       const std::vector<std::pair<CScript, double> > &outputs,
                                                       const uint32_t lockTime = 0) const = 0;

    /**
     * @brief signTransaction
     * @param key
     * @param transaction
     * @param inputIdx
     * @param unlockScript
     * @param signature
     * @return
     */
    virtual bool signTransaction(const xbridge::CKey &key,
                                 const xbridge::CTransactionPtr &transaction,
                                 const uint32_t inputIdx,
                                 const CScript &unlockScript,
                                 std::vector<unsigned char> &signature) = 0;

private:
    /**
     * @brief init
     */
    virtual void init();

    /**
     * @brief encryptPacket
     * @param packet
     * @return
     */
    bool encryptPacket(XBridgePacketPtr packet);

    /**
     * @brief decryptPacket
     * @param packet
     * @return
     */
    bool decryptPacket(XBridgePacketPtr packet);

protected:
    /**
     * @brief myaddr
     * @return
     */
    const unsigned char* myaddr() const;

    /**
     * @brief sendPacket
     * @param to
     * @param packet
     */
    void sendPacket(const std::vector<unsigned char> &to, const XBridgePacketPtr &packet);

    /**
     * @brief sendPacketBroadcast
     * @param packet
     */
    void sendPacketBroadcast(XBridgePacketPtr packet);

    //

    /**
     * @brief checkPacketAddress
     * @param packet
     * @return return return true if packet for me and need to process
     */
    bool checkPacketAddress(XBridgePacketPtr packet);

    /**
     * @brief currencyToLog - make string write to LOG
     * @return generated string
     */
    virtual std::string currencyToLog() const { return std::string("[") + m_wallet.currency + std::string("]"); }

    /**
     * @brief makeNewPubKey
     * @param newPKey
     * @return
     */
    bool makeNewPubKey(xbridge::CPubKey &newPKey) const;


    /**
     * @brief minTxFee1
     * @param inputCount
     * @param outputCount
     * @return
     */
    double minTxFee1(const uint32_t inputCount, const uint32_t outputCount);

    /**
     * @brief minTxFee2
     * @param inputCount
     * @param outputCount
     * @return
     */
    double minTxFee2(const uint32_t inputCount, const uint32_t outputCount);

    /**
     * @brief round_x
     * @param val
     * @param prec
     * @return
     */
    std::string round_x(const long double val, uint32_t prec);

    /**
     * @brief checkDepositTx
     * @param xtx
     * @param depositTxId
     * @param confirmations
     * @param neededAmount
     * @param isGood
     * @return
     */
    bool checkDepositTx(const XBridgeTransactionDescrPtr &xtx,
                        const std::string &depositTxId,
                        const uint32_t &confirmations,
                        const uint64_t &neededAmount,
                        bool &isGood);

    // fn search xaddress in transaction and restore full 'coin' address as string
    /**
     * @brief isAddressInTransaction
     * @param address
     * @param tx
     * @param fullAddress
     * @return
     */
    bool isAddressInTransaction(const std::vector<unsigned char> &address,
                                const XBridgeTransactionPtr &tx,
                                std::string &fullAddress);

protected:
    /**
     * @brief processInvalid
     * @param packet
     * @return
     */
    virtual bool processInvalid(XBridgePacketPtr packet);

    /**
     * @brief processZero
     * @param packet
     * @return
     */
    virtual bool processZero(XBridgePacketPtr packet);

    /**
     * @brief processAnnounceAddresses
     * @param packet
     * @return
     */
    virtual bool processAnnounceAddresses(XBridgePacketPtr packet);

    /**
     * @brief processXChatMessage
     * @param packet
     * @return
     */
    virtual bool processXChatMessage(XBridgePacketPtr packet);


    /**
     * @brief processTransaction
     * @param packet
     * @return
     */
    virtual bool processTransaction(XBridgePacketPtr packet);

    /**
     * @brief processPendingTransaction
     * @param packet
     * @return
     */
    virtual bool processPendingTransaction(XBridgePacketPtr packet);

    /**
     * @brief processTransactionAccepting
     * @param packet
     * @return
     */
    virtual bool processTransactionAccepting(XBridgePacketPtr packet);

    /**
     * @brief processTransactionHold
     * @param packet
     * @return
     */
    virtual bool processTransactionHold(XBridgePacketPtr packet);

    /**
     * @brief processTransactionHoldApply
     * @param packet
     * @return
     */
    virtual bool processTransactionHoldApply(XBridgePacketPtr packet);

    /**
     * @brief processTransactionInit
     * @param packet
     * @return
     */
    virtual bool processTransactionInit(XBridgePacketPtr packet);

    /**
     * @brief processTransactionInitialized
     * @param packet
     * @return
     */
    virtual bool processTransactionInitialized(XBridgePacketPtr packet);

    /**
     * @brief processTransactionCreate
     * @param packet
     * @return
     */
    virtual bool processTransactionCreate(XBridgePacketPtr packet);

    /**
     * @brief processTransactionCreatedA
     * @param packet
     * @return
     */
    virtual bool processTransactionCreatedA(XBridgePacketPtr packet);

    /**
     * @brief processTransactionCreatedB
     * @param packet
     * @return
     */
    virtual bool processTransactionCreatedB(XBridgePacketPtr packet);

    /**
     * @brief processTransactionConfirmA
     * @param packet
     * @return
     */
    virtual bool processTransactionConfirmA(XBridgePacketPtr packet);

    /**
     * @brief processTransactionConfirmedA
     * @param packet
     * @return
     */
    virtual bool processTransactionConfirmedA(XBridgePacketPtr packet);

    /**
     * @brief processTransactionConfirmB
     * @param packet
     * @return
     */
    virtual bool processTransactionConfirmB(XBridgePacketPtr packet);

    /**
     * @brief processTransactionConfirmedB
     * @param packet
     * @return
     */
    virtual bool processTransactionConfirmedB(XBridgePacketPtr packet);

    /**
     * @brief finishTransaction
     * @param tr
     * @return
     */
    virtual bool finishTransaction(XBridgeTransactionPtr tr);

    /**
     * @brief sendCancelTransaction
     * @param txid
     * @param reason
     * @return
     */
    virtual bool sendCancelTransaction(const uint256 &txid,
                                       const TxCancelReason &reason);

    /**
     * @brief sendCancelTransaction
     * @param tx
     * @param reason
     * @return
     */
    virtual bool sendCancelTransaction(const XBridgeTransactionDescrPtr &tx,
                                       const TxCancelReason &reason);

    /**
     * @brief rollbackTransaction
     * @param tr
     * @return
     */
    virtual bool rollbackTransaction(XBridgeTransactionPtr tr);

    /**
     * @brief processTransactionCancel
     * @param packet
     * @return
     */
    virtual bool processTransactionCancel(XBridgePacketPtr packet);

    /**
     * @brief cancelOrRollbackTransaction
     * @param txid
     * @param reason
     * @return
     */
    bool cancelOrRollbackTransaction(const uint256 &txid, const TxCancelReason &reason);

    /**
     * @brief processTransactionFinished
     * @param packet
     * @return
     */
    virtual bool processTransactionFinished(XBridgePacketPtr packet);

    /**
     * @brief processTransactionRollback
     * @param packet
     * @return
     */
    virtual bool processTransactionRollback(XBridgePacketPtr packet);

    /**
     * @brief processTransactionDropped
     * @param packet
     * @return
     */
    virtual bool processTransactionDropped(XBridgePacketPtr packet);

protected:

    /**
     * @brief m_myid
     */
    std::vector<unsigned char> m_myid;

    /**
     * @brief PacketHandler
     */
    typedef fastdelegate::FastDelegate1<XBridgePacketPtr, bool> PacketHandler;

    /**
     * @brief PacketHandlersMap
     */
    typedef std::map<const int, PacketHandler> PacketHandlersMap;

    /**
     * @brief m_handlers
     */
    PacketHandlersMap m_handlers;

protected:

    /**
     * @brief m_addressBook
     */
    std::set<std::vector<unsigned char> > m_addressBook;

    /**
     * @brief m_wallet
     */
    WalletParam       m_wallet;
};//class XBridgeSession

/**
 * @brief XBridgeSessionPtr
 */
typedef std::shared_ptr<XBridgeSession> XBridgeSessionPtr;

#endif // XBRIDGESESSION_H
