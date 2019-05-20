# QmlSql

  QmlSql comes with some helper Objects to connect to Databases Run Queries against SQL.
Make SQLite Databases. Create Models from SQL Queries. All from Qml. 
QmlSql source code is licensed under the MIT license.

While QmlSql documentation is licensed under the GNU Free Documentation License. 

QmlSql Comes with two examples and documents for both.
If you run the code below it will install the docs to QT_INSTALL_EXAMPLES QT_INSTALL_QML QT_INSTALL_DOCS. 
After running the first time restart QtCreator and you will see the examples on the welcome screen and the docs in the assistant 
and also in the help section of Qt Creator.


## Example for MySQL
The first thing that one must do if not using SQLite is compile the driver for qt for the database that they wish to use. 
For this this please see the qt documentation [Located Here ](http://doc.qt.io/qt-5/sql-driver.html#building-the-plugins-manually)

This plugin has only been tested on PostgreSQL MySQL and SQLite.

After that is built then you can build the plugin and its docs and examples with

```
  make
  qmake
  make
  make docs
  make install_docs
  make install
```

## QPM install
QPM is a package manager for Qt

https://www.qpm.io/

```
qpm install com.github.josephmillsatwork.qmlsql
```

## Mobile notes

I have tested this both on android and IOS and it works (MySQL, SQLite). 
I added the CONFIG flag of static to get it to compile and work on IOS. but this is now wrote into the profile. 
If one needs help with cross compile for android I am willing to help for a small fee. But it is really not that hard to do.


After building you have to copy over the lib and the qmldir file to your qt root folder qml folder after building it. 
This is what it should look like after copying the lib and qmldir file.

```
<QTBASE DIR>/<QT Version>/Toolkit/qml/QmlSql/
<QTBASE DIR>/<QT Version>/Toolkit/qml/QmlSql/libQmlSql.a
<QTBASE DIR>/<QT Version>/Toolkit/qml/QmlSql/qmldir
```

Then you can use with Android and IOS.
