#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>

class Debug : public QObject
{
	Q_OBJECT

public:
	static Debug* Instance();
	static void messageHandler(QtMsgType, const QMessageLogContext&, const QString&);

signals:
	void OutputToGUI(QString);
};

#endif

