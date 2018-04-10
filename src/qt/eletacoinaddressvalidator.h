// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELETACOIN_QT_ELETACOINADDRESSVALIDATOR_H
#define ELETACOIN_QT_ELETACOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class EletaCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit EletaCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** EletaCoin address widget validator, checks for a valid eletacoin address.
 */
class EletaCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit EletaCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ELETACOIN_QT_ELETACOINADDRESSVALIDATOR_H
