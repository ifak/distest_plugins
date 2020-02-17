#include "clickablelabel.hpp"

ClickableLabel::ClickableLabel(const QString& text, QWidget* parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
    // Do nothing
}

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    // Do nothing
}

ClickableLabel::~ClickableLabel()
{
    // Do nothing
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit clicked();
}

