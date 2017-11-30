//******************************************************************************
//******************************************************************************

#ifndef _BITCOINRPCCONNECTOR_H_
#define _BITCOINRPCCONNECTOR_H_

#include <vector>
#include <string>
#include <cstdint>

//******************************************************************************
//******************************************************************************
namespace rpc
{
    typedef std::pair<std::string, std::vector<std::string> > AddressBookEntry;

    /**
     * @brief requestAddressBook
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param entries
     * @return
     */
    bool requestAddressBook(const std::string &rpcuser,
                            const std::string &rpcpasswd,
                            const std::string &rpcip,
                            const std::string &rpcport,
                            std::vector<AddressBookEntry> & entries);

    /**
     * @brief The Info struct
     */
    struct Info
    {
        /**
         * @brief blocks
         */
        uint32_t blocks;
    };

    /**
     * @brief getInfo
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param info
     * @return
     */
    bool getInfo(const std::string &rpcuser,
                 const std::string &rpcpasswd,
                 const std::string &rpcip,
                 const std::string &rpcport,
                 Info &info);

    /**
     * @brief The Unspent struct
     */
    struct Unspent
    {
        /**
         * @brief txId
         */
        std::string txId;
        /**
         * @brief vout
         */
        int vout;
        /**
         * @brief amount
         */
        double amount;
    };

    /**
     * @brief listUnspent
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param entries
     * @return
     */
    bool listUnspent(const std::string &rpcuser,
                     const std::string &rpcpasswd,
                     const std::string &rpcip,
                     const std::string &rpcport,
                     std::vector<Unspent> &entries);

    /**
     * @brief gettxout
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param txid
     * @param out
     * @return
     */
    bool gettxout(const std::string &rpcuser,
                  const std::string &rpcpasswd,
                  const std::string &rpcip,
                  const std::string &rpcport,
                  const std::string &txid,
                  const uint32_t &out);

    /**
     * @brief getRawTransaction
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param txid
     * @param verbose
     * @param tx
     * @return
     */
    bool getRawTransaction(const std::string &rpcuser,
                           const std::string &rpcpasswd,
                           const std::string &rpcip,
                           const std::string &rpcport,
                           const std::string &txid,
                           const bool verbose,
                           std::string &tx);

    /**
     * @brief createRawTransaction
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param inputs
     * @param outputs
     * @param lockTime
     * @param tx
     * @return
     */
    bool createRawTransaction(const std::string &rpcuser,
                              const std::string &rpcpasswd,
                              const std::string &rpcip,
                              const std::string &rpcport,
                              const std::vector<std::pair<std::string, int> > &inputs,
                              const std::vector<std::pair<std::string, double> > &outputs,
                              const uint32_t lockTime,
                              std::string &tx);

    /**
     * @brief decodeRawTransaction
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param rawtx
     * @param txid
     * @param tx
     * @return
     */
    bool decodeRawTransaction(const std::string &rpcuser,
                              const std::string &rpcpasswd,
                              const std::string &rpcip,
                              const std::string &rpcport,
                              const std::string &rawtx,
                              std::string &txid,
                              std::string &tx);

    /**
     * @brief prevtxsJson
     * @param prevtxs
     * @return
     */
    std::string prevtxsJson(const std::vector<std::tuple<std::string, int, std::string, std::string> > &prevtxs);

    /**
     * @brief signRawTransaction
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param rawtx
     * @param complete
     * @return
     */
    bool signRawTransaction(const std::string &rpcuser,
                            const std::string &rpcpasswd,
                            const std::string &rpcip,
                            const std::string &rpcport,
                            std::string &rawtx,
                            bool &complete);

    /**
     * @brief signRawTransaction
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param rawtx
     * @param prevtxs
     * @param keys
     * @param complete
     * @return
     */
    bool signRawTransaction(const std::string &rpcuser,
                            const std::string &rpcpasswd,
                            const std::string &rpcip,
                            const std::string &rpcport,
                            std::string &rawtx,
                            const std::string &prevtxs,
                            const std::vector<std::string> &keys,
                            bool &complete);

