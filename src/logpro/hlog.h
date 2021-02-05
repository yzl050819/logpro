#ifndef HLOG_H
#define HLOG_H


#include <QApplication>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

#include <iostream>

#define LOG_SIZE (5)  // 单个log文件大小 5M
#define LOG_COUNT (5) // 日志文件个数


void checkSize( QFile &file, QString logPath);

void hMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    static QString logPath;

    if( logPath.isEmpty() ){
        logPath = QCoreApplication::applicationDirPath() + "/logs/";
        QDir tdir( logPath );
        if (!tdir.exists()) {
            //std::cout<< "make dir"<<std::endl;
            tdir.mkdir( logPath );
        }
    }

    QString text;

    QString mess=msg;
    switch(type)
    {
    case QtDebugMsg:
        std::cout<< msg.toLocal8Bit().toStdString()<<std::endl;
        text = QString("Debug:");
        break;
    case QtInfoMsg:
        std::cout<< msg.toLocal8Bit().toStdString()<<std::endl;
        text = QString("Info:");
        break;
    case QtWarningMsg:
        std::cout<< msg.toLocal8Bit().toStdString()<<std::endl;
        text = QString("Warning:");
        break;
    case QtCriticalMsg:
        std::cout<< msg.toLocal8Bit().toStdString()<<std::endl;
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        std::cout<< msg.toLocal8Bit().toStdString()<<std::endl;
        text = QString("Fatal:");
    }
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz");
    QString current_date = QString("[%1]").arg(current_date_time);
    QString message = QString("%1 %2 %3 \n%4\n").arg(current_date).arg(text).arg(context_info).arg(msg);
    QFile file( logPath +"log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream text_stream(&file);
    text_stream << message << "\r\n";

    checkSize(file, logPath);

    file.flush();
    file.close();

    mutex.unlock();
}


void checkSize( QFile &file, QString logPath  )
{   
    //std::cout<< "log size "<<file.fileName().toStdString()<< "   "<<file.size()<<std::endl;

    QDir dir( logPath );
    QStringList nameFilters;
    //设置文件过滤格式
    nameFilters << "*.txt";
    //将过滤后的文件名称存入到files列表中

    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Time);

    for(int i=0; i<files.count();i++){
        //std::cout<<files[i].toStdString()<<std::endl;
        if( i>LOG_COUNT ){
            QFile::remove( logPath + files[i] );
        }
    }

    if(file.size() > 1024*1024*LOG_SIZE){
        file.rename( QString(logPath+ "log %1.txt").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss")) );
    }



}



#endif // HLOG_H
