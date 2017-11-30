//******************************************************************************
//******************************************************************************

#ifndef XBRIDGETRANSACTIONSMODEL_H
#define XBRIDGETRANSACTIONSMODEL_H

#include "uint256.h"
#include "xbridge/xbridgetransactiondescr.h"
#include "xbridge/util/xbridgeerror.h"

#include <QAbstractTableModel>
#include <QStringList>
#include <QTimer>

#include <vector>
#include <string>
#include <boost/cstdint.hpp>

//******************************************************************************
//******************************************************************************
/**
 * @brief The XBridgeTransactionsModel class
 */
class XBridgeTransactionsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /**
     * @brief XBridgeTransactionsModel
     */
    XBridgeTransactionsModel();
    ~XBridgeTransactionsModel();

    /**
     * @brief The ColumnIndex enum
     */
    enum ColumnIndex
    {
        Total       = 0,
        FirstColumn = Total,
        Size        = 1,
        BID         = 2,
        State       = 3,
        LastColumn  = State
    };

    /**
     * @brief rawStateRole
     */
    static const int rawStateRole = Qt::UserRole + 1;

public:
    // static QString   thisCurrency();

    /**
     * @brief rowCount
     * @return
     */
    virtual int rowCount(const QModelIndex &) const;

    /**
     * @brief columnCount
     * @return
     */
    virtual int columnCount(const QModelIndex &) const;

    /**
     * @brief data
     * @param idx
     * @param role
     * @return
     */
    virtual QVariant data(const QModelIndex &idx, int role) const;

    /**
     * @brief headerData
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /**
     * @brief isMyTransaction
     * @param index
     * @return
     */
    bool isMyTransaction(const unsigned int index) const;


    /**
     * @brief newTransaction
     * @param from
     * @param to
     * @param fromCurrency
     * @param toCurrency
     * @param fromAmount
     * @param toAmount
     * @return
     */
    xbridge::Error newTransaction(const std::string &from,
                                  const std::string &to,
                                  const std::string &fromCurrency,
                                  const std::string &toCurrency,
                                  const double fromAmount,
                                  const double toAmount);

    /**
     * @brief newTransactionFromPending
     * @param id
     * @param hub
     * @param from
     * @param to
     * @return
     */
    xbridge::Error newTransactionFromPending(const uint256 &id,
                                             const std::vector<unsigned char> &hub,
                                             const std::string &from,
                                             const std::string &to);

    /**
     * @brief cancelTransaction
     * @param id
     * @return
     */
    bool cancelTransaction(const uint256 &id);

    /**
     * @brief rollbackTransaction
     * @param id
     * @return
     */
    bool rollbackTransaction(const uint256 &id);

    /**
     * @brief item
     * @param index
     * @return
     */
    XBridgeTransactionDescr item(const unsigned int index) const;

private slots:

    /**
     * @brief onTimer
     */
    void onTimer();

private:

    /**
     * @brief onTransactionReceived
     * @param tx
     */
    void onTransactionReceived(const XBridgeTransactionDescr &tx);

    /**
     * @brief onTransactionStateChanged
     * @param id
     * @param state
     */
    void onTransactionStateChanged(const uint256 &id, const uint32_t state);

    /**
     * @brief onTransactionCancelled
     * @param id
     * @param state
     * @param reason
     */
    void onTransactionCancelled(const uint256 &id, const uint32_t state, const uint32_t reason);

    /**
     * @brief transactionState
     * @param state
     * @return
     */
    QString transactionState(const XBridgeTransactionDescr::State state) const;

private:

    /**
     * @brief m_columns
     */
    QStringList m_columns;

    /**
     * @brief m_transactions
     */
    std::vector<XBridgeTransactionDescr> m_transactions;

    /**
     * @brief m_timer
     */
    QTimer m_timer;
};

#endif // XBRIDGETRANSACTIONSMODEL_H
