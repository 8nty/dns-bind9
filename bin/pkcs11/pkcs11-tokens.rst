.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

.. highlight: console

.. _man_pkcs11-tokens:

pkcs11-tokens - list PKCS#11 available tokens
---------------------------------------------

Synopsis
~~~~~~~~

:program:`pkcs11-tokens` [**-m** module] [**-v**]

Description
~~~~~~~~~~~

``pkcs11-tokens`` lists the PKCS#11 available tokens with defaults from
the slot/token scan performed at application initialization.

Options
~~~~~~~

``-m module``
   This option specifies the PKCS#11 provider module. This must be the full path to a
   shared library object implementing the PKCS#11 API for the device.

``-v``
   This option makes the PKCS#11 libisc initialization verbose.

See Also
~~~~~~~~

:manpage:`pkcs11-destroy(8)`, :manpage:`pkcs11-keygen(8)`, :manpage:`pkcs11-list(8)`
