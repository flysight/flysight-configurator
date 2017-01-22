#ifndef CONFIGURATIONPAGE_H
#define CONFIGURATIONPAGE_H

#include <QWidget>

class Configuration;

class ConfigurationPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationPage(QWidget *parent = 0);

    virtual QString title() const { return QString(); }
    virtual void updateConfiguration(Configuration &configuration);

signals:

public slots:
};

#endif // CONFIGURATIONPAGE_H
