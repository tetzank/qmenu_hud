#include <dbusmenuimporter.h>

#include <QApplication>
#include <QMenu>
#include <QtDebug>

#include <unistd.h>

int main(int argc, char **argv){
	QApplication app(argc, argv);

	// FIXME: hardcoded, got it this way:
	// dbus-send --type=method_call --print-reply \
	//		--dest=com.canonical.AppMenu.Registrar /com/canonical/AppMenu/Registrar \
	//		com.canonical.AppMenu.Registrar.GetMenuForWindow uint32:56623122
	// parameter at the end is window id:
	// xwininfo | grep 'Window id:' | cut -d ' ' -f4 | xargs printf '%d\n'
	DBusMenuImporter *dbusmenuimp = new DBusMenuImporter(":1.114", "/MenuBar/1");
	QMenu *menu = dbusmenuimp->menu();

	dbusmenuimp->updateMenu(); // load toplevel entries
	sleep(1); //HACK: should wait for signal menuUpdated()

	int i=0;
	for(QAction *a : menu->actions()){
		QMenu *m = a->menu();

		//HACK: entries only loaded lazily
		//m->aboutToShow();
		m->exec(); // populates menu, but also shows it
		sleep(1); 

		i++;
		qDebug() << a->text();
		for(QAction *sub_a : m->actions()){
			i++;
			qDebug() << sub_a->text();
		}
	}

	//int i=0;
	//foreach(QAction *a, menu->actions()){
	//	i++;
	//	qDebug() << a->text();
	//}

	qDebug() << i << " done";

	//delete menu;
	delete dbusmenuimp;

	return 0;
}
