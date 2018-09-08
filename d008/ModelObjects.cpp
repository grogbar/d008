#include "ModelObjects.h"



ModelObjects::ModelObjects() :QAbstractTableModel(parent)
{
}


ModelObjects::~ModelObjects()
{
}

int ModelObjects::rowCount(const QModelIndex & /*parent*/) const
{
	return 2;
}

int ModelObjects::columnCount(const QModelIndex & /*parent*/) const
{
	return 3;
}