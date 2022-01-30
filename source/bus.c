#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "bus.h"

void error_log(char *msg, int cod)
{
	printf("error in  %s: %s", msg, strerror(-cod));
	exit(EXIT_FAILURE);
}

static int callback_read(sd_bus_message *msg, void *user_data, sd_bus_error *ret_error)
{
    const sd_bus_error *error = sd_bus_message_get_error(msg);

    if (error != NULL)
    {
        printf("error: %s\n", error->message);
	return -1;
    }
    return 1;
}

void connect_bus(sd_bus **bus)
{
	int r;
	if( (r = sd_bus_open_system(bus)) < 0)
		error_log("Connect bus", r);
}

void close_bus(sd_bus *bus)
{
	sd_bus_close(bus);
	sd_bus_unref(bus);
}

void format_message(sd_bus *bus, sd_bus_message **m, char *dest, char *path, char *interface, char *method, char *type, va_list *a_list)
{
	int r;

	if( (r = sd_bus_message_new_method_call(bus, m, dest, path, interface, method)) < 0)
	{
		error_log("format message - method call", r);
		return;
	}

	if (type == NULL)
		return;

	if( (r = sd_bus_message_appendv(*m, type, *a_list)) < 0 )
		error_log("format_message - appendv", r);
}

void register_interface(sd_bus *bus, char *path, char *interface, const sd_bus_vtable *prop_spec, void *user_data)
{
	int r;

	if( (r = sd_bus_add_object_vtable(bus, NULL, "/org/bluez/advertising", "org.bluez.LEAdvertisement1", prop_spec, user_data)) < 0)
		error_log("Register interface - add object", r);
}

void call_bus(sd_bus *bus,  sd_bus_message *m, const char *ans)
{
	int r;
	sd_bus_message *reply = NULL;

	if ( (r = sd_bus_call_async(bus, NULL, m, callback_read, NULL, -1 )) < 0 )
	{
		error_log("call", r);
		return;
	}

	if (ans == NULL)
		return ;

	if( (r = sd_bus_message_read(reply, "s", &ans)) < 0)
		error_log("message_read", r);
}

void call_method(sd_bus *bus, char *dest, char *path, char *interface, char *method, char *ans, char *type, ...)
{
	sd_bus_message *m = NULL;
	va_list a_list;

	va_start(a_list, type);

	format_message(bus, &m, dest, path, interface, method, type, &a_list);
	call_bus(bus, m, ans);
	
	va_end(a_list);
	sd_bus_message_unref(m);
}

void set_property(sd_bus *bus, char *dest, char *path, ...) 
{
	sd_bus_message *m = NULL;
	va_list a_list;
	
	va_start(a_list, path);
	
	format_message(bus, &m, dest, path, PROPERTIES_DBUS, METHOD_SET, "ssv", &a_list);
	call_bus(bus, m, NULL );

	va_end(a_list);
}
