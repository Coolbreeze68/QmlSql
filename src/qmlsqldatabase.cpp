#include "qmlsqldatabase.h"

QmlSqlDatabase::QmlSqlDatabase(QObject *parent)
    : QObject(parent)

{
    connect( this, &QmlSqlDatabase::error,
             &QmlSqlDatabase::handelError);

    connect( this, &QmlSqlDatabase::connectionOpened,
             this, &QmlSqlDatabase::handelOpened );

    connect( this, &QmlSqlDatabase::closeRequested,
             this, &QmlSqlDatabase::handelCloseRequested );

    connect( this, &QmlSqlDatabase::sqlError ,
             this, &QmlSqlDatabase::handelSqlError );
}

QString QmlSqlDatabase::errorString() const
{
    return m_errorString;
}

void QmlSqlDatabase::addDataBase()
{
    if( m_parameters != Q_NULLPTR )
    {
        QLatin1String dbType = QLatin1String(
                    m_parameters->getDatabaseDriverString(
                        m_parameters->databaseDriver()
                        ).toLatin1()
                    );

        db = QSqlDatabase::addDatabase(
                    dbType
                    , m_parameters->connectionName()
                    );

        db.setHostName( m_parameters->source() );
        db.setDatabaseName( m_parameters->databaseName() );
        db.setUserName( m_parameters->user() );
        db.setPassword( m_parameters->password() );
        db.setPort( m_parameters->port() );

        if ( !db.open() )
        {
            sqlError( db.lastError() );
            closeRequested( Error, m_parameters->connectionName() );
        }
        else
        {
            connectionOpened( db , m_parameters->connectionName() );
        }
    }
    else
    {
        error( "You forgot to set the connection parameters" );
    }
}

QStringList QmlSqlDatabase::connectionNames()
{
    return db.connectionNames();
}

void QmlSqlDatabase::removeDatabase(const QString &connectionName)
{

    if( db.connectionNames().contains( connectionName ) )
    {
        QSqlDatabase::removeDatabase( connectionName );
    }
}

void QmlSqlDatabase::closeAllConnections()
{
    for( const QString l : db.connectionNames() )
    {
        QSqlDatabase::removeDatabase( l );
    }
}

bool QmlSqlDatabase::running()
{
    return m_running;
}

QStringList QmlSqlDatabase::tables( const QString &connectionName, const TableType &tableType )
{
    QStringList li;
    for( int i = 0 ; i < db.connectionNames().length(); i++ )
    {
        if( db.connectionNames().at( i ) == connectionName )
        {
            li = db.tables( setTableType( tableType ) );
        }
        else
        {
            li.clear();
            error( QString( "could not find database connection with the connectionName of %1" )
                   .arg( connectionName )
                   ) ;
        }
    }
    return li;
}

QmlSqlConnectionParameters *QmlSqlDatabase::parameters() const
{
    return m_parameters;
}

void QmlSqlDatabase::setParameters(QmlSqlConnectionParameters *parameters)
{
    m_parameters = Q_NULLPTR ;
    m_parameters = parameters;
    emit parametersChanged();
}

void QmlSqlDatabase::handelError( const QString &err )
{
    if( m_errorString != err )
    {
        m_errorString = err;
        emit errorStringChanged();
    }
}

void QmlSqlDatabase::handelOpened( QSqlDatabase database, const QString connectionName )
{
    Q_UNUSED( connectionName )
    qDebug() << " Is Open " << database.connectionName();
}

void QmlSqlDatabase::handelCloseRequested(const CloseReason &reason, const QString &connectionName)
{
    qDebug() << "Connection name has been requested to close "
             << connectionName
             << " Reason: "
             << closeReasonToString(reason) ;
}

void QmlSqlDatabase::handelSqlError(const QSqlError &err)
{
    QString er = QString("Error"
                         "\nFull reason: %1"
                         "\nDriver Error Text: %3"
                         "\nDataBase Text Error: %4"
                         "\nNative Code Reason: %2"
                         )
            .arg( err.text() )
            .arg( err.nativeErrorCode() )
            .arg( err.driverText() )
            .arg( err.databaseText() );
    error( er ) ;
}

QSql::TableType QmlSqlDatabase::setTableType(const QmlSqlDatabase::TableType &type)
{
    QSql::TableType ret;

    if ( type == Tables )
    {
        ret = QSql::Tables;
    }
    else if( type == SystemTables )
    {
        ret = QSql::SystemTables;
    }
    else if( type == Views )
    {
        ret = QSql::Views;
    }
    else if( type == AllTables )
    {
        ret = QSql::AllTables;
    }
    else
    {
        error( "Warning: Not a vaild Table Type trying with AllTypes" );
        ret = QSql::AllTables;
    }
    return ret;
}

QString QmlSqlDatabase::closeReasonToString( const QmlSqlDatabase::CloseReason &cR )
{
    QString ret = "Unknown and not good";
    if( cR == Error )
    {
        ret = "Error";
    }
    else if( cR == Requested )
    {
        ret = "User Requested";
    }
    else if( cR == Unknown )
    {
        ret = "Unknown";
    }
    return ret;
}
