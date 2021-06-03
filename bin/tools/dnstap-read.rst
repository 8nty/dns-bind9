.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

.. highlight: console

.. _man_dnstap-read:

dnstap-read - print dnstap data in human-readable form
------------------------------------------------------

Synopsis
~~~~~~~~

:program:`dnstap-read` [**-m**] [**-p**] [**-x**] [**-y**] {file}

Description
~~~~~~~~~~~

``dnstap-read`` reads ``dnstap`` data from a specified file and prints
it in a human-readable format. By default, ``dnstap`` data is printed in
a short summary format, but if the ``-y`` option is specified, a
longer and more detailed YAML format is used.

Options
~~~~~~~

``-m``
   This option indicates trace memory allocations, and is used for debugging memory leaks.

``-p``
   This option prints the text form of the DNS
   message that was encapsulated in the ``dnstap`` frame, after printing the ``dnstap`` data.

``-x``
   This option prints a hex dump of the wire form
   of the DNS message that was encapsulated in the ``dnstap`` frame, after printing the ``dnstap`` data.

``-y``
   This option prints ``dnstap`` data in a detailed YAML format.

See Also
~~~~~~~~

:manpage:`named(8)`, :manpage:`rndc(8)`, BIND 9 Administrator Reference Manual.
