//******************************************************************************
//******************************************************************************

#ifndef XBRIDGEADDRESSBOOKMODEL_H
#define XBRIDGEADDRESSBOOKMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

#include <string>
#include <tuple>
#include <vector>
#include <set>

//******************************************************************************
//******************************************************************************
/**
 * @brief The XBridgeAddressBookModel class
 */
class XBridgeAddressBookModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /**
     * @brief XBridgeAddressBookModel
     */
    XBridgeAddressBookModel();
    /**
      *
      * */
    ~XBridgeAddressBookModel();

    typedef std::tuple<std::string, std::string, std::string> AddressBookEntry;
    typedef std::vector<AddressBookEntry> AddressBook;

    /**
     * @brief The ColumnIndex enum
     */
    enum ColumnIndex
    {
        Currency     = 0,
        FirstColumn  = Currency,
        Name         = 1,
        Address      = 2,
        LastColumn   = Address
    };

    /**
     * @brief rowCount
     * @return
     */
    virtual int      rowCount(const QModelIndex &) const;
    /**
     * @brief columnCount
     * @return
     */
    virtual int      columnCount(const QModelIndex &) const;
    /**
     * @brief data
     * @param idx
     * @param role
     * @return
     */
    virtual QVariant data(const QModelIndex & idx, int role) const;
    /**
     * @brief headerData
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /**
     * @brief entry
     * @param row
     * @return
     */
    AddressBookEntry entry(const int row);

private:
    /**
     * @brief onAddressBookEntryReceived
     * @param currency
     * @param name
     * @param address
     */
    void onAddressBookEntryReceived(const std::string & currency,
                                    const std::string & name,
                                    const std::string & address);

private:
    /**
     * @brief m_columns
     */
    QStringList m_columns;

    /**
     * @brief m_addresses
     */
    std::set<std::string> m_addresses;
    /**
     * @brief m_addressBook
     */
    AddressBook m_addressBook;
};

#endif // XBRIDGEADDRESSBOOKMODEL_H
