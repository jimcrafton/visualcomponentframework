//AbstractTableModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractTableModel.h"

using namespace VCF;


AbstractTableModel::AbstractTableModel()
{

}

AbstractTableModel::~AbstractTableModel()
{

}

void AbstractTableModel::addRow()
{

}

void AbstractTableModel::insertRow( const uint32& afterRow )
{

}

void AbstractTableModel::deleteRow( const uint32& row )
{

}

void AbstractTableModel::addColumn()
{

}

void AbstractTableModel::insertColumn( const uint32& afterColumn )
{

}

void AbstractTableModel::deleteColumn( const uint32& column )
{

}

bool AbstractTableModel::isCellEditable( const uint32& row, const uint32& column )
{
	return false;
}

TableCellItem* AbstractTableModel::getItem( const uint32& row, const uint32& column )
{
	return NULL;
}

uint32 AbstractTableModel::getRowCount()
{
	return 0;
}

uint32 AbstractTableModel::getColumnCount()
{
	return 0;
}


/**
$Id$
*/
