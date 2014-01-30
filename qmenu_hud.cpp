#include <QApplication>
#include <QtDebug>

// generated
#include "app_menu.h"
#include "dbus_menu.h"
typedef com::canonical::AppMenu::Registrar AppMenu;
typedef com::canonical::dbusmenu DBusMenu;

#define REGISTRAR_SERVICE "com.canonical.AppMenu.Registrar"
#define REGISTRAR_PATH "/com/canonical/AppMenu/Registrar"

#include <X11/Xlib.h>


void inspect(const DBusMenuLayoutItem &topItem, QString &path, QMap<QString,int> &menuMap){
	QString label;
	for(const DBusMenuLayoutItem &item : topItem.children){
        label = item.properties.value("label").toString().remove("_");
		if(!item.children.isEmpty()){
			QString subPath(path);
			subPath.append(label);
			subPath.append(" > ");
			inspect(item, subPath, menuMap);
		}else{
			if(!label.isEmpty()){
				//qDebug() << path << label << " ::: " << item.id;
				menuMap.insert(path + label, item.id);
			}
		}
	}
}

int main(int argc, char **argv){
	QApplication app(argc, argv);

	// get window (id) which has currently the focus
	Display *display = XOpenDisplay(NULL);
	if(!display){
		perror("XOpenDisplay failed");
		return -1;
	}
	Window window;
	int ret;
	XGetInputFocus(display, &window, &ret);
	qDebug() << "winId: " << window;
	XCloseDisplay(display);

	DBusMenuTypes_register();

	// get dbus service of the application which exports menu
	AppMenu *appMenu = new AppMenu(REGISTRAR_SERVICE, REGISTRAR_PATH, QDBusConnection::sessionBus(), 0);
	QDBusPendingReply<QString, QDBusObjectPath> reply =
			appMenu->GetMenuForWindow(window);
	reply.waitForFinished();
	if (reply.isError()) {
		qDebug() << reply.error().name();
		qDebug() << reply.error().message();
		return -1;
	}

	QString dbus_service = reply.argumentAt<0>();
	QString dbus_path = reply.argumentAt<1>().path();
	qDebug() << "service: " << dbus_service << "; path: " << dbus_path;

	// get menu
	DBusMenu *dbusMenu = new DBusMenu(dbus_service, dbus_path, QDBusConnection::sessionBus());
	QDBusPendingReply <uint, DBusMenuLayoutItem> topItems = dbusMenu->GetLayout(0, -1, QStringList());
	topItems.waitForFinished();
	if (topItems.isError()) {
		qDebug() << topItems.error().name();
		qDebug() << topItems.error().message();
		return -1;
	}

	// traverse through all submenus
	QString path;
	QMap<QString, int> menuMap;
	for(const DBusMenuLayoutItem &topLevel : topItems.argumentAt<1>().children){
		path.append(topLevel.properties.value("label").toString().remove("_"));
		path.append(" > ");

		inspect(topLevel, path, menuMap);

		path.clear();
	}

	// call dmenu -i -l 20
	QStringList args;
	args << "-i" << "-l" << "20";
	QProcess *proc = new QProcess();
	proc->start("/usr/bin/dmenu", args);
	proc->waitForStarted();

	// write all entries to dmenu's stdin
	for(QString &key : menuMap.keys()){
		proc->write(key.toLocal8Bit().data());
		proc->write("\n");
	}
	proc->closeWriteChannel();

	//proc->waitForReadyRead();
	proc->waitForFinished();
	// read selected entry from dmenu's stdout
	QString selected = QString::fromLocal8Bit(proc->readAllStandardOutput()).remove("\n");
	qDebug() << "selected: " << selected;
	proc->close();
	delete proc;

	if(!selected.isEmpty()){ // empty when canceled with esc
		int id = menuMap[selected];
		qDebug() << "id: " << id;

		// send menu click event
		QDBusVariant empty;
		empty.setVariant(QVariant::fromValue<QString>(QString()));
		QDBusPendingReply<void> clicked_r = dbusMenu->Event(id, "clicked", empty, QDateTime::currentDateTime().toTime_t());
		if(clicked_r.isError()){
			qDebug() << clicked_r.error().message();
			qDebug() << clicked_r.error().name();
		}
	}

	delete dbusMenu;
	delete appMenu;

	return 0;
}
