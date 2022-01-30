#ifndef _BUS

#define _BUS

#include <systemd/sd-bus.h>
// gcc bus.c -o bus `pkg-config --cflags --libs libsystemd`
/*
 * Interface padrao para setar propriedades
*/

#define PROPERTIES_DBUS "org.freedesktop.DBus.Properties"

/*
 * Método da interface padrão do dbus que seta as propriedades
*/

#define METHOD_SET "Set"
int task_cb_read(sd_bus_message *msg, void *user_data, sd_bus_error *ret_error);
/*
* Funcao que printa o erro e sai do programa.
*
* msg: Mensagem adicional da chamada de erro
* cod: codigo do erro
*/

void error_log(char *msg, int cod);

/*
* Inicia a conexao com o d-bus do sistema.
*
* bus: Ponteiro NULL para referenciar a conexao
*/

void connect_bus(sd_bus **bus);


/*
 * Fecha o bus e limpa as referências
 *
 * bus: referência do dbus
*/

void close_bus(sd_bus *bus);

/*
 * Registrar uma interface no dbus
 *
 * Registra no bus a interface com os respectivos métodos e propriedades no caminho especificado
 *
 * bus: referência do dbus
 * path: Caminho de registro da interface
 * interface: nome da interface
 * prop_spec: sd_bus_table que define os métodos, propriedades, sinais e etc
 * user_data: dados passados para a função
*/

void register_interface(sd_bus *bus, char *path, char *interface, const sd_bus_vtable *prop_spec, void *user_data);

/*
* Funcao que organiza a mensagem destinada a um objeto.
*
* bus: referência do dbus
* m: Ponteiro para mensagem do bus
* dest: Objeto destino no formato org.freedesktop.dbus
* path: Caminho do objeto destino no formato /org/freedesktop/dbus
* interface: Interface do objecto que está sendo referenciada
* method: Método que será chamado via  dbus
* type: Formato dos param do dbus(u,s,b, etc)
* a_list: va_list dos tipos
*/

void format_message(sd_bus *bus, sd_bus_message **m, char *dest, char *path, char *interface, char *method, char * type, va_list *a_list);

/*
* Efetivamente realiza a chamada.
*
* bus: referência do dbus
* m: Ponteiro para mensagem do bus
* ans: Ponteiro para a resposta, se null não tem resposta
*/

void call_bus(sd_bus *bus,  sd_bus_message *m, const char *ans);

/*
* Funcao que organiza a mensagem destinada a um objeto.
*
* bus: referência do dbus
* m: Ponteiro para mensagem do bus
* dest: Objeto destino no formato org.freedesktop.dbus
* path: Caminho do objeto destino no formato /org/freedesktop/dbus
* interface: Interface do objecto que está sendo referenciada
* method: Método que será chamado via  dbus
* type: Formato dos param do dbus(u,s,b, etc)
* ans: resposta, se definida
* a_list: va_list dos tipos
*/

void  call_method(sd_bus *bus, char *dest, char *path, char *interface, char *method, char *type, char *ans, ...);

/*
* Funcao que organiza a mensagem destinada a um objeto.
*
* bus: referência do dbus
* dest: Objeto destino no formato org.freedesktop.dbus
* path: Caminho do objeto destino no formato /org/freedesktop/dbus
* ...: va_list argumentos  (char *interface, char *prop, char *type,(values) )
*/

void set_property(sd_bus *bus, char *dest, char *path, ... );

#endif
