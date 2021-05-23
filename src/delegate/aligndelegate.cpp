#include "aligndelegate.h"


AlignDelegate::AlignDelegate(Qt::Alignment align, QObject* parent)
   : QStyledItemDelegate(parent)
   , m_align(align)
{

}

AlignDelegate::~AlignDelegate()
{
}

void AlignDelegate::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const
{
   option->displayAlignment = m_align;
   QStyledItemDelegate::initStyleOption(option, index);
}

AlignProxyStyle::AlignProxyStyle(QStyle* style)
   : QProxyStyle(style)
{
}

void AlignProxyStyle::drawItemText(QPainter* painter, const QRect& rect, int alignment, const QPalette& pal, bool enabled, const QString& text, QPalette::ColorRole textRole) const
{
   QProxyStyle::drawItemText(painter, rect.adjusted(0, 0, 0, 0), Qt::AlignCenter, pal, enabled, text, textRole);
}
