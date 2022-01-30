#include <python3.6/Python.h>
#include "advertising.h"

//static PyObject *ErrorObject;
void advert(const char * data);

static PyObject * advertising(PyObject *self, PyObject *args)
{
	const char * data;

	if (!PyArg_ParseTuple(args, "s", &data))
        	return NULL;

	advert(data);
	Py_INCREF(Py_None);
	return Py_None;	
}

static PyMethodDef AdvertMethods[] = {
    {"advert_start", advertising, METH_VARARGS,
     "Start the advertising of bluetooth."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef advertisingmodule = {
    PyModuleDef_HEAD_INIT,
    "advertising",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    AdvertMethods
};

PyMODINIT_FUNC PyInit_advertising(void)
{
    return PyModule_Create(&advertisingmodule);
}

void advert(const char * data)
{
	int8_t r;
	sd_bus *bus = NULL;
	sd_bus_message *reply = NULL;
	
	connect_bus(&bus);
	set_manufacturer_data(data);
	start_advertising(bus);

	for(;;)
	{
		sd_bus_wait(bus, (uint64_t) -1);
		if( (r = sd_bus_process(bus, &reply)) < 0)
			error_log("Advertising, process error", r);

		if errno
		{
			PyErr_SetFromErrno(PyExc_BaseException);
			break;
		}
	}

	sd_bus_message_unref(reply);
	sd_bus_close(bus);
	sd_bus_unref(bus);
}
