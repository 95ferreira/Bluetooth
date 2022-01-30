#include "advertising.h"

char m_data[32];

static int  release_advertising(sd_bus_message *m, void *userdata, sd_bus_error *ret_error)
{
	return 0;
}

static int get_type(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error)
{
	return sd_bus_message_append(reply, "s", "broadcast");
}

static int get_manufacturer_data(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error)
{
	int8_t r;
	uint16_t x = 0x0;

	if( (r = sd_bus_message_open_container(reply, SD_BUS_TYPE_ARRAY, "{qv}")) < 0)
		error_log("Get manufacturer data, open container error", r);	

	if( (r = sd_bus_message_open_container(reply, SD_BUS_TYPE_DICT_ENTRY,  "qv") ) < 0)
		error_log("Get manufacturer data, open container error", r);	

	if( (r = sd_bus_message_append_basic(reply, 'q', (void *) &x) ) < 0)
		error_log("Get manufacturer data, append error", r);	

	if( (r = sd_bus_message_open_container(reply, SD_BUS_TYPE_VARIANT, "ay")) < 0)
		error_log("Get manufacturer data, open container error", r);	

	if( (r = sd_bus_message_append_array(reply, SD_BUS_TYPE_BYTE, m_data, strlen(m_data)) ) < 0)
		error_log("Get manufacturer data, append error", r);	
	
	if( (r = sd_bus_message_close_container(reply)) < 0)
		error_log("Get manufacturer data, close container error", r);	

	if( (r = sd_bus_message_close_container(reply)) < 0)
		error_log("Get manufacturer data, close container error", r);	

	if( (r = sd_bus_message_close_container(reply)) < 0)
		error_log("Get manufacturer data, close container error", r);	

	return r;
}

void start_advertising(sd_bus *bus)
{
	// Props|methods

	static const sd_bus_vtable prop_spec[] = {
	    SD_BUS_VTABLE_START(0),
	    SD_BUS_PROPERTY("Type", "s", get_type, 0, 0),
	    SD_BUS_PROPERTY("ManufacturerData", "a{qv}", get_manufacturer_data, 0, 0),
	    SD_BUS_METHOD("Release", NULL, NULL, release_advertising, 0),
	    SD_BUS_VTABLE_END
	};

	set_property(bus, DESTINATION, PATH, INTERFACE_ADAPTER, "Discoverable", "b", "1");
	set_property(bus, DESTINATION, PATH, INTERFACE_ADAPTER, "DiscoverableTimeout", "u", 0);

	// Start advert

	register_interface(bus, PATH_DATA_ADVERT, INTERFACE_DATA_ADVERT, prop_spec, NULL); 
	call_method(bus, DESTINATION, PATH, INTERFACE_ADVERTISEMENT, METHOD_ADVERTISEMENT, NULL,  "oa{sv}", PATH_DATA_ADVERT, 0);
}

void stop_advertising(sd_bus *bus)
{
	call_method(bus, DESTINATION, PATH, INTERFACE_ADVERTISEMENT, METHOD_UNREGISTER, NULL,  "o", PATH_DATA_ADVERT);
}

void set_manufacturer_data(const char *data)
{
	strncpy(m_data, data, 31);
}
