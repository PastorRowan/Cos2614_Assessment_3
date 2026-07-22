
#include "MainWindow.h"
#include "ApplicationContext.h"
#include "VehiclesFile/VehiclesFileView.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

MainWindow::MainWindow(
    ApplicationContext& contextP
): context(contextP) {

    QWidget *central = new QWidget(this);
    central->setContentsMargins(10, 10, 10, 10);
    QHBoxLayout *centralHLayout = new QHBoxLayout(central);
    QWidget *content = new QWidget(central);
    QVBoxLayout *contentVLayout = new QVBoxLayout(content);
    content->setMinimumWidth(800);

    centralHLayout->addStretch();
    centralHLayout->addWidget(content);
    centralHLayout->addStretch();

    VehiclesFileView *vehiclesFileView = new VehiclesFileView(context.vehiclesFile, content);
    QLabel *title = new QLabel(content);
    title->setText("Vehicle Rental System");
    title->setAlignment(Qt::AlignCenter);
    contentVLayout->addWidget(title);
    contentVLayout->addWidget(vehiclesFileView);
    contentVLayout->addStretch();

    setCentralWidget(central);

};

MainWindow::~MainWindow() {};
