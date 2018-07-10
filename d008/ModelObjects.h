#pragma once
#include <QAbstractTableModel>

class ModelObjects : public QAbstractTableModel
{
	Q_OBJECT
public:
	ModelObjects(QObject *parent);
	~ModelObjects();
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
};

