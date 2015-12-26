#include "mainwindow.h"

#include <QToolBar>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>

#include <libbluray/bluray.h>

#include <unordered_map>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      chaptersWidget(new ChaptersWidget(this))
{
    this->setWindowTitle("BD Titles");
    this->resize(600, 600);

    this->setCentralWidget(this->chaptersWidget);

    QToolBar* fileToolbar = this->addToolBar(tr("File"));
    QLabel* locationLabel = new QLabel(tr("Location:"), this);
    fileToolbar->addWidget(locationLabel);
    QLineEdit* locationEdit = new QLineEdit(this);
    locationEdit->setObjectName("location");
    fileToolbar->addWidget(locationEdit);
    QPushButton* goButton = new QPushButton(tr("Go"), this);
    fileToolbar->addWidget(goButton);
    connect(goButton, &QPushButton::clicked, this, &MainWindow::readChapters);
    connect(locationEdit, &QLineEdit::returnPressed, this, &MainWindow::readChapters);

    QTimer::singleShot(0, locationEdit, SLOT(setFocus()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::readChapters()
{
    this->chaptersWidget->resetRows();

    QLineEdit* locationEdit = this->findChild<QLineEdit*>("location");
    BLURAY* bd = bd_open(locationEdit->text().toStdString().c_str(), "");
    if (!bd)
    {
        QMessageBox::critical(this, tr("Error"), tr("The Blu-Ray could not be read"));
        return;
    }

    uint32_t num_titles = bd_get_titles(bd, TITLES_RELEVANT, 60);
    const BLURAY_DISC_INFO* disc_info = bd_get_disc_info(bd);
    if (!disc_info)
    {
        QMessageBox::critical(this, tr("Error"), tr("The titles could not be read"));
        return;
    }

    for (uint32_t i = 0; i < num_titles; i++)
    {
        BLURAY_TITLE_INFO* title_info = bd_get_title_info(bd, i, 0);
        if (title_info)
        {
            const int main_num = bd_get_main_title(bd);

            QSharedPointer<TitleInfo> titleInfo = QSharedPointer<TitleInfo>(new TitleInfo);
            titleInfo->name = "Test";
            titleInfo->idx = title_info->idx;
            titleInfo->playlist = title_info->playlist;
            titleInfo->duration = title_info->duration;
            titleInfo->chapter_count = title_info->chapter_count;
            titleInfo->isMain = title_info->idx == main_num;
            this->chaptersWidget->addTitle(titleInfo);

            bd_free_title_info(title_info);
        }
    }

    bd_close(bd);
}
