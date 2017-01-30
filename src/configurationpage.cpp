#include "configurationpage.h"

ConfigurationPage::ConfigurationPage(QWidget *parent) :
    QWidget(parent)
{

}

void ConfigurationPage::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    Q_UNUSED(configuration);
    Q_UNUSED(options);
}

void ConfigurationPage::setConfiguration(
        const Configuration &configuration)
{
    Q_UNUSED(configuration);
}
