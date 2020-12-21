#include "src/money.h"
#include <QErrorMessage>
#include <QSet>
#include <QMap>
#include <QDebug>

// static variables
QSet<QString> CurrConversion::currencyList = QSet<QString>();
QMap<QString, float> CurrConversion::currencyMap = QMap<QString, float>();
QString CurrConversion::activeCurrency = QString("USD");

CurrConversion::CurrConversion()
{
    CurrConversion::addCurrency("USD", 1);
}

CurrConversion::~CurrConversion()
{
    // only smart pointers used
}

void CurrConversion::addCurrency (const QString& currName, const float coef)
{
    currencyList.insert(currName);
    currencyMap.insert(currName, coef);
}

void CurrConversion::removeCurrency (const QString& currName)
{
    currencyList.remove(currName);
    currencyMap.remove(currName);
}

void CurrConversion::clearMap ()
{
    currencyList.clear();
    currencyMap.clear();
}

bool CurrConversion::isCurrSaved (const QString& currName)
{
    auto iter = currencyList.find(currName);
    if (iter == currencyList.end())
        return false;
    else
        return true;
}

float CurrConversion::getCoef (const QString& currName)
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


QString CurrConversion::getActiveCurrency ()
{
    return activeCurrency;
}

void CurrConversion::changeActiveCurrency (const QString& otherCurr)
{
    if (!isCurrSaved(otherCurr))
    {
        QErrorMessage err;
        err.showMessage(QString("Failed to change active currency (currency " + otherCurr + " not found)."));
    }
    else
        activeCurrency = otherCurr;
}


//------------------------------------------------------------------------------------------------------------

Money::Money()
{
    value = 0;
    currency = CurrConversion::activeCurrency;
}

Money::~Money()
{

}

Money::Money(float otherValue)
{
    value = otherValue;
    currency = CurrConversion::activeCurrency;
}

Money::Money(const float otherValue, const QString& otherCurr)
{
    value = otherValue;
    currency = otherCurr;
}

Money::Money(const Money &otherMoney)
{
    if (this != &otherMoney)
    {
        this->value = otherMoney.getValue();
        this->currency = otherMoney.getCurrency();
    }

}

float Money::getValue() const
{
    return value;
}

void Money::setValue (const float otherValue)
{
    value = otherValue;
}

QString Money::getCurrency() const
{
    return currency;
}

void Money::convertTo (const QString &otherCurr)
{
    float coefOther = CurrConversion::getCoef(otherCurr);
    float coefThis = CurrConversion::getCoef(currency);
    if (coefOther != 0 && coefThis != 0)
    {
        value *= coefThis / coefOther;
        currency = otherCurr;
    }
}

void Money::operator= (const Money &otherMoney)
{
    if (this != &otherMoney)
    {
        this->value = otherMoney.getValue();
        this->currency = otherMoney.getCurrency();
    }
}

bool Money::operator> (const Money &otherMoney) const
{
    float coefOther = CurrConversion::getCoef(otherMoney.getCurrency());
    float coefThis = CurrConversion::getCoef(currency);
    return (this->value / coefThis) > (otherMoney.getValue() / coefOther);  // comparing USDs
}

bool Money::operator< (const Money &otherMoney) const
{
    return !(operator>(otherMoney));
}

bool Money::operator== (const Money &otherMoney) const
{
    return !(operator>(otherMoney) || operator<(otherMoney));
}

Money Money::operator+ (const Money &otherMoney) const
{
    float coefOther = CurrConversion::getCoef(otherMoney.getCurrency());
    float coefThis = CurrConversion::getCoef(currency);
    Money result((this->value / coefThis) + (otherMoney.getValue() / coefOther), "USD");
    result.convertTo(CurrConversion::activeCurrency);
    return result;  // comparing USDs
}

void Money::operator+= (const Money &otherMoney)
{
    Money result = *this + otherMoney;
    result.convertTo(this->currency);
    this->value = result.getValue();
}

Money Money::operator- (const Money &otherMoney) const
{
    float coefOther = CurrConversion::getCoef(otherMoney.getCurrency());
    float coefThis = CurrConversion::getCoef(currency);
    Money result((this->value / coefThis) - (otherMoney.getValue() / coefOther), "USD");
    result.convertTo(CurrConversion::activeCurrency);
    return result;  // comparing USDs
}

void Money::operator-= (const Money &otherMoney)
{
    Money result = *this - otherMoney;
    result.convertTo(this->currency);
    this->value = result.getValue();
}


QString Money::to_str (QString sep) const
{
    return QStringLiteral("%1%2%3").arg(this->getValue()).arg(sep).arg(this->getCurrency());
}
