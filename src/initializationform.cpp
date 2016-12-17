#include "initializationform.h"
#include "ui_initializationform.h"

#include <QFileDialog>
#include <QFileInfo>

InitializationForm::InitializationForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::InitializationForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Do nothing");
    ui->modeComboBox->addItem("Test speech mode");
    ui->modeComboBox->addItem("Play file");

    connect(ui->browseButton, SIGNAL(clicked(bool)),
            this, SLOT(browse()));
}

InitializationForm::~InitializationForm()
{
    delete ui;
}

void InitializationForm::browse()
{
    QString result = QFileDialog::getOpenFileName(this,
                                                  tr("Browse"),
                                                  QString(),
                                                  tr("Sound files (*.wav)"));
    ui->filenameEdit->setText(QFileInfo(result).baseName());
}
