/***************************************************************************
 *   Copyright 2005-2009 Last.fm Ltd.                                      *
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

#include <QtTest/QtTest>

#include "PlayerCommandParser.h"

class TestPlayerCommandParser : public QObject
{
    Q_OBJECT

    private slots:
        void initTestCase()
        {
            
        }
        
        void testStart();
        void testStop();
        void testResume();
        void testPause();
        void testBootstrap();
        void testEmptyLine();
        void testMissingArgument();
        void testInvalidCommand();
        void testDuplicatedArgument();
        void testUnicode();
};


void
TestPlayerCommandParser::testStart()
{
    PlayerCommandParser pcp ( "START c=testapp"
                                   "&a=Test Artist"
                                   "&t=Test Title"
                                   "&b=Test Album"
                                   "&l=100"
                                   "&p=/home/tester/test.mp3" );

    QCOMPARE( pcp.command(), PlayerCommandParser::Start );
    QCOMPARE( pcp.playerId(), QString( "testapp" ) );
    QCOMPARE( pcp.track().artist(), QString( "Test Artist" ) );
    QCOMPARE( pcp.track().track(), QString( "Test Title" ) );
    QCOMPARE( pcp.track().album(), QString( "Test Album" ) );
    QCOMPARE( pcp.track().duration(), 100 );
    QCOMPARE( pcp.track().path(), QString( "/home/tester/test.mp3" ) );
}

void
TestPlayerCommandParser::testStop()
{
    PlayerCommandParser pcp ( "STOP c=testapp" );

    QCOMPARE( pcp.command(), PlayerCommandParser::Stop );
    QCOMPARE( pcp.playerId(), QString( "testapp" ) );
}

void
TestPlayerCommandParser::testResume()
{
    PlayerCommandParser pcp ( "RESUME c=testapp" );

    QCOMPARE( pcp.command(), PlayerCommandParser::Resume );
    QCOMPARE( pcp.playerId(), QString( "testapp" ) );
}

void
TestPlayerCommandParser::testPause()
{
    PlayerCommandParser pcp ( "PAUSE c=testapp" );

    QCOMPARE( pcp.command(), PlayerCommandParser::Pause );
    QCOMPARE( pcp.playerId(), QString( "testapp" ) );
}

void
TestPlayerCommandParser::testBootstrap()
{
    PlayerCommandParser pcp ( "BOOTSTRAP c=testapp&u=TestUser" );

    QCOMPARE( pcp.command(), PlayerCommandParser::Bootstrap );
    QCOMPARE( pcp.playerId(), QString( "testapp" ) );
    QCOMPARE( pcp.username(), QString( "TestUser" ) );
}

void
TestPlayerCommandParser::testEmptyLine()
{
    // The PlayerCommandParser should throw an exception on empty lines
    try
    {
        PlayerCommandParser pcp ( "" );
        
        QFAIL( "PlayerCommandParser did not throw an exception on an empty line." );
    }
    catch ( PlayerCommandParser::Exception e )
    {
        QCOMPARE( 1, 1 ); // Success
    }
}

void
TestPlayerCommandParser::testMissingArgument()
{
    // The PlayerCommandParser should throw an exception when arguments are missing
    try
    {
        PlayerCommandParser pcp ( "START c=testap" );
        
        QFAIL( "PlayerCommandParser did not throw an exception when arguments are missing." );
    }
    catch ( PlayerCommandParser::Exception e )
    {
        QCOMPARE( 1, 1 ); // Success
    }
}

void
TestPlayerCommandParser::testInvalidCommand()
{
    // The PlayerCommandParser should throw an exception when passed a invalid command
    try
    {
        PlayerCommandParser pcp ( "SUPERSTART c=testap" );
        
        QFAIL( "PlayerCommandParser did not throw an exception when passed a invalid command." );
    }
    catch ( PlayerCommandParser::Exception e )
    {
        QCOMPARE( 1, 1 ); // Success
    }
}

void
TestPlayerCommandParser::testDuplicatedArgument()
{
    // The PlayerCommandParser should throw an exception when arguments are duplicated
    try
    {
        PlayerCommandParser pcp ( "START c=testap&c=testapp2" );
        
        QFAIL( "PlayerCommandParser did not throw an exception when arguments are duplicated." );
    }
    catch ( PlayerCommandParser::Exception e )
    {
        QCOMPARE( 1, 1 ); // Success
    }
}

void
TestPlayerCommandParser::testUnicode()
{
    PlayerCommandParser pcp ( "START c=testapp"
                                   "&a=佐橋俊彦"
                                   "&t=対峙"
                                   "&b=TV Animation ジパング original Soundtrack"
                                   "&l=123"
                                   "&p=/home/tester/15 対峙.mp3" );

    QCOMPARE( pcp.command(), PlayerCommandParser::Start );
    QCOMPARE( pcp.playerId(), QString( "testapp" ) );
    QCOMPARE( pcp.track().artist(), QString( "佐橋俊彦" ) );
    QCOMPARE( pcp.track().track(), QString( "対峙" ) );
    QCOMPARE( pcp.track().album(), QString( "TV Animation ジパング original Soundtrack" ) );
    QCOMPARE( pcp.track().duration(), 123 );
    QCOMPARE( pcp.track().path(), QString( "/home/tester/15 対峙.mp3" ) );
}

QTEST_APPLESS_MAIN(TestPlayerCommandParser)
#include "TestPlayerCommandParser.moc"

