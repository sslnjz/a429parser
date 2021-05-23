#pragma once

#include <QProxyStyle>
#include <QStyledItemDelegate>

class AlignDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	AlignDelegate(Qt::Alignment align, QObject* parent = Q_NULLPTR);
	~AlignDelegate();

protected:
	virtual void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;

private:
	Qt::Alignment m_align;
};

class AlignProxyStyle : public QProxyStyle
{
public:
    AlignProxyStyle(QStyle* style = Q_NULLPTR);
    using QProxyStyle::QProxyStyle;
    virtual void drawItemText(QPainter* painter,
        const QRect& rect,
        int alignment,
        const QPalette& pal,
        bool enabled,
        const QString& text,
        QPalette::ColorRole textRole) const override;
};