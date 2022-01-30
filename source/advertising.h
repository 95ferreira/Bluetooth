#ifndef _ADVERT

#define _ADVERT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "bus.h"
#include "bluetooth.h"

/*
 * Interface do manager do advertising
 * E os respectivos métodos
*/

#define INTERFACE_ADVERTISEMENT "org.bluez.LEAdvertisingManager1"
#define METHOD_ADVERTISEMENT "RegisterAdvertisement"
#define METHOD_UNREGISTER "UnregisterAdvertisement"

/*
 * Path e interface do método para iniciar o advertising
 * Passa como parâmetro o path que define as props a serem setadas
*/

#define PATH_DATA_ADVERT "/org/bluez/advertising"
#define INTERFACE_DATA_ADVERT  "org.bluez.LEAdvertisement1"

/*
 * Callback chamado no momento de remover o advertising  
 * m: Ponteiro para a mensagem setada pelo manager ao remover
 * userdata: Ponteiro de dados setado para passagem ao callback
 * ret_error: Ponteiro de erro na chamada da função
*/

//static int  release_advertising(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);

/*
 * Método get da propriedade type do advertising
 * bus: referência do dbus
 * path: Caminho do objeto referente
 * interface: Interface referenciada na chamada
 * property: Propriedade referenciada
 * reply: Objeto de mensagem aguardando retorno
 * userdata: offset de dados do user
 * error: Erro na chamada
*/

//static int get_type(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);

/*
 * Método get da propriedade type do advertising
 * bus: referência do dbus
 * path: Caminho do objeto referente
 * interface: Interface referenciada na chamada
 * property: Propriedade referenciada
 * reply: Objeto de mensagem aguardando retorno
 * userdata: offset de dados do user
 * error: Erro na chamada
*/

//static int get_manufacturer_data(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);

/*
 * Inicia a transmitir dados via ble
 *
 * bus: referência do dbus
 *
*/

void start_advertising(sd_bus *bus);

/*
 * Termina a transmissão de dados
 *
 * bus: referência do dbus
 *
*/

void stop_advertising(sd_bus *bus);

/*
 * Funcao que seta os dados a serem transmitidos
 *
 * data: char dos dados
 *
*/

void set_manufacturer_data(const char *data);

#endif
