//******************************************************************************
//******************************************************************************

#ifndef XBRIDGETRANSACTIONSVIEW_H
#define XBRIDGETRANSACTIONSVIEW_H

#include "xbridgetransactionsmodel.h"
#include "xbridgetransactiondialog.h"

// #include "../walletmodel.h"

#include <QWidget>
#include <QMenu>
#include <QSortFilterProxyModel>

class QTableView;
class QTextEdit;

//******************************************************************************
//******************************************************************************
/**
 * @brief The StateSortFilterProxyModel class
 */
class StateSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    /**
     * @brief StateSortFilterProxyModel
     * @param parent
     */
    StateSortFilterProxyModel(QObject *parent = 0) : QSortFilterProxyModel(parent) {}

    /**
     * @brief setAcceptedStates
     * @param acceptedStates
     */
    void setAcceptedStates(const QList<xbridge::TransactionDescr::State> &acceptedStates)
    {
        m_acceptedStates = acceptedStates;
    }

protected:
    /**
     * @brief filterAcceptsRow
     * @param source_row
     * @param source_parent
     * @return
     */
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override
    {
        QModelIndex index = sourceModel()->index(source_row, XBridgeTransactionsModel::State, source_parent);
        QVariant stateVariant = sourceModel()->data(index, XBridgeTransactionsModel::rawStateRole);

        if(stateVariant.isValid())
        {
            bool ok;
            int stateValue = stateVariant.toInt(&ok);

            if(ok)
            {
                xbridge::TransactionDescr::State transactionState = static_cast<xbridge::TransactionDescr::State>(stateValue);
                return m_acceptedStates.contains(transactionState);
            }
        }

        return false;
    }

private:
    /**
     * @brief m_acceptedStates
     */
    QList<xbridge::TransactionDescr::State> m_acceptedStates;

};


//******************************************************************************
//******************************************************************************
/**
 * @brief The XBridgeTransactionsView class
 */
class XBridgeTransactionsView : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief XBridgeTransactionsView
     * @param parent
     */
    explicit XBridgeTransactionsView(QWidget *parent = 0);

private:
    /**
     * @brief setupUi
     */
    void setupUi();
    /**
     * @brief setupContextMenu
     * @param index
     * @return
     */
    QMenu * setupContextMenu(QModelIndex & index);

private slots:
    /**
     * @brief onNewTransaction
     */
    void onNewTransaction();
    /**
     * @brief onAcceptTransaction
     */
    void onAcceptTransaction();
    /**
     * @brief onCancelTransaction
     */
    void onCancelTransaction();
    /**
     * @brief onRollbackTransaction
     */
    void onRollbackTransaction();

    /**
     * @brief onContextMenu
     * @param pt
     */
    void onContextMenu(QPoint pt);

    /**
     * @brief onToggleHideHistoricTransactions
     */
    void onToggleHideHistoricTransactions();

private:
    // WalletModel            * m_walletModel;

    /**
     * @brief m_txModel
     */
    XBridgeTransactionsModel    m_txModel;
    /**
     * @brief m_transactionsProxy
     */
    StateSortFilterProxyModel   m_transactionsProxy;
    /**
     * @brief m_historicTransactionsProxy
     */
    StateSortFilterProxyModel   m_historicTransactionsProxy;

    /**
     * @brief m_dlg
     */
    XBridgeTransactionDialog m_dlg;

    /**
     * @brief m_transactionsList
     */
    QTableView  * m_transactionsList;
    /**
     * @brief m_historicTransactionsList
     */
    QTableView  * m_historicTransactionsList;

    /**
     * @brief m_contextMenuIndex
     */
    QModelIndex   m_contextMenuIndex;
};

#endif // XBRIDGETRANSACTIONSVIEW_H
