#ifndef CONFIGURATIONPAGE_H
#define CONFIGURATIONPAGE_H

#include <QWidget>

class Configuration;

class ConfigurationPage : public QWidget
{
    Q_OBJECT

public:
    typedef enum {
        Values = 1,
        Options = 2
    } UpdateOptions;

    explicit ConfigurationPage(QWidget *parent = 0);

    virtual QString title() const { return QString(); }

    virtual void updateConfiguration(Configuration &configuration,
                                     UpdateOptions options) const;
    virtual void setConfiguration(const Configuration &configuration);

signals:
    void selectionChanged();

public slots:
};

#endif // CONFIGURATIONPAGE_H
