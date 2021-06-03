.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

::

  zone <string> [ <class> ] {
  	type forward;
  	delegation-only <boolean>;
  	forward ( first | only );
  	forwarders [ port <integer> ] [ dscp <integer> ] { ( <ipv4_address> | <ipv6_address> ) [ port <integer> ] [ dscp <integer> ]; ... };
  };
