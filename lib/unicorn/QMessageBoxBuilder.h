/***************************************************************************
 *   Copyright 2007-2009 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef MESSAGE_BOX_BUILDER_H
#define MESSAGE_BOX_BUILDER_H

#include <lib/DllExportMacro.h>
#include <QtGui/QMessageBox>


class UNICORN_DLLEXPORT MessageBoxBuilder
{
    QMessageBox box;

public:
    /** Try not to use 0! */
    MessageBoxBuilder( QWidget* parent ) : box( parent )
    {}
    
    MessageBoxBuilder& setTitle( const QString& x );
    MessageBoxBuilder& setText( const QString& x );
    /** the default is Information */
    MessageBoxBuilder& setIcon( QMessageBox::Icon x ) { box.setIcon( x ); return *this; }

    int exec();
	
	MessageBoxBuilder& sheet()
	{
	#ifdef Q_WS_MAC
		box.setWindowFlags( Qt::Sheet | (box.windowFlags() & ~Qt::Drawer) );
	#endif
		return *this;
	}
};

#endif // MESSAGE_BOX_BUILDER_H
