
#include <QApplication>
#include <QtDebug>

#include "registrar.h"

//generated
#include "registraradaptor.h"

#define REGISTRAR_SERVICE "com.canonical.AppMenu.Registrar"
#define REGISTRAR_PATH "/com/canonical/AppMenu/Registrar"


int main(int argc, char *argv[]){
	QCoreApplication a(argc, argv);

	Registrar *registrar = new Registrar(NULL);
	new RegistrarAdaptor(registrar);

	QDBusConnection connection = QDBusConnection::sessionBus();
	bool ret = connection.registerService(REGISTRAR_SERVICE);
	ret = connection.registerObject(REGISTRAR_PATH, registrar);
	return a.exec();
}
