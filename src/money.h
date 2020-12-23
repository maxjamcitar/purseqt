#ifndef MONEY_H
#define MONEY_H

#include <QString>
#include <QSet>
#include <QMap>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QFile>

class CurrConversion : public QObject
{
    Q_OBJECT
public:
    CurrConversion();
    ~CurrConversion();
    static void addCurrency (const QString& currName, const double coef);
    static void removeCurrency (const QString& currName);
    static void clearMap ();
    static double getCoef (const QString& currName);
    static bool isCurrSaved (const QString& currName);
    static QString getActiveCurrency ();
    static void changeActiveCurrency (const QString& otherCurr);
    void requestRatesHttp ();
    // todo import/export from/to files (or online)
    static QSet<QString> currencyList;  // currencies are named with compliance with ISO 4217
    static QString activeCurrency;

private slots:
    void replyFinished(QNetworkReply *reply);

private:
    //QNetworkReply *reply;
    static QMap<QString, double> currencyMap;   // "double" is coefficient for conversion: 1 USD -> "double" CURR
};

class Money
{
public:
    Money();
    ~Money();
    Money(const double otherValue);
    Money(const double otherValue, const QString& otherCurr);
    Money(const Money &otherMoney);
    double getValue() const;
    void setValue (double otherValue);
    QString getCurrency() const;
    void setCurrency(const QString& otherCurrency);
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
    double value;
    QString currency;
};


#endif // MONEY_H
