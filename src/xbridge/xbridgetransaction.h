//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGETRANSACTION_H
#define XBRIDGETRANSACTION_H

#include "uint256.h"
#include "xbridgetransactionmember.h"
#include "xkey.h"
#include "xbridgedef.h"

#include <vector>
#include <string>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

//******************************************************************************
//******************************************************************************
namespace xbridge
{

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The Transaction class
 */
class Transaction
{
public:
    // see strState when editing
    enum State
    {
        trInvalid = 0,
        trNew,
        trJoined,
        trHold,
        trInitialized,
        trCreated,
        trSigned,
        trCommited,

        trConfirmed,
        trFinished,
        trCancelled,
        trDropped
    };

    enum
    {
        // transaction lock time base, in seconds, 10 min
        lockTime = 600,

        // pending transaction ttl in seconds, 72 hours
        pendingTTL = 259200,

        // transaction ttl in seconds, 60 min
        TTL = 3600
    };

public:
    /**
     * @brief Transaction
     */
    Transaction();
    /**
     * @brief Transaction - constructor
     * @param id - id of transaction
     * @param sourceAddr - source address
     * @param sourceCurrency - source currency
     * @param sourceAmount - source amount
     * @param destAddr - destination address
     * @param destCurrency - destionation currency
     * @param destAmount - destionation amount
     */
    Transaction(const uint256                    & id,
                const std::vector<unsigned char> & sourceAddr,
                const std::string                & sourceCurrency,
                const uint64_t                   & sourceAmount,
                const std::vector<unsigned char> & destAddr,
                const std::string                & destCurrency,
                const uint64_t                   & destAmount);
    ~Transaction();

    /**
     * @brief id
     * @return id of transaction
     */
    uint256 id() const;


    /**
     * @brief state
     * @return state of transaction
     */
    State state() const;

    /**
     * @brief increaseStateCounter update state counter and update state
     * @param state new state of transaction
     * @param from source address
     * @return new state of transaction
     */
    State increaseStateCounter(const State state, const std::vector<unsigned char> & from);

    /**
     * @brief strState string description transaction state
     * @param state
     * @return string description transaction state
     */
    static std::string strState(const State state);
    /**
     * @brief strState
     * @return string description transaction state
     */
    std::string strState() const;

    /**
     * @brief updateTimestamp - update creation time of transaction
     */
    void updateTimestamp();
    /**
     * @brief createdTime
     * @return the creation time of transaction
     */
    boost::posix_time::ptime createdTime() const;

    /**
     * @brief isFinished checks transaction
     * @return true, if transaction finished, canceled or dropped
     */
    bool isFinished() const;
    /**
     * @brief isValid
     * @return true, if transaction is valid
     */
    bool isValid() const;
    /**
     * @brief isExpired
     * @return true, if time of creation the transaction more than 72 hours
     */
    bool isExpired() const;

    /**
     * @brief cancel - set transaction state to canceled
     */
    void cancel();
    /**
     * @brief drop - set transaction state to dropped
     */
    void drop();
    /**
     * @brief finish - set transaction state to finished
     */
    void finish();

    /**
     * @brief confirm set transaction state to confirmed
     * @param id - id of transaction
     * @return true, if transaction state change to confirmed
     */
    bool confirm(const std::string & id);

    // hash of transaction
    /**
     * @brief hash1
     * @return hash of transaction
     */
    uint256 hash1() const;
    /**
     * @brief hash2
     * @return hash of transaction
     */
    uint256 hash2() const;

    // uint256                    firstId() const;
    /**
     * @brief a_address
     * @return Alice's address of source
     */
    std::vector<unsigned char> a_address() const;

    /**
     * @brief a_destination
     * @return  Alice's destination address
     */
    std::vector<unsigned char> a_destination() const;
    /**
     * @brief a_currency
     * @return Alice's source currecy
     */
    std::string                a_currency() const;
    /**
     * @brief a_amount
     * @return Alice's source amount
     */
    uint64_t                   a_amount() const;
    /**
     * @brief a_payTx
     * @return
     */
    std::string                a_payTx() const;
    /**
     * @brief a_refTx
     * @return
     */
    std::string                a_refTx() const;
    /**
     * @brief a_bintxid
     * @return
     */
    std::string                a_bintxid() const;

    // TODO remove script
    /**
     * @brief a_innerScript
     * @return
     */
    std::vector<unsigned char> a_innerScript() const;

