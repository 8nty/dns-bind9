.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

::

  zone <string> [ <class> ] {
  	type static-stub;
  	allow-query { <address_match_element>; ... };
  	allow-query-on { <address_match_element>; ... };
  	forward ( first | only );
  	forwarders [ port <integer> ] [ dscp <integer> ] { ( <ipv4_address> | <ipv6_address> ) [ port <integer> ] [ dscp <integer> ]; ... };
  	max-records <integer>;
  	server-addresses { ( <ipv4_address> | <ipv6_address> ); ... };
  	server-names { <string>; ... };
  	zone-statistics ( full | terse | none | <boolean> );
  };
