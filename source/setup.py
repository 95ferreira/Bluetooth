from distutils.core import setup, Extension

module1 = Extension('advertising',
                    libraries=['systemd'],
                    sources = ['bus.c', 'advertising.c', 'advertising_module.c'])

setup (name = 'advertising',
       version = '1.0',
       description = 'This is a advertising package using Linux DBUS',
       author = 'Adriano Ferreira',
       author_email = '95a.ferreira@gmail.com',
       url = 'https://docs.python.org/extending/building',
       ext_modules = [module1])
