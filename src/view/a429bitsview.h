#pragma once

#include <QTableView>

class A429BitsModel;

class A429BitsView : public QTableView
{
	Q_OBJECT
public:
	A429BitsView(QWidget* parent = Q_NULLPTR);
	~A429BitsView();

protected:
	void resizeEvent(QResizeEvent* event);

public slots:
	void clear();
	void appendRow();
	void deleteRow();
	void importTemplate();
	void exportTemplate();

protected:
	virtual void contextMenuEvent(QContextMenuEvent*) override;

private:
	A429BitsModel* m_model;
};