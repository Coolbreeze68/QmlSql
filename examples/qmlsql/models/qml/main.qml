import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QmlSql 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QmlSqlQueryModel Model Example")

    ListView{
        anchors.fill: parent
        model:queryModel
        delegate: Button{
            width: parent.width / 1.07
            anchors.horizontalCenter: parent.horizontalCenter
            // lets say you have a database and columns named like so
            // -----------------------
            // | id | name | address |
            // _______________________
            // | 0  | joe  | 123 lane|

            // the model will know all the columns and set the role names
            text: name + " address = " + address

        }
    }

    SqlQueryModel{
        id: queryModel
        // Set the connection name to the QmlSqlDatabase
        connectionName: "mainConnection"
        // Use a query string to fill the model
        queryString: "SELECT * FROM MOCK_DATA"
    }


    SqlConnectionParameters{
        id: mainConnection
        connectionName: "mainConnection"
        // Set the source of the database
        source: "127.0.0.1"
        // set the database Name
        databaseName: "mock_data"
        // set the User of the connection
        user: ""
        // set the password for that User
        password: ""
        // set the port for the connection
        port: 3306
        // set the driver to use
        databaseDriver: SqlConnectionParameters.MySql
        // add the database to memory so we can call over and over again
        Component.onCompleted:{
            // add the connection parma's
            SqlDatabase.parameters = mainConnection
            // add the database
            SqlDatabase.addDataBase()
        }
    }

    Connections{
        target: SqlDatabase
        // Run the query to fill the model
        onConnectionOpened: queryModel.exec()
    }
}
