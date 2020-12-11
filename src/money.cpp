#include "money.h"
#include <QErrorMessage>
#include <QtCore/QSet>
#include <QtCore/QMap>

CurrConversion::CurrConversion()
{
    currencyList = QSet<QString>();
    currencyMap = QMap<QString, float>();
    CurrConversion::addCurrency("USD", 1);
}

CurrConversion::~CurrConversion()
{
    // only smart pointers used
}

void CurrConversion::addCurrency (QString currName, float coef)
{
    currencyList.insert(currName);
    currencyMap.insert(currName, coef);
}

void CurrConversion::removeCurrency (QString currName)
{
    currencyList.remove(currName);
    currencyMap.remove(currName);
}

void CurrConversion::clearMap ()
{
    currencyList.clear();
    currencyMap.clear();
}

float CurrConversion::getCoef (QString currName)
{
    auto currIter = currencyMap.find(currName);
    if (currIter == currencyMap.end())
    {
        QErrorMessage err;
        err.showMessage(QString("Failed to find the conversion coefficient for currency " + currName + "."));
        return 0;
    }
    return currIter.value();
}

//------------------------------------------------------------------------------------------------------------

Money::Money()
{
    value = 0;
    activeCurrency = "USD";
    currency = activeCurrency;
}

Money::~Money()
{

}

Money::Money(float otherValue)
{
    value = otherValue;
}

Money::Money(float otherValue, QString otherCurr)
{
    float coefOther = CurrConversion::getCoef(otherCurr);
    float coefThis = CurrConversion::getCoef(currency);
    value = otherValue * (coefThis / coefOther);
    currency = otherCurr;
}

Money::Money(Money &otherMoney)
{
    Money(otherMoney.getValue(), otherMoney.getCurrency());
}

float Money::getValue() const
{
    return value;
}

void Money::setValue (float otherValue)
{
    value = otherValue;
}

QString Money::getCurrency() const
{
    return currency;
}

void Money::convertTo (QString otherCurr)
{
    float coefOther = CurrConversion::getCoef(otherCurr);
    float coefThis = CurrConversion::getCoef(currency);
    value *= coefThis / coefOther;
    currency = otherCurr;
}

bool Money::operator> (Money &otherMoney) const
{
    float coefOther = CurrConversion::getCoef(otherMoney.getCurrency());
    float coefThis = CurrConversion::getCoef(currency);
    return (this->value / coefThis) > (otherMoney.getValue() / coefOther);
}

bool Money::operator< (Money &otherMoney) const
{
    return !(operator>(otherMoney));
}

bool Money::operator== (Money &otherMoney) const
{
    return !(operator>(otherMoney) || operator<(otherMoney));
}

QString Money::to_str (QString sep) const
{
    return QStringLiteral("%1%2%3").arg(this->getValue()).arg(sep).arg(this->getCurrency());
}

Money Money::parseString (QString str, QString sep) const
{
    QString readToken;
    QString token = str.QStringRef();
}

QString Money::getActiveCurrency ()
{
    return activeCurrency;
}

void Money::changeActiveCurrency (QString otherCurr)
{
    activeCurrency = otherCurr;
}