    /**
     * @brief a_datatxid
     * @return
     */
    uint256                    a_datatxid() const;
    /**
     * @brief a_pk1
     * @return Alice's public key
     */
    std::vector<unsigned char> a_pk1() const;

    // uint256                    secondId() const;
    /**
     * @brief b_address
     * @return Bob's source address
     */
    std::vector<unsigned char> b_address() const;
    /**
     * @brief b_destination
     * @return Bob's destionation address
     */
    std::vector<unsigned char> b_destination() const;
    /**
     * @brief b_currency
     * @return Bob's source currency
     */
    std::string                b_currency() const;
    /**
     * @brief b_amount
     * @return Bob's amount
     */
    uint64_t                   b_amount() const;
    /**
     * @brief b_payTx
     * @return
     */
    std::string                b_payTx() const;
    /**
     * @brief b_refTx
     * @return
     */
    std::string                b_refTx() const;
    /**
     * @brief b_bintxid
     * @return
     */
    std::string                b_bintxid() const;


    // TODO remove script
    /**
     * @brief b_innerScript
     * @return
     */
    std::vector<unsigned char> b_innerScript() const;

    // uint256                    b_datatxid() const;
    /**
     * @brief b_pk1
     * @return Bob's public key
     */
    std::vector<unsigned char> b_pk1() const;

    /**
     * @brief tryJoin
     * @param other
     * @return
     */
    bool tryJoin(const TransactionPtr other);

    /**
     * @brief setKeys - set public key for Alice or Bob transaction
     * @param addr - wallet address
     * @param datatxid
     * @param pk - public key
     * @return - true, if Alice or Bob public key value installed
     */
    bool                       setKeys(const std::vector<unsigned char> & addr,
                                       const uint256 & datatxid,
                                       const std::vector<unsigned char> & pk);
    /**
     * @brief setBinTxId
     * @param addr
     * @param id
     * @param innerScript
     * @return
     */
    bool                       setBinTxId(const std::vector<unsigned char> &addr,
                                          const std::string & id,
                                          const std::vector<unsigned char> & innerScript);

public:
    /**
     * @brief m_lock
     */
    boost::mutex               m_lock;

private:
    /**
     * @brief m_id - id of transaction
     */
    uint256                    m_id;

    /**
     * @brief m_created - time of creation transaction
     */
    boost::posix_time::ptime   m_created;

    /**
     * @brief m_state - state of transaction
     */
    State                      m_state;

    /**
     * @brief m_a_stateChanged - flag of Alice's transaction status changed
     */
    bool                       m_a_stateChanged;
    /**
     * @brief m_b_stateChanged - flag of Bob's transaction changed
     */
    bool                       m_b_stateChanged;

    /**
     * @brief m_confirmationCounter
     */
    unsigned int               m_confirmationCounter;

    /**
     * @brief m_sourceCurrency - source currency
     */
    std::string                m_sourceCurrency;
    /**
     * @brief m_destCurrency - destination currency
     */
    std::string                m_destCurrency;

    /**
     * @brief m_sourceAmount - source amount
     */
    uint64_t                   m_sourceAmount;
    /**
     * @brief m_destAmount - destinations amount
     */
    uint64_t                   m_destAmount;

    /**
     * @brief m_bintxid1
     */
    std::string                m_bintxid1;
    /**
     * @brief m_bintxid2
     */
    std::string                m_bintxid2;

    /**
     * @brief m_innerScript1
     */
    std::vector<unsigned char> m_innerScript1;
    /**
     * @brief m_innerScript2
     */
    std::vector<unsigned char> m_innerScript2;

    /**
     * @brief m_a - Alice's transaction
     */
    XBridgeTransactionMember   m_a;
    /**
     * @brief m_b - Bob's transaction
     */
    XBridgeTransactionMember   m_b;

    /**
     * @brief m_a_datatxid
     */
    uint256                    m_a_datatxid;
    /**
     * @brief m_b_datatxid
     */
    uint256                    m_b_datatxid;

    /**
     * @brief m_a_pk1 - Alice's public key
     */
    std::vector<unsigned char> m_a_pk1;
    /**
     * @brief m_b_pk1 - Bob's public key
     */
    std::vector<unsigned char> m_b_pk1;
};

} // namespace xbridge

#endif // XBRIDGETRANSACTION_H
