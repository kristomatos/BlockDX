//******************************************************************************
//******************************************************************************

#ifndef XBRIDGEWALLETCONNECTORBCC_H
#define XBRIDGEWALLETCONNECTORBCC_H

#include "xbridgewalletconnectorbtc.h"

//*****************************************************************************
//*****************************************************************************
namespace xbridge
{

//******************************************************************************
//******************************************************************************
class BccWalletConnector : public BtcWalletConnector
{
public:
    BccWalletConnector();

public:
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

#endif // XBRIDGEWALLETCONNECTORBCC_H
