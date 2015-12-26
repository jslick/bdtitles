#ifndef CHAPTERSWIDGET_H
#define CHAPTERSWIDGET_H

#include <QTableWidget>

struct TitleInfo
{
    QString name;
    uint32_t idx;
    uint32_t playlist;
    uint64_t duration;
    uint32_t chapter_count;

    bool isMain = false;
};

class ChaptersWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit ChaptersWidget(QWidget* parent = 0);

signals:

public slots:
    void resetRows();
    void addTitle(QSharedPointer<TitleInfo> titleInfo);
};

#endif // CHAPTERSWIDGET_H
