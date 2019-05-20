#include "qmlsqlconnectionparameters.h"
#include <QHashIterator>
QmlSqlConnectionParameters::QmlSqlConnectionParameters( QObject *parent ) :
    QObject( parent )
  , m_databaseDriver( SQLight )
{
    m_databaseDriverHash.insert( PostGre, "PostGre" );
    m_databaseDriverHash.insert( MySql, "MySql" );
    m_databaseDriverHash.insert( OCI, "OCI" );
    m_databaseDriverHash.insert( ODBC, "ODBC" );
    m_databaseDriverHash.insert( DB2, "DB2" );
    m_databaseDriverHash.insert( TDS, "TDS" );
    m_databaseDriverHash.insert( SQLight, "SQLight" );
    m_databaseDriverHash.insert( SQLight2, "SQLight2" );
    m_databaseDriverHash.insert( IBase, "IBase" );

    QHashIterator< DataBaseDriver, QString> it = m_databaseDriverHash;
    while( it.hasNext() )
    {
        it.next();
        m_databaseDriverList.append( it.value() );
    }
}

QmlSqlConnectionParameters::DataBaseDriver QmlSqlConnectionParameters::databaseDriver() const
{
    return m_databaseDriver;
}
void QmlSqlConnectionParameters::setDatabaseDriver(const QmlSqlConnectionParameters::DataBaseDriver &databaseDriver)
{
    if( m_databaseDriver != databaseDriver )
    {
        m_databaseDriver = databaseDriver;
        emit databaseDriverChanged( databaseDriver );
    }
}

QString QmlSqlConnectionParameters::getDatabaseDriverString(const QmlSqlConnectionParameters::DataBaseDriver &dbd)
{
    return m_databaseDriverHash.value( dbd );
}

QString QmlSqlConnectionParameters::source() const
{
    return m_source;
}

void QmlSqlConnectionParameters::setSource(const QString &source)
{
    if ( m_source != source )
    {
        m_source = source;
        emit sourceChanged( m_source );
    }
}

QString QmlSqlConnectionParameters::databaseName() const
{
    return m_databaseName;
}

void QmlSqlConnectionParameters::setdatabaseName(const QString &databaseName)
{
    if ( m_databaseName != databaseName )
    {
        m_databaseName = databaseName;
        emit databaseNameChanged( m_databaseName );
    }
}

QString QmlSqlConnectionParameters::user() const
{
    return m_user;
}

void QmlSqlConnectionParameters::setUser(const QString &user)
{
    if ( m_user != user )
    {
        m_user = user;
        emit userChanged( m_user );
    }
}

QString QmlSqlConnectionParameters::password() const
{
    return m_password;
}

void QmlSqlConnectionParameters::setPassword( const QString &password )
{
    if ( m_password != password )
    {
        m_password = password;
        emit passwordChanged( m_password );
    }
}

int QmlSqlConnectionParameters::port() const
{
    return m_port;
}

void QmlSqlConnectionParameters::setPort(const int &port)
{
    if ( m_port != port )
    {
        m_port = port;
        emit portChanged( m_port );
    }
}

QString QmlSqlConnectionParameters::connectionName() const
{
    return m_connectionName;
}

void QmlSqlConnectionParameters::setConnectionName(const QString &connectionName)
{
    if ( m_connectionName != connectionName )
    {
        m_connectionName = connectionName;
        emit connectionNameChanged( m_connectionName );
    }
}

QStringList QmlSqlConnectionParameters::databaseDriverList() const
{
    return m_databaseDriverList;
}