    /**
     * @brief sendRawTransaction
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param rawtx
     * @param txid
     * @param errorCode
     * @return
     */
    bool sendRawTransaction(const std::string &rpcuser,
                            const std::string &rpcpasswd,
                            const std::string &rpcip,
                            const std::string &rpcport,
                            const std::string &rawtx,
                            std::string &txid,
                            int32_t &errorCode);

    /**
     * @brief getNewAddress
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param addr
     * @return
     */
    bool getNewAddress(const std::string &rpcuser,
                       const std::string &rpcpasswd,
                       const std::string &rpcip,
                       const std::string &rpcport,
                       std::string &addr);

    /**
     * @brief addMultisigAddress
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param keys
     * @param addr
     * @return
     */
    bool addMultisigAddress(const std::string &rpcuser,
                            const std::string &rpcpasswd,
                            const std::string &rpcip,
                            const std::string &rpcport,
                            const std::vector<std::string> &keys,
                            std::string &addr);

    /**
     * @brief getTransaction
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param txid
     * @param tx
     * @return
     */
    bool getTransaction(const std::string &rpcuser,
                        const std::string &rpcpasswd,
                        const std::string &rpcip,
                        const std::string &rpcport,
                        const std::string &txid,
                        std::string &tx);

    /**
     * @brief getNewPubKey
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param key
     * @return
     */
    bool getNewPubKey(const std::string &rpcuser,
                      const std::string &rpcpasswd,
                      const std::string &rpcip,
                      const std::string &rpcport,
                      std::string &key);

    /**
     * @brief dumpPrivKey
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param address
     * @param key
     * @return
     */
    bool dumpPrivKey(const std::string &rpcuser,
                     const std::string &rpcpasswd,
                     const std::string &rpcip,
                     const std::string &rpcport,
                     const std::string &address,
                     std::string &key);

    /**
     * @brief importPrivKey
     * @param rpcuser
     * @param rpcpasswd
     * @param rpcip
     * @param rpcport
     * @param key
     * @param label
     * @param noScanWallet
     * @return
     */
    bool importPrivKey(const std::string &rpcuser,
                       const std::string &rpcpasswd,
                       const std::string &rpcip,
                       const std::string &rpcport,
                       const std::string &key,
                       const std::string &label,
                       const bool &noScanWallet = false);

    // ethereum rpc
    /**
     * @brief eth_gasPrice
     * @param rpcip
     * @param rpcport
     * @param gasPrice
     * @return
     */
    bool eth_gasPrice(const std::string &rpcip,
                      const std::string &rpcport,
                      uint64_t &gasPrice);

    /**
     * @brief eth_accounts
     * @param rpcip
     * @param rpcport
     * @param addresses
     * @return
     */
    bool eth_accounts(const std::string &rpcip,
                      const std::string &rpcport,
                      std::vector<std::string> &addresses);

    /**
     * @brief eth_getBalance
     * @param rpcip
     * @param rpcport
     * @param account
     * @param amount
     * @return
     */
    bool eth_getBalance(const std::string &rpcip,
                        const std::string &rpcport,
                        const std::string &account,
                        uint64_t &amount);

    /**
     * @brief eth_sendTransaction
     * @param rpcip
     * @param rpcport
     * @param from
     * @param to
     * @param amount
     * @param fee
     * @return
     */
    bool eth_sendTransaction(const std::string &rpcip,
                             const std::string &rpcport,
                             const std::string &from,
                             const std::string &to,
                             const uint64_t &amount,
                             const uint64_t &fee);

    // helper fn-s
    /**
     * @brief getNewAddress
     * @param addr
     * @return
     */
    bool getNewAddress(std::vector<unsigned char> &addr);
    bool storeDataIntoBlockchain(const std::vector<unsigned char> &dstAddress,
                                 const double amount,
                                 const std::vector<unsigned char> &data,
                                 std::string &txid);

    /**
     * @brief getDataFromTx
     * @param txid
     * @param data
     * @return
     */
    bool getDataFromTx(const std::string & txid, std::vector<unsigned char> &data);

} // namespace rpc

#endif // _BITCOINRPCCONNECTOR_H_
