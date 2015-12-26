#include "chapterswidget.h"

#include <QHeaderView>

enum ChaptersColumns : int
{
    IndexColumn = 0,
    PlaylistColumn = 1,
    ChapterCountColumn = 2,
    DurationColumn = 3,
    CommentColumn = 4,
    ColumnCount
};

static
QString timeAsString(uint64_t duration)
{
    return QString(duration < 10 ? "0%1" : "%1").arg(duration);
}

ChaptersWidget::ChaptersWidget(QWidget* parent) : QTableWidget(parent)
{
    this->setColumnCount(ChaptersColumns::ColumnCount);
    this->setHorizontalHeaderLabels(QStringList()
                                    << tr("Title Index")
                                    << tr("Playlist Number")
                                    << tr("Chapters")
                                    << tr("Duration")
                                    << tr("")
                );
    this->verticalHeader()->hide();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ChaptersWidget::resetRows()
{
    this->setRowCount(0);
}

void ChaptersWidget::addTitle(QSharedPointer<TitleInfo> titleInfo)
{
    const int row = this->rowCount();
    this->setRowCount(row + 1);

    this->setItem(row, ChaptersColumns::IndexColumn, new QTableWidgetItem(QString("%1").arg(titleInfo->idx)));
    this->setItem(row, ChaptersColumns::PlaylistColumn, new QTableWidgetItem(QString("%1").arg(titleInfo->playlist)));
    this->setItem(row, ChaptersColumns::ChapterCountColumn, new QTableWidgetItem(QString("%1").arg(titleInfo->chapter_count)));
    const uint64_t minutes = ((titleInfo->duration / 90000) % 3600) / 60;
    this->setItem(row, ChaptersColumns::DurationColumn,
                  new QTableWidgetItem(tr("%1:%2:%3")
                                       .arg(titleInfo->duration / 90000 / 3600)
                                       .arg(timeAsString(minutes))
                                       .arg(timeAsString(titleInfo->duration % 60))
                                       ));
    if (titleInfo->isMain)
        this->setItem(row, ChaptersColumns::CommentColumn, new QTableWidgetItem(tr("Main title")));
    this->resizeRowsToContents();
}
