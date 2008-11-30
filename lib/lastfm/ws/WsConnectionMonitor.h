/***************************************************************************
*   Copyright 2005-2008 Last.fm Ltd.                                      *
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
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
***************************************************************************/

#ifndef WS_CONNECTION_MONITOR_H
#define WS_CONNECTION_MONITOR_H

#include "lib/lastfm/DllExportMacro.h"
#include <QObject>
#ifdef WIN32
#include "win/NdisEvents.h"
#endif
#ifdef __APPLE__
#include <SystemConfiguration/SCNetwork.h>
typedef const struct __SCNetworkReachability * SCNetworkReachabilityRef;
#endif


class LASTFM_WS_DLLEXPORT WsConnectionMonitor
        : public QObject
#ifdef WIN32
        , NdisEvents
#endif
{
	Q_OBJECT

#ifdef WIN32
    // WmiSink callbacks:
    virtual void onConnectionUp( BSTR name )
    {
        emit up( QString::fromUtf16(name) );
    }
    
    virtual void onConnectionDown( BSTR name )
    {
        emit down( QString::fromUtf16(name) );
    }
#endif
#ifdef __APPLE__
    static void callback( SCNetworkReachabilityRef, SCNetworkConnectionFlags, void* );
#endif

public:
	WsConnectionMonitor( QObject *parent = 0 );

signals:
    /** yay! internet has returned */
	void up( const QString& connectionName = "" );
    
    /** we think the internet is unavailable, but well, still try, but show
      * an unhappy face in the statusbar or something */
	void down( const QString& connectionName = "" );
};

#endif