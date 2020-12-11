#ifndef MONEY_H
#define MONEY_H

#include "QtCore/QString"

class CurrConversion
{
public:
    CurrConversion();
    ~CurrConversion();
    static void addCurrency (QString currName, float coef);
    static void removeCurrency (QString currName);
    static void clearMap ();
    static float getCoef (QString currName);
    // todo import/export from/to files (or online)
    static QSet<QString> currencyList;  // currencies are named with compliance with ISO 4217
private:
    static QMap<QString, float> currencyMap;   // "float" is coefficient for conversion: 1 USD -> "float" CURR
};

class Money
{
public:
    Money();
    ~Money();
    Money(float otherValue);
    Money(float otherValue, QString otherCurr);
    Money(Money &otherMoney);
    float getValue() const;
    void setValue (float otherValue);
    QString getCurrency() const;
    void convertTo (QString otherCurr);
    bool operator> (Money &otherMoney) const;
    bool operator< (Money &otherMoney) const;
    bool operator== (Money &otherMoney) const;
    QString to_str (QString sep=QString(" ")) const;
    static QString getActiveCurrency ();
    static void changeActiveCurrency (QString otherCurr);
    static QString activeCurrency;
private:
    float value;
    QString currency;
};


#endif // MONEY_H
