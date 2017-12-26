//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGEWALLETCONNECTOR_H
#define XBRIDGEWALLETCONNECTOR_H

#include "xbridgewallet.h"

#include <vector>
#include <string>
#include <memory>

//*****************************************************************************
//*****************************************************************************
namespace xbridge
{

//*****************************************************************************
//*****************************************************************************
namespace wallet
{
typedef std::pair<std::string, std::vector<std::string> > AddressBookEntry;

struct UtxoEntry
{
    std::string txId;
    uint32_t    vout;
    double      amount;

    friend bool operator < (const UtxoEntry & l, const UtxoEntry & r);
    friend bool operator == (const UtxoEntry & l, const UtxoEntry & r);
};

} // namespace wallet

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The WalletConnector class
 */
class WalletConnector : public WalletParam
{
public:
    /**
     * @brief WalletConnector
     */
    WalletConnector();

public:
    /**
     * @brief operator =
     * @param other
     * @return
     */
    WalletConnector & operator = (const WalletParam & other)
    {
        *(WalletParam *)this = other;
        return *this;
    }

public:
    // reimplement for currency
    /**
     * @brief fromXAddr
     * @param xaddr
     * @return
     */
    virtual std::string fromXAddr(const std::vector<unsigned char> & xaddr) const = 0;
    /**
     * @brief toXAddr
     * @param addr
     * @return
     */
    virtual std::vector<unsigned char> toXAddr(const std::string & addr) const = 0;

public:
    // wallet RPC

    /**
     * @brief requestAddressBook
     * @param entries
     * @return
     */
    virtual bool requestAddressBook(std::vector<wallet::AddressBookEntry> & entries) = 0;

    /**
     * @brief getUnspent
     * @param inputs
     * @return
     */
    virtual bool getUnspent(std::vector<wallet::UtxoEntry> & inputs) const = 0;

    /**
     * @brief checkAmount
     * @param amount
     * @return
     */
    bool checkAmount(const uint64_t amount) const;
    /**
     * @brief getWalletBalance
     * @return
     */
    double getWalletBalance() const;

    /**
     * @brief lockUnspent
     * @param inputs
     * @param lock
     * @return
     */
    virtual bool lockUnspent(const std::vector<wallet::UtxoEntry> & inputs,
                             const bool lock = true) const = 0;

    /**
     * @brief getRawTransaction
     * @param txid
     * @param verbose
     * @param tx
     * @return
     */
    virtual bool getRawTransaction(const std::string & txid, const bool verbose, std::string & tx) = 0;

    /**
     * @brief getNewAddress
     * @param addr
     * @return
     */
    virtual bool getNewAddress(std::string & addr) = 0;

    /**
     * @brief createRawTransaction
     * @param inputs
     * @param outputs
     * @param lockTime
     * @param tx
     * @return
     */
    virtual bool createRawTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                      const std::vector<std::pair<std::string, double> > & outputs,
                                      const uint32_t lockTime,
                                      std::string & tx) = 0;

    /**
     * @brief signRawTransaction
     * @param rawtx
     * @param complete
     * @return
     */
    virtual bool signRawTransaction(std::string & rawtx, bool & complete) = 0;

    /**
     * @brief decodeRawTransaction
     * @param rawtx
     * @param txid
     * @param tx
     * @return
     */
    virtual bool decodeRawTransaction(const std::string & rawtx,
                                      std::string & txid,
                                      std::string & tx) = 0;

    /**
     * @brief sendRawTransaction
     * @param rawtx
     * @param txid
     * @param errorCode
     * @return
     */
    virtual bool sendRawTransaction(const std::string & rawtx,
                                    std::string & txid,
                                    int32_t & errorCode) = 0;

public:
    // helper functions

    /**
     * @brief newKeyPair
     * @param pubkey
     * @param privkey
     * @return
     */
    virtual bool newKeyPair(std::vector<unsigned char> & pubkey, std::vector<unsigned char> & privkey) = 0;

    /**
     * @brief getKeyId
     * @param pubkey
     * @return
     */
    virtual std::vector<unsigned char> getKeyId(const std::vector<unsigned char> & pubkey) = 0;
    /**
     * @brief getScriptId
     * @param script
     * @return
     */
    virtual std::vector<unsigned char> getScriptId(const std::vector<unsigned char> & script) = 0;
    /**
     * @brief scriptIdToString
     * @param id
     * @return
     */
    virtual std::string scriptIdToString(const std::vector<unsigned char> & id) const = 0;

    /**
     * @brief minTxFee1
     * @param inputCount
     * @param outputCount
     * @return
     */
    virtual double minTxFee1(const uint32_t inputCount, const uint32_t outputCount) = 0;

    /**
     * @brief minTxFee2
     * @param inputCount
     * @param outputCount
     * @return
     */
    virtual double minTxFee2(const uint32_t inputCount, const uint32_t outputCount) = 0;

    /**
     * @brief checkTransaction
     * @param depositTxId
     * @param isGood
     * @return
     */
    virtual bool checkTransaction(const std::string & depositTxId,
                                  const std::string & /*destination*/,
                                  const uint64_t & /*amount*/,
                                  bool & isGood) = 0;

    /**
     * @brief lockTime
     * @param role
     * @return
     */
    virtual uint32_t lockTime(const char role) const = 0;

    /**
     * @brief createDepositUnlockScript
     * @param myPubKey
     * @param otherPubKey
     * @param xdata
     * @param lockTime
     * @param resultSript
     * @return
     */
    virtual bool createDepositUnlockScript(const std::vector<unsigned char> & myPubKey,
                                           const std::vector<unsigned char> & otherPubKey,
                                           const std::vector<unsigned char> & xdata,
                                           const uint32_t lockTime,
                                           std::vector<unsigned char> & resultSript) = 0;

    /**
     * @brief createDepositTransaction
     * @param inputs
     * @param outputs
     * @param txId
     * @param rawTx
     * @return
     */
    virtual bool createDepositTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                          const std::vector<std::pair<std::string, double> > & outputs,
                                          std::string & txId,
                                          std::string & rawTx) = 0;

    /**
     * @brief createRefundTransaction
     * @param inputs
     * @param outputs
     * @param mpubKey
     * @param mprivKey
     * @param innerScript
     * @param lockTime
     * @param txId
     * @param rawTx
     * @return
     */
    virtual bool createRefundTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                         const std::vector<std::pair<std::string, double> > & outputs,
                                         const std::vector<unsigned char> & mpubKey,
                                         const std::vector<unsigned char> & mprivKey,
                                         const std::vector<unsigned char> & innerScript,
                                         const uint32_t lockTime,
                                         std::string & txId,
                                         std::string & rawTx) = 0;

    /**
     * @brief createPaymentTransaction
     * @param inputs
     * @param outputs
     * @param mpubKey
     * @param mprivKey
     * @param xpubKey
     * @param innerScript
     * @param txId
     * @param rawTx
     * @return
     */
    virtual bool createPaymentTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                          const std::vector<std::pair<std::string, double> > & outputs,
                                          const std::vector<unsigned char> & mpubKey,
                                          const std::vector<unsigned char> & mprivKey,
                                          const std::vector<unsigned char> & xpubKey,
                                          const std::vector<unsigned char> & innerScript,
                                          std::string & txId,
                                          std::string & rawTx) = 0;
};

} // namespace xbridge

#endif // XBRIDGEWALLETCONNECTOR_H
