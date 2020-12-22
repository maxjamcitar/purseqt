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
        QMessageBox::critical(nullptr, "Currency conversion failure", "ERROR! Failed to find the conversion coefficient for currency " + currName + ".");
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
        QMessageBox::critical(nullptr, "Currency changing failure", "Failed to change active currency (currency " + otherCurr + " not found).");
    }
    else
        activeCurrency = otherCurr;
}

void CurrConversion::requestRatesHttp ()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    auto status = connect(manager, SIGNAL(finished(QNetworkReply*)),
                          this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://www.google.com")));

    //QByteArray data=reply->readAll();
    //qDebug() << data.data();

}

void CurrConversion::replyFinished(QNetworkReply *reply)
{
     QString answer = QString::fromUtf8(reply->readAll());
     qDebug () << answer;
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

void Money::setCurrency(const QString& otherCurrency)
{
    currency = otherCurrency;
}

bool Money::convertTo (const QString &otherCurr)
{
    float coefOther = CurrConversion::getCoef(otherCurr);
    float coefThis = CurrConversion::getCoef(currency);
    if (coefOther != 0 && coefThis != 0)
    {
        value *= coefOther / coefThis;
        value = round( value * 100.0 ) / 100.0; // rounding to 2 decimals
        currency = otherCurr;
        return true;
    }
    else
    {
        return false;
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

    float valueThisConverted = this->value / coefThis;
    valueThisConverted = round( valueThisConverted * 100.0 ) / 100.0; // rounding to 2 decimals
    float valueOtherConverted = otherMoney.getValue() / coefOther;
    valueOtherConverted = round( valueOtherConverted * 100.0 ) / 100.0; // rounding to 2 decimals

    return (valueThisConverted > valueOtherConverted);  // comparing USDs
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
    float valueThisConverted = this->value / coefThis;
    valueThisConverted = round( valueThisConverted * 100.0 ) / 100.0; // rounding to 2 decimals
    float valueOtherConverted = otherMoney.getValue() / coefOther;
    valueOtherConverted = round( valueOtherConverted * 100.0 ) / 100.0; // rounding to 2 decimals

    Money result(valueThisConverted + valueOtherConverted, "USD");
    result.convertTo(CurrConversion::activeCurrency);
    return result;  // comparing USDs
}

void Money::operator+= (const Money &otherMoney)
{
    Money result = *this + otherMoney;
    if (result.convertTo(this->currency))
    {
        this->value = result.getValue();
    }
}

Money Money::operator- (const Money &otherMoney) const
{
    float coefOther = CurrConversion::getCoef(otherMoney.getCurrency());
    float coefThis = CurrConversion::getCoef(currency);
    float valueThisConverted = this->value / coefThis;
    valueThisConverted = round( valueThisConverted * 100.0 ) / 100.0; // rounding to 2 decimals
    float valueOtherConverted = otherMoney.getValue() / coefOther;
    valueOtherConverted = round( valueOtherConverted * 100.0 ) / 100.0; // rounding to 2 decimals

    Money result(valueThisConverted - valueOtherConverted, "USD");
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
    return QStringLiteral("%1%2%3").arg( round(this->getValue() * 100.0) / 100.0 ).arg(sep).arg(this->getCurrency());
}
