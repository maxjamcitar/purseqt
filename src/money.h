#ifndef MONEY_H
#define MONEY_H

#include <QString>
#include <QSet>
#include <QMap>
#include <QMessageBox>

class CurrConversion
{
public:
    CurrConversion();
    ~CurrConversion();
    static void addCurrency (const QString& currName, const float coef);
    static void removeCurrency (const QString& currName);
    static void clearMap ();
    static float getCoef (const QString& currName);
    static bool isCurrSaved (const QString& currName);
    static QString getActiveCurrency ();
    static void changeActiveCurrency (const QString& otherCurr);
    // todo import/export from/to files (or online)
    static QSet<QString> currencyList;  // currencies are named with compliance with ISO 4217
    static QString activeCurrency;
private:
    static QMap<QString, float> currencyMap;   // "float" is coefficient for conversion: 1 USD -> "float" CURR
};

class Money
{
public:
    Money();
    ~Money();
    Money(const float otherValue);
    Money(const float otherValue, const QString& otherCurr);
    Money(const Money &otherMoney);
    float getValue() const;
    void setValue (float otherValue);
    QString getCurrency() const;
    bool convertTo (const QString &otherCurr);
    void operator= (const Money &otherMoney);
    bool operator> (const Money &otherMoney) const;
    bool operator< (const Money &otherMoney) const;
    bool operator== (const Money &otherMoney) const;
    Money operator+ (const Money &otherMoney) const;
    void operator+= (const Money &otherMoney);
    Money operator- (const Money &otherMoney) const;
    void operator-= (const Money &otherMoney);
    QString to_str (QString sep=QString(" ")) const;
    Money parseString (const QString &str, const QString &sep) const;
    static QString getActiveCurrency ();
    static void changeActiveCurrency (QString otherCurr);
private:
    float value;
    QString currency;
};


#endif // MONEY_H
