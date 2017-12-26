//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGEWALLETCONNECTORBTC_H
#define XBRIDGEWALLETCONNECTORBTC_H

#include "xbridgewalletconnector.h"

//*****************************************************************************
//*****************************************************************************
namespace xbridge
{

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The BtcWalletConnector class
 */
class BtcWalletConnector : public WalletConnector
{
public:
    /**
     * @brief BtcWalletConnector
     */
    BtcWalletConnector();

public:
    // reimplement for currency
    /**
     * @brief fromXAddr
     * @param xaddr
     * @return
     */
    std::string fromXAddr(const std::vector<unsigned char> & xaddr) const;
    /**
     * @brief toXAddr
     * @param addr
     * @return
     */
    std::vector<unsigned char> toXAddr(const std::string & addr) const;

public:
    /**
     * @brief requestAddressBook
     * @param entries
     * @return
     */
    bool requestAddressBook(std::vector<wallet::AddressBookEntry> & entries);

    /**
     * @brief getUnspent
     * @param inputs
     * @return
     */
    bool getUnspent(std::vector<wallet::UtxoEntry> & inputs) const;
    /**
     * @brief lockUnspent
     * @param inputs
     * @param lock
     * @return
     */
    bool lockUnspent(const std::vector<wallet::UtxoEntry> & inputs, const bool lock = true) const;

    /**
     * @brief getRawTransaction
     * @param txid
     * @param verbose
     * @param tx
     * @return
     */
    bool getRawTransaction(const std::string & txid, const bool verbose, std::string & tx);

    /**
     * @brief getNewAddress
     * @param addr
     * @return
     */
    bool getNewAddress(std::string & addr);

    /**
     * @brief createRawTransaction
     * @param inputs
     * @param outputs
     * @param lockTime
     * @param tx
     * @return
     */
    bool createRawTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                              const std::vector<std::pair<std::string, double> > & outputs,
                              const uint32_t lockTime,
                              std::string & tx);

    /**
     * @brief signRawTransaction
     * @param rawtx
     * @param complete
     * @return
     */
    bool signRawTransaction(std::string & rawtx, bool & complete);

    /**
     * @brief decodeRawTransaction
     * @param rawtx
     * @param txid
     * @param tx
     * @return
     */
    bool decodeRawTransaction(const std::string & rawtx,
                              std::string & txid,
                              std::string & tx);

    /**
     * @brief sendRawTransaction
     * @param rawtx
     * @param txid
     * @param errorCode
     * @return
     */
    bool sendRawTransaction(const std::string & rawtx,
                            std::string & txid,
                            int32_t & errorCode);

public:
    /**
     * @brief newKeyPair
     * @param pubkey
     * @param privkey
     * @return
     */
    bool newKeyPair(std::vector<unsigned char> & pubkey, std::vector<unsigned char> & privkey);

    /**
     * @brief getKeyId
     * @param pubkey
     * @return
     */
    std::vector<unsigned char> getKeyId(const std::vector<unsigned char> & pubkey);

    /**
     * @brief getScriptId
     * @param script
     * @return
     */
    std::vector<unsigned char> getScriptId(const std::vector<unsigned char> & script);

    /**
     * @brief scriptIdToString
     * @param id
     * @return
     */
    std::string scriptIdToString(const std::vector<unsigned char> & id) const;

    /**
     * @brief minTxFee1 calculate tx fee for deposit tx
     * output count always 1
     * @param inputCount
     * @param outputCount
     * @return
     */
    double minTxFee1(const uint32_t inputCount, const uint32_t outputCount);
    /**
     * @brief minTxFee2 calculate tx fee for payment/refund tx
     * input count always 1
     * @param inputCount
     * @param outputCount
     * @return
     */
    double minTxFee2(const uint32_t inputCount, const uint32_t outputCount);

    /**
     * @brief checkTransaction
     * @param depositTxId
     * @param isGood
     * @return  return false if deposit tx not found (need wait tx)
     * true if tx found and checked
     * isGood == true id depost tx is OK
     */
    bool checkTransaction(const std::string & depositTxId,
                          const std::string & /*destination*/,
                          const uint64_t & /*amount*/,
                          bool & isGood);

    /**
     * @brief lockTime
     * @param role
     * @return
     */
    uint32_t lockTime(const char role) const;

    /**
     * @brief createDepositUnlockScript
     * @param myPubKey
     * @param otherPubKey
     * @param xdata
     * @param lockTime
     * @param resultSript
     * @return
     */
    bool createDepositUnlockScript(const std::vector<unsigned char> & myPubKey,
                                   const std::vector<unsigned char> & otherPubKey,
                                   const std::vector<unsigned char> & xdata,
                                   const uint32_t lockTime,
                                   std::vector<unsigned char> & resultSript);

    /**
     * @brief createDepositTransaction
     * @param inputs
     * @param outputs
     * @param txId
     * @param rawTx
     * @return
     */
    bool createDepositTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                  const std::vector<std::pair<std::string, double> > & outputs,
                                  std::string & txId,
                                  std::string & rawTx);

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
    bool createRefundTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                 const std::vector<std::pair<std::string, double> > & outputs,
                                 const std::vector<unsigned char> & mpubKey,
                                 const std::vector<unsigned char> & mprivKey,
                                 const std::vector<unsigned char> & innerScript,
                                 const uint32_t lockTime,
                                 std::string & txId,
                                 std::string & rawTx);

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
    bool createPaymentTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                  const std::vector<std::pair<std::string, double> > & outputs,
                                  const std::vector<unsigned char> & mpubKey,
                                  const std::vector<unsigned char> & mprivKey,
                                  const std::vector<unsigned char> & xpubKey,
                                  const std::vector<unsigned char> & innerScript,
                                  std::string & txId,
                                  std::string & rawTx);
};

} // namespace xbridge

#endif // XBRIDGEWALLETCONNECTORBTC_H
