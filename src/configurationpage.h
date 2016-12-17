#ifndef CONFIGURATIONPAGE_H
#define CONFIGURATIONPAGE_H

#include <QWidget>

class ConfigurationPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationPage(QWidget *parent = 0);

    virtual QString title() const { return QString(); }

signals:

public slots:
};

#endif // CONFIGURATIONPAGE_H
